#include <iostream>

using namespace std;


bool division_entiere(int a, int b) {
    if (b % a == 0) {
        cout << b << " divisé par " << a << " donne " << b / a << ", qui est un nombre entier." << endl;
        return true;
    } else {
        cout << b << " divisé par " << a << " ne donne pas un nombre entier." << endl;
        return false;
    }
}

bool decomposer(int n, int facteur1_max, int facteur2_max) {
    for (int i = 2; i <= facteur1_max; i++) {
        if (n % i == 0) {
            int j = n / i;
            if (j <= facteur2_max) {
                cout << n << " = " << i << " * " << j << endl;
                return true;
            }
        }
    }
    cout << n << " ne peut pas être décomposé en deux facteurs inférieurs à " << facteur1_max << " et " << facteur2_max << "." << endl;
    return false;
}

int main() {
    int n, facteur1_max, facteur2_max;
    cout << "Entrez un nombre: ";
    cin >> n;
    cout << "Entrez le maximum pour le premier facteur: ";
    cin >> facteur1_max;
    cout << "Entrez le maximum pour le second facteur: ";
    cin >> facteur2_max;
    decomposer(n, facteur1_max, facteur2_max);
    return 0;
}
