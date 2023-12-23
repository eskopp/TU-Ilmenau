#include<iostream>
#include<vector>
#include<iterator>

template<class T>
std::ostream &operator<<(std::ostream &out, const std::vector <T> &v) {
    out << '(';
    if (!v.empty()) {
        std::copy(v.begin(), v.end() - 1, std::ostream_iterator<T>(out, ","));
        out << v.back();
    }
    return out << ')';
}

const std::string EMPTY = "",  /* kommen nie als Schlüssel vor */
DELETED = "-";

std::vector <std::string> table;

const int p = 16777259;
const std::vector <std::uint64_t> a = {
        5902272, 7629265, 5333771, 12383661, 11774175,
        9802969, 12640503, 3201625, 16072600, 3335533,
        5101852, 3440, 13405035, 12903727, 13147288,
        1825828, 16182670, 12801869, 8007159, 2376172,
};

int linHash(const std::string &s) {
    /* TODO */
    unsigned long long sum = 0;
    for (int i = 0; i < s.size(); ++i) {
        sum += a[i] * s[i];
    }
    return sum % p;
}

bool lookup(const std::string &s) {
    /* TODO */
    int hash = linHash(s);
    int size = table.size();
    for (int i = 0; i < size; ++i) {
        int pos = (hash + i) % size;

        if (table[pos] == s) {
            return true;
        }

        if (table[pos] == EMPTY) {
            return false;
        }
    }
    return false;
}

const double alpha0 = 0.7,
        alpha1 = 0.8 * alpha0;
int inUse = 0, load = 0;

void insert(const std::string &s) {
    int size = table.size();
    int hash = linHash(s);

    if (!lookup(s)) {

        for (int i = 0; i < size; ++i) {
            int pos = (hash + i) % size;

            if (table[pos] == EMPTY) {
                table[pos] = s;
                ++inUse;
                ++load;
                break;
            }
            if (table[pos] == DELETED) {
                table[pos] = s;
                ++load;
                break;
            }
        }
    }
}

void _delete(const std::string &s) {
    /* TODO */
    int hash = linHash(s);
    int size = table.size();

    for (int i = 0; i < size; ++i) {
        int pos = (hash + i) % size;

        if (table[pos] == s) {
            table[pos] = DELETED;
            --load;
        }

        if (table[pos] == EMPTY) {
            break;
        }
    }

}

void resize() {
    std::vector <std::string> old_table = table;
    table.resize(table.size() * 2, EMPTY);
    load = 0;
    inUse = 0;
    for (int i = 0; i < old_table.size(); ++i) {
        if (old_table[i] != EMPTY && old_table[i] != DELETED) {
            insert(old_table[i]);
        }
    }
}

void reorganize() {
    std::vector <std::string> old_table = table;
    table.resize(table.size(), EMPTY);
    load = 0;
    inUse = 0;
    for (int i = 0; i < old_table.size(); ++i) {
        if (old_table[i] != EMPTY && old_table[i] != DELETED) {
            insert(old_table[i]);
        }
    }
}

int main() {
    table.resize(2, EMPTY);
    char c;
    std::string s;
    while (std::cin >> c >> s) {
        /* TODO */
        if (c == 'h') {
            std::cout << "h(" << s << ") = " << linHash(s) << std::endl;
        }
        if (c == 'p') {
            std::cout << table << std::endl;
        }
        if (c == 'l') {
            std::cout << lookup(s) << std::endl;
        }
        if (c == 'i') {
            //Teste auf möglichen Überlauf
            if (inUse + 1 > alpha0 * table.size()) {
                if (load + 1 > alpha1 * table.size()) {
                    resize();
                } else {
                    reorganize();
                }
            }
            insert(s);
        }
        if (c == 'd') {
            _delete(s);
        }
    }
}