/*	Datagram sample client.
	CSC 3600 - Carthage College - Prof. Kivolowitz - Spring 2016
*/

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <getopt.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>

using namespace std;

int main(int argc, char *argv[]) {
	int retval = 0;
	int udp_socket = -1;
	int server_port = 0;
	char * server_address = nullptr;
	char * message = nullptr;

	struct sockaddr_in server_sockaddr;
	struct hostent * server_hostent;

	char c;
	try {
		while ((c = getopt(argc, argv, "hs:p:m:")) != -1) {
			switch (c) {
				case 'h':
					cerr << argv[0] << "options:" << endl;
					cerr << "	-h displays help" << endl;
					cerr << "	-s server_address (required)" << endl;
					cerr << "	-p port_number (required)" << endl;
					cerr << "   -m message (required)" << endl;
					throw 0;

				case 'm':
					message = optarg;
					break;

				case 's':
					server_address = optarg;
					break;
					
				case 'p':
					server_port	= atoi(optarg);
					break;

			}
		}

		if (server_port == 0) {
			cerr << "Server port required\n";
			throw 1;
		}

		if (server_address == nullptr) {
			cerr << "Server address required\n";
			throw 1;
		}

		if (message == nullptr) {
			cerr << "Message required\n";
			throw 1;
		}

		udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
		if (udp_socket < 0) {
			perror("ERROR opening socket");
			throw 1;
		}

		server_hostent = gethostbyname(server_address);
		if (server_hostent == nullptr) {
			close(udp_socket);
			cerr << "ERROR, no such host: " << server_address << endl;
			throw 1;
		}

		memset(&server_sockaddr, 0, sizeof(server_sockaddr));
		server_sockaddr.sin_family = AF_INET;
		memmove(&server_sockaddr.sin_addr.s_addr, server_hostent->h_addr, server_hostent->h_length);
		server_sockaddr.sin_port = htons(server_port);
		ssize_t ml = strlen(message) + 1;
		ssize_t bytes_sent = sendto(udp_socket, (void *) message, ml, 0, (struct sockaddr *) &server_sockaddr, sizeof(server_sockaddr));
		if (bytes_sent != ml) {
			cerr << "Sent: " << bytes_sent << " expected to send: " << ml << endl;
			perror("sendto()");
			throw 1;
		}
	}
	catch (int rv) {
		retval = rv;
	}
	if (udp_socket >= 0)
		close(udp_socket);
	return retval;
}
