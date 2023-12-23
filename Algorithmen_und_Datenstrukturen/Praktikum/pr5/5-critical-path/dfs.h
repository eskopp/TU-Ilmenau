
#ifndef __DFS_H_INCLUDED__
#define __DFS_H_INCLUDED__

#include <iostream>
#include <vector>
#include <utility>

/*****************************************************
* Folgende Variablen werden von der vorgegebenen
* DFS-Implementierung initialisiert.
* Greifen Sie auf diese Informationen zu,
* wenn es ihnen nützlich erscheint.
*****************************************************/

int n, m;                                   // Anzahl Knoten und Kanten
std::vector <std::vector<int>> G;            // Digraph (Adjazenzlisten-Darstellung)
std::vector<int> dfsNum, fNum;              // dfsNum[v] ∈ {0,…,n-1} ist dfs-Nummer von v ∈ {0,…,n-1}
std::vector <std::pair<int, int>> T, B, F, C; // klassifizierte Kanten

/*****************************************************
* ↑↑↑ Datenstrukturen für DFS           ↑↑↑
* ↓↓↓ Callback-Funktionen (Deklaration) ↓↓↓
*****************************************************/

void preDFS();              // Aktionen direkt vor DFS()
void dfsVisit(const int v); // Präorder-Aktionen an Knoten v bei Entdeckung
void finVisit(const int v); // Postorder-Aktionen an Knoten v bei Abschluss
void postDFS();             // Aktionen direkt nach DFS()

/*****************************************************
* ↑↑↑ Callback-Funktionen (Deklaration) ↑↑↑
* ↓↓↓ vorimplementierte DFS             ↓↓↓
*****************************************************/

int dfsCount, fCount; // nächste freie dfs/f-Nummer

/* lokale Tiefensuche in neuem Knoten v */
void dfs(const int v) {
    // Präorder-Aktionen an Knoten v bei Entdeckung
    dfsNum[v] = dfsCount++;
    dfsVisit(v);
    // untersuche alle aus v ausgehenden Kanten
    // G[v] enthält alle direkten Nachfolger von v
    for (int w: G[v]) {
        if (dfsNum[w] == -1) {
            T.push_back({v, w});
            dfs(w);
        } else if (fNum[w] == -1) {
            B.push_back({v, w});
        } else if (dfsNum[v] < dfsNum[w]) {
            F.push_back({v, w});
        } else {
            C.push_back({v, w});
        }
    }
    // Postorder-Aktionen an Knoten v bei Abschluss
    fNum[v] = fCount++;
    finVisit(v);
}

/* globale Tiefensuche im Digraphen G */
void DFS() {
    // Initialisierung
    dfsNum = fNum = std::vector<int>(n, -1);
    dfsCount = fCount = 0;
    T = B = F = C = {};
    // globale Schleife der vollen Tiefensuche
    for (int v = 0; v < n; ++v) {
        if (dfsNum[v] == -1) {
            dfs(v); // lokale Tiefensuche in neuem Knoten v
        }
    }
}

/* main-Methode */
int main() {
    while (std::cin >> n) {
        // erzeuge den Digraphen G
        std::cin >> m;
        G.clear();
        G.resize(n, {});
        for (int i = 0; i < m; ++i) {
            char _;
            int u;
            int w;
            std::cin >> _ >> u >> _ >> w >> _;
            G[u].push_back(w);
        }
        // globale Tiefensuche in G + Callback-Funktionalität
        preDFS();
        DFS();
        postDFS();
    }
}

#endif // __DFS_H_INCLUDED__