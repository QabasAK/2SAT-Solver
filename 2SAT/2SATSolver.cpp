#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>
using namespace std;

// defining CNFs
using Clause = vector<int>;
using Formula = vector<Clause>; 

// implication graph with vertices = 2 * variables
unordered_map <int,vector<int>*> graph;
int vars = 0;

// necessary data structures for SCC & DFS
int id = 0;
unordered_map<int, int> ids;
unordered_map<int, int> low;

// if node currently being explored in the DFS, it might 
        // belong to the same SCC
// once popped, a node wont be considered for other SCC
unordered_map<int, bool> inStack;
stack<int> s;


// hypothesis --> conclusion 
// a or b = -a -> b 
//        = -b -> a
void implicationGraph(Formula &formula) {

    // max literal 
    for (const auto &clause : formula){
        for (int literal : clause){
            vars = max (vars, abs(literal));
        }
    }

    // creating vertices 
    for (int i = 1; i <= vars; i++) {
        if (graph.find(i) == graph.end()) graph[i] = new vector<int>();
        if (graph.find(-i) == graph.end()) graph[-i] = new vector<int>();
    }

    //creating edges 
    for (const auto &clause : formula) {
        int hypothesis = clause[0];
        int conclusion = clause[1];
        graph[-hypothesis]->push_back(conclusion);
        graph[-conclusion]->push_back(hypothesis);
    }
}

// to find strongly connected components with Tarjan's Algorithm 
void DFS(int source) {
    s.push(source);
    inStack[source] = true;
    ids[source] = id;
    low[source] = id;
    id++;
    
    if (graph.find(source) != graph.end()){
        for (int v : *graph[source]) {
            // if unvisited, DFS 
            if (ids.find(v) == ids.end() || ids[v] == -1)
                DFS(v);
            // smallest ID reachable from source to identify 
            // root node in SCC
            if (inStack[v])
                low[source] = min(low[source], low[v]);
        }
    }
    
    // remove from the stack to avoid revisiting 
    if (ids[source] == low[source]) {
        while (!s.empty()) {
            int node = s.top();
            s.pop();
    
            inStack[node] = false;
            low[node] = ids[source];
            if (node == source)
                break;
        }
    }

}

// O(V + E)
void SCC(){
    for (int i = 1; i <= vars; i++){
        ids[i] = -1;
        ids[-i] = -1;
        inStack[i] = false;
        inStack[-i] = false;
    }

    for (int i = 1; i <= vars; i++) {
        if (ids[i] == -1) DFS(i);
        if (ids[-i] == -1) DFS(-i);
    }
}

// for memory allocation 
void cleanUp() {
    for (auto & entry : graph)
        delete entry.second;
    graph.clear();
}

// if a variable and its negation are in the same SCC : UNSAT
bool twoSAT() {    
    SCC();
    for (int i = 1; i <= vars; i++){
        if (low[i] == low[-i]){
            cleanUp();
            return false;
        }
    }

    cleanUp();
    return true;
}

int main() {
    Formula formula = {
        {1, 2},
        {-3, 1},
        {-4, -3},
        {2, 5},
        {5, -2},
        {1, 4}
    };

    implicationGraph(formula);
    
    if (twoSAT())
        cout << "SAT <3\n";
    else 
        cout << "UNSAT :(\n";

    return 0;
}