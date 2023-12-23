#include <iostream>
#include <vector>

void accessViolation() {
    // Wir lassen bad_pointer auf die Adresse 0x1337 zeigen.
    int *bad_pointer = (int *) 0x1337;
    // Mehr Infos zu Pointern:
    // https://en.cppreference.com/w/cpp/language/pointer

    // Nun geben wir den Inhalt aus.
    // Da wir nicht wissen, ob diese Adresse überhaupt von unserem Programm
    // reserviert ist, werden wir höchstwahrscheinlich eine Exception bekommen.
    std::cout << "Value: " << *bad_pointer << std::endl;
}

void arithmeticError() {
    std::vector<int> values;
    int out = 42;
    while (out > -13) {
        out = out - 3;
        values.push_back(out);
    }
    out = 24;
    for (int var: values) {
        std::cout << "Result: " << out % var << std::endl;
    }
}

int main(int argc, char *argv[]) {
    // Wir rufen hier einzelne Unterprogramme auf, welche Exceptions auslösen.
    int test = 1;
    if (test == 1)
        accessViolation();
    else
        arithmeticError();
    // Damit sich das Programm nicht direkt schließt:
    getchar();
    return 0;
}
