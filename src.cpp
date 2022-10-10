#include <iostream>
using namespace std;

struct Player{
    char symbol;
    bool isTurn;
    bool hasWon;
};

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

void win(char** T, Player & p, int N){ // N for number of rows/lines to set the for loop limit
    int verif = 0;
    for(int j = 0; j < N; j++){
        if(T[0][j] == p.symbol){
            verif=+1;
        }
    }
    if(verif == N){
        p.hasWon = true;
    }
    verif = 0;
    for(int i = 0; i < N; i++){
        if(T[0][i] == p.symbol){
            verif=+1;
        }
    }
    if(verif == N){
        p.hasWon = true;
    }
    verif = 0;

    for(int i = 0, j = 0; i < N, j < N; j++, i++){
        if(T[i][j] == p.symbol){
            verif=+1;
        }
    }
    if(verif == N){
        p.hasWon = true;
    }

}

//fix: find when a player has won
void playRound(char** & T, Player A, Player B, int N){
    if((A.hasWon == false) && (B.hasWon == false)){
        if(A.isTurn){
            int i, j;
            cout<<"Joueur 1, entrez la Ligne "<<endl;
            cin>>i;
            cout<<"Joueur 1, entrez la Cologne "<<endl;
            cin>>j;
            
            while(T[i][j] != ' '){
                cout<<"Position deja occupée !!! >:("<<endl;
            }
            T[i-1][j-1] = A.symbol;
            A.isTurn = false;
            B.isTurn = true;
            win(T, A, N); //did the player win ?
            if(A.hasWon){
                cout<<"Félicitations Joueur 1, Alias "<<A.symbol<<", c'est gagné !"<<endl;
            }
        }else{
            int i, j;
            cout<<"Joueur 2, entrez la Ligne "<<endl;
            cin>>i;
            cout<<"Joueur 2, entrez la Cologne "<<endl;
            cin>>j;
            
            while(T[i][j] != ' '){
                cout<<"Position deja occupee !!! >:("<<endl;
            }
            T[i-1][j-1] = B.symbol;
            B.isTurn = false;
            A.isTurn = true;
            win(T, B, N);
            if(A.hasWon){
                cout<<"Félicitations Joueur 2, Alias "<<B.symbol<<", c'est gagné !"<<endl;
            }
        }
    }
    afficher(T, N, N); // N represents cols and lns at once
}


int main(){

Player p1, p2;
int cols, lns;
saisieTaille(cols, lns);

//alloc
char** tab;
tab = new char*[cols];
for(int i = 0; i < cols; i++){
    tab[i] = new char[lns];
}
selectSymbol(p1.symbol, p2.symbol);
emptyFill(tab, cols, lns); 
afficher(tab, cols, lns);

// cols or lns, they have the same value
p1.isTurn == true;
playRound(tab, p1, p2, cols); 




//desalloc
for(int i = 0; i < cols; i++){
    delete[] tab[i];
}
delete[] tab;


}