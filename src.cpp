#include <iostream>
using namespace std;


void emptyFill(char** & T, int ln, int cl){
    for(int i = 0; i < ln; i++){
        for(int j = 0; j < cl; j++){
            T[i][j] = ' ';
        }
    }
}

//fix: when size<=2
void saisieTaille(int & cl, int & ln){
    cout << "Morpion de taille NxN, saisir N: "<<endl;
    cin>>cl;
    ln = cl;
}

void selectSymbol(char & A, char & B){
    cout<<"Quelle caractere pour le joueur 1 ? "<<endl;
    cin>>A;
    cout<<"Quelle caractere pour le joueur 2 ? "<<endl;
    cin>>B;
}

void afficher(char** T, int cl, int ln){
    for(int i = 0; i < ln; i++){
        cout<<'|';
        for(int j = 0; j < cl; j++){
            cout<<T[i][j]<<'|';
        }
        cout<<endl;
        cout<<'-';
        for(int j = 0; j < cl; j++){
            cout<<"--";
        }
        cout<<endl;
    }
}


int main(){


int cols, lns;
char symbolA, symbolB;
saisieTaille(cols, lns);

//alloc
char** tab;
tab = new char*[cols];
for(int i = 0; i < cols; i++){
    tab[i] = new char[lns];
}
selectSymbol(symbolA, symbolB);
emptyFill(tab, cols, lns); 
afficher(tab, cols, lns);






//desalloc
for(int i = 0; i < cols; i++){
    delete[] tab[i];
}
delete[] tab;


}