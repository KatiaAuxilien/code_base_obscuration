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


void decomposeDimension(int *nHComp, int *nWComp, int sizeComp, int nH, int nW) {
    int facteur1_max = nH;
    int facteur2_max = nW;

    for (int i = 2; i <= facteur1_max; i++) {
        if (sizeComp % i == 0) {
            int j = sizeComp / i;
            if (j <= facteur2_max) {
                *nHComp = i;
                *nWComp = j;
                cout << "New dimensions: Height = " << *nHComp << ", Width = " << *nWComp << endl;
                return;
            }
        }
    }

    cout << "The size of the compressed image cannot be decomposed into dimensions within the original image's dimensions." << endl;
}


// void decomposer_en_produit_de_deux_facteurs(int n) {
//     for (int i = 2; i <= n / 2; i++) {
//         if (n % i == 0) {
//             cout << n << " = " << i << " * " << n / i << endl;
//         }
//     }
// }

pair<int, int> decomposer_en_produit_de_deux_facteurs(int n) {
    int facteur1 = 1, facteur2 = n;
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            int diff = abs(i - n / i);
            int diff_actuelle = abs(facteur1 - facteur2);
            if (diff < diff_actuelle) {
                facteur1 = i;
                facteur2 = n / i;
            }
        }
    }
    return make_pair(facteur1, facteur2);
}

int main() {
    int n;
    cout << "Entrez un nombre : ";
    cin >> n;
    pair<int, int> facteurs = decomposer_en_produit_de_deux_facteurs(n);
    cout << n << " = " << facteurs.first << " * " << facteurs.second << endl;
    return 0;
}