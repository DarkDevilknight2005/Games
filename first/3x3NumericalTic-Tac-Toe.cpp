#include <iostream>
#include "BoardGame_Classes.h"
#include "3x3NumericalTic-Tac-Toe.h"
#include "7x6_FIAR.h"

using namespace std;

int main0()
{
    while(true)
        {
            cout<<"A) Game: 3X3 Numerical"<<endl;
            cout<<"B) Game: Connect"<<endl;
            cout<<"C) Exit"<<endl;
            string choice;
            getline(cin,choice);
            if(choice =="A" || choice == "a")
                {
                    string choice;
                    Player<int>* players[2];
                    Board<int>* B = new N_T_T_Tboard<int>();
                    string playerXName, player2Name;

                    cout << "Welcome to FCAI X-O Game. :)\n";

                    // Set up player 1
                    cout << "Enter Player X name: ";
                    getline(cin,playerXName);
                    cout << "Choose Player X type:\n";
                    cout << "1. Human\n";
                    cout << "2. Random Computer\n";
                    while(true)
                        {
                            getline(cin,choice);
                            if(choice=="1")
                                {
                                    players[0] = new N_T_T_T_player<int>(playerXName,10);
                                    break;
                                }
                            else if(choice == "2")
                                {
                                     players[0] = new N_T_T_T_Random_Player<int>(10);
                                     break;
                                }
                            else
                                {
                                 cout<<"please enter correct choice"<<endl;
                                }
                        }

                    // Set up player 2
                    cout << "Enter Player 2 name: ";
                    getline(cin,player2Name);
                    cout << "Choose Player 2 type:\n";
                    cout << "1. Human\n";
                    cout << "2. Random Computer\n";
                    while(true)
                        {
                            getline(cin,choice);
                            if(choice=="1")
                                {
                                    players[1] = new N_T_T_T_player<int>(player2Name,0);
                                    break;
                                }
                            else if(choice == "2")
                                {
                                     players[1] = new N_T_T_T_Random_Player<int>(0);
                                     break;
                                }
                            else
                                {
                                 cout<<"please enter correct choice"<<endl;
                                }
                        }

                    // Create the game manager and run the game
                    GameManager<int> N_T_T_T_game(B, players);
                    N_T_T_T_game.run();

                    // Clean up
                    delete B;
                    for (int i = 0; i < 2; ++i) {
                        delete players[i];
                    }
                }
            else if(choice =="B" || choice == "b")
                {
                    int choice;
                    Player<char>* players[2];
                    Board<char>* B = new FIAR_board<char>();
                    string playerXName, player2Name;

                    cout << "Welcome to FCAI X-O Game. :)\n";

                    // Set up player 1
                    cout << "Enter Player X name: ";
                    cin >> playerXName;
                    cout << "Choose Player X type:\n";
                    cout << "1. Human\n";
                    cout << "2. Random Computer\n";
                    cin >> choice;
                    cin.ignore();
                    switch(choice) {
                        case 1:
                            players[0] = new FIAR_player<char>(playerXName, 'X');
                            break;
                        case 2:
                            players[0] = new FIAR_Rplayer<char>('X');
                            break;
                        default:
                            cout << "Invalid choice for Player 1. Exiting the game.\n";
                            return 1;
                    }

                    // Set up player 2
                    cout << "Enter Player 2 name: ";
                    cin >> player2Name;
                    cout << "Choose Player 2 type:\n";
                    cout << "1. Human\n";
                    cout << "2. Random Computer\n";
                    cin >> choice;
                    cin.ignore();

                    switch(choice) {
                        case 1:
                            players[1] = new FIAR_player<char>(player2Name, 'O');
                            break;
                        case 2:
                            players[1] = new FIAR_Rplayer<char>('O');
                            break;
                        default:
                            cout << "Invalid choice for Player 2. Exiting the game.\n";
                            return 1;
                    }

                    // Create the game manager and run the game
                    GameManager<char> FIAR(B, players);
                    FIAR.run();

                    // Clean up
                    delete B;
                    for (int i = 0; i < 2; ++i) {
                        delete players[i];
                    }
                }
            else if(choice =="C" || choice == "c")
                {
                    break;
                }
            if(choice =="A" || choice == "a")
                {

                }
            else
                {

                }
        }
}
