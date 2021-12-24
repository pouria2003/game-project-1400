#include <stdio.h>
#include <string.h>
#include <math.h>

char world[6][6] = {{'A', '.', '.', '#', '.', '.'}, {'.', '.', '.', '#', '.', '.'}, {'.', '#', '#', '#', '.', '.'}
        , {'.', '.', '.', '#', '.', '.'}, {'.', '.', '.', '.', '#', 'H'}, {'.', '.', '.', '.', '.', '.'}};


void win(){
}

/* in function gharare yek tak harkato ham check kone ham age lazem shod heyvoon ro ja be ja kone */
int single_move(char code, int * r, int * c, char mode){      // code jahat harkato moshakhas mikone
    int row = *r, col = *b;                                   // r hamon pointer be row va c pointer be column
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
                *c += 1;
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
                *r -= 1;
                *c += 1;
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
                *r -= 1;
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
                *r -= 1;
                *c -= 1;
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
                *c -= 1;
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
                *r += 1;
                *c -= 1;
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
                *r += 1;
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
                *r += 1;
                *c += 1;
                break;
            }
            else return 0;
    }
    return 1;
}

    // int ModifyWay(int * way_code_index, char * way_code, char direct_move, char oblique_move, ){
    //     while(*way_code_index){
    //         way_code[*way_code_index] = '\0';
    //         way_code_index--;
    //         if(way_code[*way_code_index] == direct_move){
    //             if(oblique_moves_number > 0){
    //                 if(single_move(oblique_move, &a_row, &a_col, 'c')){
    //                     way_code[way_code_index] = oblique_move;
    //                     oblique_moves_number--;
    //                     direct_moves_numbers++;
    //                     way_code_index++;
    //                     a_row = a[0];
    //                     a_col = a[1];
    //                     for(int i = 0; i < way_code_index; i++){
    //                         single_move(way_code[i], &a_row, &a_col, 'c');
    //                     }
    //                     return 1;
    //                 }
    //                 else direct_moves_numbers++;
    //             }
    //         }
    //         else oblique_moves_number++;
    //     }
    //     return 0;
    // }

// int shortest_way(const int * a, const int * b){
//     int a_row = a[0], a_col = a[1], b_row = b[0], b_col = b[1];
//     int total_moves;
//     int oblique_moves_number;
//     int direct_moves_numbers;
//     char way_code[20];      // code baraye zakhire harakata
//     int way_code_index = 0;
//     char oblique_move, direct_move;
//     int ofoghi;
//     int sw;             // jelo tar migam koja estefade mishe
//     if(abs(b_row - a_row) > abs(b_col - a_col)){
//         total_moves = abs(b_row - a_row);
//         oblique_moves_number = abs(b_col - a_col);
//         ofoghi = 0;
//     }
//     else{
//         oblique_moves_number = abs(b_row - a_row);
//         total_moves = abs(b_col - a_col);
//         ofoghi = 1;
//     }

//     direct_moves_numbers = total_moves - oblique_moves_number;

//     if(b_row > a_row){
//         if(b_col > a_col){
//             oblique_move = '3';
//             direct_move = (ofoghi) ? '6' : '2';
//         }
//         else{
//             oblique_move = '1';
//             direct_move = (ofoghi) ? '4' : '2';
//         }
//     }
//     else{
//         if(b_col > a_col){
//             oblique_move = '9';
//             direct_move = (ofoghi) ? '6' : '8';
//         }
//         else{
//             oblique_move = '7';
//             direct_move = (ofoghi) ? '4' : '8';
//         }
//     }

    
//     while(1) {
//         if (direct_moves_numbers > 0) {
//             if (single_move(direct_move, &a_row, &a_col, 'c')) {
//                 way_code[way_code_index] = direct_move;
//                 way_code_index++;
//                 direct_moves_numbers--;
//             } else if (oblique_moves_number > 0) {
//                 if (single_move(oblique_move, &a_row, &a_col, 'c')) {
//                     way_code[way_code_index] = oblique_move;
//                     way_code_index++;
//                     oblique_moves_number--;
//                 } else
//                 {
//                     sw = 0;
//                     while(way_code_index){
//                         way_code[way_code_index] = '\0';
//                         way_code_index--;
//                         if(way_code[way_code_index] == direct_move){
//                             if(oblique_moves_number > 0){
//                                 if(single_move(oblique_move, &a_row, &a_col, 'c')){
//                                     way_code[way_code_index] = oblique_move;
//                                     oblique_moves_number--;
//                                     direct_moves_numbers++;
//                                     way_code_index++;
//                                     a_row = a[0];
//                                     a_col = a[1];
//                                     for(int i = 0; i < way_code_index; i++){
//                                         single_move(way_code[i], &a_row, &a_col, 'c');
//                                     }
//                                     sw = 1;
//                                     break;
//                                 }
//                                 else direct_moves_numbers++;
//                             }
//                         }
//                         else oblique_moves_number++;
//                     }
//                     if(sw){
//                         return 0;
//                     }
//                 }
//             else{
//                 sw = 0;
//                     while(way_code_index){
//                         way_code[way_code_index] = '\0';
//                         way_code_index--;
//                         if(way_code[way_code_index] == direct_move){
//                             if(oblique_moves_number > 0){
//                                 if(single_move(oblique_move, &a_row, &a_col, 'c')){
//                                     way_code[way_code_index] = oblique_move;
//                                     oblique_moves_number--;
//                                     direct_moves_numbers++;
//                                     way_code_index++;
//                                     a_row = a[0];
//                                     a_col = a[1];
//                                     for(int i = 0; i < way_code_index; i++){
//                                         single_move(way_code[i], &a_row, &a_col, 'c');
//                                     }
//                                     sw = 1;
//                                     break;
//                                 }
//                                 else direct_moves_numbers++;
//                             }
//                         }
//                         else oblique_moves_number++;
//                     }
//                     if(sw){
//                         return 0;
//                     }
//             }
//         } else if (oblique_move > 0) {
//             if (single_move(oblique_move, &a_row, &a_col, 'c')){
//                 way_code[way_code_index] = oblique_move;
//                 oblique_moves_number--;
//                 way_code_index++;
//             }else {
//                 sw = 0;
//                     while(way_code_index){
//                         way_code[way_code_index] = '\0';
//                         way_code_index--;
//                         if(way_code[way_code_index] == direct_move){
//                             if(oblique_moves_number > 0){
//                                 if(single_move(oblique_move, &a_row, &a_col, 'c')){
//                                     way_code[way_code_index] = oblique_move;
//                                     oblique_moves_number--;
//                                     direct_moves_numbers++;
//                                     way_code_index++;
//                                     a_row = a[0];
//                                     a_col = a[1];
//                                     for(int i = 0; i < way_code_index; i++){
//                                         single_move(way_code[i], &a_row, &a_col, 'c');
//                                     }
//                                     sw = 1;
//                                     break;
//                                 }
//                                 else direct_moves_numbers++;
//                             }
//                         }
//                         else oblique_moves_number++;
//                     }
//                     if(sw){
//                         return 0;
//                     }
//             }
            
//         }
//         else break;
//     }
//     }
//     if(a_row == b_row && a_col == b_col){
//     printf("%s", way_code);
//     return 1;
//     }
// }
// int a[2] = {0,0};
// int b[2] = {4,2};
// int main(){
//     shortest_way(a, b);
// }