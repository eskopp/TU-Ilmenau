#include "decode.h"

/*
 * Diese Methode erzeugt den Codierungsbaum, dessen Beschreibung mit dem
 * nächsten einzulesenden Zeichen der Eingabedatei beginnt.
 * Es eignet sich ein rekursiver Ansatz, der "input >> b" (für "bool b") und
 * "input >> c" (für "char c") verwendet, wobei "readTree" jeweils rekursiv
 * zur Konstruktion der nicht-leeren Teilbäume aufgerufen wird.
 * 
 * Sie dürfen annehmen, dass die Eingabe mit einer gültigen Beschreibung
 * eines Codierungsbaumes beginnt. Daher müssen Sie (bei korrekter
 * Implementierung) niemals "if(input)" verwenden, da stets weitere
 * einzulesende Bits existieren.
 */
Tree *readTree() { // rekursiv
    /* TODO */
    bool b;
    char c;
    input >> b;
    Tree *T;
    if (b) {
        input >> c;
        T = new Tree(nullptr, c, nullptr);
    } else {
        T = new Tree(readTree(), '\000', readTree());
    }
    return T;
}

/*
 * Diese Methode ist der Startpunkt für Ihre Implementierung. Lesen Sie den
 * "BitStream input" Stück für Stück aus und erzeugen Sie währenddessen die
 * in der Aufgabenstellung beschriebene gewünschte Ausgabe.
 * 
 * Verwenden Sie "readTree" zur Erzeugung des Codierungsbaums.
 * Geben Sie ihn anschließend direkt per "std::cout" aus.
 */
void run() {
    // Codierungsbaum einlesen
    Tree *codingTree = readTree();
    // Codierungsbaum ausgeben
    std::cout << codingTree << std::endl;
    // Speicher des Codierungsbaums wieder freigeben
    delete codingTree;
}
