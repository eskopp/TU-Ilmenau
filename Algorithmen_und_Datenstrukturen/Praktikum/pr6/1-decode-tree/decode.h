////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// DECODE ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef __DECODE_H_INCLUDED__
#define __DECODE_H_INCLUDED__

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////
//////////////////// Zum Lesen der Eingabe mittels "input" /////////////////////
////////////////////////////////////////////////////////////////////////////////

const std::size_t logN = 7; // Bits pro ASCII-Zeichen

/*
 * Erlaubt das Lesen der Eingabe in Form eines Bitstroms "input". Verwendung:
 *  - "if(input)":
 *      Der Test liefert genau
 *      dann "true", wenn noch nicht alle Bits des
 *      Bitstroms gelesen wurden.
 *  - "input >> b" für "bool b":
 *      Liest das nächste Bit aus der Eingabe und speichert es in einer
 *      bool-Variablen b.
 *  - "input >> c" für "char c":
 *      Liest die nächsten "logN = 7" Bits aus der Eingabe und speichert das
 *      entsprechende ASCII-Zeichen in einer char-Variablen c.
 */
class BitStream {
private:
    std::vector<bool> bits;
    std::size_t size;
    std::size_t next;
public:
    BitStream(const std::string &s) : size(s.length()), next(0) {
        bits.reserve(s.length());
        for (auto c: s) {
            bits.push_back(c == '1' ? 1 : 0);
        }
    }

    explicit operator bool() const {
        return (next < size);
    }

    friend BitStream &operator>>(BitStream &s, bool &b) {
        b = (s.next < s.size ? s.bits[s.next++] : 0);
        return s;
    }

    friend BitStream &operator>>(BitStream &s, char &c) {
        c = 0;
        if (s.next + (logN - 1) < s.size) {
            for (std::size_t i = 0; i < logN; ++i) {
                c <<= 1;
                c |= s.bits[s.next++];
            }
        }
        return s;
    }
};

BitStream input{""};

////////////////////////////////////////////////////////////////////////////////
//////////////// Repräsentation des Codierungsbaums als "Tree" /////////////////
////////////////////////////////////////////////////////////////////////////////

/*
 * Verwendung wie gewohnt, z.B.:
 *   Tree* t = new Tree{ nullptr, 0, nullptr };
 *   t->left = new Tree{ nullptr, 'a', nullptr };
 *   std::cout << t->letter << std::endl;
 *   delete t; t = nullptr;
 */
int livingTrees = 0;

struct Tree {
    Tree *left;
    char letter;
    Tree *right;

    Tree(Tree *l, char c, Tree *r) : left(l), letter(c), right(r) {
        ++livingTrees;
    }

    ~Tree() {
        delete left;
        delete right;
        --livingTrees;
    }
};

/*
 * Für die Ausgabe Ihres konstruierten Codierungsbaums in Klammerschreibweise.
 * Verwendung: Tree* T = ...; ...; std::cout << T << std::endl;
 */
std::ostream &operator<<(std::ostream &out, const Tree *T) {
    if (!T)
        return out;
    else if (!T->left && !T->right)
        return out << T->letter;
    else if (T->left && T->right)
        return out << "(" << T->left << "," << T->right << ")";
    else
        return out << "Fehler: Innerer Knoten mit nur einem Kind entdeckt.";
}

////////////////////////////////////////////////////////////////////////////////
///////////////////// main-Methode mit Aufruf von "run()" //////////////////////
////////////////////////////////////////////////////////////////////////////////

/*
 * Diese Methode ist der Startpunkt für Ihre Implementierung in "decode.cpp".
 */
void run();

/*
 * Liest die Eingabe komplett ein und erzeugt daraus einen "BitStream input",
 * den Sie in der Methode "run" auslesen und mit diesem arbeiten können.
 */
int main() {
    std::string s;
    std::cin >> s;
    input = {s};
    run();
    assert(livingTrees == 0);
}

#endif // __DECODE_H_INCLUDED__