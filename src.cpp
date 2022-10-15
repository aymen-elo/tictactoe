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

void display(char** T, int cl, int ln){
    
    //Horizontal Indexes
    cout<<"   ";
    for(int i = 0; i < ln; i++){
        cout<<i+1<<"   ";
    }
    cout<<endl;
    
    
    for(int i = 0; i < ln-1; i++){
        
        //Symbols & Vertical: Indexes + Separations
        cout<<i+1<<' ';
        for(int j = 0; j < cl-1; j++){
            cout<<' '<<T[i][j]<<' '<<'|';
        }
        cout<<' '<<T[i][cl-1]<<endl;
        
        //Horizontal Separation
        cout<<" -";
        for(int j = 0; j < cl; j++){
            cout<<"----";
        }
        cout<<endl;
    }

    //Last line
    cout<<ln<<' ';
    for(int j = 0; j < cl-1; j++){
        cout<<' '<<T[ln-1][j]<<' '<<"|";
    }
    cout<<' '<<T[ln-1][cl-1]<<endl;

}

void winCases(char** & T, Player & Pl, int N){
    
    int cpt=1;
    //lines
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(T[i][j] == Pl.symbol){
                cpt+=1;
            }
        }
        if(cpt == N){
            Pl.hasWon = true;
        }
        cpt=1;
    }
    
    //columns
    for(int j = 0; j < N; j++){
        for(int i = 0; i < N; i++){
            if(T[i][j] == Pl.symbol){
                cpt+=1;
            }
        }
        if(cpt == N){
            Pl.hasWon = true;
        }
        cpt=1;
    }

    //diagonal from upper left
    for(int i = 0, j = 0; i<N, j<N; i++, j++){
        if(T[i][j] == Pl.symbol){
            cpt+=1;
        }
        if(cpt == N){
            Pl.hasWon = true;
        }
    }
    //cpt reinitalized outside of the loop because there is one only primary diagonal
    cpt=1;

    //diagonal from lower left
    for(int i = N-1, j = 0; i>=0, j<N; i--, j++){
        if(T[i][j] == Pl.symbol){
            cpt+=1;
        }
        if(cpt == N){
            Pl.hasWon = true;
        }
    }
}

//checks weither a case was already checked before being inserted
void fillIfCorrect(char** & TAB, Player & Pl, int & a, int & b, int N){

    while((TAB[a-1][b-1] != ' ') || ((a>N && a<1) || (b>N && b<1))){
        cout<<"Position impossible !! >:c"<<endl;
        cout<<"Joueur "<<Pl.symbol<<", entrez la Ligne "<<endl;
        cin>>a;
        cout<<"Joueur "<<Pl.symbol<<", entrez la Colonne "<<endl;
        cin>>b; 
    }
}

void playRound(char** & T, Player & P, int N){
    
    int i, j;
    cout<<"Joueur "<<P.symbol<<", entrez la Ligne "<<endl;
    cin>>i;
    cout<<"Joueur "<<P.symbol<<", entrez la Colonne "<<endl;
    cin>>j;
    
    fillIfCorrect(T, P, i, j, N);
    winCases(T, P, N);
    T[i-1][j-1] = P.symbol;
    display(T, N, N); // N represents cols and lns at once
}

void gameWinner(Player A, Player B){
    if(B.hasWon == true){
        cout<<"Felicitations Joueur 2, c'est gagne !"<<endl;
    }
    if(A.hasWon == true){
        cout<<"Felicitations Joueur 1, c'est gagne !"<<endl;
    }
}

void playGame(char** & T,Player & A, Player & B, int N){
    int cpt = 0; //incrementing cpt each round
    int maxRounds = N*N;

    while((A.hasWon == false) && (B.hasWon == false) && (cpt < maxRounds)){
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
    }
    
    //Either a winner or draw match
    if((A.hasWon == false) && (B.hasWon == false)){
        cout<<"MATCH NUL :/"<<endl;
    }else{
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
display(tab, cols, lns);
playGame(tab, p1, p2, lns); // N=lns=cols;




//desalloc
for(int i = 0; i < cols; i++){
    delete[] tab[i];
}
delete[] tab;


}