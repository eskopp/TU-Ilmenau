#include "dfs.h"
#include <vector>

/*****************************************************
* Definition/Implementierung der Callback-Funktionen
*****************************************************/

/* zusätzliche Variablen und Datenstrukturen */
/* TODO */
std::vector<int> stack;

/* Aktionen direkt vor DFS() */
void preDFS() {
    /* TODO */
    stack.resize(0);
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
    if(!B.size()){
        for(int i = stack.size()-1; 0 < i; --i){
            std::cout <<stack[i] << " ";
        }
        std::cout << stack[0] << std::endl;
    }
    else{
        std::cout << "-" << std::endl;
    }
}
