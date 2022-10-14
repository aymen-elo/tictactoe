#include <iostream>
using namespace std;

struct Player{
    char symbol;
    bool isTurn;
    bool hasWon;
};

void initPl(Player & A, Player & B){
    A.isTurn = true;
    B.isTurn = false;
    A.hasWon = false;
    B.hasWon = false;
}

void emptyFill(char** & T, int ln, int cl){
    for(int i = 0; i < ln; i++){
        for(int j = 0; j < cl; j++){
            T[i][j] = ' ';
        }
    }
}


void saisieTaille(int & cl, int & ln){
    cl = 0;
    while(cl < 3){
        cout << "Morpion de taille NxN, saisir N >= 3: "<<endl;
        cin>>cl;
    }
    ln = cl;
}

void selectSymbol(char & A, char & B){
    cout<<"Quelle caractere pour le joueur 1 ? "<<endl;
    cin>>A;
    cout<<"Quelle caractere pour le joueur 2 ? "<<endl;
    cin>>B;
}

void afficher(char** T, int cl, int ln){
    
    for(int i = 0; i < ln-1; i++){
        cout<<' ';
        for(int j = 0; j < cl-1; j++){
            cout<<T[i][j]<<'|';
        }
        cout<<T[i][cl-1]<<endl;
        
        cout<<" -";
        for(int j = 0; j < cl-1; j++){
            cout<<"--";
        }
        cout<<endl;
    }
    cout<<' ';
    for(int j = 0; j < cl-1; j++){
        cout<<T[ln-1][j]<<"|";
    }
    cout<<T[ln-1][cl-1]<<endl;

}

void winCase(char** T, Player & p, int N){ // N for number of rows/lines to set the for loop limit
    
    int verif;

    //lns
    verif = 0;
    for(int j = 0; j < N; j++){
        if(T[0][j] == p.symbol){
            verif=+1;
        }
    }
    if(verif == N){
        p.hasWon = true;
    }

    //cols
    verif = 0;
    for(int i = 0; i < N; i++){
        if(T[0][i] == p.symbol){
            verif=+1;
        }
    }
    if(verif == N){
        p.hasWon = true;
    }

    //diago gauche haut vers droit bas
    verif = 0;
    for(int i = 0, j = 0; i < N, j < N; j++, i++){
        if(T[i][j] == p.symbol){
            verif=+1;
        }
    }
    if(verif == N){
        p.hasWon = true;
    }

    //diago gauche bas ver droit haut
    verif = 0;
    for(int i = N-1, j = 0; i >= 0, j < N; j++, i--){
        if(T[i][j] == p.symbol){
            verif=+1;
        }
    }
    if(verif == N){
        p.hasWon = true;
    }
}

//checks weither a case was already checked before being inserted
void fillIfEmpty(char** & TAB, Player & Pl, int & a, int & b){

    while(TAB[a-1][b-1] != ' '){
        cout<<"Position deja occupee !!! >:("<<endl;
        cout<<"Joueur "<<Pl.symbol<<", entrez la Ligne "<<endl;
        cin>>a;
        cout<<"Joueur "<<Pl.symbol<<", entrez la Cologne "<<endl;
        cin>>b; 
    }
}

void playRound(char** & T, Player & P, int N){
    
    int i, j;
    cout<<"Joueur "<<P.symbol<<", entrez la Ligne "<<endl;
    cin>>i;
    cout<<"Joueur "<<P.symbol<<", entrez la Cologne "<<endl;
    cin>>j;
    
    fillIfEmpty(T, P, i, j);

    T[i-1][j-1] = P.symbol;
    winCase(T, P, N); //did the player win ?
    afficher(T, N, N); // N represents cols and lns at once
}

void gameWinner(Player A, Player B){
    if(B.hasWon == true){
        cout<<"Félicitations Joueur 2, c'est gagné !"<<endl;
    }
    if(A.hasWon == true){
        cout<<"Félicitations Joueur 1, c'est gagné !"<<endl;
    }
}

void playGame(char** & T,Player & A, Player & B, int N){
    int cpt = 0; //incrementing cpt each round
    int maxRounds = N*N;

    while((A.hasWon == false) && (B.hasWon == false) && (cpt <= maxRounds)){
        if(A.isTurn == true){
          playRound(T, A, N);
          A.isTurn = false;
          B.isTurn = true;
        }else{
          playRound(T, B, N);
          B.isTurn = false;
          A.isTurn = true;
        }
        cpt += 1;
        gameWinner(A, B);
    }
    
}




// MAIN PROGRAM
int main(){


Player p1, p2;
int cols, lns;
initPl(p1, p2);
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
playGame(tab, p1, p2, lns); // N=lns=cols;




//desalloc
for(int i = 0; i < cols; i++){
    delete[] tab[i];
}
delete[] tab;


}
/*
diagonale opposée
li,es
*/