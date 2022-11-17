#include <iostream>
#include <utility> 
#include <stack> 
#include <vector> 

using namespace std;

const int boardSize = 10;

void printBoard(int board [boardSize][boardSize]){
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            printf("%d ", board[i][j]);

        }
        printf("\n");
    }
}

/* 
    params: 
        - boardSize: is the max index of the board (ex. in a 10x10 board the max is 9)
        - x: the x position
        - y: the y position
        
    returns a stack containing the pairs (x,y) of all possible moves from a 
    starting position
*/ 
std::stack<std::pair <int, int>> calculatePossibleMoves(int x, int y) {
    int tempX, tempY;
    std::stack<std::pair <int, int>> moves;
    tempX = x + 1;
    if(tempX <= boardSize){
        tempY = y + 2;
        if(tempY <= boardSize)
            moves.push(std::make_pair(tempX, tempY));
        tempY = y - 2;
        if(tempY >= 0)
            moves.push(std::make_pair(tempX, tempY));
    }

    tempX = x - 1;
    if(tempX >= 0){
        tempY = y + 2;
        if(tempY <= boardSize)
            moves.push(std::make_pair(tempX, tempY));
        tempY = y - 2;
        if(tempY >= 0)
            moves.push(std::make_pair(tempX, tempY));
    }

    tempX = x + 2;
    if(tempX <= boardSize){
        tempY = y + 1;
        if(tempY <= boardSize)
            moves.push(std::make_pair(tempX, tempY));
        tempY = y - 1;
        if(tempY >= 0)
            moves.push(std::make_pair(tempX, tempY));
    }

    tempX = x - 2;
    if(tempX >= 0){
        tempY = y + 1;
        if(tempY <= boardSize)
            moves.push(std::make_pair(tempX, tempY));
        tempY = y - 1;
        if(tempY >= 0)
            moves.push(std::make_pair(tempX, tempY));
    }

    return moves;
}

int backtracking(std::pair <int, int> startingPos, std::pair <int, int> curPos, 
                    int nextCount, int board [boardSize][boardSize], 
                    std::vector<std::pair <int, int>> fixedPositions){

    if(nextCount > 50)
        return 0;

    int res, valueOnNewPos;
    bool foundNextStep;
    std::pair <int, int> newPos;
    std::vector<std::pair <int, int>>::iterator it;
    std::stack<std::pair <int, int>> moves = calculatePossibleMoves(curPos.first, curPos.second);

    while(!moves.empty()){
        foundNextStep = false;
        do{
            if(moves.empty()) // out of valid moves
                return -1;

            newPos = moves.top(); // get next move in line
            moves.pop(); // remove from stack

            // get the current value on the aimed position
            valueOnNewPos = board[newPos.first][newPos.second]; 

            // if the value is 0 means that the kniht never passed there before, so is valid move
            // if the value is the same one as the current count, means that is on the right path, it should skip and go on normally
            // any other situation describes an invalid move, it should be discarded
            if(valueOnNewPos == 0 || valueOnNewPos == nextCount)
                foundNextStep = true;  
            
        }while(!foundNextStep);

        // with a valid move, mark the position with the next count
        board[newPos.first][newPos.second] = nextCount;

        res = backtracking(startingPos, newPos, nextCount + 1, board, fixedPositions);

        if(res == -1){ // got a wrong path

            // if its a fixed position the value doesn't change, even if the algorithm fot into a wrong path
            for (it = fixedPositions.begin() ; it != fixedPositions.end(); ++it){
                if((*it).first == newPos.first && (*it).second == newPos.second){
                    return res;
                }
            }
            // if it's not a fixed position, the value is changed back to zero and a new move will be searched for the current count
            board[newPos.first][newPos.second] = 0; // in case of unsuccessful find reset the movement
        } else{
            return res; // in case of successful find
        }
    }
    return -1; // there's no more moves
}


int main (){
    std::pair <int, int> startingPair;
    std::vector <std::pair <int, int>> fixedPositions;
    int tempX, tempY, pieceValue, numFilledPositions, res;

    int board [boardSize][boardSize] = {};

    cin >> tempX;
    cin >> tempY;
    startingPair = std::make_pair(tempX, tempY);

    // fill the board with preexisting labels
    cin >> numFilledPositions;
    for(int i = 0; i < numFilledPositions; i++){
        cin >> tempX;
        cin >> tempY;
        cin >> pieceValue;
        board[tempX][tempY] = pieceValue;
        fixedPositions.push_back(std::make_pair(tempX, tempY));
    }
    printf("\nStarting Board\n\n");
    printBoard(board);
    
    res = backtracking(startingPair, startingPair, 
                board[startingPair.first][startingPair.second] + 1, board, fixedPositions);

    if(res == -1)
        printf("\nPath couldn't be found\n");
    else {
        printf("\n Resulting Board \n\n");
        printBoard(board);
    }


}