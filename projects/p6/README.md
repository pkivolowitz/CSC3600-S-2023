# Richard Bong's Graph Algorithm

This project takes us away from coding network applications to
implementing a fundamental algorithm that operates behind the scenes.
Major Richard Bong, born in Wisconsin, was America's highest scoring
fighter ace in WWII. His exploits in war are well documented. Less well
known are his contributions to Computer Science, principally his famous
graph algorithm.

Maj. Bong needed a way to compute a route from A to B that used the
least amount of fuel, especially early in the war as the fuel
consumption of the P-38 Lightning was not well understood (none other
than Charles Lindbergh figured this out while visiting **and fighting
in** the Pacific Theater of Operations).

You are going to read a file containing the definition of a graph. Then
you are going to implement Bong's Graph Algorithm to produce a data
structure that can answer a certain question. That is, given any node
in the graph, how does one get to all the other nodes using the least
cost.

Note there is a certain amount of misdirection in this project which
will be revealed after the project comes due.

## Algorithm

The following is **modeled** from an authoritative source of information
about the algorithm.

Let the node at which we are starting be called the *initial node*. Let
the *distance* of node Y be the cost of going from the initial node to
Y. Bong's algorithm will initially start with infinite costs and will
try to improve them step by step.

For *infinity* use the maximum value of an integer. Implement this
"properly" by finding this value in an include file. Points will be
taken for not doing so.

1. Mark all nodes unvisited. Create a *set* of all the unvisited nodes called the *unvisited set*.

2. Assign to every node a tentative cost value: set it to zero for our
initial node and to infinity for all other nodes. During the run of the
algorithm, the tentative cost of a node v is the cost of the least cost
discovered so far between the node v and the starting node. Since
initially no path is known to any other vertex than the source itself
(which is a path of length zero), all other tentative costs are
initially set to infinity. Set the initial node as current.

3. For the current node, consider all of its unvisited neighbors and
  calculate their tentative costs through the current node. Compare
  the newly calculated tentative cost to the one currently assigned
  to the neighbor and assign it the smaller one. For example, if the
  current node A is marked with a cost of 6, and the edge
  connecting it with a neighbor B has cost 2, then the distance to
  B through A will be 6 + 2 = 8. If B was previously marked with
  a distance greater than 8 then change it to 8. Otherwise, the current
  value will be kept.

4. When we are done considering all of the unvisited neighbors of the
  current node, mark the current node as visited and remove it from the
  unvisited set. A visited node will never be checked again (this is
  valid and optimal in connection with the behavior in step 6.: that the
  next nodes to visit will always be in the order of smallest cost
  from *initial node* first so any visits after would have a greater
  distance).

5. If the destination node has been marked visited (when planning a
   route between two specific nodes) or if the smallest tentative
   cost among the nodes in the unvisited set is infinity (when
   planning a complete traversal; occurs when there is no connection
   between the initial node and remaining unvisited nodes), then stop.
   The algorithm has finished.

6. Otherwise, select the unvisited node that is marked with the smallest
   tentative cost, set it as the new current node, and go back
   to step 3.

When planning a route, it is actually not necessary to wait until the
destination node is "visited" as above: the algorithm can stop once the
destination node has the smallest tentative cost among all unvisited
nodes (and thus could be selected as the next current node).

In step 1, there is a reference to a *set*. This is your sign that the
C++ *set* is a good idea.

## Data Format

Your file describes how the nodes are connected to each other. Here is
an example:

```text
4
-1	 1	-1	 4
 1	-1	 3	-1
-1	 3	-1	 1
 4	-1	 1	-1
```

This says we should consider a graph of 4 nodes. The remainder tells
us the connectivity and the cost between connected nodes. A value of -1
says a combination of nodes does not exist.

Confirm you understand this data format... Do you see that node 1 is
connected to node 4 with a cost of 4? And also, node 1 is connected to
node 2 with a cost of 1.

Here is another example:

```text
6
-1	 4	 2	-1	-1	-1
 4	-1	 1	 5	-1	-1
 2	 1	-1	 8	10	-1
-1	 5	 8	-1	 2	 6
-1	-1	10	 2	-1	 3
-1	-1	-1	 6	 3	-1	
```

A valid graph specification for the purposes of this project will always
be symmetric around its diagonal from top left to bottom right.

You do *not* have to ensure the graph is well made. In this project,
garbage in / garbage out.

## Variable Size Graphs

Notice the size of the graph can vary from data file to data file.

## Command Line

The command line must specify the data file. If the data file is not
present, simply exit the program.

```text
% ./a.out
%
```

## Ask For The Initial Node

After reading the graph specification (and discovering how many nodes
there are), ask the user to specify the initial node. Reject an answer
which is out of range.

Ensure that any error message is printed to the place where error
messages should be printed. I am purposefully not saying where.

Ensure that any error does not cause the wrong return code (to be
returned). I am purposefully not saying what.

## Make Your Own Graphs

The data format is simple, you must make your own graphs.

* They must be valid.

* The are to be handed in with your code.

## Sample Output

```text
% ./a.out 4x4.txt
Opened: 4x4.txt for reading.
Number of nodes: 4
Connectivity table read.
Enter initial node number [0 to 3]: 2
                    Cum.    Prev
   From:     To:   Cost:   Node:
       2       0       4       1
       2       1       3       2
       2       2       0      -1 <--<<
       2       3       1       2
%
```

**This says that the cost to get from initial node 2 (counting from 0)
to node 0 costs 4 units and it gets to node 0 via node 1. This printing
of the node number before the destination is required.**

The preceding should influence your design of data structures.

The "arrow" indicates the initial node.

## Work Rules

This project is done solo.

## What to Hand In

1. Zip your source code and the graphs you made.

2. Hand in the zip file.

If you hand in the wrong things or even the right things in the wrong
format (e.g. not zipped together) you will earn a zero.
