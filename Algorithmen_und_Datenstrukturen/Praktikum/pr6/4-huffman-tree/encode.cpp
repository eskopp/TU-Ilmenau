#include "encode.h"

/*
 * Die nachfolgenden Variablen/Datenstrukturen könnten für Sie nützlich sein.
 * - "n" ist die Anzahl unterschiedlicher ASCII-Zeichen in der Eingabe.
 *   Für 0 <= i < n ist "label[i]" das i-te tatsächlich vorkommende ASCII-
 *   Zeichen. Dieses kommt "p[i]" mal in der Eingabe vor.
 *   Die tatsächlich vorkommenden ASCII-Zeichen sind dabei wie gewünscht
 *   angeordnet:
 *     p[0] <= p[1] <= p[2] <= ... <= p[n-1]
 *   und
 *     wenn p[i] = p[i+1], dann label[i] < label[i+1].
 * - "labelIndex" ist die Umkehrung von "label", d.h. für ein in der Eingabe
 *   vorkommendes ASCII-Zeichen c gilt "label[labelIndex[c]] == c" und es kommt
 *   "p[labelIndex[c]]" mal in der Eingabe vor.
 * - "pred" und "mark" sind die Ausgaben des Huffman-Algorithmus.
 *   Sie enthalten "nodes" viele Einträge - die Anzahl Knoten des zugehörigen
 *   optimalen Codierungsbaums.
 */
// Folgendes können Sie mittels "input.countChars(n, labelIndex, label, p)"
// bestimmen lassen:
unsigned int n;                     // Anzahl verschiedener ASCII-Zeichen in der Eingabe = Anzahl Blätter
std::vector<int> labelIndex;        // labelIndex[c] = Index des Blattes mit Beschriftung (ASCII-Zeichen) c
std::vector<char> label;            // label[i] = Beschriftung (ASCII-Zeichen) des Blattes mit Index i
std::vector<unsigned int> p;        // p[i] = absolute Häufigkeiten (>0) des ASCII-Zeichens des Blattes mit Index i
// Folgendes müssen Sie manuell bestimmen:
unsigned int nodes;                 // Anzahl Knoten (des Huffman-Baums)
std::vector<unsigned int> pred;     // Vorgänger-Array
std::vector<bool> mark;             // Markierungs-Array: false = 0 = links, true = 1 = rechts

/*
 * Implementieren Sie den Algorithmus von Huffman aus der Vorlesung.
 * 
 * Verwenden Sie n, labelIndex, label und p als (global gegebene) Eingabe.
 * Bestimmen Sie nodes, pred und mark als (global verfügbare) Ausgabe.
 * 
 * Hinweise:
 * - Achten Sie darauf, dass die Indizierung in C++ bei 0 beginnt,
 *   in den Vorlesungsfolien hingegen bei 1.
 * - Vergessen Sie nicht, die Größe von p (mittels "p.resize(nodes)",
 *    wenn Sie "nodes" zuvor passend bestimmt haben) anzupassen,
 *    damit Sie die Häufigkeiten der Kunstbuchstaben zwischenspeichern können.
 * - Wenn Sie die Häufigkeiten in p mittels input.countChars(...) bestimmt haben
 *   und sich treu an den Pseudocode aus der Vorlesung halten, erreichen Sie das
 *   folgende erwünschte Verhalten automatisch:
 *     Immer dann, wenn (Kunst-)Buchstaben die gleiche Häufigkeit haben, soll
 *     zunächst derjenige (Kunst-)Buchstabe mit kleinstem Index gewählt werden,
 *     d.h., der in den Tabellen p/pred/mark am weitesten vorne/links steht.
 */
void huffman() {
    /* TODO */
}

/*
 * Um den Codierungsbaum ausgeben zu können, muss dieser zunächst mehr oder
 * weniger konkret berechnet werden. Eine Möglichkeit ist die Berechnung der
 * aus der Vorlesung bekannten Arrays "leaf" und "inner".
 * Auf ähnliche Weise kann man sich auch einen Baum wie bei der Decodierung
 * berechnen, indem man mit "nodes" vielen "leeren Knoten" startet
 *   vector<Tree*> treeNodes(nodes, nullptr);
 * anschließend die Blätter mit passenden Beschriftungen an Positionen 0 bis
 * n-1 und innere Knoten an Positionen n bis nodes-1 erzeugt und schließlich
 * "mark" und "pred" nutzt, um die Zeiger von Vater- zu Kindknoten zu ergänzen.
 * treeNodes[nodes-1] ist dann ein Zeiger auf die Wurzel des Codierungsbaums.
 */
Tree *computeTree() { // iterativ
    /* TODO */
}

/*
 * Nutzen Sie "output << b" (für "bool b") und "output << c" (für "char c"),
 * um den Baum, auf dessen Wurzel der Zeiger "codingTree" zeigt, in Präorder-
 * Reihenfolge gemäß der vereinbarten Codierung auszugeben.
 * Ein rekursiver Ansatz ist besonders einfach.
 */
void writeTree(Tree *codingTree) { // rekursiv
    /* TODO */
}

/*
 * Diese Methode ist der Startpunkt für Ihre Implementierung. Lesen Sie den
 * "ASCIIStream input" Stück für Stück aus und erzeugen Sie währenddessen die
 * in der Aufgabenstellung beschriebene gewünschte Ausgabe.
 * 
 * Verwenden Sie dazu zunächst "input.countChars(...)" und Ihre
 * Implementierungen von "huffman()" und "computeTree()".
 * Der erste Teil der Ausgabe des Codierungsbaums "Tree* t" erfolgt dann
 * einfach per "std::cout << t << std::endl", der zweite Teil durch
 * "writeTree(t)".
 */
void run() {
    // zähle ASCII-Zeichen, berechne "n", "labelIndex", "label", "p"
    input.countChars(n, labelIndex, label, p);
    // berechne "nodes", pred", "mark" (Huffman-Algorithmus)
    huffman();
    // berechne Codierungsbaum (als Tree*) und gib diesen (zweimal) aus
    Tree *codingTree = computeTree();
    std::cout << codingTree << std::endl;
    writeTree(codingTree);
    std::cout << std::endl;
    delete codingTree;
    codingTree = nullptr;
}