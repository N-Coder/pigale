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

int extractNumber(const string &filename) {
    std::regex re("_(\\d+)_nodes");
    std::smatch match;

    if (std::regex_search(filename, match, re)) {
        return stoi(match[1]);  // Extract the number as an integer
    }
    return 0;  // Default in case of no match
}

int main ()
{

    // Taxi_FileIOGraphml TFG;
    // TFG.Read(GC, './demograph.graphml',1,1);

    std::string path = "./mapped_data";  // Directory path you want to iterate

    DIR *dir = opendir(path.c_str());
    if (dir == nullptr) {
        std::cerr << "Error: Could not open directory " << path << std::endl;
        return 1;
    }
    vector<string> filePaths;

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {

        string filename = entry->d_name;
        if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".txt") {
            std::cout << "Found file: " << filename << std::endl;
            filePaths.push_back("./mapped_data/" + filename);
        }
    }

    closedir(dir);

    // Sort the files lexicographically (default sorting for strings)
    sort(filePaths.begin(), filePaths.end(), [](const string &a, const string &b) {
        return extractNumber(a) < extractNumber(b);  // Reverse the comparison
    });


    // Process each sorted file
    for (const auto &filePath : filePaths) {
        cout << "Processing file: " << filePath << endl;

        GraphContainer GC; // defined in TAXI/graph.h


        std::ifstream inputFile(filePath);

        if (!inputFile.is_open()) {
            std::cerr << "Error: could not open the file " << filePath << std::endl;
            return 1;
        }

        // Read the number of vertices and edges from the first two lines
        int n, m;
        inputFile >> n >> m;
        GC.setsize(n, m);

        Prop <tvertex> vin(GC.Set(tbrin()), PROP_VIN);


        for (int edgeIndex = 1; edgeIndex <= m; ++edgeIndex) {
            int u, v;
            inputFile >> u >> v;

            vin[edgeIndex] = (tvertex) u;   // Edge is incident to vertex u
            vin[-edgeIndex] = (tvertex) v;  // Edge is incident to vertex v
        }

        /*
      // GC is the object that will contains all the information of a graph.
      int n = 4; // n =  number of vertices [1,n]
      int m = 5; // m = number of edges     [1,m]

      GC.setsize(n,m);  // defines the size of the container

      // - a tvertex v is internally represented by an integer v(): 1 <= v() <= n = GC.nv()
      // - a tedge   e is internally represented by an integer e(): 1 <= e() <= m = GC.ne()
      // - a tedge   e is composed of 2 tbrin b0,b1 internally represented by e() and -e()
      // tvertex, tedge, tbrin behave like integers in many respects


      Prop<tvertex> vin(GC.Set(tbrin()),PROP_VIN);// vin is an array  of tbrin whose values are tvertex.

      // Create the edges: each edge (tedge) is incident to 2 vertices (tvertex)
      vin[1] = 1; vin[-1] = 2;  // means that the edge 1 is incident to the vertex 1 and 2
      vin[2] = 1; vin[-2] = 3;
      vin[3] = 2; vin[-3] = 3;
      vin[4] = 3; vin[-4] = 4;
      vin[5] = 2; vin[-5] = 4;  // vin[-5] = 4 could be written vin[(tbrin)-5] = (tvertex)4;

         */

        // create a topological graph access
        TopologicalGraph G(GC); // defined in TAXI/graphs.h
        // print the number of vertices and edges
        cout << "Nodes: " << G.nv() << "\tEdges: " << G.ne() << endl;

        /*
        // print the edges (if e is a tedge, e() is the int that represents it)
        cout << "Edges:" << endl;
        for (tedge e = 1; e <= G.ne(); e++)
            cout << e() << " = [" << G.vin[e] << "," << G.vin[-e] << "]" << endl;

         */

        // at this point loops are FORBIDDEN. You can remove them:
        // int nloops = RemoveLoops();
        cout << "**********." << endl;
        // Compute a planar embedding or return -1
        auto start = chrono::high_resolution_clock::now();
        auto planarGraph = G.Planarity();
        cout << "planar graph: " << planarGraph << endl;
        bool isPlanar = planarGraph != 0;
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "Pigale.Planarity execution time: " << elapsed.count() << " seconds" << endl;
        cout << "Is planar: " << isPlanar << endl;
        /*
        if (G.Planarity() == 0) {
            cout << "not planar" << endl;
            return -1;
        }
        else
            cout << "planar graph" << endl;

         */
        /*
        // At each vertex v  there is a tbrin G.pbrin[v] incident to it: G.vin[G.pbrin[v]] = v;
        // So we can print the planar map (cirular order of half edges around each  vertex)
        cout << "Map (half edges):"<<endl;
        for(tvertex v = 1; v <= G.nv() ; v++)
          {cout << v() <<"  -> ";
            tbrin first = G.pbrin[v];
            tbrin b = first;
            do
          {cout << b() << " ";
          }while((b = G.cir[b]) != first);
            cout << endl;
          }
        // Or you could print the circular order of vertices aroud each vertex
        cout << "Map (vertices):"<<endl;
        for(tvertex v = 1; v <= G.nv() ; v++)
          {cout << v() <<"  -> ";
            tbrin first = G.pbrin[v];
            tbrin b = first;
            do
          {cout << G.vin[-b]() << " ";
          }while((b = G.cir[b]) != first);
            cout << endl;
          }
          */
        break;
    }
    return 0;
}


