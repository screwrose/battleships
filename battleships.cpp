#include <iostream>
#include <vector>

using namespace std;

const int BOARD_SIZE = 5;  //size of the game board

class BattleshipBoard 
{
private:
    
    vector<pair<int, int>> ships[3]; //stores ship placement
    int shipSizes[3] = {4, 3, 2};   //ship sizing
    int lifePoints = 4 + 3 + 2;    //used for determining winner
    int playerNumber;

public:
    BattleshipBoard(int _playerNumber) 
    { 
        initializeBoard(board);
        initializeBoard(FogOfWarBoard);
        playerNumber = _playerNumber;
    }

    char board[BOARD_SIZE][BOARD_SIZE];         //main game board
    char FogOfWarBoard[BOARD_SIZE][BOARD_SIZE];//used to display where the player shoudl attack

    void initializeBoard(char someboard[BOARD_SIZE][BOARD_SIZE]); //fills board with '~'
    void displayBoard(char someboard[BOARD_SIZE][BOARD_SIZE]);   //outputs the board
    void placeShips(); //ship placement
    bool isHit(int x, int y, char board[BOARD_SIZE][BOARD_SIZE]); //checks if attacked square is a ship
    void playTurn(char board[BOARD_SIZE][BOARD_SIZE]); //performs a singular attack
    bool isDead(); //checks lifePoints
};

//fills board with '~'
void BattleshipBoard::initializeBoard(char someboard[BOARD_SIZE][BOARD_SIZE]) 
{
    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            someboard[i][j] = '~';
        }
    }
}

//outputs the board
void BattleshipBoard::displayBoard(char someboard[BOARD_SIZE][BOARD_SIZE]) 
{
    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            cout << someboard[i][j] << " ";
        }
        cout << endl;
    }
}

//ship placement
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
            //inverting the order of x and y, since it's easier for me to think of a coordinate system than rows/columns
            cin >> y >> x;

            ships[i].push_back({x, y});
            board[x][y] = 'S';
        }

        cout << "Player " << playerNumber << "'s board after placing the ship:" << endl;
        displayBoard(board);

    }
}

//checks if attacked square is a ship
bool BattleshipBoard::isHit(int x, int y, char board[BOARD_SIZE][BOARD_SIZE]) 
{
    return board[x][y] == 'S';
}

//performs a singular attack
void BattleshipBoard::playTurn(char board[BOARD_SIZE][BOARD_SIZE]) 
{

    int x, y;
    bool validCords = false;
    while(!validCords) 
    {
        cout << "Enter target coordinates (row and column): ";
        //inverting the order of x and y, since it's easier for me to think of a coordinate system rather than rows/columns
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
        FogOfWarBoard[x][y] = 'X'; //reflects on FogOfWar
        lifePoints--; //reduces lifepoints so that the if statement in main can break the while loop
    } 
    else 
    {
        cout << "Missed!" << endl;
        board[x][y] = 'O';
        FogOfWarBoard[x][y] = 'O'; //reflects on FogOfWar
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

    //loops until one of the if statements becomes true, returning a break and thus ending the game
    while (true) 
    {
        //NOTICE: playTurn lowers the current player's lifePoints, that's why the numeration in win scenarios is swapped
        cout << "Player " << 1 << "'s Turn" << endl;
        
        //if you also want to see your own board uncomment this line
        //player1.displayBoard(player1.board);
        player1.displayBoard(player1.FogOfWarBoard);
        player1.playTurn(player2.board);
        if (player1.isDead()) 
        {
            cout << "Player 1 wins!" << endl;
            player1.displayBoard(player2.board);
            break;
        }

        cout << "Player " << 2 << "'s Turn" << endl;

        //if you also want to see your own board uncomment this line
        //player2.displayBoard(player2.board);
        player2.displayBoard(player2.FogOfWarBoard);
        player2.playTurn(player1.board);
        if (player2.isDead()) 
        {
            cout << "Player 2 wins!" << endl;
            player2.displayBoard(player1.board);
            break;
        }
    }

    return 0;
}