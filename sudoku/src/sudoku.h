#include <iostream>
#include <cstring>
using namespace std;
class Sudoku {
private:
    int grid[9][9]{};

public:
    explicit Sudoku(int (*grid)[9]) {
        memcpy(this->grid, grid, 9 * 9 * sizeof(int));
    }

    bool operator ==(const int (*otherGrid)[9]) {
        for (int i=0; i<9*9; i++) {
            if (grid[i%9][i/9] != otherGrid[i%9][i/9]) {
                return false;
            }
        }
        return true;
    }

    bool operator ==(const Sudoku & other) {
        for (int i=0; i<9*9; i++) {
#ifdef PRINT
            printf("comparing grid(%d, %d)\n", i%9, i/9);
#endif
            if (grid[i%9][i/9] != other.grid[i%9][i/9]) {
                return false;
            }
        }
        return true;
    }


    int get(int i, int j) {
        if (i >= 0 && i < 9 && j >= 0 && j < 9) {
            return grid[i][j];
        }

        return -1;
    }

    int set(int i, int j, int val) {
        if (i >= 0 && i < 9 && j >= 0 && j < 9) {
            return grid[i][j] = val;
        }
        return -1;
    }

    void print() {
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) {
                printf(" [%d] ", get(i, j));
                if (j == 8) {
                    printf("\n");
                }
            }
        }
    }

    bool checkRows(int row, int num){
        for(int i=0;i<9;i++){
            if(grid[row][i]==num ){
                return true;
            }
        }
        return false;
    }

    bool checkCol(int col, int num){
         for(int i=0;i<9;i++){
            if(grid[i][col]==num ){
                return true;
            }
        }
        return false;
    }

    bool checkBox(int row, int col, int num) {
        for(int i = 0 ; i< 3 ; i++){
            for(int j = 0; j < 3 ; j++){
                if(grid[i+row][j+col]==num ){
                    return true;
                }
            }
        }
        return false;
    }
    //https://codepumpkin.com/sudoku-solver-using-backtracking/
    bool checkRules( int row, int col, int num) {
        return !(checkRows(row,num)||checkCol(col,num)||checkBox(row-row%3, col-col%3, num));
    }

    bool solve() {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (grid[row][col] == 0) {
                    for (int num = 1; num <= 9; num++) {
                        if (checkRules(row, col, num)) {
                            grid[row][col] = num;
                            if (solve()) {
                                return true;
                            } else {
                                grid[row][col] = 0;
                            }
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }


};