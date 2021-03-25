/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <algorithm>
#include "MutablePriorityQueue.h"


template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    T info;						// content of the vertex
    std::vector<Edge<T> > adj;		// outgoing edges

    double dist = 0;
    Vertex<T> *path = NULL;
    int queueIndex = 0; 		// required by MutablePriorityQueue

    bool visited = false;		// auxiliary field
    bool processing = false;	// auxiliary field

    void addEdge(Vertex<T> *dest, double w);

public:
    Vertex(T in);
    T getInfo() const;
    double getDist() const;
    Vertex *getPath() const;

    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set

    std::vector<std::vector<double>> D;
    std::vector<std::vector<int>> P;

public:
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;

    // Fp06 - single source
    void unweightedShortestPath(const T &s);    //TODO...
    void dijkstraShortestPath(const T &s);      //TODO...
    void bellmanFordShortestPath(const T &s);   //TODO...
    std::vector<T> getPath(const T &origin, const T &dest) const;   //TODO...

    // Fp06 - all pairs
    void floydWarshallShortestPath();   //TODO...
    std::vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {

    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        (*it)->dist = INF;
        (*it)->path = NULL;
    }

    Vertex<T> *v = findVertex(orig);

    if (v == NULL)
        return;

    v->dist = 0;
    std::queue<Vertex<T>*> q;
    q.push(v);

    while(!q.empty()) {
        Vertex<T>* v = q.front();
        q.pop();

        for (auto it = v->adj.begin(); it != v->adj.end(); it++) {
            if ((*it).dest->dist == INF) {

                q.push((*it).dest);
                (*it).dest->dist = v->dist + 1;
                (*it).dest->path = v;

            }
        }

    }
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {

    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        (*it)->dist = INF;
        (*it)->path = NULL;
    }

    Vertex<T> *orig = findVertex(origin);

    if (orig == NULL)
        return;

    orig->dist = 0;
    orig->queueIndex = 0;
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(orig);

    while(!q.empty()) {
        Vertex<T>* v = q.extractMin();

        for (auto e: v->adj) {
            if (e.dest->dist > v->dist + e.weight) {
                double old_dist = e.dest->dist;

                e.dest->dist = v->dist + e.weight;
                e.dest->path = v;

                if (old_dist == INF) {
                    q.insert(e.dest);
                }
                else {
                    q.decreaseKey(e.dest);
                }
            }
        }
    }
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {

    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        (*it)->dist = INF;
        (*it)->path = NULL;
    }

    Vertex<T> *origin = findVertex(orig);

    if (origin == NULL)
        return;

    origin->dist = 0;

    for (int i = 1; i < vertexSet.size(); i++) {

        for (auto v: vertexSet) {

            for (auto e: v->adj) {
                if (e.dest->dist > v->dist + e.weight) {

                    e.dest->dist = v->dist + e.weight;
                    e.dest->path = v;
                }
            }
        }
    }


    for (auto v: vertexSet) {

        for (auto e: v->adj) {
            if (e.dest->dist > v->dist + e.weight) {

                std::cout << "There are cycles of negative weight.\n";
                return;
            }
        }
    }

}


template<class T>
std::vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
    std::vector<T> res;
    Vertex<T> * v = findVertex(dest);

    while (v != NULL) {
        res.push_back(v->info);
        v = v->path;
    }

    std::reverse(res.begin(), res.end());

    return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {

    D = std::vector<std::vector<double>>(vertexSet.size(), std::vector<double>(vertexSet.size()));
    P = std::vector<std::vector<int>>(vertexSet.size(), std::vector<int>(vertexSet.size()));

    for (int i = 0; i < vertexSet.size(); i++) {
        for (int j = 0; j < vertexSet.size(); j++) {

            if (i == j) {
                D[i][j] = 0;
            }
            else {
                D[i][j] = INF;
            }
            P[i][j] = -1;
        }

        for (int j = 0; j < (*vertexSet[i]).adj.size(); j++) {

            Vertex<T>* v = vertexSet[i]->adj[j].dest;
            int indexJ = -1;
            for (int index = 0; index < vertexSet.size(); index++) {
                if (vertexSet[index] == v) {
                    indexJ = index;
                    break;
                }
            }

            D[i][indexJ] = (*vertexSet[i]).adj[j].weight;
            P[i][indexJ] = i;
        }
    }

    for (int k = 0; k < vertexSet.size(); k++) {
        for (int i = 0; i < vertexSet.size(); i++) {
            for (int j = 0; j < vertexSet.size(); j++) {

                if(D[i][k] == INF || D[k][j] == INF)
                    continue;

                if (D[i][j] > D[i][k] + D[k][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = P[k][j];

                }
            }
        }
    }

}

template<class T>
std::vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{

    std::vector<T> res;
    Vertex<T> * v_dest = findVertex(dest);
    Vertex<T> * v_orig = findVertex(orig);

    int indexI = -1, indexJ = -1;

    for (int i = 0; i < vertexSet.size(); i++) {
        if (vertexSet[i] == v_orig) {
            indexI = i;
        }
        if (vertexSet[i] == v_dest) {
            indexJ = i;
        }

        if (indexJ != -1 && indexI != -1)
            break;

    }

    if (indexI == -1 || indexJ == -1 || D[indexI][indexJ] == INF)
        return {};

    while (indexJ != -1) {
        res.push_back(vertexSet[indexJ]->info);
        indexJ = P[indexI][indexJ];
    }

    std::reverse(res.begin(), res.end());
    return res;
}


#endif /* GRAPH_H_ */
