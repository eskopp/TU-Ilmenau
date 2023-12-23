#include "dfs.h"

/*****************************************************
* Definition/Implementierung der Callback-Funktionen
*****************************************************/

/* zusätzliche Variablen und Datenstrukturen */
/* TODO */
std::vector<int> stack;
std::vector<unsigned long long> costs;
int end_node;

/* Aktionen direkt vor DFS() */
void preDFS() {
    /* TODO */
    stack.resize(0);
    end_node = n - 1;
    costs.resize(0);
    costs.resize(n, 0);
}

/* Präorder-Aktionen an Knoten v bei Entdeckung */
void dfsVisit(const int v) {
    /* TODO */
}

/* Postorder-Aktionen an Knoten v bei Abschluss */
void finVisit(const int v) {
    /* TODO */
    stack.push_back(v);
}

/* Aktionen direkt nach DFS() */
void postDFS() {
    /* TODO */
    if (!B.size()) {
        for (int node: stack) {
            if (node == end_node) {
                costs[node] = 1;
            } else {
                for (int neighbour: G[node]) {
                    costs[node] += costs[neighbour];
                }
            }
            if (!node) { break; }
        }
        std::cout << costs[0] << std::endl;
    } else {
        std::cout << "-" << std::endl;
    }
}
