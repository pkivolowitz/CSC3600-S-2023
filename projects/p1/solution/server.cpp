#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#ifdef	 __linux__
#include <unistd.h>
#endif
#include <getopt.h>
#include <memory.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>

#include "defaults.hpp"
#include "structure.hpp"

#define BUFFER_SIZE	2048

using namespace std;

#define	LOG		cerr << "Line: " << __LINE__ << endl;

int main(int argc, char * argv[])
{
	int udp_socket;
	int server_port = PORT_NUMBER;
	//char * server_address = (char *) "127.0.0.1";	
	ServerDatagram sd;
	ClientDatagram * cd;
	bool verbose = false;
	struct sockaddr_in server_sockaddr;
	struct sockaddr_in client_sockaddr;
	unsigned char buffer[BUFFER_SIZE];
	ssize_t bytes_received;
	ssize_t bytes_sent;
	socklen_t l = sizeof(client_sockaddr);
	int c;

	memset((void *) &client_sockaddr, 0, sizeof(client_sockaddr));
	memset((void *) &sd, 0, sizeof(ServerDatagram));

	// Process command line options using getopt. Note that getopt makes use of an
	// externally defined char pointer "optarg". Note that the use of atoi() is
	// risky in general but suffices here. I would ward you away from using it in
	// production code.
	while ((c = getopt(argc, argv, "hp:vd")) != -1) {
		switch (c) {

			case 'h':
				cerr << argv[0] << "options:" << endl;
				cerr << "   -h displays help" << endl;
				cerr << "   -d enables debugging features" << endl;
				cerr << "   -p port_number ... defaults to " << PORT_NUMBER << endl;
				cerr << "   -v verbose mode - prints the received payloads" << endl;
				exit(0);

			case 'p':
				server_port = atoi(optarg);
				break;

			case 'v':
				verbose = true;
				break;
		}
	}
	cout << "Server binding to port: " << server_port << endl;

	udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (udp_socket < 0)
	{
		// perror makes use of "errno" to provide an error message meaningful
		// to humans. It emits the string you provide as a prefix to the error message.
		perror("ERROR opening socket");
		exit(1);
	}

	memset(&server_sockaddr, 0, sizeof(server_sockaddr));

	// We're going to bind() to all of the network adapters on this computer. This
	// is the effect of INADDR_ANY. Notice the call to host-to-network-short (htons())
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_addr.s_addr = INADDR_ANY;
	server_sockaddr.sin_port = htons(server_port);

	// This port is MINE! Pending error check, of course.
	if (bind(udp_socket, (const struct sockaddr *) &server_sockaddr, socklen_t(sizeof(server_sockaddr))) < 0)
	{
		close(udp_socket);
		perror("ERROR on binding");
		exit(4);
	}
	cout << "Network structs initialized and port is bound." << endl;

	while (true) {
		bytes_received = recvfrom(udp_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &client_sockaddr, &l);
		// If this were NONBLOCKING, then bytes_received might be -1 to signify that no datagram was waiting for us.
		// If you get a -1, either it means the above OR it means there was an error. Check errno. If errno is
		// EAGAIN, then there was no error - just nothing waiting for us.
		if (bytes_received > 0) {
			cd = (ClientDatagram *) buffer;
			sd.sequence_number = cd->sequence_number;
			sd.datagram_length = htons(bytes_received);
			if (verbose) {
				string payload;
				uint16_t payload_length = ntohs(cd->payload_length);
				payload.resize(payload_length);
				memcpy(&payload[0], buffer + sizeof(ClientDatagram), payload_length);
				cout << "Sequence number: " << ntohl(cd->sequence_number) << " Payload length: " << payload_length << " received: " << payload << endl;
			}
			bytes_sent = sendto(udp_socket, (void *) &sd, sizeof(ServerDatagram), 0, (struct sockaddr *) &client_sockaddr, sizeof(sockaddr_in));
			
			if (bytes_sent != sizeof(ServerDatagram)) {
				memset(buffer, 0, BUFFER_SIZE);
				inet_ntop(AF_INET, &client_sockaddr.sin_addr, (char *) buffer, BUFFER_SIZE - 4);
				cerr << "ERROR in sendto to: " << buffer << endl;
				perror("ERROR in sendto:");
				continue;
			}
		}
	}

	return 0;
}

