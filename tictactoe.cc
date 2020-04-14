#include <string>
#include <vector>
#include <iostream>
#include <math.h> 

using namespace std;

void printGrid(vector<vector<string> > table){
    cout << " 0 1 2" << endl;
    for(int i = 0; i < 3; i ++){
        cout << i;
        for(int j = 0; j < 3; j++){
            string bar = "|";
            if( j == 2){
                bar = "";
            }
            cout << table[j][i] << bar;
        }
        cout << endl;
        if(i != 2){
            cout << " -----" << endl;
        }
    }
}

bool threeEqual(string A, string B, string C){
    return(A == B && B == C && A != " ");
}

bool inRange(int low, int high, int x){
    return (low <= x && x <= high);
}

string winnerCheck(vector<vector<string> > table){
    bool blank = false;
    for(int i = 0; i < 3; i++){
        if(threeEqual(table[i][0], table[i][1], table[i][2])){
            return table[i][0];
        }
        else if(threeEqual(table[0][i], table[1][i], table[2][i])) {
            return table[0][i];
        }
        for(int j = 0; j < 3; j++){
            if(table[i][j] == " "){
                blank = true;
            }
        }
    }
    if(threeEqual(table[0][0], table[1][1], table[2][2])) {
        return table[0][0];
    }
    else if(threeEqual(table[0][2], table[1][1], table[2][0])) {
        return table[0][2];
    }
    if(blank == false){
        return "no one";
    }
    return " ";
}

void playerMove(vector<vector<string> > &table, string playerFigure){
    string playerChoice;
    cout << "Where would you like to place your " << playerFigure << " (use the format \"x, y\"): ";
    cin >> playerChoice; // assuming input is valid
    int xcoordinate = playerChoice[0] - '0';
    int ycoordinate = playerChoice[2] - '0';
    table[xcoordinate][ycoordinate] = playerFigure;
}

void computerMove(vector<vector<string> > &table, string computerFigure){
    int xcoordinate = floor((rand()% 3));
    int ycoordinate = floor((rand()% 3));
    while(table[ycoordinate][xcoordinate] != " "){
        xcoordinate = floor((rand()% 3));
        ycoordinate = floor((rand()% 3));
    }
    table[ycoordinate][xcoordinate] = computerFigure;
}

void printVector (vector<vector<int> > available){
    for(int i = 0; i < 9; i ++){
        cout << "[" << available[i][0] << "," << available[i][1] << "]" << endl;
    }
}


int main(int argc, char* argv[]){
    cout << "Would you like to play as X's or O's (input X or O to choose): ";
    string playerFigure = "";
    string computerFigure = "x";
    while(cin >> playerFigure && (playerFigure != "x" && playerFigure !="o")){
        cout << "Would you like to play as X's or O's (input X or O to choose): ";
    }
    vector<vector<string> > grid;
    for(int i = 0 ; i < 3; i++){
        vector<string> row;
        grid.push_back(row);
        for(int j = 0; j < 3; j++){
            grid[i].push_back(" ");
        }
    }
    int movecount = 0;
    if(playerFigure == "x"){
        computerFigure = "o";
        printGrid(grid);
        playerMove(grid, playerFigure);
        movecount++;
    }
    while(winnerCheck(grid) == " "){
        computerMove(grid, computerFigure);
        movecount++;
        if(movecount != 9){
            printGrid(grid);
            playerMove(grid, playerFigure);
            movecount++;
        }
    }
    printGrid(grid);
    cout << winnerCheck(grid) << " won" << endl;
}