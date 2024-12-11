
#ifndef _Ultimate_H
#define _Ultimate_H

#include <iostream>
#include <iomanip>
#include <cctype>
#include <utility>
#include "BoardGame_Classes.h"

using namespace std;

template <typename T>
class Ultimate_board:public Board<T> {
public:
    Ultimate_board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    pair<int,int> Check_board();

};

template <typename T>
class Ultimate_player : public Player<T> {
public:
    Ultimate_player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Ultimate_Rplayer : public RandomPlayer<T>{
public:
    Ultimate_Rplayer (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION


using namespace std;

// Constructor for X_O_Board
template <typename T>
Ultimate_board<T>::Ultimate_board() {
    this->rows = this->columns = 12;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Ultimate_board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows-3 || y < 0 || y >= this->columns-3) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
            pair<int,int> here=Check_board();
            cout<<here.first<<" "<<here.second<<endl;
            if(here.first!=15)
                {
                    this->board[(here.first+9)][(here.second+3)] = toupper(mark);
                    for(int i=here.first*3;i<(here.first*3)+3;i++)
                        {
                            for(int j=here.second*3;j<(here.second*3)+3;j++)
                                {
                                    if(this->board[i][j] == 0)
                                        {
                                            this->board[i][j] =1;
                                        }
                                }
                        }
                }
            here.first=15;here.second=15;
        }

        return true;
    }
    return false;
}

template <typename T>
pair<int,int> Ultimate_board<T>::Check_board() {
    // Only update if move is valid
    int check=0;
  for(int z=0;z<9;z++)
        {
            for(int y =0;y<9;y++)
                {
                    for(int m=0;m<3;m++)
                    {
                        for(int n=0;n<3;n++)
                            {
                                if(this->board[m+z][n+y]==1)
                                    {
                                        check=1;
                                    }
                            }
                    }
                    if(check ==0)
                        {
                            for (int i = 0; i < 3; i++)
                                {
                            if ((this->board[i+z][0+y] == this->board[i+z][1+y] && this->board[i+z][1+y] == this->board[i+z][2+y] && this->board[i+z][0+y] != 0) ||
                                (this->board[0+z][i+y] == this->board[1+z][i+y] && this->board[1+z][i+y] == this->board[2+z][i+y] && this->board[0+z][i+y] != 0))
                                    {
                                      return make_pair(z/3,y/3);
                                    }
                                }

                        // Check diagonals
                        if ((this->board[0+z][0+y] == this->board[1+z][1+y] && this->board[1+z][1+y] == this->board[2+z][2+y] && this->board[0+z][0+y] != 0) ||
                            (this->board[0+z][2+y] == this->board[1+z][1+y] && this->board[1+z][1+y] == this->board[2+z][0+y] && this->board[0+z][2+y] != 0))
                            {
                              return make_pair(z/3,y/3);
                            }
                        }
                    else
                        {
                            check=0;
                        }
                y=y+2;
                }
            z=z+2;
        }
    return make_pair(15,15);
}

// Display the board and the pieces on it
template <typename T>
void Ultimate_board<T>::display_board() {
    for (int i = 0; i < 9; i++) {
        cout << "\n| ";
        for (int j = 0; j < 9; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";

        }
         if(i==2 || i==5 || i==8 )
                {
                    cout<<"\n____________________________|__________________________|__________________________|"<<endl;
                    cout<<"                            |                          |                          ";
                    if(i!=8)
                        {
                            cout<<"|";
                        }
                }
        else
            {
                cout << "\n----------------------------|--------------------------|--------------------------|";
            }
    }
    for (int i = 0; i < 3; i++) {
        cout << "\n ";
        cout<<setw(28)<<"|";
        for (int j = 0; j < 3; j++) {
            cout << setw(5) << this->board[i+9][j+3]<<"   |";
        }
         if(i==2 || i==5 || i==8 )
                {
                    if(i==8)
                        {
                            cout<<endl;
                        }
                    else
                        {
                            cout<<"\n                            |__________________________|"<<endl;
                            //cout<<"                     |";
                        }

                }
        else
            {
                //cout << "\n----------------------------|--------------------------|--------------------------|";
                cout << "\n                            |--------------------------|";
            }
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool Ultimate_board<T>::is_win() {
    for (int i = 9; i < this->rows; i++) {
        if ((this->board[i][3] == this->board[i][4] && this->board[i][4] == this->board[i][5] && this->board[i][3] != 0)) {
            return true;
        }
    }
    for (int j = 3; j < 6; j++) {
        if ((this->board[9][j] == this->board[10][j] && this->board[10][j] == this->board[11][j] && this->board[9][j] != 0)) {
            return true;
        }
    }
    // Check diagonals
    if ((this->board[9][3] == this->board[10][4] && this->board[10][4] == this->board[11][5] && this->board[9][3] != 0) ||
        (this->board[9][5] == this->board[10][4] && this->board[10][4] == this->board[11][3] && this->board[9][5] != 0)) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Ultimate_board<T>::is_draw() {
    for(int i =0;i<9;i++)
        {
            for(int j=0;j<9;j++)
                {
                    if(this->board[i][j]==0)
                        {
                            return false;
                        }
                }
        }
    if(is_win())
        {
            return false;
        }
    return true;
}

template <typename T>
bool Ultimate_board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
Ultimate_player<T>::Ultimate_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Ultimate_player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 8) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
Ultimate_Rplayer<T>::Ultimate_Rplayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Ultimate_Rplayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

#endif
