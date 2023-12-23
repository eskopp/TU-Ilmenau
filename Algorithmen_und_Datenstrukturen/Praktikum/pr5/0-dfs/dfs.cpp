#include "dfs.h"

/*****************************************************
* Definition/Implementierung der Callback-Funktionen
*****************************************************/

/* zusätzliche Variablen und Datenstrukturen */
int level;

/* Aktionen direkt vor DFS() */
void preDFS() {
    std::cout << "n = " << n << ", m = " << m << std::endl;
    level = -1;
    std::cout << "(node,level):";
}

/* Präorder-Aktionen an Knoten v bei Entdeckung */
void dfsVisit(const int v) {
    std::cout << " (" << v << "," << ++level << ")";
}

/* Postorder-Aktionen an Knoten v bei Abschluss */
void finVisit(const int v) {
    --level;
}

/* Aktionen direkt nach DFS() */
void postDFS() {
    std::cout << std::endl << "dfsNum:";
    for (int i: dfsNum) std::cout << " " << i;
    std::cout << std::endl << "fNum:";
    for (int i: fNum) std::cout << " " << i;
    std::cout << std::endl << "T:";
    for (auto &e: T) std::cout << " (" << e.first << "," << e.second << ")";
    std::cout << std::endl << "B:";
    for (auto &e: B) std::cout << " (" << e.first << "," << e.second << ")";
    std::cout << std::endl << "F:";
    for (auto &e: F) std::cout << " (" << e.first << "," << e.second << ")";
    std::cout << std::endl << "C:";
    for (auto &e: C) std::cout << " (" << e.first << "," << e.second << ")";
    std::cout << std::endl;
}
