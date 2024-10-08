#include "../incl/Pigale.h"
#include <limits>
// #include "../incl/QT/graphml.h"
#include "../incl/TAXI/graph.h"
#include <iostream>
#include <fstream>
#include <dirent.h>  // For POSIX directory functions
#include <algorithm>
#include <regex>      // For extracting numbers from filenames


#ifndef NDEBUG
#define log if(true) std::cout
#else
#define log if(false) std::cout
#endif

bool stringToBool(const std::string& str) {
    if (str == "true") {
        return true;
    } else if (str == "false") {
        return false;
    } else {
        throw std::invalid_argument("Invalid boolean string");
    }
}

int extractNumber(const string &filename) {
    std::regex re("_(\\d+)_nodes");
    std::smatch match;

    if (std::regex_search(filename, match, re)) {
        return stoi(match[1]);  // Extract the number as an integer
    }
    return 0;  // Default in case of no match
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <graphfile> <embedding>" << std::endl;
        return 1;
    }

    GraphContainer GC; // defined in TAXI/graph.h


    string filePath = argv[1];
    bool embedding = stringToBool(argv[2]);
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        std::cerr << "Error: could not open the file " << filePath << std::endl;
        return 1;
    }

    // Read the number of vertices and edges from the first two lines
    int n, m;
    inputFile >> n >> m;
    GC.setsize(n, m);

    Prop<tvertex> vin(GC.Set(tbrin()), PROP_VIN);


    for (int edgeIndex = 1; edgeIndex <= m; ++edgeIndex) {
        int u, v;
        inputFile >> u >> v;

        vin[edgeIndex] = (tvertex) u;   // Edge is incident to vertex u
        vin[-edgeIndex] = (tvertex) v;  // Edge is incident to vertex v
    }


    for (int i = 0; i < 4; i++) {
        if (embedding) {
            // create a topological graph access
            TopologicalGraph G(GC); // defined in TAXI/graphs.h
            // print the number of vertices and edges

            // Compute a planar embedding or return -1
            auto start = chrono::high_resolution_clock::now();
            auto planarGraph = G.Planarity();
            bool isPlanar = planarGraph != 0;
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;
            cout << isPlanar << " " << elapsed.count() << " ";
        } else {
            // create a topological graph access
            TopologicalGraph G(GC); // defined in TAXI/graphs.h
            // print the number of vertices and edges

            // Compute a planar embedding or return -1
            auto start = chrono::high_resolution_clock::now();
            auto planarGraph = G.Planarity();
            bool isPlanar = planarGraph != 0;
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;
            cout << isPlanar << " " << elapsed.count() << " ";
        }
    }
    return 0;
}


