/*
Sean Vaserman
20880231

Paige Kobzar
20914548

2020/11/06
SYDE121
a4_q1

This program allows two people to play a 4x4 game of tic tac toe while taking alternating turns

We tested this project by playing multiple rounds with
different outcomes. For example, having X win, having O win,
Winning by getting four in a row, a column, and on a diagonal,
as well as a tie game.
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

//this is our main logic checker that we will pass into our other functions 
//this checks whether or not 4 values are the same given a vector of those values
bool check_logic(vector<int> values)
{
    //stores the first value in the vector as a temporary variable to compare the other values too
    int temp = values[0];

    //immediately returns false if the first square is empty
    if (temp == 0)
    {
        return false;
    }
    else {
        //loops through the next values in the list of 4 and returns false if one of them is different at any point
        for (int i = 1; i < 4; i++)
        {
            if (values[i] != temp)
            {
                return false;
            }
        }
        //returns true if the loop finished, meaning all 4 values are the same and not 0 (empty)
        return true;
    }
}

//this function checks whether or not there are four in a row on a diagonal
bool diagonal_check(vector<vector<int>> table)
{
    //boolean value to hold the output, starts as false
    bool output = false;
    
    //creates a vector to hold the 4 values in the diagonal that is gonna be checked
    vector<int> values;

    //fills the diagonal values vector from top left to bottom right
    for (int i = 0; i < 4; i++)
    {
        values.push_back(table[i][i]);//we chose [i][i] because the numbers going on a diagonal 
                                        //from the top left to bottom right would have those coordinates
    }

    //checks diagonal going from top left to bottom right
    output = check_logic(values);

    //returns true immediately if the diagonal is full
    if (output)
    {
        return output;
    }

    //clears the value vector if the diagonal is not full
    values.clear();

    //fills the diagonal values vector from top right to bottom left
    for (int i = 0; i < 4; i++)
    {
        values.push_back(table[i][3 - i]);
    }

    //checks diagonal going from top right to bottom left
    output = check_logic(values);

    //final return for the final output value after checking both diagonals
    return output;
}

//this function checks whether or not a horizontal row has 4 in a row
bool row_check(vector<vector<int>> table)
{
    //boolean value to hold the output, starts as false
    bool output = false;

    //loops through the 4 rows in the table
    for (int i = 0; i < 4; i++)
    {
        //checks if each row is full
        output = check_logic(table[i]);

        //outputs true if one of the rows ever tests as full
        if (output)
        {
            return output;
        }
    }

    //outputs the final output which would be false if the code gets to this point
    return output;
}

//this function checks whether or not a vertical column has 4 in a row
bool column_check(vector<vector<int>> table)
{
    //boolean value to hold the output, starts as false
    bool output = false;

    //creates a vector to hold the 4 values in the column that is gonna be checked
    vector<int> values;

    //loop for every column
    for (int j = 0; j < 4; j++)
    {
        //loop for every value in each column
        for (int i = 0; i < 4; i++)
        {
            //adds the value in the column to the new values vector
            values.push_back(table[i][j]);
        }
        //checks if a column is full
        output = check_logic(values);

        //returns true if the column if full
        if (output)
        {
            return output;
        }

        //clears the values in the new values vector so the loop can move on to the next column
        values.clear();
    }

    //outputs the final output which would be false if the code gets to this point
    return output;
}

//this function checks if there is a win in a row or diagonal or column
bool win_check(vector<vector<int>> table)
{
    return diagonal_check(table) || row_check(table) || column_check(table);
}

//this function takes the input from each player and modifies the data table and the output table
void game_input(vector<vector<int>>& table, vector<vector<string>>& output_table, int turn)
{
    //boolean to keep track of if the input is valid
    bool valid = false;

    //integer to store the input
    int input;

    //integers to store the input as coordinates in the table
    int i_input, j_input;

    //depending on whether it is the first or second turn, this will output an X or O
    cout << "Type in the spot you want to move for player " << ((turn % 2) ? "X: " : "O: "); 
    
    while (!valid) {

        //handles input
        cin >> input;

        //checks if the input is between 1 and 16
        valid = (input >= 1 && input <= 16);

        //if the number they choose is not in the table, this will prompt a new input and restart the loop to make sure the table doesnt get an out of bounds error
        if (!valid)
        {
            cout << "Input is invalid. Enter a new input: ";
            continue;
        }

        //this formula takes the input and turns it into coordinates in the table
        i_input = (input - 1) / 4;
        j_input = (input - 1) % 4;

        //this says that the input is valid if the square is empty
        valid = (table[i_input][j_input] == 0);

        //if the square is occupied this will prompt a new input
        if (!valid)
        {
            cout << "Input is invalid. Enter a new input: ";
        }
    }

    //changes the value in the data table to a 1 if player X just went or a 2 if player 0 just went
    table[i_input][j_input] = (turn % 2) + 1;

    //puts an X or O in the valid spot in the output table
    (turn % 2) ? output_table[i_input][j_input] = "X" : output_table[i_input][j_input] = "O";

    //makes a new line for readability
    cout << endl;
}

//this function outputs the 2d vector into a table you can read in the console
void game_output(vector<vector<string>> output_table)
{
    //setting the width of each column in the table
    const int COLUMN_WIDTH = 7;

    //looping through every coordinate [i][j]
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << left << setw(COLUMN_WIDTH) << setfill(' ') << output_table[i][j]; //outputting the value in the table at the correct spot in the console
        }
        cout << endl; //making a new line when the loop moves on to the next row
    }

    cout << endl; //making a new line at the end of the table for better readability
}

//fills the output table with the initial output which is just the numbers from 1 to 16
void fill_output_table(vector<vector<string>>& output_table)
{
    //declaring a variable to be used as a counter to fill the table with consecutive numbers
    int counter = 1;

    //looping through every coordinate [i][j]
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            output_table[i][j] = to_string(counter); //setting the value at the given coordinate to the counter as a string
            counter++; //incrementing the counter
        }
    }
}
//this function runs the upper most level of the game logic
void game()
{
    //creating a 4x4 2d vector of integers filled with 0s to store the board data
    vector<vector<int>> table(4, vector<int>(4, 0));

    //creating a 4x4 2d vector of strings to store the output
    vector<vector<string>> output_table(4, vector<string>(4));

    //filling the output table with numbers from 1 to 16
    fill_output_table(output_table);

    //outputting the first iteration of the board
    game_output(output_table);

    //declaring a variable that keeps track of whether the game has been won or not
    bool game_won = false;

    //declaring a variable to keep track of the turn number
    int turn = 0;

    //looping until either the game has been won or the board is filled up because all 16 turns have been used
    while (!game_won && turn < 16)
    {
        //incrementing the turn
        turn++;

        //asking for player input and modifying the data tables
        game_input(table, output_table, turn);

        //outputing the new output table
        game_output(output_table);

        //checking if the game has been won
        game_won = win_check(table);
    }

    //output for when the game is over
    if (game_won)
    {
        cout << ((turn % 2) ? "X has won!" : "O has won!"); //this formula outputs who wins based on who took the last turn
    }
    else {
        cout << "Game is a tie"; //outputs that the game is a tie if the game has not been won
    }
}


//main method to run the game method
int main()
{
    game();
}