#include <stdio.h>
#include <string.h>
#include <math.h>


extern char world[20][20];
extern int energys[20][20];
extern int animals_coordinate[20][4];
extern int side;
extern int lastmojaver[100][2];
extern int currentmojaver[100][2];
extern int lastmojaveindex;
extern int currentmojaverindex;
extern int counter;
extern int hx;
extern int hy;


void win(){
}

void num(char world[][20], int world2[][20],int x,int y,int size){
    if(world[x][y] == 'H'){
        hx = x;
        hy = y;
        return;
    }
    printf("x = %d, y = %d\n", x, y);
    int a = world2[x][y] + 1;
    if(x > 0 && world2[x-1][y] == 0){
        world2[x-1][y] = a;
        printf("in r = %d , j = %d changed to %d\n", x - 1, y, a);
        currentmojaver[currentmojaverindex][0] = x - 1;
        currentmojaver[currentmojaverindex][1] = y;
        currentmojaverindex++;
    }
    if(x < size && y > 0 && world2[x+1][y-1] == 0){
        world2[x+1][y-1] = a;
        printf("in r = %d , j = %d changed to %d\n", x + 1, y - 1, a);
        currentmojaver[currentmojaverindex][0] = x + 1;
        currentmojaver[currentmojaverindex][1] = y - 1;
        currentmojaverindex++;
    }
    if(x < size && y < size && world2[x+1][y+1] == 0){
        world2[x+1][y+1]=a;
        printf("in r = %d , j = %d changed to %d\n", x + 1, y + 1, a);
        currentmojaver[currentmojaverindex][0] = x + 1;
        currentmojaver[currentmojaverindex][1] = y + 1;
        currentmojaverindex++;
    }
    if(x > 0 && y > 0 && world2[x-1][y-1] == 0){
        world2[x-1][y-1] = a;
        printf("in r = %d , j = %d changed to %d\n", x - 1, y - 1, a);
        currentmojaver[currentmojaverindex][0] = x - 1;
        currentmojaver[currentmojaverindex][1] = y - 1;
        currentmojaverindex++;
    }
    if(x > 0 && y < size && world2[x-1][y+1] == 0){
        world2[x-1][y+1] = a;
        printf("in r = %d , j = %d changed to %d\n", x - 1, y + 1, a);
        currentmojaver[currentmojaverindex][0] = x - 1;
        currentmojaver[currentmojaverindex][1] = y + 1;
        currentmojaverindex++;
    }
    if(y < size && world2[x][y+1] == 0){
        world2[x][y+1]=a;
        printf("in r = %d , j = %d changed to %d\n", x, y + 1, a);
        currentmojaver[currentmojaverindex][0] = x;
        currentmojaver[currentmojaverindex][1] = y + 1;
        currentmojaverindex++;
    }
    if(y > 0 && world2[x][y-1] == 0){
        world2[x][y-1]=a;
        printf("in r = %d , j = %d changed to %d\n", x , y - 1, a);
        currentmojaver[currentmojaverindex][0] = x;
        currentmojaver[currentmojaverindex][1] = y - 1;
        currentmojaverindex++;
    }
    if(x < size && world2[x+1][y]==0){
        world2[x+1][y]=a;
        printf("in r = %d , j = %d changed to %d\n", x + 1, y, a);
        currentmojaver[currentmojaverindex][0] = x + 1;
        currentmojaver[currentmojaverindex][1] = y;
        currentmojaverindex++;
    }

    counter++;
    if(counter < lastmojaveindex){
        num(world, world2, lastmojaver[counter][0], lastmojaver[counter][1], 6);
    }
    else{
        if(currentmojaverindex == 0){
            return;
        }
        for(int i = 0; i < currentmojaverindex; i++){
            lastmojaver[i][0] = currentmojaver[i][0];
            lastmojaver[i][1] = currentmojaver[i][1];
        }
        counter = 0;
        lastmojaveindex = currentmojaverindex;
        currentmojaverindex = 0;
        num(world, world2, lastmojaver[0][0], lastmojaver[0][1], 6);
    }
}




/* in function gharare yek tak harkato ham check kone ham age lazem shod heyvoon ro ja be ja kone */
int single_move(char code, int * r, int * c, char mode){      // code jahat harkato moshakhas mikone
    int row = *r, col = *c;                                   // r hamon pointer be row va c pointer be column
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