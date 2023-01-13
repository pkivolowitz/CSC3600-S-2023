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

using namespace std;

int main(int argc, char * argv[]) {
	int retval = 0;
	const size_t BUFFER_SIZE = 1024;
	int udp_socket;
	int server_port = 0;
	struct sockaddr_in server_sockaddr;
	struct sockaddr_in client_sockaddr;
	unsigned char buffer[BUFFER_SIZE];
	ssize_t bytes_received;
	socklen_t l = sizeof(client_sockaddr);

	memset((void *) &client_sockaddr, 0, sizeof(client_sockaddr));

	int c;
	try {
		while ((c = getopt(argc, argv, "hp:vd")) != -1) {
			switch (c) {

				case 'h':
					cerr << argv[0] << "options:" << endl;
					cerr << "   -h displays help" << endl;
					cerr << "   -p port_number" << endl;
					throw 0;

				case 'p':
					server_port = atoi(optarg);
					break;
			}
		}
		if (server_port == 0) {
			cout << "Must specify server's port." << endl;
			throw 1;
		}
		
		cout << "Server will attempt to bind to port: " << server_port << endl;

		udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
		if (udp_socket < 0) {
			perror("ERROR opening socket");
			throw 1;
		}

		memset(&server_sockaddr, 0, sizeof(server_sockaddr));

		server_sockaddr.sin_family = AF_INET;
		server_sockaddr.sin_addr.s_addr = INADDR_ANY;
		server_sockaddr.sin_port = htons(server_port);

		if (bind(udp_socket, (const struct sockaddr *) &server_sockaddr, socklen_t(sizeof(server_sockaddr))) < 0) {
			close(udp_socket);
			perror("ERROR on binding");
			throw 1;
		}
		cout << "Network structs initialized and port is bound." << endl;

		while (true) {
			memset(buffer, 0, BUFFER_SIZE);
			bytes_received = recvfrom(udp_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &client_sockaddr, &l);

			if (bytes_received > 0) {
				cout << bytes_received << " bytes received from: ";
				cout << inet_ntoa(client_sockaddr.sin_addr) << " string: ";
				cout << buffer << endl;
			}
			else if (bytes_received == 0) {
				cout << "Received zero bytes - I don't think this can happen.\n";
			}
			else {
				perror("recvfrom()");
				throw 1;
			}
		}
	}
	catch (int rv) {
		retval = rv;
	}
	return retval;
}

