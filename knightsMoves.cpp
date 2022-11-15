#include <iostream>
#include <utility> 
#include <stach> 

using namespace std;

int backtracking(std::pair <int, int> startingPair, 
                    std::pair <int, int> curPair, int boardSize){

    std::stack<std::pair <int, int>> moves = calculatePossibleMoves(boardSize, curPair.first, curPair.second);
    curPair = moves.top();
    moves.pop();
    return backtracking(curPair, boardSize);
}

/* 
    params: 
        - max: is the max index of the board (ex. in a 10x10 board the max is 9)
        - x: the x position
        - y: the y position
        
    returns a stack containing the pairs (x,y) of all possible moves from a 
    starting position
*/ 
std::stack<std::pair <int, int>> calculatePossibleMoves(int max, int x, int y) {
    int tempX, tempY;
    std::stack<std::pair <int, int>> moves;
    tempX = x + 1;
    if(tempX <= max){
        tempY = y + 2;
        if(tempY <= maxY)
            moves.push(std::make_pair(tempX, tempY))
        tempY = y - 2;
        if(tempY >= 0)
            moves.push(std::make_pair(tempX, tempY))
    }

    tempX = x - 1;
    if(tempX >= 0){
        tempY = y + 2;
        if(tempY <= max)
            moves.push(std::make_pair(tempX, tempY))
        tempY = y - 2;
        if(tempY >= 0)
            moves.push(std::make_pair(tempX, tempY))
    }

    tempX = x + 2;
    if(tempX <= max){
        tempY = y + 1;
        if(tempY <= maxY)
            moves.push(std::make_pair(tempX, tempY))
        tempY = y - 1;
        if(tempY >= 0)
            moves.push(std::make_pair(tempX, tempY))
    }

    tempX = x - 2;
    if(tempX >= 0){
        tempY = y + 1;
        if(tempY <= max)
            moves.push(std::make_pair(tempX, tempY))
        tempY = y - 1;
        if(tempY >= 0)
            moves.push(std::make_pair(tempX, tempY))
    }

    return moves;
}

int main (){
    int boardSize; 
    std::pair <int, int> startingPair;
    int tempX, tempY, pieceValue, numFilledLabels;

    cin >> boardSize;
    int board [boardSize][boardSize] = {};

    cin >> tempX;
    cin >> tempY;
    startingPair = std::make_pair(tempX, tempY);

    // fill the board with preexisting labels
    cin >> numFilledLabels;
    for(int i = 0; i < numFilledLabels; i++){
        cin >> tempX;
        cin >> tempY;
        cin >> pieceValue;
        board[tempX][tempY] = pieceValue;
    }
    


    

}