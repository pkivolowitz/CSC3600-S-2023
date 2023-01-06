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
| Learning Outcomes | [Here](#learning-outcomes) |
| Textbook | [Here](#textbook) |
| Programming Environment | [Here](#programming-environment) |
| Special Note on Projects | [Here](#special-note-on-projects) |
| Grading Criteria | [Here](#grading-criteria) |
| Attendance is Graded | [Here](#attendance-is-graded) |
| Projects will be Checked for Academic Honesty | [Here](#projects-will-be-checked-for-academic-honesty) |
| getopt Tutorial | [Here](./getopt/README.md) |

---

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

The textbook is [An Introduction to Computer Networks](<http://intronetworks.cs.luc.edu/current2/ComputerNetworks.pdf>) by Peter
Dordal.

It is free.

Specifically for all our projects,
[this link will be your lifesaver](<https://beej.us/guide/bgnet/html/split-wide/>).

---

## Programming Environment

Projects mostly require the Berkeley Sockets API.

* The Mac terminal can be used directly.

* Windows does not expose the Berkeley Sockets API to users. Instead,
you will have to use WSL or WSL 2 or some other virtual machine
capability.

### Programming Language

Except for one project, all projects must be implemented in C, C++ or
a mixture of C and C++.

One project will require the use of a prog

### How Programs are Graded

Programs will be graded:

* on a Macintosh - do not use features specific to Windows.

* for style and clarity

* for comments

You are approaching graduation and the real world. Grading standards
correspondingly shift closer to the real world.

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
