#include "dfs.h"

/*****************************************************
* Definition/Implementierung der Callback-Funktionen
*****************************************************/

/* zusätzliche Variablen und Datenstrukturen */
/* TODO */
int level;
bool flag;

/* Aktionen direkt vor DFS() */
void preDFS() {
    /* TODO */
    level = 0;
    flag = true;
}

/* Präorder-Aktionen an Knoten v bei Entdeckung */
void dfsVisit(const int v) {
    /* TODO */
    if (flag && !level) {
        std::cout << v;
        ++level;
    } else if (flag && level) {
        std::cout << " " << v;
        ++level;
    }

}

/* Postorder-Aktionen an Knoten v bei Abschluss */
void finVisit(const int v) {
    /* TODO */
    if (!--level) {
        flag = false;
    }
}

/* Aktionen direkt nach DFS() */
void postDFS() {
    /* TODO */
    std::cout << std::endl;
}
