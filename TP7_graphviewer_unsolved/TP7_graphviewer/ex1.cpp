#include "graphviewer.h"

using namespace std;
using Node = GraphViewer::Node;
using Edge = GraphViewer::Edge;

void ex1() {

    // Instantiate GraphViewer
    GraphViewer gv;
    // Set coordinates of window center
    gv.setCenter(sf::Vector2f(300, 300));

    Node &node0 = gv.addNode(0, sf::Vector2f(200, 300)); // Create node
    node0.setColor(GraphViewer::BLUE);

    Node &node1 = gv.addNode(1, sf::Vector2f(400, 500)); // Create node
    node1.setColor(GraphViewer::BLUE);


    // for bidirectional edges
    Edge &edge1 = gv.addEdge(1, node0, node1, Edge::UNDIRECTED);
    // for directed edges
    Edge &edge2 = gv.addEdge(2, node0, node1, Edge::DIRECTED);

    // Remove node
    //gv.removeNode(1);

    Node &node2 = gv.addNode(2, sf::Vector2f(500, 300)); // Create node
    Edge &edge3 = gv.addEdge(3, node0, node2, Edge::UNDIRECTED);

    // Add label
    node2.setLabel("This is a vertex");
    edge3.setLabel("This is an edge");


    // Configure vertex color
    node2.setColor(GraphViewer::GREEN);

    // Make edges yellow
    for(Edge *edge: gv.getEdges())
        edge->setColor(GraphViewer::YELLOW);

    // Set background
    gv.setBackground("../TP7_graphviewer/resources/background.png");

    // Create window
    gv.createWindow(600, 600);

    // Join viewer thread (blocks till window closed)
    gv.join();

}
