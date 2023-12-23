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
 * Diese Methode wird dazu genutzt, per rekursivem Ansatz die Zeichen aus der
 * Eingabe zu decodieren. Mittels
 *   Tree* root = readTree();
 *   char c = decodeChar(root);
 * soll man beispielsweise das erste decodierte ASCII-Zeichen erhalten.
 * (Weitere Aufrufe "decodeChar(root)" liefern die jeweils nächsten Zeichen.)
 * Verwenden Sie "input >> b" (für "bool b") und ggf. einen rekursiven Aufruf
 * auf dem passenden Unterbaum.
 * Die Beschriftung eines Blattes "codingTree" ist "codingTree->letter".
 * 
 * Sie dürfen annehmen, dass die Eingabe (nach der gültigen Beschreibung eines
 * Codierungsbaumes) aus der Folge von codierten Zeichen besteht; nach dem
 * letzten codierten Zeichen ist die Eingabe zu Ende.
 * Wenn Sie vor jedem Aufruf "decodeChar(root)" mittels "if(input)" (oder in
 * einer großen Schleife mittels "while(input)") sicherstellen, dass es noch
 * mindestens ein zu decodierendes Zeichen in der Eingabe gibt, müssen Sie (bei
 * korrekter Implementierung) diesen Test in der Methode "decodeChar" selbst
 * deshalb nie verwenden.
 */
char decodeChar(Tree *codingTree) { // rekursiv
    /* TODO */
    bool b;
    if (codingTree->left == codingTree->right) {
        return codingTree->letter;
    }
    input >> b;
    if (b) {
        decodeChar(codingTree->right);
    } else {
        decodeChar(codingTree->left);
    }
}

/*
 * Diese Methode ist der Startpunkt für Ihre Implementierung. Lesen Sie den
 * "BitStream input" Stück für Stück aus und erzeugen Sie währenddessen die
 * in der Aufgabenstellung beschriebene gewünschte Ausgabe.
 * 
 * Verwenden Sie "readTree" zur Erzeugung des Codierungsbaums. Wenn
 * "if(input)" zutrifft, dann ist die Datei noch nicht zu Ende gelesen
 * und es kann mittels "decodeChar" das nächste Zeichen decodiert werden.
 * (Sie können auch eine Formulierung mit "while(input)" verwenden.)
 * 
 * Geben Sie die decodierten Zeichen direkt per "std::cout" aus.
 */
void run() {
    // Codierungsbaum einlesen
    Tree *codingTree = readTree();
    // codierten Eingabetext decodieren
    while (input) {
        std::cout << decodeChar(codingTree);
    }
    std::cout << std::endl;
    // Speicher des Codierungsbaums wieder freigeben
    delete codingTree;
}
