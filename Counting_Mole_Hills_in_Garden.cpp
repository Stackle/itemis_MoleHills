#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
#define MAX_SYMBOLS_IN_LINES 16
#define MAX_LINES 16

string field[MAX_LINES];
string area[MAX_SYMBOLS_IN_LINES][MAX_LINES];

int amountOfMoleHills;

void floodFillUtil(string field[][MAX_LINES], int x, int y, string prevDot, string nextDot){
    if(x < 0 || x >= MAX_SYMBOLS_IN_LINES || y < 0 || y >= MAX_LINES){
        return;
    }
    if(field[x][y] == "+")return;
    if(field[x][y] == "-")return;
    if(field[x][y] == "|")return;
    if(field[x][y] == " ")return;
    if(field[x][y] == nextDot)return;

    field[x][y] = nextDot;

    floodFillUtil(field, x+1, y, prevDot, nextDot);
    floodFillUtil(field, x-1, y, prevDot, nextDot);
    floodFillUtil(field, x, y+1, prevDot, nextDot);
    floodFillUtil(field, x, y-1, prevDot, nextDot);
}

void floodFill(string field[][MAX_LINES], int x, int y, string nextDot){
    string prevDot = "o";
    floodFillUtil(field, x, y, prevDot, nextDot);
}

void lookingForGarden(int x, int y){
    for(int i = 0; i < MAX_LINES; i++){
        string nextDot = "x";
        floodFill(area, x, y, nextDot);
    }
}

void lookingForMap(){
    for(int i = 0; i < MAX_LINES - 1; i++){
        for(int j = 0; j < MAX_SYMBOLS_IN_LINES - 1; j++){
            if(area[i][j] == "."){
                lookingForGarden(j, i);
            }
            if(area[i][j] == "o" && (area[i+1][j] == "-" 
            && area[i-1][j] == "-") 
            && (area[i][j+1] == "o")
            && (area[i][j-1] == "|")
            || ((area[0][j] == "o") || (area[i][0] == "o"))){
                lookingForGarden(i,j);
            }
        }
    }
}

void createField(){
    for (int i = 0; i < MAX_SYMBOLS_IN_LINES; i++) {
        string line;
        getline(cin, line);
        field[i] = line;
    }
}

void fieldIntoArea(){
    for(int i = 0; i < MAX_LINES; i++){
        for(int j = 0; j < MAX_SYMBOLS_IN_LINES; j++){
            area[j][i] = field[j][i];
        }
    }
}

int main()
{
    createField();
    fieldIntoArea();
    lookingForMap();
    
    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    for(int i = 0; i < 16; i++){
        for(int j = 0; j< 16; j++){
            if(area[j][i] == "o"){
                amountOfMoleHills++;
            }
            //cout << area[i][j];
        }
        //cout << endl;
    }
    cout<< amountOfMoleHills << endl;
}