# Notes to myself

## What is needed for the first project?

* Introduce 5 layer network stack.

  * Application

  * Transport

  * Network

  * Link

  * Physical

* Introduce idea of using exceptions to make code cleaner

* Introduce concept of `localhost`. It lives at the transport layer.

* Ports must be introduced.

* IP addresses must be introduced.

* `getopt` must be introduced.

* What is a client - what is a server.

* `udp`

  * `memmove()`

  * `memset()`

  * best effort

  * `socket()`

  * `sockaddr_in`

  * `hostent`

  * `sin_family`

  * `AF_INET`

  * `sendto()`

  * `errno`

  * `bind()`

  * `recvfrom()`

## Hardware

* What is a hub? What layers?

* What is a switch? What layers?

* What is a router? What layers?

* What is a NIC?

  * Show EB920

  * Tell naming story (Business lesson)

  * Show National Semiconductor document (Device Driver lesson)

## ARP

* From bottom to top

* Bridges network to link layer i.e. bridges IP address to MAC address.

* See [book](http://intronetworks.cs.luc.edu/current2/html/ipv4companions.html#address-resolution-protocol-arp)

* Essentially

  * "Who has IP <nnnnn>"

  * "I do - my MAC address is <yyyyy>"

