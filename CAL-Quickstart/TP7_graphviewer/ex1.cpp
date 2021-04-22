#include "graphviewer.h"

using namespace std;
using Node = GraphViewer::Node;
using Edge = GraphViewer::Edge;

void ex1() {
    // TODO

    // Instantiate GraphViewer
    GraphViewer gv;
    // Set coordinates of window center
    gv.setCenter(sf::Vector2f(300, 300));
    // Create window
    gv.createWindow(600, 600);
    // Join viewer thread (blocks till window closed)
    gv.join();

    Node &node0 = gv.addNode(0, sf::Vector2f(200, 300)); // Create node
    node0.setColor(GraphViewer::BLUE);

    Node &node1 = gv.addNode(1, sf::Vector2f(400, 300)); // Create node
    node1.setColor(GraphViewer::BLUE);


    // for bidirectional edges
    Edge &edge1 = gv.addEdge(1,0,1,GraphViewer::EdgeType::UNDIRECTED);
    // for directed edges
    //Edge &edge1 = gv.addEdge(idEdge,idSource,idDestination,GraphViewer::EdgeType::DIRECTED);
}
