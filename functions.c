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
int single_move(char code, int * r, int * c, char mode){      // code jahat harkato moshakhas mikone
    int row = * r , col = * c;
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
                    * c += 1;
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
                    * r -= 1;
                    * c += 1;
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
                    * r -= 1;
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
                    * r -= 1;
                    * c -= 1;
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
                    * c -= 1;
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
                    * r += 1;
                    * c -= 1;
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
                    * r += 1;
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
                    * r += 1;
                    * c += 1;
                }
                break;
            }
            else return 0;
    }
    return 1;
}

int shortest_way(int * a, const int * b){
    int a_row = a[0], a_col = a[1], b_row = b[0], b_col = b[1];
    int total_moves;
    int orib_moves_number;
    int non_orib_moves_numbers;
    char way_code[20];      // code baraye zakhire harakata
    int way_code_index = 0;
    char orib_move, non_orib_move;
    int ofoghi;
    if(abs(b_row - a_row) > abs(b_col - a_col)){
        total_moves = abs(b_row - a_row);
        orib_moves_number = abs(b_col - a_col);
        ofoghi = 0;
    }
    else{
        orib_moves_number = abs(b_row - a_row);
        total_moves = abs(b_col - a_col);
        ofoghi = 1;
    }

    non_orib_moves_numbers = total_moves - orib_moves_number;

    if(b_row > a_row){
        if(b_col > a_col){
            orib_move = '3';
            non_orib_move = (ofoghi) ? '6' : '2';
        }
        else{
            orib_move = '1';
            non_orib_move = (ofoghi) ? '4' : '2';
        }
    }
    else{
        if(b_col > a_col){
            orib_move = '9';
            non_orib_move = (ofoghi) ? '6' : '8';
        }
        else{
            orib_move = '7';
            non_orib_move = (ofoghi) ? '4' : '8';
        }
    }
    while(1) {
        if (non_orib_moves_numbers > 0) {
            if (single_move(non_orib_move, a, 'c')) {
                way_code[way_code_index] = non_orib_move;
                way_code_index++;
                non_orib_moves_numbers--;
            } else if (orib_moves_number > 0) {
                if (single_move(orib_move, a, 'c')) {
                    way_code[way_code_index] = orib_move;
                    way_code_index++;
                    orib_moves_number--;
                } else {
                    way_code_index--;
                    way_code[way_code_index] = '\0';
                    way_code_index--;
                    if (way_code[way_code_index] == non_orib_move) {
                        way_code[way_code_index] = orib_move;
                        orib_moves_number--;
                        non_orib_moves_numbers++;
                    }
                }
            }
        } else if (orib_move > 0) {

        }
        else break;

    }
}
