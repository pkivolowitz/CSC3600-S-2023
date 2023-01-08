# Introductory TCP Projects

These projects a first effort at TCP-based projects.

NOTICE the use of plural. This specification serves for **TWO
PROJECTS**.

Project 1 was your UDP project.

Project 2 is to write the client side using this specification. I will
have to build a number of servers for you to test with. I will at first
provide you with a single Mac version build for Intel. I expect this to
work on the ARM Macs as well but we'll see. I have to provide an Intel
WSL version. I don't expect anyone in class to have an ARM Windows
machine (yet).

Project 3 is to write the server side using this specification.

## Overview

Think of this as a very dumb walkie-talkie.

The client sends lines of text over to the server ending in OVER. The
server sends back the length of the line of text (not including OVER)
ending with OVER.

## Framing

Recall that TCP is a streaming protocol where UDP is a datagram based
protocol. A single UDP packet is either received in its entirety or it
is not received at all. TCP is free to break up packets anyway it
chooses. Therefore, there is no built in way to determine where a
message is meant to end.

That was why the client and server each end their discrete exchanges of
information with the word OVER.

## Work Rules

Every student in this class must master setting up TCP-based network
applications. Therefore, this project must be done solo.

## Client

Your client:

* establishes a TCP connection to a server.

* in a loop, prompts you for a line of text. You determine when to end
one "message" by entering OVER as part of your text. Never provide any
text after the word OVER - this is to make the project a little easier.

* it sends each line of text to the server including the word OVER, if
given. Remember - no text after the word OVER.

* waits for a response from the server - it will end its message with
OVER.

* on receiving a response, it prints the received text after having
stripped the word OVER from it.

* the client repeats until you enter QUIT.

* upon reading QUIT, the client closes the connection to the server and
exits printing "Client exiting normally".

### Required Command Line Options

* `-h` prints help text to **stderr / cerr** and exits with return code
  0.

* `-p` overrides the default destination port.

* `-d` overrides the default destination address.

## Server

Your server:

* sets up to listen to a port.

* it accepts one connection at a time. It prints a nice message when it
accepts a connection. See sample.

* it waits for lines of text, accumulating received text until it finds
the text OVER.

* it calculates the length of the accumulated text (not including the
word OVER).

* it sends the length back to the client appending the word OVER.

* it does the above over and over until the connection closes at which
time the server prints a nice message and quits. See sample. Note: my
server is coded to accept multiple sequential connections. I did this
to make my own debugging simpler and to permit the class to connect with
my server on work days (in class).

### Name Clash with `bind()`

The server needs to call `bind()` but there is a name clash with another
function called `bind()`. To break the clash, call `::bind()` instead.

### `SO_REUSEADDR`

When TCP sockets close, by default they wait a period of time before
totally shutting down so that any packets circling the globe have time
to reach the server so that they can be acknowledged. This amount of
time is several minutes. To avoid these, use the `SO_REUSEADDR` feature
via `setsockopt()`. See Beej
[here](<https://beej.us/guide/bgnet/html/split-wide/man-pages.html#setsockoptman>).

### Server Buffer Size

You must set your server side buffer to a size of 80 bytes. This means
you can receive up to 80 bytes per `recv()`. This is completely
arbitrary and is decided by me for the purposes of this project. That
is, to emphasize the streaming nature of TCP and the need for framing,
you are required to use a small buffer and to accumulate characters in a
larger buffer.

Hint: I used a C array of `char` of size 80 + 1. I used a `stringstream`
to accumulate the full message.

Hint: The buffer must be initialized to zero before each `recv()` so you
can tell where the C string ends. This is why the C array of `char` must
be one larger than the amount you tell `recv()` you can handle at one
time.

Note that the value of 80 is a *magic number*. You **must** make this a
constant.

### Required Command Line Options

* `-h` prints help text to **stderr / cerr** and exits with return code
  0.

* `-p` overrides the port on which the server listens.

## Return Codes

For both the client and server, if an error occurs the return code from
your program must be 1. If all goes well, the return code must be 0.

## Defaults

The default destination to which the client attempts to connect is:

```127.0.0.1```

The default port over which the client attempts to connect, and the port
upon which the server is listening is:

```9838```

## Samples

Normal execution of client:

```text
% ./client
> This is a test.OVER
Server sent: Line length: 15
> This is line 1
> This is line 2
> OVER
Server sent: Line length: 28
> ^D
Client exiting normally
```

And the matching output of the server:

```text
% ./server
Server received connection from 127.0.0.1 on port 1251
Server received: This is a test.
Server sending: Line length: 15 OVER
Server received: This is line 1
Server received: This is line 1This is line 2
Server sending: Line length: 28 OVER
Client closed its connection.
```

Help message from client:

```text
% ./client -h
Usage:
-h       prints this text
-d ip    overrides the default address of 127.0.0.1
-p port  overrides the default port of 9838
```

Help message from server:

```text
% ./server -h
Usage:
-h       prints this text
-p port  overrides default port of 9838
```

## What to Hand In

You must zip together all source files you write as long as any includes
you may have created. Plus you must include your makefile in case you
have made any changes to the one I give you.
