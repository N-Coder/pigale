cmake_minimum_required(VERSION 3.28)
project(pigale)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_DEBUG_POSTFIX _debug)

add_library(tgraph STATIC
    tgraph/3-ConOrientTriang.cpp
    tgraph/3-ConShelling1.cpp
    tgraph/3-ConShelling2.cpp
    tgraph/Barycenter.cpp
    tgraph/BFS.cpp
    tgraph/Biconnect.cpp
    tgraph/Bipolar.cpp
    tgraph/BipPlanarize.cpp
    tgraph/CotreeCritical.cpp
    tgraph/Debug.cpp
    tgraph/DFS.cpp
    tgraph/DFSGraph.cpp
    tgraph/DFSMap.cpp
    tgraph/Diagonalise.cpp
    tgraph/Embed2Pages.cpp
    tgraph/EmbedPolrec.cpp
    tgraph/EmbedFPP.cpp
    tgraph/EmbedCCD.cpp
    tgraph/EmbedPolyline.cpp
    tgraph/EmbedTutteCircle.cpp
    tgraph/EmbedVision.cpp
    tgraph/FastTwit.cpp
    tgraph/File.cpp
    tgraph/Generate.cpp
    tgraph/GeoAlgs.cpp
    tgraph/Graph.cpp
    tgraph/HeapSort.cpp
    tgraph/k-InfOrient.cpp
    tgraph/LR-Algo.cpp
    tgraph/LR-Map.cpp
    tgraph/mark.cpp
    tgraph/MaxPlanar.cpp
    tgraph/more.cpp
    tgraph/netcut.cpp
    tgraph/NewPolar.cpp
    tgraph/NpBiconnect.cpp
    tgraph/Planar.cpp
    tgraph/PropName.cpp
    tgraph/PropTgf.cpp
    tgraph/PSet.cpp
    tgraph/random.cpp
    tgraph/reduce.cpp
    tgraph/SchaefferGen.cpp
    tgraph/Schnyder.cpp
    tgraph/SchnyderWood.cpp
    tgraph/SWShelling.cpp
    tgraph/STList.cpp
    tgraph/TestSinglePassPlanar.cpp
    tgraph/Tgf.cpp
    tgraph/TopoAlgs.cpp
    tgraph/Twit.cpp
    tgraph/VertexPacking.cpp
    tgraph/Vision.cpp
)
target_include_directories(tgraph PUBLIC incl)

add_executable(usingtgraph UsingTgraph/main.cpp)
set_target_properties(usingtgraph PROPERTIES DEBUG_POSTFIX _debug)
target_link_libraries(usingtgraph PUBLIC tgraph)
