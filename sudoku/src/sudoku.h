#include <iostream>
#include <cstring>

class Sudoku {
private:
    int grid[9][9]{};

public:
    explicit Sudoku(int (*grid)[9]) {
        memcpy(this->grid, grid, 9 * 9 * sizeof(int));
    }

    bool operator ==(const int (*otherGrid)[9]) {
        for (int i=0; i<9*9; i++) {
            if (grid[i%3][i/3] != otherGrid[i%3][i/3]) {
                return false;
            }
        }
        return true;
    }

    bool operator ==(const Sudoku & other) {
        for (int i=0; i<9*9; i++) {
            if (grid[i%3][i/3] != other.grid[i%3][i/3]) {
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

    bool solve() {
        int row, col;

        if (!FindUnassignedLocation(grid, row, col))
            return true;

        for (int num = 1; num <= 9; num++)
        {
            if (isSafe(grid, row, col, num))
            {
                grid[row][col] = num;
                if (SolveSudoku(grid))
                    return true;
                grid[row][col] = UNASSIGNED;
            }
        }
        return false;
    }
    bool helper(int grid[9,9],int&row, int& col){
        for(row = 0; row< 9; row++){
            for(col = 0; col <9; col++){
                if(grid[row, col]== 0){
                    return true;
                }
            }
        }
        return false;
    }
};
