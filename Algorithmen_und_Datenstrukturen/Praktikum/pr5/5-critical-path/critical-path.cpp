#include "dfs.h"

/*****************************************************
* Definition/Implementierung der Callback-Funktionen
*****************************************************/

/* zusätzliche Variablen und Datenstrukturen */
/* TODO */
int max;
std::vector<int> stack;
std::vector<unsigned long long> costs;

/* Aktionen direkt vor DFS() */
void preDFS() {
    /* TODO */
    max = 0;
    stack.resize(0);
    costs.resize(0);
    costs.resize(n, {0});
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

void rec_path(int node) {
    std::cout << " " << node;
    for (int neighbour: G[node]) {
        if (costs[node] - 1 == costs[neighbour]) {
            rec_path(neighbour);
            break;
        }
    }
}

/* Aktionen direkt nach DFS() */
void postDFS() {
    /* TODO */
    if (!B.size()) {
        for (int node: stack) {
            for (int neighbour: G[node]) {
                if (costs[node] < costs[neighbour]) {
                    costs[node] = costs[neighbour];
                }
            }
            if (++costs[node] > costs[max]) { max = node; }
        }
        std::cout << costs[max] << ":";
        rec_path(max);
        std::cout << std::endl;
    } else {
        std::cout << "-" << std::endl;
    }
}
