#include <stdio.h>
#include <string.h>
#include <math.h>

char world[6][6] = {{'A', '.', '.', '#', '.', '.'}, {'.', '.', '.', '#', '.', '.'}, {'.', '#', '#', '#', '.', '.'}
        , {'.', '.', '.', '#', '.', '.'}, {'.', '.', '.', '.', '#', 'H'}, {'.', '.', '.', '.', '.', '.'}};

int min(int a, int b){
    if(a > b)return b;
    return a;
}

int max(int a, int b){
    if(a > b)return a;
    return b;
}

void win(){
}

/* in function gharare yek tak harkato ham check kone ham age lazem shod heyvoon ro ja be ja kone */
int single_move(char code, int row, int col, char mode){      // code jahat harkato moshakhas mikone
    switch (code) {                                          // mode agar c bashe yani faghat check she agar m bashe
        case '6':                                            // yani harkat ham dade she
            if(world[row][col + 1] == '.'|| world[row][col + 1] == 'H'){
                if(world[row][col + 1] == 'H'){
                    win();
                    return 0;
                }
                else if (mode == 'm'){
                    world[row][col + 1] = world[row][col];
                    world[row][col] = '.';
                }
                break;
            }
            else return 0;
        case '9':
            if(world[row - 1][col + 1] == '.'|| world[row - 1][col + 1] == 'H'){
                if(world[row - 1][col + 1] == 'H'){
                    win();
                    return 0;
                }
                else  if (mode == 'm'){
                    world[row - 1][col + 1] = world[row][col];
                    world[row][col] = '.';
                }
                break;
            }
            else return 0;
        case '8':
            if(world[row - 1][col] == '.'|| world[row - 1][col] == 'H'){
                if(world[row - 1][col] == 'H'){
                    win();
                    return 0;
                }
                else if (mode == 'm'){
                    world[row - 1][col] = world[row][col];
                    world[row][col] = '.';
                }
                break;
            }
            else return 0;
        case '7':
            if(world[row - 1][col - 1] == '.'|| world[row - 1][col - 1] == 'H'){
                if(world[row - 1][col - 1] == 'H'){
                    win();
                    return 0;
                }
                else if (mode == 'm'){
                    world[row - 1][col - 1] = world[row][col];
                    world[row][col] = '.';
                }
                break;
            }
            else return 0;
        case '4':
            if(world[row][col - 1] == '.'|| world[row][col - 1] == 'H'){
                if(world[row][col - 1] == 'H'){
                    win();
                    return 0;
                }
                else if (mode == 'm') {
                    world[row][col - 1] = world[row][col];
                    world[row][col] = '.';
                }
                break;
            }
            else return 0;
        case '1':
            if(world[row + 1][col - 1] == '.'|| world[row + 1][col - 1] == 'H'){
                if(world[row + 1][col - 1] == 'H'){
                    win();
                    return 0;
                }
                else if (mode == 'm') {
                    world[row + 1][col - 1] = world[row][col];
                    world[row][col] = '.';
                }
                break;
            }
            else return 0;
        case '2':
            if(world[row + 1][col] == '.'|| world[row + 1][col] == 'H'){
                if(world[row + 1][col] == 'H'){
                    win();
                    return 0;
                }
                else if (mode == 'm') {
                    world[row + 1][col] = world[row][col];
                    world[row][col] = '.';
                }
                break;
            }
            else return 0;
        case '3':
            if(world[row + 1][col + 1] == '.'|| world[row + 1][col + 1] == 'H'){
                if(world[row + 1][col + 1] == 'H'){
                    win();
                    return 0;
                }
                else if (mode == 'm') {
                    world[row + 1][col + 1] = world[row][col];
                    world[row][col] = '.';
                }
                break;
            }
            else return 0;
    }
    return 1;
}

int shortest_way(const int * a, const int * b){
    int a_row = a[0], a_col = a[1], b_row = b[0], b_col = b[1];
    int total_moves = max(abs(b_row - a_row) , abs(b_col - a_col));
    int orib_num = min(abs(b_row - a_row) , abs(b_col - a_col));
    char way_code[20];      // code baraye zakhire harakatame
    int row_direction, col_direction;    // ina mige bayad dar satr va soton be rast beram ya chap va bala ya payin
    if(b_row > a_row){
        if(b_col > a_col){
            row_direction = 1;
            col_direction = 1;
        }
        else{
            row_direction = 1;
            col_direction = -1;
        }
    }
    else{
        if(b_col > a_col){
            row_direction = -1;
            col_direction = 1;
        }
        else{
            row_direction = -1;
            col_direction = -1;
        }
    }

}
