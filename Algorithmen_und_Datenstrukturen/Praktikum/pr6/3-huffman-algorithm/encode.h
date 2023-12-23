////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ENCODE ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef __ENCODE_H_INCLUDED__
#define __ENCODE_H_INCLUDED__

#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <functional>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////
//////////////////// Zum Lesen der Eingabe mittels "input" /////////////////////
////////////////////////////////////////////////////////////////////////////////

const std::size_t logN = 7;        // Bits pro ASCII-Zeichen
const std::size_t N = (1 << logN); // Größe des ASCII-Alphabets

/*
 * Erlaubt das Lesen der Eingabe in Form eines ASCII-Zeichen-Stroms "input".
 * Verwendung:
 *  - "if(input)":
 *      Der Test liefert genau dann "true", wenn noch nicht alle ASCII-Zeichen
 *      des ASCII-Zeichen-Stroms gelesen wurden.
 *  - "char c; input >> c;":
 *      Liest das nächste ASCII-Zeichen aus der Eingabe und speichert es in
 *      einer char-Variablen c.
 *  - "input.countChars(...)":
 *      Zählt die ASCII-Zeichen in der gesamten Eingabe und liefert die
 *      Ergebnisse per Referenz über die Eingabeparameter.
 */
class ASCIIStream {
private:
    std::vector<char> letters;
    std::size_t size;
    std::size_t next;
public:
    ASCIIStream(bool read = true) : next(0) {
        if (read) {
            char c;
            while (std::cin.get(c).good()) {
                if (c == '\n') break;
                letters.push_back(c);
            }
            size = letters.size();
        }
    }

    explicit operator bool() const {
        return (next <= size);
    }

    friend ASCIIStream &operator>>(ASCIIStream &s, char &c) {
        c = (s.next < s.size ? s.letters[s.next] : 0);
        ++s.next;
        return s;
    }

    /*
     * Verwendung:
     *   unsigned int n;                        // Anzahl verschiedener ASCII-Zeichen in der Eingabe = Anzahl Blätter
     *   std::vector<unsigned int> labelIndex;  // labelIndex[c] = Index des Blattes mit Beschriftung (ASCII-Zeichen) c
     *   std::vector<char> label;               // label[i] = Beschriftung (ASCII-Zeichen) des Blattes mit Index i
     *   std::vector<unsigned int> p;           // p[i] = absolute Häufigkeiten (>0) des ASCII-Zeichens des Blattes mit Index i
     *   input.countChars(n, labelIndex, label, p);
     * 
     * Die Methode verarbeitet die komplette Eingabe und zählt dabei die Anzahl
     * der vorkommenden ASCII-Zeichen. Nach dem Aufruf gilt:
     *   n ist die Anzahl unterschiedlicher gelesener ASCII-Zeichen, also
     *   derjenigen ASCII-Zeichen, die tatsächlich in der Eingabe vorkommen.
     *   Für 0 <= i < n gilt:
     *     label[i] ist das i-te vorkommende ASCII-Zeichen.
     *     Es kommt genau p[i] mal in der Eingabe vor.
     *   Kommt ein ASCII-Zeichen c in der Eingabe vor, so gibt labelIndex[c] den
     *   Index dieses Zeichens in den anderen beiden Arrays an, d. h.:
     *     label[labelIndex[c]] == c und
     *     c kommt p[labelIndex[c]] mal in der Eingabe vor.
     *   Andernfalls ist labelIndex[c] == -1.
     * 
     * Die tatsächlich vorkommenden ASCII-Zeichen sind dabei wie gewünscht
     * angeordnet:
     *   p[0] <= p[1] <= p[2] <= ... <= p[n-1]
     * und
     *   wenn p[i] = p[i+1], dann label[i] < label[i+1].
     */
    void countChars(unsigned int &n, std::vector<int> &labelIndex,
                    std::vector<char> &label, std::vector<unsigned int> &p) const {
        // Zähle in pAll (pAll[i] = p[i] für alle ASCII-Zeichen i) und bestimme n.
        std::map<char, unsigned int> pAll;
        for (auto c: letters) {
            ++pAll[c];
        }
        n = pAll.size();
        // Sortiere pAll als Menge von n Paaren (a,b)=(i,pAll[i]) mit pAll[i] > 0
        // aufsteigend, so dass
        //   (a,b) < (c,d) genau dann, wenn (b < d) oder (b == d && a < c).
        using pEntry = std::pair<char, unsigned int>;
        auto compFunc = [](pEntry left, pEntry right) {
            return (left.second < right.second) ||
                   (left.second == right.second && left.first < right.first);
        };
        std::set <pEntry, std::function<bool(pEntry, pEntry)>>
                pSet(pAll.begin(), pAll.end(), compFunc);
        // Erzeuge labelIndex, label und p wie verlangt.
        labelIndex = std::vector<int>(N, -1);
        label = std::vector<char>(n);
        p = std::vector<unsigned int>(n);
        unsigned int idx = 0;
        for (const pEntry &e: pSet) {
            label[idx] = e.first;
            p[idx] = e.second;
            labelIndex[e.first] = idx;
            ++idx;
        }
    }
};

ASCIIStream input{false};

////////////////////////////////////////////////////////////////////////////////
////////////////// Zum Schreiben der Ausgabe mittels "output" //////////////////
////////////////////////////////////////////////////////////////////////////////

/*
 * Erlaubt das Schreiben der Ausgabe in Form eines Bitstroms "output".
 * Verwendung:
 *  - "output << b" für "bool b":
 *      Schreibt ein Bit (gegeben als bool b) als einzelne 0/1 in die Ausgabe.
 *  - "output << c " für "char c":
 *      Schreibt ein ASCII-Zeichen (gegeben als char c) als Folge von "logN = 7"
 *      0/1en in die Ausgabe.
 */
class BitStream {
public:
    friend BitStream &operator<<(BitStream &s, bool b) {
        std::cout << b << std::flush;
        return s;
    }

    friend BitStream &operator<<(BitStream &s, char c) {
        for (unsigned int i = 0, shift = logN - 1; i < logN; ++i, --shift) {
            std::cout << ((c >> shift) & 1) << std::flush;
        }
        return s;
    }
};

BitStream output{};

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
/////////////////////// Zum Ausgeben von vector-Inhalten ///////////////////////
////////////////////////////////////////////////////////////////////////////////

/*
 * Für die einfache Ausgabe von vector-Instanzen,
 * z.B.: "std::cout << label << std::endl".
 */
template<class T>
std::ostream &operator<<(std::ostream &out, const std::vector <T> &v) {
    for (const T &e: v) {
        out << ' ' << e;
    }
    return out;
}

////////////////////////////////////////////////////////////////////////////////
///////////////////// main-Methode mit Aufruf von "run()" //////////////////////
////////////////////////////////////////////////////////////////////////////////

/*
 * Diese Methode ist der Startpunkt für Ihre Implementierung in "encode.cpp".
 */
void run();

/*
 * Liest die Eingabe komplett ein und erzeugt daraus einen "ASCIIStream input",
 * den Sie in der Methode "run" auslesen und mit diesem arbeiten können.
 */
int main() {
    input = {};
    run();
    assert(livingTrees == 0);
}

#endif // __ENCODE_H_INCLUDED__