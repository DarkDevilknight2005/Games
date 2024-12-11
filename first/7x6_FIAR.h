
#ifndef _7x6_FIAR_H
#define _7x6_FIAR_H

#include <iostream>
#include <iomanip>
#include <cctype>
#include "BoardGame_Classes.h"
#include <limits>
#include <algorithm>

using namespace std;

template <typename T>
class FIAR_board:public Board<T>
{
public:
    FIAR_board();
    bool update_board (int x , int y , T symbol);
    bool AIupdate_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class FIAR_player:public Player<T>
{
public:
    FIAR_player (string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class FIAR_Rplayer : public RandomPlayer<T>
{
public:
    FIAR_Rplayer (T symbol);
    void getmove(int &x, int &y);
};


//--------------------------------------------

template <typename T>
FIAR_board<T>::FIAR_board()
{
    this->rows=6;
    this->columns=7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++)
        {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++)
                {
                    this->board[i][j] = 0;
                }
        }
    this->n_moves = 0;
}

template <typename T>
bool FIAR_board<T>::update_board (int x , int y , T symbol)
{
     if (!(y < 0 || y >= this->columns))
        {
            if(this->board[5][y]==0 || symbol == 0 )
                {
                    if (symbol == 0)
                        {
                        this->n_moves--;
                        this->board[5][y] = 0;
                        }
                    else
                        {
                            this->n_moves++;
                            this->board[5][y] = toupper(symbol);
                        }
                    return true;
                }
            for(int i=4;i>0;i--)
                {
                    if(this->board[i][y]==0 || symbol == 0)
                        {
                         if (symbol == 0)
                            {
                            this->n_moves--;
                            this->board[i][y] = 0;
                            }
                        else
                            {
                                this->n_moves++;
                                this->board[i][y] = toupper(symbol);
                            }
                        return true;
                        }
                }
        }
    return false;
}


template <typename T>
void FIAR_board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------------------------------------------";
    }
    cout << endl;
}

template <typename T>
bool FIAR_board<T>::is_win() {
    for (int i = 0 ; i < 4 ; i++)
        {
            for (int j = 5 ; j >2 ; j--)
                {
                    if ( (this->board[j][i] == this->board[j-1][i] && this->board[j-1][i] == this->board[j-2][i] && this->board[j-2][i] == this->board[j-3][i] && this->board[j][i] != 0)
                        ||(this->board[j][i] == this->board[j][i+1] && this->board[j][i+1] == this->board[j][i+2] && this->board[j][i+2] == this->board[j][i+3] && this->board[j][i] != 0)
                        ||(this->board[j][i] == this->board[j-1][i+1] && this->board[j-1][i+1] == this->board[j-2][i+2] && this->board[j-2][i+2] == this->board[j-3][i+3] && this->board[j][i] != 0))
                        {
                            return true;
                        }
                }
        }
   for (int j = 5 ; j >2 ; j--)
            {
                for (int i = 0 ; i < 4 ; i++)
                {
                    if ((this->board[j][i] == this->board[j-1][i+1] && this->board[j-1][i+1] == this->board[j-2][i-2] && this->board[j-2][i-2] == this->board[j-3][i-3] && this->board[j][i] != 0))
                        {
                            return true;
                        }
                }

            }
    return false;
}

template <typename T>
bool FIAR_board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool FIAR_board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------

template <typename T>
FIAR_player<T>::FIAR_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void FIAR_player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces & the place under it have and input: ";
    cin >> y ;
    cin.ignore();
}

// Constructor for X_O_Random_Player
template <typename T>
FIAR_Rplayer<T>::FIAR_Rplayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void FIAR_Rplayer<T>::getmove(int& x, int& y) {
// Random number between 0 and 2
    y = rand() % (this->dimension);
}

//------------------------------------------------------------------


#endif
