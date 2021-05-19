#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <limits>
#include <utility> 
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#include "Node.cpp"

using namespace std;

template <typename T> // the template allows the weight of vertex to take any numeric data type (denoted by T).
class BST {

	public:
        /* define your data structure to represent a binary search tree (bst) */
        Node<T>* root=nullptr;
        int vertexCount=0;
        vector<Node<T>*> nodes;
        vector<string> post_order_traversal;
        vector<string> pre_order_traversal;

        /* test1 */
		BST(); // the contructor function.
		~BST(); // the destructor function.
		size_t num_vertices(); // returns the total number of vertices in the bst.
		size_t num_edges(); // returns the total number of edges in the bst.
        T sum_weight(); // return the total weight of all the vertices in the bst.

        /* test2 */
        void add_vertex(const string&, const T&); // adds a vertex, which has a weight, to the tree -- every vertex uses a string as its unique identifier.
        bool contains(const string&); // checks if a vertex is in the bst -- returns true if the bst contains the given vertex; otherwise, returns false.
        void traverse_tree( Node<T>*, const Node<T>*);
        Node<T>* node_lookup(const string&);

        /* test3 */
        vector<string> get_vertices(); // returns a vector of all the vertices in the bst.
        vector<string> get_leaves(); // returns a vector of all the leaves in the bst.
                                     //     Leaves are the vertices that do not have any children in the bst.

        /* test4 */
        bool adjacent(const string&, const string&); // check if there is an edge between the two vertices in the bst -- returns true if the edge exists; otherwise, returns false.
		
        /* test5 */
        vector<pair<string,string>> get_edges(); // returns a vector of all the edges in the bst -- each edge is represented by a pair of vertices incident to the edge.
        
        /* test6 */
        vector<string> get_neighbours(const string&); // returns a vector of all the vertices, each of which is directly connected with the given vertex via an edge.
        size_t degree(const string&); // returns the degree of a vertex.

        /* test7 */
		vector<string> preorder_traversal(); // returns a vector of all the vertices in the visiting order of a preorder traversal over the bst.
        void traverse_preorder(Node<T>* current);
		
        /* test8 */
        vector<string> inorder_traversal(); // returns a vector of all the vertices in the visiting order of an inorder traversal over the bst.
        
        /* test9 */
        vector<string> postorder_traversal(); // returns a vector of all the vertices in the visiting order of a postorder traversal over the bst.
        void traverse_postorder(Node<T>* current);
        
        /* test10 */
        vector<string> breadth_first_traversal(); // returns a vector of all the vertices in the visiting order of a breadth first traversal over the bst.
		
        /* test11 */
        vector<string> path(const string&, const string&); // returns a vector of all the vertices in the path from the first vertex to the second vertex.
                                                            //     A path should include the source and destination vertices at the begining and the end, respectively.

        /* test12 */
        vector<string> path_with_largest_weight(); // returns a path that has the largest weight in the bst.
                                       //    The weight of a path is the sum of the weights of all the vertices (including the source and destination vertices) in the path.

        /* test13 */
        size_t height(); // returns the height of bst. Height of a tree is the number of edges that form the longest path from root to any leaf.

        /* test14 */
        void remove_leaf(const Node<T>* node);
        void remove_vertex_with_child(const Node<T>* node);
        void remove_vertex(const string&); // delete the given vertex from bst -- note that, all incident edges of the vertex should be deleted as well.
};

/* test1 */

template <typename T>
BST<T>::BST() {
    Node<T>* root=nullptr; 
    int vertexCount=0;
    vector<Node<T>*> nodes;
    vector<string> post_order_traversal;
    vector<string> pre_order_traversal;
}

template <typename T>
BST<T>::~BST() {
    delete root;
}


template <typename T>
size_t BST<T>::num_vertices() {
    return vertexCount;
}

template <typename T>
size_t BST<T>::num_edges() {
    return (num_vertices()==0) ? 0 : num_vertices()-1; //if the number of vertices is 0 is returns 0 edges to ensure that it is a positive no. of type size_t
}

template <typename T>
T BST<T>::sum_weight() {
    T total=0; //adds the weight variables and returns it 
    for(Node<T>* i: nodes) {
        total+=i->weight;
    }
    return total;
}

/* test2 */

template <typename T>
void BST<T>::traverse_tree(Node<T>* root, const Node<T>* vertex) {     //helper function for adding nodes to BST
    //traverses to position where child is empty and is bigger or smaller than the parent, occupies position in BST and pushes vertex to nodes vector
    T root_weight= root->weight;
    T vertex_weight= vertex->weight;
        if(root->left==nullptr && ( root_weight > vertex_weight)) {
            root->left= new Node<T>(vertex->vertex,vertex->weight);
            root->left->parent= root;
            nodes.push_back(root->left);
            return;
        }
        else if(root->right==nullptr && (root_weight <= vertex_weight)) {
            root->right= new Node<T>(vertex->vertex,vertex->weight);
            root->right->parent= root;
            nodes.push_back(root->right);
            return;
            }
        //uses recursion to iterate through the BST
    if((root_weight<= vertex_weight)) {
        traverse_tree(root->right,vertex);
    }
    else if ((root_weight > vertex_weight)) {
        traverse_tree(root->left,vertex);
    }
}

template <typename T>
void BST<T>::add_vertex(const string& u, const T& w) {
     if (root==nullptr) {
        root=new Node<T>(u, w);
        nodes.push_back(root);
        vertexCount++;
    }
    else {
        traverse_tree(root, new Node<T>(u,w));
        vertexCount++;
    }
}

template <typename T>
Node<T>* BST<T>::node_lookup(const string& u) {
    for(Node<T>* i: nodes) {     //helper function to look up and return node in BST
        if(u.compare(i->vertex)==0) {
            return i;
        }
    }
    return nullptr;
}

template <typename T>
bool BST<T>::contains(const string& u) {
    //checks whether u exists in nodes vector and returns bool, if both string are the same it should return 0
    for(Node<T>* i: nodes) {
        if(u.compare(i->vertex)==0) {
            return true;
        }
    }
    return false;
}

/* test3 */

template <typename T>
vector<string> BST<T>::get_vertices() {
   vector<string> vertices;
   for(Node<T>* i: nodes) {
       vertices.push_back(i->vertex);
   }
    return vertices;
}

template <typename T>
vector<string> BST<T>::get_leaves() {
    vector<string> leaves;
    for(Node<T>* i: nodes) { //add leaves when node has no children
        if(i->left==nullptr && i->right==nullptr) {
            leaves.push_back(i->vertex);
        }
    }
    return leaves;
}

/* test4 */

template <typename T>
bool BST<T>::adjacent(const string& u, const string& v) {
    vector<string> adjacent_neighbours= get_neighbours(u);
    return find(adjacent_neighbours.begin(), adjacent_neighbours.end(), v)!= adjacent_neighbours.end(); //return true if v is adjacent/neighbour of u
}

/* test5 */

template <typename T>
vector<pair<string,string>> BST<T>::get_edges() {
    //in BST a node doesnt need to check if a node has been visited since it traverses down a BST by checking whether a new left or right node exists
    vector<pair<string,string>> edges;
    for(Node<T>* i: nodes) {     //traverses in a depth first manner, if its child nodes are not null it pushes a edge into edges 
        if(i->left!=nullptr) {
            edges.push_back(make_pair(i->vertex, i->left->vertex));
        }
        if(i->right!=nullptr) {
            edges.push_back(make_pair(i->vertex, i->right->vertex));
        }
    }
    return edges;
}

/* test6 */

template <typename T>
vector<string> BST<T>::get_neighbours(const string& u) {
    vector<string> neighbours;     //for root case, checks if parent node is not null then pushes to neighbours, if children exist they are added to neighbours 
    if(node_lookup(u)->parent!=nullptr) { //node_lookup(u) returns the correct node in BST
        neighbours.push_back(node_lookup(u)->parent->vertex);
    }
    if(node_lookup(u)->left!=nullptr) {
        neighbours.push_back(node_lookup(u)->left->vertex);
    }
    if(node_lookup(u)->right!=nullptr) {
        neighbours.push_back(node_lookup(u)->right->vertex);
    }
    return neighbours;
}

template <typename T>
size_t BST<T>::degree(const string& u) {
    int degree=0;
    //for root cases, checks if parent is exists then increment degree++, if children exist degree is incremented 
    if(node_lookup(u)->parent!=nullptr) {
        degree++;
    }
    if (node_lookup(u)->left!=nullptr) {
        degree++;
    }
    if (node_lookup(u)->right!=nullptr) {
        degree++;
    }
    return degree;
}

/* test7 */

template <typename T>
void BST<T>::traverse_preorder(Node<T>* current) { //helper function used to recurse in a pre-order traversal
    if(current==nullptr) { //if current node does not exist, return/break recursion
        return;
    }
    pre_order_traversal.push_back(current->vertex); // push current vertex into pre_order_traversal vector
    traverse_preorder(current->left); //traverse left sub-tree
    traverse_preorder(current->right); //traverse right sub-tree
}

template <typename T>
vector<string> BST<T>::preorder_traversal() {  //uses traverse_preorder() function to traverse and returns the final pre_order_traversal vector
    traverse_preorder(root);
    return pre_order_traversal;
}

/* test8 */

template <typename T>
vector<string> BST<T>::inorder_traversal() {
    //visits left sub-tree, if it cannot find a left child pushes vertex to inorder_traversal, traverses and pushes root then visits the right subtree
    vector<string> inorder_traversal;
    stack<Node<T>*> inorder_stack;
    Node<T>* current= root;
    while(current!=nullptr || !inorder_stack.empty()) {
        if(current!=nullptr) {
            inorder_stack.push(current); //push the current node into the inorder_stack
            current= current->left; // visit left sub-tree
        }
        else {
            current= inorder_stack.top(); //store the node at top of inorder_stack into current 
            inorder_stack.pop();
            inorder_traversal.push_back(current->vertex); //push current vertex into inorder_traversal
            current= current->right; //visit right sub-tree
        }
    }
    return inorder_traversal;
}

/* test9 */

template <typename T>
void BST<T>::traverse_postorder(Node<T>* current) {  //helper function used to recurse in a post-order traversal
    if(current==nullptr) { //if current node does not exist, return/break recursion
        return;
    }
    traverse_postorder(current->left); //traverse left sub-tree 
    traverse_postorder(current->right); //traverse right sub-tree
    post_order_traversal.push_back(current->vertex); // push current vertex into post_order_traversal vector
}

template <typename T>
vector<string> BST<T>::postorder_traversal() { //uses traverse_postorder() function to traverse and returns the final post_order_traversal vector
    traverse_postorder(root);
    return post_order_traversal;
}

/* test10 */

template <typename T>
vector<string> BST<T>::breadth_first_traversal() {
    //checks left and right children, if they exist they are pushed to bft_queue, then traverses BST horizontally and vertically 
    vector<string> bft_traversal;
    queue<Node<T>*> bft_queue;  //uses a bft_queue to push current vertex and retrive it from the front of queue 
    bft_queue.push(root); //pushes root to bft_queue
    while(!bft_queue.empty()) {
        Node<T>* current= bft_queue.front(); //retrieve node from beginning of bft_queue
        bft_queue.pop();
        bft_traversal.push_back(current->vertex);
        if(current->left!=nullptr) { //if left child of current node exists push to bft_queue 
            bft_queue.push(current->left);
        } 
        if(current->right!=nullptr) { //if right child of current node exists push to bft_queue
            bft_queue.push(current->right);
        }
    }
    return bft_traversal;
}

/* test11 */

template <typename T>
vector<string> BST<T>::path(const string& u, const string& v){
    vector<string> path;
    vector<Node<T>*> visited;
    Node<T>* current= node_lookup(u);
    Node<T>* target= node_lookup(v);
    path.push_back(current->vertex);
    visited.push_back(current);
    while(v.compare(current->vertex)!=0) { //while (the current vertex is not the target (target: node at end of path))
        //checks if the left child exists and current vertex weight is larger than target weight and checks that it has not been visited 
        if(current->left!=nullptr && (current->weight > target->weight) && current->parent!=target && find(visited.begin(), visited.end(), current->left)==visited.end()) {
            visited.push_back(current->left);
            path.push_back(current->left->vertex);
            current= current->left;
        }
        //checks if the right child exists and current vertex weight is smaller or equal to target weight and checks that it has not been visited 
        else if(current->right!=nullptr && (current->weight <= target->weight) && current->parent!=target && find(visited.begin(), visited.end(), current->right)==visited.end()) {
            visited.push_back(current->right);
            path.push_back(current->right->vertex);
            current= current->right;
        }
        else {   //visit parent node
            visited.push_back(current->parent);
            path.push_back(current->parent->vertex);
            current= current->parent;
        }
    }
    for(int i=0; i<path.size(); i++) { //removes unnecessary loops in the path e.g. A D A C H -> A C H
        if(count(path.begin(),path.end(),path[i])>1) { //checks if there are duplicate vertices in path
            path.erase(path.begin()+i);
            path.erase(path.begin()+i);
            break;
        }
    }
    return path;
}

/* test12 */

template <typename T>
vector<string> BST<T>::path_with_largest_weight(){
    return vector<string>();
}

/* test13 */

template <typename T>
size_t BST<T>::height() {
    return 0;
}

/* test14 */

template <typename T>
void BST<T>::remove_leaf(const Node<T>* node) {     //helper function to remove a vertex that is a leaf
    if(node->parent->left==node) { //check if the node is occupied in parent's left position 
        node->parent->left= nullptr; //points parent left position to nullptr
        remove(nodes.begin(), nodes.end(), node); //removes the vertex  from nodes list
    }
    else if(node->parent->right==node) { //check if node is occupied in parent's right position
        node->parent->right= nullptr; //points parent right position to nullptr
        remove(nodes.begin(), nodes.end(), node); //removes the vertex from nodes list
    }
}

template <typename T>
void BST<T>::remove_vertex_with_child(const Node<T>* node) {    //helper function to remove a vertex that has atleast one child 
    Node<T>* child= (node->right!=nullptr) ? node->right : node->left; //use ternary operator to find which child exists and store in child variable
    if(node->parent->left==node) {      //check if the node is occupied in parent's left position 
        node->parent->left= child;     //point parent left position to child of node
        remove(nodes.begin(), nodes.end(), node);   //remove node from nodes list
    }
    else if(node->parent->right==node) {  //check if the node is occupied in parent's right position 
        node->parent->right= child;      //point parent left position to child of node
        remove(nodes.begin(), nodes.end(), node);  //remove node from nodes list
    }
}

template <typename T>
void BST<T>::remove_vertex(const string& u) {
    Node<T>* node= node_lookup(u); //find vertex and store in node variable 
    if(node->left==nullptr && node->right==nullptr) { //remove leaf nodes
        remove_leaf(node);  //use helper function to remove leaf
    }
    else if(node->left!=nullptr && node->right!=nullptr) { //remove node where both children exist
        if(root!=node) { //for cases where both children exist and it is not the root node
            Node<T>* tmp= node->right; //store in tmp variable
            if(node->parent->right==node) {
                node->right->parent= node->parent;
                node->parent->right=tmp;
                tmp->left=node->left;
                tmp->right=nullptr; 
                remove(nodes.begin(), nodes.end(), node); //remove vertex (node) from nodes list
            } 
            else if(node->parent->left==node) {
                node->left->parent= node->parent;
                node->parent->left=tmp;
                tmp->left=node->left;
                tmp->right=nullptr;
                remove(nodes.begin(), nodes.end(), node); //remove vertex (node) from nodes list
            }
        }
        else { //for root cases ,where both children exist and vertex has no parents
            Node<T>* right_node= root->left;  //right_node visits left sub-tree
            while(right_node->right!=nullptr) { //loop stores the right most node in left subtree in variable right_node
		        right_node=right_node->right;
	        }
            //exchange values with node and rightmost_node
            string vertex= node->vertex; //store vertex and weight into variables 
            T weight= node->weight;
            node->vertex=right_node->vertex; //change string (vertex) values  
            node->weight=right_node->weight; //change T (weight) values
            right_node->vertex= vertex;     //right most node in left sub-tree is changed with values from node 
            right_node->weight= weight;     //right_most node now holds root (node) // original node (root) holds right most node in left sub-tree  
            if(right_node->left==nullptr && right_node->right==nullptr) { //remove right_node if it is a leaf
                remove_leaf(right_node);
            }
            else if(right_node->left!=nullptr || right_node->right!=nullptr) { //remove right_node where a child exists
            remove_vertex_with_child(right_node);
        
            }
        }       
    }
    else if(node->left!=nullptr || node->right!=nullptr) { //remove node when either child exists
        remove_vertex_with_child(node);     //use helper function to remove node with atleast one child
    }
}
