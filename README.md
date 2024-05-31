# The Traveling Salesman Problem

I have created 3 projects in order to compute the minimum cost for the simple predefined data:
- **Istudor_Eduard_BFS** for the BFS algorithm
- **Istudor_Eduard_UniformCost** for the UCS algorithm
- **Istudor_Eduard_A_Star_Search** for the A* algorithm

Each algorithm has an additional project that includes a file parser to enable reading inputs from a `.tsp` file:
- **Istudor_Eduard_BFS_FileParser**
- **Istudor_Eduard_UniformCost_FileParser**
- **Istudor_Eduard_A_Star_Search_FileParser**

## Datasets

The datasets used for testing are:
- `st70_9` (9 cities)
- `bier127_10` (10 cities)
- `eil101_11` (11 cities)

## Usage

To select from which file to read, change the name inside the quotes in the code as one of the 3 datasets provided like for example:

```cpp
string filename = "st70_9.tsp";
