#include <iostream>
#include <vector>

using namespace std;

const int BOARD_SIZE = 5;  // Size of the game board

class BattleshipBoard 
{
private:
    
    vector<pair<int, int>> ships[3];
    int shipSizes[3] = {4, 3, 2};
    int lifePoints = 4 + 3 + 2;
    int playerNumber;

public:
    BattleshipBoard(int _playerNumber) 
    { 
        initializeBoard();
        playerNumber = _playerNumber;
    }

    char board[BOARD_SIZE][BOARD_SIZE];

    void initializeBoard();
    void displayBoard();
    void placeShips();
    bool isHit(int x, int y, char board[BOARD_SIZE][BOARD_SIZE]);
    void playTurn(char board[BOARD_SIZE][BOARD_SIZE]);
    bool isDead();
};

void BattleshipBoard::initializeBoard() 
{
    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            board[i][j] = '~';
        }
    }
}

void BattleshipBoard::displayBoard() 
{
    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void BattleshipBoard::placeShips() 
{
    for (int i = 0; i < 3; i++) 
    {
        int size = shipSizes[i];
        cout << "Player " << playerNumber << ", place your " << size << "-unit ship (row and column):" << endl;

        for (int j = 0; j < size; j++) 
        {
            int x, y;
            cout << "Enter coordinates (x,y) for unit [" << j + 1 << "] (indices start from 0,0 to 4,4): ";
            cin >> y >> x;

            ships[i].push_back({x, y});
            board[x][y] = 'S';
        }

        cout << "Player " << playerNumber << "'s board after placing the ship:" << endl;
        displayBoard();

    }
}

bool BattleshipBoard::isHit(int x, int y, char board[BOARD_SIZE][BOARD_SIZE]) 
{
    return board[x][y] == 'S';
}

void BattleshipBoard::playTurn(char board[BOARD_SIZE][BOARD_SIZE]) 
{

    int x, y;
    bool validCords = false;
    while(!validCords) 
    {
        cout << "Enter target coordinates (row and column): ";
        cin >> y >> x;

        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) 
        {
            cout << "Invalid coordinates. Try again." << endl;
        }
        else 
        {
            validCords = true;
        }
    }

    if (isHit(x, y, board)) 
    {
        cout << "It's a hit!" << endl;
        board[x][y] = 'X';
        lifePoints--;
    } 
    else 
    {
        cout << "Missed!" << endl;
        board[x][y] = 'O';
    }

}

bool BattleshipBoard::isDead() 
{
    return lifePoints == 0;
}

int main() {
    BattleshipBoard player1 = BattleshipBoard(1);
    BattleshipBoard player2 = BattleshipBoard(2);

    cout << "Player 1, place your ships:" << endl;
    player1.placeShips();

    cout << "Player 2, place your ships:" << endl;
    player2.placeShips();

    while (true) 
    {
        //NOTICE: playTurn lowers the current player's lifePoints, that's why the numeration in win scenarios is swapped
        cout << "Player " << 1 << "'s Turn" << endl;
        player1.displayBoard();
        player1.playTurn(player2.board);
        if (player1.isDead()) 
        {
            cout << "Player 1 wins!" << endl;
            break;
        }

        cout << "Player " << 2 << "'s Turn" << endl;
        player2.displayBoard();
        player2.playTurn(player1.board);
        if (player2.isDead()) 
        {
            cout << "Player 2 wins!" << endl;
            break;
        }
    }

    return 0;
}