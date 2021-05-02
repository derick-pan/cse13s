Derick Pan
dpan7
Spring 2021
Asgn 4: The circumnavigations of Denver Long

---------------------------------------------
DESCRIPTION

This C code is my implementation of a recursive DFS search
to search through all possible vertices of an adjacency matrix
and back to my first vertice.
The function names were given from the ASGN4 pdf and my stack
function mostly originates from my Asgn3 code.

Graph:
Graph stores the edges onto a graph and produces a visual idea of where I 
can and will be recursing to find the shortest path possible. Graph can
also tell me the amount of vertices, and whether or not an edge exists.

Path:
Path is a struct and functions to store a way for me to remember my previous paths.
As we recursively search for a solution, we require a way to push and pop vertices 
in a stack like manner. Path allows us to find the total amount of vertices, vertices in a path
and be able to copy one path to another.

Stack:
As said in path, we need a way to push and pop vertices. I use the majority of my stack
functions from asgn3 as it's all already implemented already.

-----------------------------------------------------
FILES

-vertices.h
-graph.h
-graph.c
-stack.h
-stack.c
-path.h
-tsp.c
-Makefile
-README.md
-DESIGN.pdf

----------------------------------------------------
INSTRUCTIONS

To run these files, download these files on a machine that runs the lastest
 version of Ubuntu. Then open a terminal and type "make". This will compile 
the code and create an executable. If you want to only format the code then 
run "make format"
Then type "./tsp"

to view the options to run the code, also shown following:
SYNOPSIS
  Traveling Salesman Problem using DFS.

USAGE
  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]

OPTIONS
  -u             Use undirected graph.  This allows the user to specify
					whether or not they want their 
					graph to be directed/undirected.

  -v             Enable verbose printing. This allows the user to see
					  all of the hamiltonian paths that
					  stood a chance of being the shortest

  -h             Program usage and help. User has to know what to do! This shows them

  -i infile      Input containing graph (default: stdin) Allows the code to know where 
							 the graph details are coming from

  -o outfile     Output of computed path (default: stdout) If the user wants the code's output
							   to be in a specified file.

