/************* UDP CLIENT CODE *******************/
/*
   UDP PROJECT CLIENT

   Perry Kivolowitz
   Professor of Computer Science
   Carthage College
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <set>
#include <cstdlib>

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <memory.h>
#include <getopt.h>
#include <unistd.h>
#include <fcntl.h>

#include "defaults.hpp"
#include "structure.hpp"

using namespace std;

bool debug_mode = false;

#define LOG		 if (debug_mode) cerr << "Line: " << __LINE__ << endl;

void DumpDG(ClientDatagram * p, int line)
{
	if (debug_mode) 
		cout << "Line: " << line << " sequence number: " << ntohl(p->sequence_number) << " payload length: " << ntohs(p->payload_length) << " payload: " << ((char *) p) + sizeof(ClientDatagram) << endl;
}

bool AttemptReception(int udp_socket, set<int> & unmatched_sequence_numbers, size_t datagram_length)
{
	bool retval = true;
	ssize_t bytes_received;
	struct sockaddr_in recv_sockaddr;
	socklen_t l = sizeof(recv_sockaddr);
	ServerDatagram sd;

	bytes_received = recvfrom(udp_socket, (void *) &sd, sizeof(ServerDatagram), MSG_DONTWAIT, (struct sockaddr *) &recv_sockaddr, &l);
	if (bytes_received != sizeof(ServerDatagram)) {
		// The bytes_received is not what we had hoped. If errno is of the right
		// value then all is OK - there simply weren't any datagrams to read. If
		// not one of the values below, an error occurred.
		if (errno != EAGAIN && errno != EWOULDBLOCK) {
			retval = false;
		}
		return retval;
	}
	// We have received the number of bytes we were expecting.
	uint32_t sequence_number = ntohl(sd.sequence_number);
	auto it = unmatched_sequence_numbers.find(sequence_number);
	if (it == unmatched_sequence_numbers.end()) {
		retval = false;
		cerr << "ERROR unknown sequence number received: " << sequence_number << " Bytes received: " << bytes_received << endl;
	}
	else {
		unmatched_sequence_numbers.erase(it);
		// The sequence number checked out - now ensure the ServerDatagram includes the right
		// value.
		unsigned short v = ntohs(sd.datagram_length);
		if (v != datagram_length) {
			retval = false;
			cerr << "ERROR wrong datagram_length: " << v << " should be: " << datagram_length << endl;
			cerr << "Sequence number: " << sequence_number << endl;
		}
	}

	return retval;
}

int main(int argc, char *argv[])
{
	set<int> unmatched_sequence_numbers;

	char * carthage_user_id = (char *) "pkivolowitz";
	size_t carthage_user_id_length = strlen(carthage_user_id) + 1;

	int udp_socket;
	int server_port = PORT_NUMBER;
	int number_of_packets = NUMBER_OF_DATAGRAMS;
	char * server_address = (char *) SERVER_IP;
    int delay = 0;
	struct sockaddr_in server_sockaddr;
	struct hostent * server_hostent;

	size_t datagram_length = sizeof(ClientDatagram) + carthage_user_id_length;
	cout << "Datagram length: " << sizeof(ClientDatagram) << " size of string: " << carthage_user_id_length << " total length: " << datagram_length << endl;
	ClientDatagram * cd = (ClientDatagram *) malloc(sizeof(datagram_length));

	if (cd == nullptr) {
		cerr << "Unable to allocate space for buffer: " << datagram_length << " bytes." << endl;
		exit(4);
	}

	memset(cd, 0, datagram_length);

	int c;

	// Process command line options using getopt. Note that getopt makes use of an
	// externally defined char pointer "optarg". Note that the use of atoi() is
	// risky in general but suffices here. I would ward you away from using it in
	// production code.
	while ((c = getopt(argc, argv, "hs:p:dy:n:")) != -1)
	{
		switch (c)
		{
			case 'h':
				cerr << argv[0] << "options:" << endl;
				cerr << " -h displays help" << endl;
				cerr << " -d turns on debug mode" << endl;
				cerr << " -s server_address ... defaults to 127.0.0.1" << endl;
				cerr << " -p port_number ... defaults to " << PORT_NUMBER << endl;
                cerr << " -y overrides delay ... defaults to 0" << endl;
                cerr << " -n overrides number of datagrams ... defaults to 2^18" << endl;
				free(cd);
				exit(0);

			case 'd':
				debug_mode = true;
				break;

			case 's':
				server_address = optarg;
				break;

			case 'p':
				server_port	= atoi(optarg);
				break;

            case 'n':
                number_of_packets = atoi(optarg);
                break;

            case 'y':
                delay = atoi(optarg);
                break;
		}
	}
	cout << "Client attempting to connect to port: " << server_port << endl;
	cout << "Client attempting to connect to ip:   " << server_address << endl;

	// Create a UDP (DGRAM) socket and check the return value.
	udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (udp_socket < 0)
	{
		// perror makes use of "errno" to provide an error message meaningful
		// to humans. It emits the string you provide as a prefix to the error message.
		perror("ERROR opening socket");
		free(cd);
		exit(1);
	}

	if (fcntl(udp_socket, F_SETFL, O_NONBLOCK) < 0) {
		perror("ERROR setting nonblocking");
		close(udp_socket);
		free(cd);
		exit(2);
	}

	// gethostbyname() may cause a DNS lookup to translate a URI into an IPv4 address.
	// Note that gethostbyname() is deprecated but most sample programs use it. The
	// function has been replaced by getaddrinfo() which is WAY more complicated. Maybe
	// it is for the best that we stick with gethostbyname(). 
	server_hostent = gethostbyname(server_address);
	cd->payload_length = htons(carthage_user_id_length);
	char * p = (char *) cd;
	memcpy(p + sizeof(ClientDatagram), carthage_user_id, carthage_user_id_length);
	DumpDG(cd, __LINE__);

	if (server_hostent == nullptr)
	{
		cerr << "ERROR, no such host: " << server_address << endl;
		close(udp_socket);
		free(cd);
		exit(3);
	}

	//DumpDG(cd, __LINE__);

	// Zero out the entire server_sockaddr. Note that many sample programs use the
	// less portable bzero(). memset() is preferred.
	memset(&server_sockaddr, 0, sizeof(server_sockaddr));

	// The family specifies an INTERNET socket rather than a file system socket.
	server_sockaddr.sin_family = AF_INET;
//	cout << __LINE__ << " "; DumpDG(cd);

	// Initialize the server address by copying the results of gethostbyname. Note
	// many samples online use bcopy. This is not portable. memmove is more powerful
	// than memcpy so is used here (even though, by construction, the benefits of
	// memmove are not being used).
	memmove(&server_sockaddr.sin_addr.s_addr, server_hostent->h_addr, server_hostent->h_length);

	// To assign the port number, use host-to-network-short.
	server_sockaddr.sin_port = htons(server_port);

	ssize_t bytes_sent;
//	number_of_packets = 100;
//	cout << __LINE__ << " "; DumpDG(cd);

	int retval = 0;
	int i;
	for (i = 0; i < number_of_packets; i++)
	{
		// Fill in the sequence number in a network portable manner.
		cd->sequence_number = htonl(i);

		// sendto() contains everything we need to know as UDP is entirely stateless. It returns
		// the number of bytes sent. It behooves you to ensure this is correct especially if
		// MSG_DONTWAIT is used (it is not used here).
		//DumpDG(cd);
		bytes_sent = sendto(udp_socket, (void *) cd, datagram_length, 0, (struct sockaddr *) &server_sockaddr, sizeof(server_sockaddr));
		if ((ssize_t) bytes_sent != (ssize_t) datagram_length) 
		{
			perror("bytes sent");
			if (bytes_sent != 0)
			{
				cerr << "ERROR Number of bytes sent [" << bytes_sent << "] does not match message size [" << datagram_length << "]" << endl;
				retval = 5;
				break;
			}
		} else {
			unmatched_sequence_numbers.insert(i);
            for (int counter = 0; counter < 3; counter++) {
                if (!AttemptReception(udp_socket, unmatched_sequence_numbers, datagram_length)) {
                    cerr << "ERROR failure in packet reception" << endl;
                    retval = 6;
                    goto bad;
                }
            }
		}
        if (delay)
            usleep(delay);
	}

bad:
    free(cd);
	close(udp_socket);
	cout << i << " messages sent." << endl;
	cout << "Unacknowledged packets: " << unmatched_sequence_numbers.size() << endl;
	return retval;
}
