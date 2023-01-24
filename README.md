# Network Programming Spring 2023

## Overview

This course is primarily about designing and implementing network
centric or network aware single threaded and multithreaded
applications. As such, the course is project intensive.

Additionally, the nature, purpose and mechanics of certain protocols
such as TCP, IP and others will be covered.

---

## Table of Contents

| Topic | Link |
| ----- | ---- |
| Help | [Here](#help) |
| Learning Outcomes | [Here](#learning-outcomes) |
| Textbook | [Here](#textbook) |
| Programming Environment | [Here](#programming-environment) |
| Projects | [Here](#projects) |
| Special Note on Projects | [Here](#special-note-on-projects) |
| Grading Criteria | [Here](#grading-criteria) |
| Attendance is Graded | [Here](#attendance-is-graded) |
| Projects will be Checked for Academic Honesty | [Here](#projects-will-be-checked-for-academic-honesty) |
| getopt Tutorial | [Here](./getopt/README.md) |

---

## Help

I do not post office hours despite this being a requirement of all
faculty.

What I do instead, which I believe is better, is have "open" office
hours. I.e. any time is a potential office hour. Simply use Google
Calendar to book an appointment with me. Remember to send me the
invitation!

As all help sessions are provided via Zoom, nights and weekends are OK
within reason. Mornings are difficult.

Wednesdays near noon hours are not possible due to campus obligations.

[This is the link to a standing Zoom
meeting](https://carthage-edu.zoom.us/j/4456320007?pwd=UmZNa3ZDOTI2NHdhR21sSmxDR21KUT09).
Use this meeting link for all out-of-class help from me.

## Learning Outcomes

As a result of taking this course, students should be able to:

* Design and implement client-server applications using datagram (UDP) means.

* Design and implement client-server applications using reliable (TCP) means.

* Design and implement multithreaded client-server applications using reliable (TCP) means.

* Understand principles underlying protocols such as ARP, TCP, IP, UDP, DHCP.

* Understand NAT, Broadcasting, VPN, Shortest Path, Reachability, Forwarding, Routing, Ports,
and Sockets

* Utilize the Linux / Unix development tool chain featuring make and gcc / g++.

* Utilize and understand Linux-based networking tools such as ping, traceroute, and other tools

---

## Textbook

### Dordal

The textbook is [An Introduction to Computer Networks](<http://intronetworks.cs.luc.edu/current2/ComputerNetworks.pdf>) by Peter
Dordal.

It is free.

### Beej

Specifically for our projects, [this
link](<https://beej.us/guide/bgnet/html/split-wide/>) to Beej's Guide
 will be your lifesaver.

---

## Programming Environment

Projects mostly require the Berkeley Sockets API.

* The Mac terminal can be used directly.

* Windows does not expose the Berkeley Sockets API to users. Instead,
you will have to use WSL or WSL 2 or some other virtual machine
capability. This will be easy for running both client and server on
your own machine but running a server on WSL and expecting to be
reached from the outside is hard. You're running a VM inside Windows.
Also, Microsoft. Meaning by WSL version 11 it'll be easy to do. We're
on WSL version 2. So. Microsoft.

### Installing WSL the Easy Way

On Windows, run a command prompt **in Administrator mode**. Then type:

```wsl --install```

You'll get some version of Ubuntu and that's good enough.

### Programming Language

Except for one project, all projects must be implemented in C, C++ or
a mixture of C and C++.

One project, the last, will be different. It is based on the first
project so do a good job on that first project.

### How Programs are Graded

Except for one project, projects will be graded:

* on a Macintosh - do not use features specific to Windows.

* for style and clarity

* for comments

* for correctness, of course

You are approaching graduation and the real world. Grading standards
correspondingly shift closer to the real world.

For the "other" project, you will grade your peers.

## Special Note on Projects

Network applications require more than one party to be involved. These
parties might be called Client, Server or Peer representing Client /
Server and Peer to Peer applications.

In projects where you are required to write both a Client and a Server
or a Peer, you will have to balance writing two sides for every
feature implemented. For example, you cannot test the code you just
added to your client without also implementing something in the Server.
Similarly, you cannot test something you've just added to the Server
until you have implemented something in the Client.

In this way, network applications are bootstrapped side-by-side.

On the other hand, suppose you had a kind hearted sweet pushover for a
professor who assigned writing one side at a time and provided the
other side to you for testing. Boy that professor would get great
evaluations, wouldn't they?

---

## Grading Criteria

The following are the gradable categories along with their weighting.
Note that these values supersede those given in the published syllabus.

| Category | Weight |
| -------- | ------ |
| Attendance | 10 |
| Midterm - March 27th | 10 |
| Final  - May 23 1PM - 3PM | 10 |
| Projects | 70 |

Both exams will be administered on Schoology. The Final exam is
cumulative.

---

## Attendance is Graded

Attendance will be graded as follows:

* After 4 absences (i.e., starting at the fifth absence) each additional
absence will mean 1 points being deducted from your final aggregate
score.

* After 8 absences (i.e., starting at the ninth absence) each additional
absence will be 2 points being deducted from your final aggregate score.

For example:

* at 8 absences you will have lost 4 points from your aggregate score.

* At 10 absences you will have lost 8 points from your aggregate score.

* At 11 absences and beyond you will have lost 10 points from your aggregate score.

Your aggregate score is defined as the weighted average of course
grades. Students begin with an assumed perfect score for attendance.
At the end of the term, your final attendance record will be reflected
in an adjusted grade for attendance.

*Since attendance is graded, you must check to ensure your attendance
is captured accurately.*

---

## Projects will be Checked for Academic Honesty

As this is an advanced elective course withing the Carthage College
Computer Science program, the instructor will be on guard for academic
honesty violations.

* One violation will earn a score of zero for the project.

* Two violations will be reported to the Provost for disciplinary
consequences.

---

## Projects

| Project | Content | Location |
| ------- | ------- | -------- |
| P1 | UDP Blaster | [Here](./projects/p1) |
| P2 | Client Side Walkie Talkie | [Here](./projects/p2_and_p3/) |
| P3 | Server Side Walkie Talkie | [Here](./projects/p2_and_p3/) |
| P4 | Client Side Retro Chat | [Here](./projects/p4_and_p5/) |
| P5 | Server Side Retro Chat | [Here](./projects/p4_and_p5/) |
| P6 | maybe - place holder | N/A |
| P*n* | Fun! Fun! Fun! | [Here](./projects/p_last/) |

## Useful Links

| Topic | Link |
| ----- | ---- |
| getopt | [here](https://azrael.digipen.edu/~mmead/www/Courses/CS180/getopt.html) |
