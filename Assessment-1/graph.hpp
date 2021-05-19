#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <iterator>
#include <unordered_set>
#include <set>
#include <queue>
#include <stack>
#include <limits>
#include <utility> 
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace std;

template <typename T> // the template allows the weight of an edge to take any numeric data type (denoted by T).
class Graph {

	public:
        map<string, map<string, T>> adj_list;
        int edgeCount=0;
        /* define your data structure to represent a weighted undirected graph */

        /* test1 */
		Graph(); // the contructor function.
		~Graph(); // the destructor function.
		size_t num_vertices(); // returns the total number of vertices in the graph.
		size_t num_edges(); // returns the total number of edges in the graph.

        /* test2 */
        void add_vertex(const string&); // adds a vertex to the graph -- every vertex uses a string as its unique identifier.
        bool contains(const string&); // checks if a vertex is in the graph -- returns true if the graph contains the given vertex; otherwise, returns false.
        
        /* test3 */
        vector<string> get_vertices(); // returns a vector of all the vertices in the graph.

        /* test4 */
        void add_edge(const string&, const string&, const T&); // adds a weighted edge to the graph -- the two strings represent the incident vertices; the third parameter represents the edge's weight.
        bool adjacent(const string&, const string&); // check if there is an edge between the two vertices in the graph -- returns true if the edge exists; otherwise, returns false.
		
        /* test5 */
        vector<pair<string,string>> get_edges(); // returns a vector of all the edges in the graph -- each edge is represented by a pair of vertices incident to the edge.
        
        /* test6 */
        vector<string> get_neighbours(const string&); // returns a vector of all the vertices, each of which is directly connected with the given vertex by an edge.
        size_t degree(const string&); // returns the degree of a vertex.

        /* test7 */
		void remove_edge(const string&, const string&); // removes the edge between two vertices, if it exists.
        
        /* test8 */
        void remove_vertex(const string&); // delete the given vertex from the graph -- note that, all incident edges of the vertex should be deleted as well.

        /* test9 */
		vector<string> depth_first_traversal(const string&); // returns a vector of all the vertices in the visiting order of a depth-first traversal from the given vertex.
		
        /* test10 */
        vector<string> breadth_first_traversal(const string&); // returns a vector of all the vertices in the visiting order of a breadth-first traversal from the given vertex.

        /* test11 */
		bool contain_cycles(); // check if the graph contains any cycle -- returns true if there exists a path from a vertex to itself; otherwise, return false.
        
        /* test12 */
		Graph<T> minimum_spanning_tree(); // returns a spanning tree of the graph -- the returned tree is preferably a minimum spanning tree.
		
};

/* test1 */

template <typename T>
Graph<T>::Graph() {
    //initialises variables
    map<string,map<string, T>> adj_list;
    int edgeCount=0;
}

template <typename T>
Graph<T>::~Graph() {}


template <typename T>
size_t Graph<T>::num_vertices() {
    //returns size of adj_list which is the number of vertices
    return adj_list.size();
}

template <typename T>
size_t Graph<T>::num_edges() {
    //returns number of edges
    return edgeCount;
}

/* test2 */

template <typename T>
void Graph<T>::add_vertex(const string& u) {
    //add vertex and empty map object to store edges
    //adds vertex implicitly
    adj_list[u]= map<string,T>();
}

template <typename T>
bool Graph<T>::contains(const string& u) {
    //checks if a vertex exists in adj_list
    return adj_list.count(u)>0;
}

/* test3 */

template <typename T>
vector<string> Graph<T>::get_vertices() {
    //pushes all vertices into vector vertices and returns it 
    vector<string> vertices;
    for(auto i= adj_list.begin(); i!= adj_list.end(); i++) {
        vertices.push_back(i->first);
    } 
    return vertices;
}

/* test4 */

template <typename T>
void Graph<T>::add_edge(const string& u, const string& v, const T& weight) {
    //inserts an edge into a vertex u adj_list and vice versa
    //edgeCount increments when a new edge is added
    adj_list[u].insert({v, weight});
    adj_list[v].insert({u,weight});
    edgeCount++;
}

template <typename T>
bool Graph<T>::adjacent(const string& u, const string& v) {
    //checks if an edge exists to vertex v that is adjacent to vertex u  
    return adj_list[u].count(v)>0;
}

/* test5 */

template <typename T>
vector<pair<string,string>> Graph<T>::get_edges() {
    //returns list of edges for graph
    // find() returns the iterator/position that finds a match, otherwise returns the last position
    //if neighbour vertex is not found in visited, then make_pair(vertex A, vertex B), add to edge vector
    //push vertex into visited at the end for cases like a loop
    vector<pair<string, string>> edges;
    vector<string> visited;
     for(auto i= adj_list.begin(); i!= adj_list.end(); i++) {
        for(auto j=adj_list[i->first].begin(); j!=adj_list[i->first].end(); j++) {
            if(find(visited.begin(), visited.end(), j->first)==visited.end()) {
                 edges.push_back(make_pair(i->first, j->first));
            }
        }
        visited.push_back(i->first);
     }
    return edges;
}

/* test6 */

template <typename T>
vector<string> Graph<T>::get_neighbours(const string& u) {
    //pushes adjacent vertices of vertex u into vector neighbours and returns it
    vector<string> neighbours;
    for(auto i= adj_list[u].begin(); i!= adj_list[u].end(); i++) {
        neighbours.push_back(i->first);
    }
    return neighbours;
}

template <typename T>
size_t Graph<T>::degree(const string& u) {
    //returns size of edge list for vertex u
    return adj_list[u].size();
}

/* test7 */

template <typename T>
void Graph<T>::remove_edge(const string& u, const string& v) {
    //removes vertex v from edge list of vertex u and vice-versa
    //decrements the edgeCount 
	adj_list[u].erase(v);
    adj_list[v].erase(u);
    edgeCount--;
}

/* test8 */

template <typename T>
void Graph<T>::remove_vertex(const string& u) {
    //remove edges of vertex, before removing vertex
    //pushes edge list to vector vertex and removes edge 
    //erases vertex u from adj_list
    vector<string> vertex;
    for(auto i= adj_list[u].begin(); i!= adj_list[u].end(); i++) {
        vertex.push_back(i->first);
    }
    for (int i=0; i<vertex.size(); i++) {
        remove_edge(u, vertex[i]);
    }
    adj_list.erase(u);
}

/* test9 */

template <typename T>
vector<string> Graph<T>::depth_first_traversal(const string& u) {
    //returns a traversal of vertices in breadth first order
    //initialises variable and pushes vertex to stack
    stack<string> dft_stack;
    vector<string> dft_visited;
    vector<string> dft_traversal;
    dft_stack.push(u);
    while (!dft_stack.empty()) {
        //stores vertex at top of dft_stack into variable vertex
        string vertex= dft_stack.top();
        dft_stack.pop();
        //checks if vertex has not been visited
        if(find(dft_visited.begin(), dft_visited.end(), vertex)==dft_visited.end()) {
            dft_visited.push_back(vertex);
            dft_traversal.push_back(vertex);
            //pushes edge list of vertex to stack
            for(auto i: adj_list[vertex]) {
                dft_stack.push(i.first);
            }
        }
    }
    return dft_traversal;
}

/* test10 */

template <typename T>
vector<string> Graph<T>::breadth_first_traversal(const string& u) {
    //returns a traversal of vertices in breadth first order
    //bft_traversal collects/gather vertices in bft order
    vector<string> bft_traversal;
    //bft_visited used to check if vertex is visited
    vector<string> bft_visited;
    //queue<string> used to traverse through graph
    queue<string> bft_queue;
    bft_queue.push(u);
    while (!bft_queue.empty()) {
        //stores vertex from front of queue into variable vertex 
        string vertex= bft_queue.front();
        bft_queue.pop();
        //checks if vertex has not been visited 
        if(find(bft_visited.begin(), bft_visited.end(), vertex)==bft_visited.end()) {
            bft_visited.push_back(vertex);
            bft_traversal.push_back(vertex);
            //push edge list of vertex to bft_queue
            for(auto i: adj_list[vertex]) {
                bft_queue.push(i.first);
            }
        }
    }
    return bft_traversal;
}

/* test11 */

template <typename T>
bool Graph<T>::contain_cycles() {
    //returns true/false if no. of edges is greater than (no. of vertices)-1
    return num_edges() > num_vertices()-1;
}

/* test12 */

template <typename T>
Graph<T> Graph<T>::minimum_spanning_tree() {
    //Prim's algorithm
    //initialises graph and adds first vertex of adj_list
    //pushes first vertex of adj_list to visited 
    Graph<T> mst;
    vector<string> visited;
    mst.add_vertex(adj_list.begin()->first);
    visited.push_back(adj_list.begin()->first);
    while (visited.size()< num_vertices()) {
        //initialises variables
        int minimum_weight= 99;
        pair<string,string> edge;
        //for-each vertex in visited
        for(auto i: visited) {
            //for-each edge in adj_list[vertex]
            for(auto j: adj_list[i]) {   
                //check edge vertex is not in visited and the edge weight is smaller than minimum weight
                if(count(visited.begin(), visited.end(), j.first)==0 && j.second<minimum_weight) {
                    //smallest edge weight stored in minimum_weight
                    minimum_weight= j.second;
                    //pair is created and stored in edge
                    //store i (vertex) and j.first(edge) with smallest weight into edge pair 
                    edge= make_pair(i,j.first);
                }
            }
        }
        //push edge in adj_list[vertex] to visited 
        visited.push_back(edge.second);
        //adds edges to minimum spanning tree (mst) with weight and adds vertex implicitly
        mst.add_edge(edge.first, edge.second, adj_list[edge.first][edge.second]);
    }
    return mst;
}
