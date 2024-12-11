#ifndef _3x3NumericalTic_Tac_Toe_H
#define _3x3NumericalTic_Tac_Toe_H
#include "BoardGame_Classes.h"
#include <time.h>
int m=0;

template <typename T>
class N_T_T_Tboard:public Board<T> {
public:
    N_T_T_Tboard ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class N_T_T_T_player : public Player<T> {
private:
    vector <T> symbols;
    T symbol2;
public:
    N_T_T_T_player (string name, T symbol);
    void getmove(int& x, int& y) ;
    bool check();
};

template <typename T>
class N_T_T_T_Random_Player : public RandomPlayer<T>{
    private:
    vector <T> symbols;
public:
    N_T_T_T_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
N_T_T_Tboard<T>::N_T_T_Tboard() {
    this->rows = this->columns = 3;
    this->board = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool N_T_T_Tboard<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            m=0;
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void N_T_T_Tboard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool N_T_T_Tboard<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if (((this->board[i][0] + this->board[i][1] +  this->board[i][2] == 15) ) ||
            ((this->board[0][i] + this->board[1][i] + this->board[2][i] == 15) )) {
            return true;
        }
    }

    // Check diagonals
    if (((this->board[0][0] + this->board[1][1] + this->board[2][2] == 15) ) ||
        ((this->board[0][2] + this->board[1][1] + this->board[2][0] == 15))) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool N_T_T_Tboard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool N_T_T_Tboard<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
N_T_T_T_player<T>::N_T_T_T_player(string name, T symbol) : Player<T>(name, symbol),symbol2(symbol)
{
    if(this->symbol==10)
        {
            symbols={1,3,5,7,9};
        }
    else
        {
            symbols={2,4,6,8};
        }
}

template <typename T>
void N_T_T_T_player<T>::getmove(int& x, int& y ) {
    if(m==0)
        {
            while(true)
                {
                    cout<<"Please enter one of those numbers"<<endl;
                    cout<<"{ ";
                    for(int i=0;i<symbols.size();i++)
                        {
                            cout<<symbols[i];
                            if(i!=symbols.size()-1)
                                {
                                    cout<<" , ";
                                }
                        }
                    cout<<" }"<<endl;
                    if(check())
                        {
                            m=1;
                            break;
                        }

                }
        }

    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y ;
    cin.ignore();
}

template <typename T>
bool N_T_T_T_player<T>::check()
{
    T change;
    cin>>change;
    cin.ignore();
    this->symbol=change;
    for(int i=0;i<symbols.size();i++)
        {
            if(this->symbol == symbols[i])
                {
                    symbols.erase(symbols.begin()+i);
                    return true;
                }
        }
    return false;
}


template <typename T>
N_T_T_T_Random_Player<T>::N_T_T_T_Random_Player(T symbol) : RandomPlayer<T>(symbol){
    if(this->symbol== 10)
        {
            symbols={1,3,5,7,9};
        }
    else if(this->symbol== 0)
        {
            symbols={2,4,6,8};
        }
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void N_T_T_T_Random_Player<T>::getmove(int& x, int& y)
{
    if(m==0)
        {
            int i=rand()%(symbols.size());
            this ->symbol=symbols[i];
            symbols.erase(symbols.begin()+i);
            m=1;
        }
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}



#endif //_3X3X_O_H
