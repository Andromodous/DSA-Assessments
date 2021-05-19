#include "tree.hpp"

int main(){

	BST<int> t;

    t.add_vertex("C", 5);
    t.add_vertex("A", 1);
    t.add_vertex("D", 3);
    t.add_vertex("H", 10);
    t.add_vertex("G", 20);
    t.add_vertex("F", 15);
    t.add_vertex("B", 30);
    t.add_vertex("E", 17);
    
    cout << t.num_vertices() << endl;
    cout << t.num_edges() << endl;
    cout << t.sum_weight() << endl;
    
    for(auto x : t.path("A", "H")){
        cout << x << " ";
    }
    cout << endl;
    for(auto x : t.path("D", "F")){
        cout << x << " ";
    }
    cout << endl;
    for(auto x : t.path("B", "H")){
        cout << x << " ";
    }
    cout << endl;
    //test-functions
    t.degree("F");
    t.adjacent("A", "C");
    cout << "no. of edges before removal are " << t.get_edges().size() << endl;
    for(auto i: t.get_edges()) {
        cout << "{" << i.first << ", " << i.second << "} ";
    }
    t.remove_vertex("G");
    cout << endl << "no. of edges are " << t.get_edges().size() << endl;
    for(auto i: t.get_edges()) {
        cout << "{" << i.first << ", " << i.second << "} " ;
    }
}
