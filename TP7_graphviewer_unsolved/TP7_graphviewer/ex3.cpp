#include "graphviewer.h"
#include <fstream>

using namespace std;
using Node = GraphViewer::Node;
using Edge = GraphViewer::Edge;

void ex3() {

    // Instantiate GraphViewer
    GraphViewer gv;
    // Set coordinates of window center
    gv.setCenter(sf::Vector2f(300, 300));

    // Create window
    gv.createWindow(600, 600);


    ifstream nodes("../TP7_graphviewer/resources/map1/nodes.txt");
    string text;
    int n;
    nodes >> n ;

    for (int i = 0; i < n; i++) {
        int id, x, y;
        nodes >> id >> x >> y;
        gv.addNode(id, sf::Vector2f(x, y)); // Create node
    }
    nodes.close();
    ifstream edges("../TP7_graphviewer/resources/map1/edges.txt");
    edges >> n;
    for (int i = 0; i < n; i++) {
        int id, fromNode, toNode;
        edges >> id >> fromNode >> toNode;
        gv.addEdge(id, gv.getNode(fromNode), gv.getNode(toNode), Edge::UNDIRECTED);
    }

    edges.close();

    // Join viewer thread (blocks till window closed)
    gv.join();

}

