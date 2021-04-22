#include "graphviewer.h"
#include <fstream>
#include <unistd.h>

using namespace std;
using Node = GraphViewer::Node;
using Edge = GraphViewer::Edge;

void ex2() {
    // TODO

    // Instantiate GraphViewer
    GraphViewer gv;
    // Set coordinates of window center
    gv.setCenter(sf::Vector2f(300, 300));

    // Create window
    gv.createWindow(600, 600);


    ifstream nodes("../TP7_graphviewer/resources/map_ex2/nodes.txt");
    string text;
    int n;
    nodes >> n ;

    for (int i = 0; i < n; i++) {
        int id, x, y;
        nodes >> id >> x >> y;
        gv.addNode(id, sf::Vector2f(x, y)); // Create node
    }
    nodes.close();
    ifstream edges("../TP7_graphviewer/resources/map_ex2/edges.txt");
    edges >> n;
    for (int i = 0; i < n; i++) {
        int id, fromNode, toNode;
        edges >> id >> fromNode >> toNode;
        gv.addEdge(id, gv.getNode(fromNode), gv.getNode(toNode), Edge::UNDIRECTED);
    }

    edges.close();

    int nr = 10;
    while (nr) {
        if (nr % 2 == 0) {
            Node &node12 = gv.getNode(12); // Get reference to node
            node12.setPosition(sf::Vector2f(250, 550)); // Set position

            Node &node13 = gv.getNode(13); // Get reference to node
            node13.setPosition(sf::Vector2f(350, 550)); // Set position
        }
        else {
            Node &node12 = gv.getNode(12); // Get reference to node
            node12.setPosition(sf::Vector2f(200, 550)); // Set position

            Node &node13 = gv.getNode(13); // Get reference to node
            node13.setPosition(sf::Vector2f(400, 550)); // Set position
        }

        nr--;
        sleep(1);
    }


    // Join viewer thread (blocks till window closed)
    gv.join();
}

