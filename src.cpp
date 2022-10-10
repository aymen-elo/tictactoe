#include <iostream>
using namespace std;

void saisieTaille(int & cl, int & ln){
    cout << "Morpion de taille NxN, saisir N: "<<endl;
    cin>>cl;
    ln = cl;
}

void afficher(char** T, int cl, int ln){
    for(int i = 0; i < ln; i++ ){
        cout<<'|';
        for(int j = 0; j < cl; j++){
            cout<<T[j]<<'|';
        }

    }
}


int main(){


int cols, lns;
saisieTaille(cols, lns);

//alloc
char** tab;
tab = new char*[cols];
for(int i = 0; i < cols; i++){
    tab[i] = new char[lns];
}







//desalloc
for(int i = 0; i < cols; i++){
    delete[] tab[i];
}
delete[] tab;


}
