#I have created 3 projects in order to compute the minmum cost for the simple predefined data:
Istudor_Eduard_BFS  for the BFS algorithm
Istudor_Eduard_UniformCost for the UCS algorithm
Istudor_Eduard_A_Star_Search for the A* algorithm

#After that, for each of the aglorithms above I have added a file parser that enables reading inputs from a .tsp file:
Istudor_Eduard_BFS _FileParser
Istudor_Eduard_UniformCost_FileParser
Istudor_Eduard_A_Star_Search _FileParser

#The datasets I have chosen are st70_9(9 cities), bier127_10(10 cities), eil101_11(cities).

#In order to select from which file to read, the name inside the " " has to be changed to the desired file
string filename = "st70_9.tsp";
