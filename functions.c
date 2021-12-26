#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

extern int integer_world_copy[20][20];
extern char world[20][20];
extern int energys[20][20];
extern int animals_coordinate[20][2];
extern int user_animals_coordinate[10][2];
extern int side;
extern int lastmojaver[100][2];
extern int currentmojaver[100][2];
extern int lastmojaveindex;
extern int currentmojaverindex;
extern int counter;
extern int hx;
extern int hy;

int win( char A )
{
	system("cls");
    char str[5] = "Type";
    for (int i=0; i<4 ; i++)
    {
        Sleep (200);
        printf ("%c",str[i]);
    }
    Sleep (300);
    printf (" %c ",A);
    char str1[12] = "survived!!";
    for (int i=0; i<10 ; i++)
    {
        Sleep(150);
        printf ("%c",str1[i]);
    }
    for (int i=1; i<=10; i++)
    {
        system ("Color 07");
        Sleep(200);
        system ("Color 70");
        Sleep(200);
    }
    system ("Color 07");
    system ("cls");
    Sleep(1000);
    char str2[200] = "Congratulations! Your actions toward saving your species across the apocalypse have been successful! Your kind will now live in peace and serenity.";
    for (int i=0; i<147 ; i++)
    {
        if (i>=0 && i<=15) system ("Color 5E");
        printf ("%c",str2[i]);
        Sleep(120);
    }
    exit (0);
}

void CreateWorldCopy(int ax, int ay){
    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++){
            if(world[i][j] == '#')integer_world_copy[i][j] = -1;
            else integer_world_copy[i][j] = 0;
        }
    }
    integer_world_copy[ax][ay] = 0;

}

/* in function gharare yek tak harkato ham check kone ham age lazem shod heyvoon ro ja be ja kone */
int single_move(char code, int * r, int * c){      // code jahat harkato moshakhas mikone
    int row = *r, col = *c;                                   // r hamon pointer be row va c pointer be column

    switch (code) {                                          // mode agar c bashe yani faghat check she agar m bashe
        case '6':                                            // yani harkat ham dade she
            if(world[row][col + 1] == '.'|| world[row][col + 1] == 'H'){
                if(world[row][col + 1] == 'H'){
                    win(world[*r][*c]);
                    return 0;
                }
                else{
                    world[row][col + 1] = world[row][col];
                    world[row][col] = '.';
                    *c += 1;
                }
                break;
            }
            else return 0;
        case '9':
            if(world[row - 1][col + 1] == '.'|| world[row - 1][col + 1] == 'H'){
                if(world[row - 1][col + 1] == 'H'){
                    win(world[*r][*c]);
                    return 0;
                }
                else{
                    world[row - 1][col + 1] = world[row][col];
                    world[row][col] = '.';
                    *r -= 1;
                    *c += 1;
                }
                break;
            }
            else return 0;
        case '8':
            if(world[row - 1][col] == '.'|| world[row - 1][col] == 'H'){
                if(world[row - 1][col] == 'H'){
                    win(world[*r][*c]);
                    return 0;
                }
                else{
                    world[row - 1][col] = world[row][col];
                    world[row][col] = '.'; 
                    *r -= 1;
                }
                break;
            }
            else return 0;
        case '7':
            if(world[row - 1][col - 1] == '.'|| world[row - 1][col - 1] == 'H'){
                if(world[row - 1][col - 1] == 'H'){
                    win(world[*r][*c]);
                    return 0;
                }
                else {
                    world[row - 1][col - 1] = world[row][col];
                    world[row][col] = '.';
                    *r -= 1;
                    *c -= 1;
                }
                
                break;
            }
            else return 0;
        case '4':
            if(world[row][col - 1] == '.'|| world[row][col - 1] == 'H'){
                if(world[row][col - 1] == 'H'){
                    win(world[*r][*c]);
                    return 0;
                }
                else{
                    world[row][col - 1] = world[row][col];
                    world[row][col] = '.';
                    *c -= 1;
                }
                break;
            }
            else return 0;
        case '1':
            if(world[row + 1][col - 1] == '.'|| world[row + 1][col - 1] == 'H'){
                if(world[row + 1][col - 1] == 'H'){
                    win(world[*r][*c]);
                    return 0;
                }
                else {
                    world[row + 1][col - 1] = world[row][col];
                    world[row][col] = '.';
                    *r += 1;
                    *c -= 1;
                }
                break;
            }
            else return 0;
        case '2':
            if(world[row + 1][col] == '.'|| world[row + 1][col] == 'H'){
                if(world[row + 1][col] == 'H'){
                    win(world[*r][*c]);
                    return 0;
                }
                else {
                    world[row + 1][col] = world[row][col];
                    world[row][col] = '.';
                    *r += 1;
                }
                break;
            }
            else return 0;
        case '3':
            if(world[row + 1][col + 1] == '.'|| world[row + 1][col + 1] == 'H'){
                if(world[row + 1][col + 1] == 'H'){
                    win(world[*r][*c]);
                    return 0;
                }
                else {
                    world[row + 1][col + 1] = world[row][col];
                    world[row][col] = '.';
                    *r += 1;
                    *c += 1;
                }
                break;
            }
            else return 0;
        default : 
            return 0;
    }
    return 1;
}

void FindWay(int start_x, int start_y, int * pstop_x, int * pstop_y, char mode){ // f => finde heaven , g => go
    int stop_x = *pstop_x, stop_y = *pstop_y;
    if((start_x == stop_x) && (start_y == stop_y) && (mode == 'g')){
    	integer_world_copy[hx][hy] = 0;
        if(integer_world_copy[stop_x-1][stop_y] == integer_world_copy[stop_x][stop_y] - 1 && stop_x > 0){
            if(single_move('8', pstop_x, pstop_y))return;
        }
        if(integer_world_copy[stop_x+1][stop_y-1] == integer_world_copy[stop_x][stop_y] - 1 && stop_x  < side && stop_y > 0){
            if(single_move('1', pstop_x, pstop_y))return;
        }
        if(integer_world_copy[stop_x+1][stop_y+1] == integer_world_copy[stop_x][stop_y] - 1 && stop_x  < side && stop_y  < side){
            if(single_move('3', pstop_x, pstop_y))return;
        }
        if(integer_world_copy[stop_x-1][stop_y-1] == integer_world_copy[stop_x][stop_y] - 1 && stop_x > 0 && stop_y > 0){
            if(single_move('7', pstop_x, pstop_y))return;
        }
        if(integer_world_copy[stop_x-1][stop_y+1] == integer_world_copy[stop_x][stop_y] - 1 && stop_x > 0 && stop_y  < side){
            if(single_move('9', pstop_x, pstop_y))return;
        }
        if(integer_world_copy[stop_x][stop_y+1] == integer_world_copy[stop_x][stop_y] - 1 && stop_y  < side){
            if(single_move('6', pstop_x, pstop_y))return;
        }
        if(integer_world_copy[stop_x][stop_y-1] == integer_world_copy[stop_x][stop_y] - 1 && stop_y > 0){
            if(single_move('4', pstop_x, pstop_y))return;
        }
        if(integer_world_copy[stop_x+1][stop_y] == integer_world_copy[stop_x][stop_y] -1 && stop_x  < side){
            if(single_move('2', pstop_x, pstop_y))return;
        }

/*#########################################################################################################################################*/

        if(integer_world_copy[stop_x-1][stop_y] == integer_world_copy[stop_x][stop_y] && stop_x > 0){
            if(single_move('8', pstop_x, pstop_y))return;
        }
        if(integer_world_copy[stop_x+1][stop_y-1] == integer_world_copy[stop_x][stop_y] && stop_x  < side && stop_y > 0){
            if(single_move('1', pstop_x, pstop_y))return;
        }
        if(integer_world_copy[stop_x+1][stop_y+1] == integer_world_copy[stop_x][stop_y] && stop_x  < side && stop_y  < side){
            if(single_move('3', pstop_x, pstop_y))return;
        }
        if(integer_world_copy[stop_x-1][stop_y-1] == integer_world_copy[stop_x][stop_y] && stop_x > 0 && stop_y > 0){
            if(single_move('7', pstop_x, pstop_y))return;
        }
        if(integer_world_copy[stop_x-1][stop_y+1] == integer_world_copy[stop_x][stop_y] && stop_x > 0 && stop_y  < side){
            if(single_move('9', pstop_x, pstop_y))return;
        }
        if(integer_world_copy[stop_x][stop_y+1] == integer_world_copy[stop_x][stop_y] && stop_y  < side){
            if(single_move('6', pstop_x, pstop_y))return;
        }
        if(integer_world_copy[stop_x][stop_y-1] == integer_world_copy[stop_x][stop_y] && stop_y > 0){
            if(single_move('4', pstop_x, pstop_y))return;
        }
        if(integer_world_copy[stop_x+1][stop_y] == integer_world_copy[stop_x][stop_y] && stop_x  < side){
            if(single_move('2', pstop_x, pstop_y))return;
        }

        
    }
    if(world[start_x][start_y] == 'H' && mode == 'f'){
        hx = start_x;
        hy = start_y;
        return;
    }
    // printf("x = %d, y = %d\n", x, y);
    int a = integer_world_copy[start_x][start_y] + 1;
    if(start_x > 0 && integer_world_copy[start_x - 1][start_y] == 0){
        integer_world_copy[start_x - 1][start_y] = a;
        // printf("in r = %d , j = %d changed to %d\n", x - 1, y, a);
        currentmojaver[currentmojaverindex][0] = start_x - 1;
        currentmojaver[currentmojaverindex][1] = start_y;
        currentmojaverindex++;
    }
    if(start_x < side && start_y > 0 && integer_world_copy[start_x + 1][start_y-1] == 0){
        integer_world_copy[start_x + 1][start_y - 1] = a;
        // printf("in r = %d , j = %d changed to %d\n", x + 1, y - 1, a);
        currentmojaver[currentmojaverindex][0] = start_x + 1;
        currentmojaver[currentmojaverindex][1] = start_y - 1;
        currentmojaverindex++;
    }
    if(start_x < side && start_y < side && integer_world_copy[start_x + 1][start_y + 1] == 0){
        integer_world_copy[start_x + 1][start_y + 1]=a;
        // printf("in r = %d , j = %d changed to %d\n", x + 1, y + 1, a);
        currentmojaver[currentmojaverindex][0] = start_x + 1;
        currentmojaver[currentmojaverindex][1] = start_y + 1;
        currentmojaverindex++;
    }
    if(start_x > 0 && start_y > 0 && integer_world_copy[start_x - 1][start_y - 1] == 0){
        integer_world_copy[start_x - 1][start_y - 1] = a;
        // printf("in r = %d , j = %d changed to %d\n", x - 1, y - 1, a);
        currentmojaver[currentmojaverindex][0] = start_x - 1;
        currentmojaver[currentmojaverindex][1] = start_y - 1;
        currentmojaverindex++;
    }
    if(start_x > 0 && start_y < side && integer_world_copy[start_x - 1][start_y + 1] == 0){
        integer_world_copy[start_x - 1][start_y + 1] = a;
        // printf("in r = %d , j = %d changed to %d\n", x - 1, y + 1, a);
        currentmojaver[currentmojaverindex][0] = start_x - 1;
        currentmojaver[currentmojaverindex][1] = start_y + 1;
        currentmojaverindex++;
    }
    if(start_y < side && integer_world_copy[start_x][start_y + 1] == 0){
        integer_world_copy[start_x][start_y + 1]=a;
        // printf("in r = %d , j = %d changed to %d\n", x, y + 1, a);
        currentmojaver[currentmojaverindex][0] = start_x;
        currentmojaver[currentmojaverindex][1] = start_y + 1;
        currentmojaverindex++;
    }
    if(start_y > 0 && integer_world_copy[start_x][start_y - 1] == 0){
        integer_world_copy[start_x][start_y - 1]=a;
        // printf("in r = %d , j = %d changed to %d\n", x , y - 1, a);
        currentmojaver[currentmojaverindex][0] = start_x;
        currentmojaver[currentmojaverindex][1] = start_y - 1;
        currentmojaverindex++;
    }
    if(start_x < side && integer_world_copy[start_x+1][start_y]==0){
        integer_world_copy[start_x+1][start_y]=a;
        // printf("in r = %d , j = %d changed to %d\n", x + 1, y, a);
        currentmojaver[currentmojaverindex][0] = start_x + 1;
        currentmojaver[currentmojaverindex][1] = start_y;
        currentmojaverindex++;
    }

    counter++;

//    integer_world_copy[start_x][start_y] = 0;
    if(counter < lastmojaveindex){
        FindWay(lastmojaver[counter][0], lastmojaver[counter][1], pstop_x, pstop_y, mode);
    }
    else{
        if(currentmojaverindex == 0){
        	printf("im here for %c!\n", world[stop_x][stop_y]);
            return;
        }
        for(int i = 0; i < currentmojaverindex; i++){
            lastmojaver[i][0] = currentmojaver[i][0];
            lastmojaver[i][1] = currentmojaver[i][1];
        }
        counter = 0;
        lastmojaveindex = currentmojaverindex;
        currentmojaverindex = 0;
        FindWay(lastmojaver[0][0], lastmojaver[0][1], pstop_x, pstop_y, mode);
    }
}

int find_integer(char * str){    // int function yek string migire va avalin addi ke dakhel string peyda kone barmigardone va  
   int ans = 0;                  // charracter haye string ro bejaye adade mikone '.'
   for(int i = 0; str[i]; i++){
      if(str[i] > 47 && str[i] < 58){
         ans = str[i] - '0';
         str[i] = '.';
         i++;
         if(str[i] > 47 && str[i] < 58){
            ans *= 10;
            ans += str[i] - '0';
            str[i] = '.';
            return ans;
         }
         return ans;
      }
   }
}

int is_equal_str(const char * First_Str, const char * Second_Str){   // in function barabari do ta string ro check mikone
   for(int i = 0; First_Str[i] || Second_Str[i]; i++){
      if(First_Str[i] != Second_Str[i])return 0;
   }
   return 1;
}

void print(){
    int i, j;
    for(i = 0; i < side; i++){
        printf("|");
        for(j = 0; j < side; j++){
            printf("%c", world[i][j]);
            printf("|");
        }
        printf("\n");
    }
}

void shift_eb_payin(int index, int last_index){
    for(; index < last_index; index++){
        animals_coordinate[index][0] = animals_coordinate[index + 1][0];
        animals_coordinate[index][1] = animals_coordinate[index + 1][1];
    }
}