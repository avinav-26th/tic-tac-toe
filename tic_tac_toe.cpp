#include <bits/stdc++.h>

using namespace std;

pair<bool, char> check_row(vector<vector<char>> &main_grid)
{
    unordered_set<char> simmilars;
    pair<bool, char> returnPair(false, '#');

    for (int i = 0; i < main_grid.size(); i++)
    {
        for (int j = 0; j < main_grid.size(); j++)
            simmilars.insert(main_grid[i][j]);

        if (simmilars.size() == 1 && *simmilars.begin() != '*')
        {
            returnPair.first = true;
            returnPair.second = *simmilars.begin();
        }
        simmilars.clear();
    }
    return make_pair(returnPair.first, returnPair.second);
}

pair<bool, char> check_column(vector<vector<char>> &main_grid)
{
    unordered_set<char> simmilars;
    pair<bool, char> returnPair(false, '#');

    for (int i = 0; i < main_grid.size(); i++)
    {
        for (int j = 0; j < main_grid.size(); j++)
            simmilars.insert(main_grid[j][i]);

        if (simmilars.size() == 1 && *simmilars.begin() != '*')
        {
            returnPair.first = true;
            returnPair.second = *simmilars.begin();
        }
        simmilars.clear();
    }
    return make_pair(returnPair.first, returnPair.second);
}

pair<bool, char> check_diagonal(vector<vector<char>> &main_grid)
{
    unordered_set<char> simmilars;
    pair<bool, char> returnPair(false, '#');

    for (int i = 0; i < main_grid.size(); i++)
    {
        for (int j = 0; j < main_grid.size(); j++)
            if (i == j)
                simmilars.insert(main_grid[i][j]);
    }
    if (simmilars.size() == 1 && *simmilars.begin() != '*')
    {
        returnPair.first = true;
        returnPair.second = *simmilars.begin();
    }

    else
    {
        simmilars.clear();
        for (int i = 0; i < main_grid.size(); i++)
        {
            for (int j = 0; j < main_grid.size(); j++)
                if (i + j == main_grid.size() - 1)
                    simmilars.insert(main_grid[i][j]);
        }
        if (simmilars.size() == 1 && *simmilars.begin() != '*')
        {
            returnPair.first = true;
            returnPair.second = *simmilars.begin();
        }
    }
    return make_pair(returnPair.first, returnPair.second);
}

char find_winner(vector<vector<char>> &main_grid)
{
    // if(check_row(main_grid) && check_column(main_grid) && check_diagonal(main_grid))
    pair<bool, char> row_result = check_row(main_grid);
    pair<bool, char> column_result = check_column(main_grid);
    pair<bool, char> diagonal_result = check_diagonal(main_grid);

    if (row_result.first || column_result.first || diagonal_result.first)
    {
        if (row_result.second == 'O' || column_result.second == 'O' || diagonal_result.second == 'O')
            return 'O';
        else
            return 'X';
    }
    return 'd';
}

bool is_draw(vector<vector<char>> &main_grid)
{
    int countBlanks = 0;

    for (int i = 0; i < main_grid.size(); i++)
        for (int j = 0; j < main_grid.size(); j++)
            if (main_grid[i][j] == '*')
                countBlanks++;

    return(!countBlanks);
}

void display_current_grid(vector<vector<char>> &main_grid)
{
    for (int i = 0; i < main_grid.size(); i++)
    {
        for (int j = 0; j < main_grid.size(); j++)
            cout << main_grid[i][j] << " ";

        cout << "\n";
    }
}

void display_grid_scheme(int &n)
{
    int display = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++, display++)
            cout << display << " ";

        cout << "\n";
    }
}

int main()
{
    system("cls");
    cout << "\n\n==========================================================================\n\n";
    cout << "\n\n\t\tWelcome to my Hybrid TIC-TAC-TOE\n(you can have custom grid)\n\n";
    cout << "\n\n==========================================================================\n\n";

    char gameChoice;
    do
    {
        cout << "\nChoose the Game-Mode\n";
        cout << "\n1. HUMAN v/s HUMAN\n2. HUMAN v/s COMPUTER\n3. COMPUTER v/s COMPUTER\n\n";
        int gameModeChoice;

        do
        {
            cin >> gameModeChoice;
            if (gameModeChoice < 1 && gameModeChoice > 3)
                cout << "\nPlease enter a valid choice!\n";
        } while (gameModeChoice < 1 && gameModeChoice > 3);

        switch (gameModeChoice)
        {
        case 1:
        {
            system("cls");
            cout << "\n\t\tTIC-TAC-TOE\n\tHUMAN v/s HUMAN mode\n";
            string player1, player2;

            cout << "\nNote:- player 1 will pick 1st, when the game starts\n";
            cout << "\nEnter name of player 1 - ";
            cin >> player1;
            cout << "\nEnter name of player 2 - ";
            cin >> player2;
            cout << "\n";

            char p1Avatar, p2Avatar;
            cout << player1 << " choose your avatar (by entering either 'o' or 'x') - ";
            do
            {
                cin >> p1Avatar;
                if (p1Avatar != 'o' && p1Avatar != 'x')
                    cout << "\nPlease enter a valid avatar-choice! : ";
            } while (p1Avatar != 'o' && p1Avatar != 'x');

            if (p1Avatar == 'o')
            {
                p2Avatar = 'X';
                p1Avatar = 'O';
            }
            else
            {
                p2Avatar = 'O';
                p1Avatar = 'X';
            }

            cout << "\nOkay, so " << player1 << "'s avatar is - " << p1Avatar << " and " << player2 << "'s avatar is - " << p2Avatar;
            cout << "\n";

            int n;
            cout << "\nNow enter the size of (nXn) grid ('n' must be greater than 3 and must not be more than 5)\n";
            do
            {
                cin >> n;
                if (n < 2 || n > 5)
                    cout << "\nPlease enter a valid grid_size!\n";
            } while (n < 2 || n > 5);

            if (n == 2)
            {
                cout << "\nYou both won :)\n";
                goto playing_choice;
            }

            vector<vector<char>> main_grid(n, vector<char>(n, '*'));

            cout << "\nThe grid is marked according to following scheme and when you want to mark any block as 'O' or 'X' then you have to mention the block number and your avatar accordingly, separated by a space.\n";

            unordered_map<int, pair<int, int>> m;
            int display = 1;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++, display++)
                {
                    cout << display << " ";
                    m[display].first = i;
                    m[display].second = j;
                }
                cout << "\n";
            }
            cout << "\nAlright, start playing!! All the best to both of you.\n\n";

            // for(auto it:m)
            // cout<<it.first<<" - ("<<it.second.first<<","<<it.second.second<<")\n";

            int playerCount = 0;
            while (playerCount < n * n)
            {
                if (playerCount % 2 == 0)
                    cout << player1 << "'s turn("<<p1Avatar<<")\n";
                else
                    cout << player2 << "'s turn("<<p2Avatar<<")\n";

                pair<int, char> inputPair;
                cin >> inputPair.first >> inputPair.second;

                if (inputPair.first >= 1 && inputPair.first <= n * n && (inputPair.second == 'o' || inputPair.second == 'x') && main_grid[m[inputPair.first].first][m[inputPair.first].second] == '*')
                {
                    if ((playerCount % 2 == 0 && toupper(inputPair.second) != p1Avatar) || (playerCount % 2 == 1 && toupper(inputPair.second) != p2Avatar))
                        goto warning_message;

                    playerCount++;

                    main_grid[m[inputPair.first].first][m[inputPair.first].second] = toupper(inputPair.second);

                    system("cls");
                    cout << "\n\n";
                    display_grid_scheme(n);
                    cout << "\n\n";
                    display_current_grid(main_grid);
                    cout << "\n\n";

                    // call find_winner() function after every two inputs have been made
                    char winnerAvatar = find_winner(main_grid);

                    switch (winnerAvatar)
                    {
                    case 'O':
                    {
                        string winnerPlayer;
                        if (p1Avatar == 'O')
                            winnerPlayer = player1;
                        else
                            winnerPlayer = player2;
                        cout << "\n\nYay, " << winnerPlayer << " won!!\n\n";
                        goto playing_choice;
                        break;
                    }

                    case 'X':
                    {
                        string winnerPlayer;
                        if (p1Avatar == 'X')
                            winnerPlayer = player1;
                        else
                            winnerPlayer = player2;
                        cout << "\n\nYay, " << winnerPlayer << " won!!\n\n";
                        goto playing_choice;
                        break;
                    }

                    default:
                        if (is_draw(main_grid))
                        {
                            cout << "\n\n! DRAW !\n\n";
                            goto playing_choice;
                        }
                        break;
                    }
                }
                else
                warning_message:
                    cout << "\nRe-enter with a valid choice!\n";
                // else
                // {
                //     count++;
                //     display--;
                //     if (count == 3)
                //     {
                //         cout << "\nDear creative players, do not try to mess up with the game, as we already coded for players like you so please concentrate on the game and try to win. Now the game will resatart again.\nThank You!\n";
                //         exit(0);
                //         //remove exit(0) and write code to re-start the game
                //     }
                //     cout << "\nRe-enter please\n";
                // }
            }
        }

        case 2:
        {
            cout << "\nDevelopement in progress\n";
            goto playing_choice;
        }

        case 3:
        {
            cout << "\nDevelopement in progress\n";
            goto playing_choice;
        }
        }

    playing_choice:
    {
        cout << "\n\nDo you want to play again?\nRespond in either [y/n] or [Y/N]\n";
        do
        {
            cin >> gameChoice;
            if (gameChoice != 'y' && gameChoice != 'n' && gameChoice != 'Y' && gameChoice != 'N')
                cout << "\nTake a chill-pill bro, you still can't break the code ;)\nRe-enter a valid choice\n";
        } while (gameChoice != 'y' && gameChoice != 'n' && gameChoice != 'Y' && gameChoice != 'N');

        if(gameChoice == 'y' || gameChoice == 'Y')
        system("cls");
    }
    } while (gameChoice == 'y' || gameChoice == 'Y');

    system("cls");
    cout << "\nThanx for playing, hope it was a smooth experience...bye\n\n";

    return 0;
}