#include "dfs.h"

/*****************************************************
* Definition/Implementierung der Callback-Funktionen
*****************************************************/

/* zusätzliche Variablen und Datenstrukturen */
/* TODO */
int level;
int trees;

/* Aktionen direkt vor DFS() */
void preDFS() {
    /* TODO */
    level = 0;
    trees = 0;
}

/* Präorder-Aktionen an Knoten v bei Entdeckung */
void dfsVisit(const int v) {
    /* TODO */
    if (!level++) { ++trees; }
    std::cout << v << "(";
}

/* Postorder-Aktionen an Knoten v bei Abschluss */
void finVisit(const int v) {
    /* TODO */
    if (!--level) {
        std::cout << ")" << " ";
    } else {
        std::cout << ")";
    }
}

/* Aktionen direkt nach DFS() */
void postDFS() {
    /* TODO */
    std::cout << ": " << trees << std::endl;
}
