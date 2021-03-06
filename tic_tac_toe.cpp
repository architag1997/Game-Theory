#include<bits/stdc++.h>
#include<iostream>
#include<conio.h>
using namespace std;
char player, opponent, mode;

struct Move
{
    int row, col;
};

//checks if any moves are left to be played.
bool isMoveLeft(string b[3])
{
    for(int i = 0; i<3; i++)
        for(int j = 0; j<3; j++)
            if(b[i][j] == ' ')
                return true;
    return false;
}

//check and returns the score of board depending upon who is winning.
int board_check(string b[3])
{
    for(int row = 0; row<3; row++)
    {
        if(b[row][0] == b[row][1] && b[row][1] == b[row][2])
        {
            if (b[row][0] == player)
                return +10;
            else if (b[row][0] == opponent)
                return -10;
        }
    }

    for(int col = 0; col<3; col++)
    {
        if(b[0][col] == b[1][col] && b[1][col] == b[2][col])
        {
            if (b[0][col] == player)
                return +10;
            else if (b[0][col] == opponent)
                return -10;
        }
    }

    if(b[0][0] == b[1][1] && b[1][1] == b[2][2] || b[0][2] == b[1][1] && b[1][1] == b[2][0])
    {
        if (b[1][1] == player)
            return +10;
        else if (b[1][1] == opponent)
            return -10;
    }
    return 0;
}

int minimax(string board[3], int depth, bool isMax)
{
    int scr = board_check(board);
    if(scr == 10)
        return (scr - depth);

    if(scr == -10)
        return (scr + depth);

    if(!isMoveLeft(board))
        return 0;

    if(isMax)
    {
        int best = -1000;
        for(int i = 0; i<3; i++)
        {
            for(int j = 0; j<3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = player;
                    best = max(best, minimax(board, depth+1, !isMax));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
    else
    {
        int best = 1000;
        for(int i = 0; i<3; i++)
        {
            for(int j = 0; j<3; j++)
            {
                if(board[i][j] == ' ')
                {
                    board[i][j] = opponent;
                    best = min(best, minimax(board, depth+1, !isMax));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

Move findBestMove(string board[3])
{
    int bestVal = 1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for(int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = opponent;
                int moveVal = minimax(board, 0, true);
                board[i][j] = ' ';
                if (moveVal < bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int getProb()
{
    int start, stop;
    if(mode == 'e')
    {
        start = 0;
        stop = 60;
    }
    else if(mode == 'm')
    {
        start = 50;
        stop = 78;
    }
    else
    {
        start = 67;
        stop = 100;
    }
    static bool first = true;
    if(first)
    {
        srand(time(0));
        first = false;
    }
    return start + rand()%(stop - start + 1);
}

void ini_display()
{
    system("cls");
    cout<<"\n\t\t\tWelcome to a Game of TIC TAC TOE\n";
    cout<<"RULES:\nEnter the place position of the square in the board to play.\n";
    cout<<"For reference, the board is of the form as below:";
    cout<<"\n\n\t\t\t\t     |     |     ";
    cout<<"\n\t\t\t\t  1  |  2  |  3  ";
    cout<<"\n\t\t\t\t_____|_____|_____";
    cout<<"\n\t\t\t\t     |     |     ";
    cout<<"\n\t\t\t\t  4  |  5  |  6  ";
    cout<<"\n\t\t\t\t_____|_____|_____";
    cout<<"\n\t\t\t\t     |     |     ";
    cout<<"\n\t\t\t\t  7  |  8  |  9  ";
    cout<<"\n\t\t\t\t     |     |     ";
}

void startup()
{
    while(true)
    {
        cout<<"\nPlayer choose your symbol (X|O): ";
        cin>>player;
        if(player == 'X' || player == 'O')
            break;
        else
            cout<<"Oops!!!Enter either X or O only.";
    }
    if(player == 'X')
        opponent = 'O';
    else
        opponent = 'X';
    cout<<"Select mode:\n\t1. Easy (Press 'E')\n\t2. Medium (Press 'M')\n\t3. Hard (Press 'H')";
    while(true)
    {
        cout<<"\nEnter your choice: ";
        cin>>mode;
        mode = tolower(mode);
        if(mode == 'e' || mode == 'm' || mode == 'h')
            break;
        else
            cout<<"Invalid choice...Try Again.";
    }
    cout<<"\nLets start the game...";
    getch();
}

void disp_board(string board[3])
{
    system("cls");
    cout<<"\n\t\t\tWelcome to a Game of TIC TAC TOE\n";
    cout<<"\n\n\t\t\t\t     |     |     ";
    cout<<"\n\t\t\t\t  "<<board[0][0]<<"  |  "<<board[0][1]<<"  |  "<<board[0][2];
    cout<<"\n\t\t\t\t_____|_____|_____";
    cout<<"\n\t\t\t\t     |     |     ";
    cout<<"\n\t\t\t\t  "<<board[1][0]<<"  |  "<<board[1][1]<<"  |  "<<board[1][2];
    cout<<"\n\t\t\t\t_____|_____|_____";
    cout<<"\n\t\t\t\t     |     |     ";
    cout<<"\n\t\t\t\t  "<<board[2][0]<<"  |  "<<board[2][1]<<"  |  "<<board[2][2];
    cout<<"\n\t\t\t\t     |     |     ";
}

void play_game()
{
    ini_display();
    startup();
    string board[3] = {"   ", "   ", "   "};
    string place_counter = "000000000";
    int turn_counter = 1, mov;
    while(true)
    {
        disp_board(board);
        if(turn_counter % 2)
        {
            cout<<"\n\nPLAYER Enter your move: ";
            cin>>mov;
            if(place_counter[mov-1] == '0')
            {
                board[(mov-1)/3][(mov-1)%3] = player;
                place_counter[mov-1] = '1';
                disp_board(board);
            }
            else
            {
                cout<<"Invalid Move:(\n";
                turn_counter--;
                getch();
            }
        }
        else
        {
            int prob = getProb();
            int pos;
            if(prob > 70)
            {
                Move bestMove = findBestMove(board);
                board[bestMove.row][bestMove.col] = opponent;
                pos = 3*bestMove.row + bestMove.col;
            }
            else
            {
                while(true)
                {
                    int row = rand() % 3;
                    int col = rand() % 3;
                    if(board[row][col] == ' ')
                    {
                        board[row][col] = opponent;
                        pos = 3*row + col;
                        break;
                    }
                }
            }
            place_counter[pos] = '1';
            disp_board(board);
            cout<<"\n\nCPU played at "<<pos+1;
            getch();
        }
        int win = board_check(board);
        if(win != 0)
        {
            cout<<"\nGAME OVER.";
            if(win == 10)
                cout<<"\nHurray! You WON:)";
            else if(win == -10)
                cout<<"\nSorry! You LOST:(";
            break;
        }

        if(!isMoveLeft(board))
        {
            cout<<"\nGAME OVER.\nIt's A Draw";
            break;
        }
        turn_counter++;
    }
}

bool replay()
{
    char c;
    cout<<"\n\nWanna play again (Y/N)? ";
    cin>>c;
    system("cls");
    if(c == 'Y' || c == 'y')
        return true;
    return false;
}
int main()
{
    do
    {
        play_game();
    }while(replay());
    return 0;
}
