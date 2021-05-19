#include <iostream>
using namespace std;

template <typename T>
class Node {
    public:
    T weight;
    string vertex;
    Node<T>* left=nullptr;
    Node<T>* right=nullptr;
    Node<T>* parent=nullptr;
    Node<T>(string vertex, T weight) {
        this->vertex=vertex;
        this->weight=weight;
    }
};
