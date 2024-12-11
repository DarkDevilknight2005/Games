#include <iostream>
#include "BoardGame_Classes.h"
#include "Ultimate.h"

using namespace std;

int main() {

    int choice;
    Player<char>* players[2];
    Board<char>* B = new Ultimate_board<char>();
    string playerXName, player2Name;

    //cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    //cout << "Enter Player X name: ";
    //cin >> playerXName;
    //cout << "Choose Player X type:\n";
    //cout << "1. Human\n";
    //cout << "2. Random Computer\n";
    //cin >> choice;
    playerXName="s";
    choice=2;
    switch(choice) {
        case 1:
            players[0] = new Ultimate_player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new Ultimate_Rplayer<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    /*cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;*/
    player2Name="s2";
    choice=2;
    switch(choice) {
        case 1:
            players[1] = new Ultimate_player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new Ultimate_Rplayer<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<char> Ultimate(B, players);
    Ultimate.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    return 0;
}
