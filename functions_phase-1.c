#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>


struct Animal{
   int row;
   int column;
   int energy;
   int single_move_energy;
   int movement_number;
   int reproduction_energy;
   int attack_energy;
   int defense_energy;
};

#define maxside 20
#define maxanimals 50
#define maxuseranimals 10

char world[maxside][maxside];
int integer_world_copy[maxside][maxside];
int world3[maxside][maxside];
int energys[maxside][maxside] = {{0}};
struct Animal program_animals[maxanimals];
struct Animal user_animals[maxuseranimals];
int program_animals_index = 0;
int user_animals_index = 0;
int side;
int lastmojaver[100][2];
int currentmojaver[100][2];
int lastmojaveindex = 0;
int currentmojaverindex = 0;
int counter = 0;
int hx;
int hy;


/*######################################################################  WIN  ##############################################################################*/

void win( char A )
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
    char str2[200] = "Congratulations! Your actions towards saving your species across the apocalypse have been successful! Your kind will now live in peace and serenity.";
    for (int i=0; i<148 ; i++)
    {
        if (i>=0 && i<=15) system ("Color 90");
        printf ("%c",str2[i]);
        Sleep(120);
    }
    exit (0);
}

/*######################################################################  CREATE WORLD COPY  ##############################################################################*/

void CreateWorldCopy(){
    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++){
            if(world[i][j] == '#')integer_world_copy[i][j] = -1;
            else integer_world_copy[i][j] = 0;
        }
    }
}

/*######################################################################  SINGLE MOVE  ##############################################################################*/

/* in function gharare yek tak harkato ham check kone ham age lazem shod heyvoon ro ja be ja kone */
int single_move(char code, int * r, int * c){      // code jahat harkato moshakhas mikone
    int row = *r, col = *c;                                   // r hamon pointer be row va c pointer be column

    switch (code) {

        case '6':
            if(world[row][col + 1] == '.'){
                world[row][col + 1] = world[row][col];
                world[row][col] = '.';
                *c += 1;
            }
            else if(world[row][col + 1] == 'H'){
                win(world[*r][*c]);
                return 1;
            }
            else return 0;
            break;

        case '9':
            if(world[row - 1][col + 1] == '.'){
                world[row - 1][col + 1] = world[row][col];
                world[row][col] = '.';
                *r -= 1;
                *c += 1;
            }
            else if(world[row - 1][col + 1] == 'H'){
                win(world[*r][*c]);
                return 1;
            }
            else return 0;
            break;

        case '8':
            if(world[row - 1][col] == '.'){
                world[row - 1][col] = world[row][col];
                world[row][col] = '.';
                *r -= 1;
            }
            else if(world[row - 1][col] == 'H'){
                win(world[*r][*c]);
                return 1;
            }
            else return 0;
            break;

        case '7':
            if(world[row - 1][col - 1] == '.'){
                world[row - 1][col - 1] = world[row][col];
                world[row][col] = '.';
                *r -= 1;
                *c -= 1;
            }
            else if(world[row - 1][col - 1] == 'H'){
                win(world[*r][*c]);
                return 1;
            }
            else return 0;
            break;

        case '4':
            if(world[row][col - 1] == '.'){
                world[row][col - 1] = world[row][col];
                world[row][col] = '.';
                *c -= 1;
            }
            else if(world[row][col - 1] == 'H'){
                win(world[*r][*c]);
                return 1;
            }
            else return 0;
            break;

        case '1':
            if(world[row + 1][col - 1] == '.'){
                world[row + 1][col - 1] = world[row][col];
                world[row][col] = '.';
                *r += 1;
                *c -= 1;
            }
            else if(world[row + 1][col - 1] == 'H'){
                win(world[*r][*c]);
                return 1;
            }
            else return 0;
            break;

        case '2':
            if(world[row + 1][col] == '.'){
                world[row + 1][col] = world[row][col];
                world[row][col] = '.';
                *r += 1;
            }
            else if(world[row + 1][col] == 'H'){
                win(world[*r][*c]);
                return 1;
            }
            else return 0;
            break;

        case '3':
            if(world[row + 1][col + 1] == '.'){
                world[row + 1][col + 1] = world[row][col];
                world[row][col] = '.';
                *r += 1;
                *c += 1;
            }
            else if(world[row + 1][col + 1] == 'H'){
                win(world[*r][*c]);
                return 1;
            }
            else return 0;
            break;

        default :
            return 0;
    }

    return 1;
}

/*######################################################################  FIND WAY  ##############################################################################*/

/*void FindWay(int start_x, int start_y, int * pstop_x, int * pstop_y, char mode){ // f => finde heaven , g => go
    int stop_x = *pstop_x, stop_y = *pstop_y;
     if((start_x == stop_x) && (start_y == stop_y) && (mode == 'g'))return;        // inja mal tamom kardan tabea dar halatie ke ro mode g bashe ke mige age
    // 	integer_world_copy[hx][hy] = 1;                                     // be heyvoon resid adadet dige adad nazar va harkat kon be khune i ke faselash kamtare

    //     if(integer_world_copy[stop_x-1][stop_y] == integer_world_copy[stop_x][stop_y] - 1 && stop_x > 0){
    //         if(single_move('8', pstop_x, pstop_y))return;
    //     }
    //     if(integer_world_copy[stop_x+1][stop_y-1] == integer_world_copy[stop_x][stop_y] - 1 && stop_x  < side && stop_y > 0){
    //         if(single_move('1', pstop_x, pstop_y))return;
    //     }
    //     if(integer_world_copy[stop_x+1][stop_y+1] == integer_world_copy[stop_x][stop_y] - 1 && stop_x  < side && stop_y  < side){
    //         if(single_move('3', pstop_x, pstop_y))return;
    //     }
    //     if(integer_world_copy[stop_x-1][stop_y-1] == integer_world_copy[stop_x][stop_y] - 1 && stop_x > 0 && stop_y > 0){
    //         if(single_move('7', pstop_x, pstop_y))return;
    //     }
    //     if(integer_world_copy[stop_x-1][stop_y+1] == integer_world_copy[stop_x][stop_y] - 1 && stop_x > 0 && stop_y  < side){
    //         if(single_move('9', pstop_x, pstop_y))return;
    //     }
    //     if(integer_world_copy[stop_x][stop_y+1] == integer_world_copy[stop_x][stop_y] - 1 && stop_y  < side){
    //         if(single_move('6', pstop_x, pstop_y))return;
    //     }
    //     if(integer_world_copy[stop_x][stop_y-1] == integer_world_copy[stop_x][stop_y] - 1 && stop_y > 0){
    //         if(single_move('4', pstop_x, pstop_y))return;
    //     }
    //     if(integer_world_copy[stop_x+1][stop_y] == integer_world_copy[stop_x][stop_y] -1 && stop_x  < side){
    //         if(single_move('2', pstop_x, pstop_y))return;
    //     }

    //     /* =============== agar dor heyvoon az heyvoon haye dige joori por bashe ke natoone faselasho kam kone be inja mirese ke faselasho taghir nade  ===========*/

    //     if(integer_world_copy[stop_x-1][stop_y] == integer_world_copy[stop_x][stop_y] && stop_x > 0){
    //         if(single_move('8', pstop_x, pstop_y))return;
    //     }
    //     if(integer_world_copy[stop_x+1][stop_y-1] == integer_world_copy[stop_x][stop_y] && stop_x  < side && stop_y > 0){
    //         if(single_move('1', pstop_x, pstop_y))return;
    //     }
    //     if(integer_world_copy[stop_x+1][stop_y+1] == integer_world_copy[stop_x][stop_y] && stop_x  < side && stop_y  < side){
    //         if(single_move('3', pstop_x, pstop_y))return;
    //     }
    //     if(integer_world_copy[stop_x-1][stop_y-1] == integer_world_copy[stop_x][stop_y] && stop_x > 0 && stop_y > 0){
    //         if(single_move('7', pstop_x, pstop_y))return;
    //     }
    //     if(integer_world_copy[stop_x-1][stop_y+1] == integer_world_copy[stop_x][stop_y] && stop_x > 0 && stop_y  < side){
    //         if(single_move('9', pstop_x, pstop_y))return;
    //     }
    //     if(integer_world_copy[stop_x][stop_y+1] == integer_world_copy[stop_x][stop_y] && stop_y  < side){
    //         if(single_move('6', pstop_x, pstop_y))return;
    //     }
    //     if(integer_world_copy[stop_x][stop_y-1] == integer_world_copy[stop_x][stop_y] && stop_y > 0){
    //         if(single_move('4', pstop_x, pstop_y))return;
    //     }
    //     if(integer_world_copy[stop_x+1][stop_y] == integer_world_copy[stop_x][stop_y] && stop_x  < side){
    //         if(single_move('2', pstop_x, pstop_y))return;
    //     }

    //     for(int i = 1; i < 10; i++){
    //         if(single_move(i + '0', pstop_x, pstop_y))return;
    //     }
    // }

    //int a = integer_world_copy[start_x][start_y] + 1;

    /*======== inja ma miaim mojaver haye ghabli (adad ghbli) ro check mikonim va adad jadid ro midim behesh va mirizimesh to mojaver haye jadid  ========

    if(start_x > 0 && integer_world_copy[start_x - 1][start_y] == 0){
        integer_world_copy[start_x - 1][start_y] = a;
        if(world[start_x - 1][start_y] == 'H' && mode == 'f'){
            hx = start_x - 1;
            hy = start_y;
            return;
        }
        currentmojaver[currentmojaverindex][0] = start_x - 1;
        currentmojaver[currentmojaverindex][1] = start_y;
        currentmojaverindex++;
    }
    if(start_x < side && start_y > 0 && integer_world_copy[start_x + 1][start_y-1] == 0){
        integer_world_copy[start_x + 1][start_y - 1] = a;
        if(world[start_x + 1][start_y - 1] == 'H' && mode == 'f'){
            hx = start_x + 1;
            hy = start_y - 1;
            return;
        }
        currentmojaver[currentmojaverindex][0] = start_x + 1;
        currentmojaver[currentmojaverindex][1] = start_y - 1;
        currentmojaverindex++;
    }
    if(start_x < side && start_y < side && integer_world_copy[start_x + 1][start_y + 1] == 0){
        integer_world_copy[start_x + 1][start_y + 1]=a;
        if(world[start_x + 1][start_y + 1] == 'H' && mode == 'f'){
            hx = start_x + 1;
            hy = start_y + 1;
            return;
        }
        currentmojaver[currentmojaverindex][0] = start_x + 1;
        currentmojaver[currentmojaverindex][1] = start_y + 1;
        currentmojaverindex++;
    }
    if(start_x > 0 && start_y > 0 && integer_world_copy[start_x - 1][start_y - 1] == 0){
        if(world[start_x - 1][start_y - 1] == 'H' && mode == 'f'){
            hx = start_x - 1;
            hy = start_y - 1;
            return;
        }
        integer_world_copy[start_x - 1][start_y - 1] = a;
        currentmojaver[currentmojaverindex][0] = start_x - 1;
        currentmojaver[currentmojaverindex][1] = start_y - 1;
        currentmojaverindex++;
    }
    if(start_x > 0 && start_y < side && integer_world_copy[start_x - 1][start_y + 1] == 0){
        integer_world_copy[start_x - 1][start_y + 1] = a;
        if(world[start_x - 1][start_y + 1] == 'H' && mode == 'f'){
            hx = start_x - 1;
            hy = start_y + 1;
            return;
        }
        currentmojaver[currentmojaverindex][0] = start_x - 1;
        currentmojaver[currentmojaverindex][1] = start_y + 1;
        currentmojaverindex++;
    }
    if(start_y < side && integer_world_copy[start_x][start_y + 1] == 0){
        integer_world_copy[start_x][start_y + 1]=a;
        if(world[start_x][start_y + 1] == 'H' && mode == 'f'){
            hx = start_x;
            hy = start_y;
            return;
        }
        currentmojaver[currentmojaverindex][0] = start_x;
        currentmojaver[currentmojaverindex][1] = start_y + 1;
        currentmojaverindex++;
    }
    if(start_y > 0 && integer_world_copy[start_x][start_y - 1] == 0){
        integer_world_copy[start_x][start_y - 1]=a;
        if(world[start_x][start_y - 1] == 'H' && mode == 'f'){
            hx = start_x;
            hy = start_y - 1;
            return;
        }
        currentmojaver[currentmojaverindex][0] = start_x;
        currentmojaver[currentmojaverindex][1] = start_y - 1;
        currentmojaverindex++;
    }
    if(start_x < side && integer_world_copy[start_x + 1][start_y] == 0){
        integer_world_copy[start_x + 1][start_y]=a;
        if(world[start_x + 1][start_y] == 'H' && mode == 'f'){
            hx = start_x + 1;
            hy = start_y;
            return;
        }
        currentmojaver[currentmojaverindex][0] = start_x + 1;
        currentmojaver[currentmojaverindex][1] = start_y;
        currentmojaverindex++;
    }

	integer_world_copy[hx][hy] = 1;
    counter++;

    /*========== inja ham rikhtan mojaver hay e jadid to mojaver haye ghbli va amade shodan baraye farakhani dobare va dar sorat niaz biroon omadan =============

    if(counter < lastmojaveindex){
        FindWay(lastmojaver[counter][0], lastmojaver[counter][1], pstop_x, pstop_y, mode);
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
        FindWay(lastmojaver[0][0], lastmojaver[0][1], pstop_x, pstop_y, mode);
    }
}*/



void FindWay(int start_x, int start_y, int * pstop_x, int * pstop_y, char mode){ // f => finde heaven , g => go
    int stop_x = *pstop_x, stop_y = *pstop_y;
    if((start_x == stop_x) && (start_y == stop_y) && (mode == 'g'))return;        // inja mal tamom kardan tabea dar halatie ke ro mode g bashe ke mige age
/*    	integer_world_copy[hx][hy] = 1;                                     // be heyvoon resid adadet dige adad nazar va harkat kon be khune i ke faselash kamtare
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

        /* =============== agar dor heyvoon az heyvoon haye dige joori por bashe ke natoone faselasho kam kone be inja mirese ke faselasho taghir nade  ===========

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

        for(int i = 1; i < 10; i++){
            if(single_move(i + '0', pstop_x, pstop_y))return;
        }
    }

*/

    if(world[start_x][start_y] == 'H' && mode == 'f'){      // inja mal vaghtie ke ro mode find heaven bashim va mige vaghti be behesh residi mokhtasetesh
        hx = start_x;                                       // negah dar va az tabea bia biroon
        hy = start_y;
        return;
    }

    int a = integer_world_copy[start_x][start_y] + 1;

    /*======== inja ma miaim mojaver haye ghabli (adad ghbli) ro check mikonim va adad jadid ro midim behesh va mirizimesh to mojaver haye jadid  ========*/

    if(start_x > 0 && integer_world_copy[start_x - 1][start_y] == 0){
        integer_world_copy[start_x - 1][start_y] = a;
        currentmojaver[currentmojaverindex][0] = start_x - 1;
        currentmojaver[currentmojaverindex][1] = start_y;
        currentmojaverindex++;
    }
    if(start_x < side && start_y > 0 && integer_world_copy[start_x + 1][start_y-1] == 0){
        integer_world_copy[start_x + 1][start_y - 1] = a;
        currentmojaver[currentmojaverindex][0] = start_x + 1;
        currentmojaver[currentmojaverindex][1] = start_y - 1;
        currentmojaverindex++;
    }
    if(start_x < side && start_y < side && integer_world_copy[start_x + 1][start_y + 1] == 0){
        integer_world_copy[start_x + 1][start_y + 1]=a;
        currentmojaver[currentmojaverindex][0] = start_x + 1;
        currentmojaver[currentmojaverindex][1] = start_y + 1;
        currentmojaverindex++;
    }
    if(start_x > 0 && start_y > 0 && integer_world_copy[start_x - 1][start_y - 1] == 0){
        integer_world_copy[start_x - 1][start_y - 1] = a;
        currentmojaver[currentmojaverindex][0] = start_x - 1;
        currentmojaver[currentmojaverindex][1] = start_y - 1;
        currentmojaverindex++;
    }
    if(start_x > 0 && start_y < side && integer_world_copy[start_x - 1][start_y + 1] == 0){
        integer_world_copy[start_x - 1][start_y + 1] = a;
        currentmojaver[currentmojaverindex][0] = start_x - 1;
        currentmojaver[currentmojaverindex][1] = start_y + 1;
        currentmojaverindex++;
    }
    if(start_y < side && integer_world_copy[start_x][start_y + 1] == 0){
        integer_world_copy[start_x][start_y + 1]=a;
        currentmojaver[currentmojaverindex][0] = start_x;
        currentmojaver[currentmojaverindex][1] = start_y + 1;
        currentmojaverindex++;
    }
    if(start_y > 0 && integer_world_copy[start_x][start_y - 1] == 0){
        integer_world_copy[start_x][start_y - 1]=a;
        currentmojaver[currentmojaverindex][0] = start_x;
        currentmojaver[currentmojaverindex][1] = start_y - 1;
        currentmojaverindex++;
    }
    if(start_x < side && integer_world_copy[start_x+1][start_y]==0){
        integer_world_copy[start_x + 1][start_y]=a;
        currentmojaver[currentmojaverindex][0] = start_x + 1;
        currentmojaver[currentmojaverindex][1] = start_y;
        currentmojaverindex++;
    }

    counter++;
    if(mode == 'g') integer_world_copy[hx][hy] == 1;
    /*========== inja ham rikhtan mojaver hay e jadid to mojaver haye ghbli va amade shodan baraye farakhani dobare va dar sorat niaz biroon omadan =============*/

    if(counter < lastmojaveindex){
        FindWay(lastmojaver[counter][0], lastmojaver[counter][1], pstop_x, pstop_y, mode);
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
        FindWay(lastmojaver[0][0], lastmojaver[0][1], pstop_x, pstop_y, mode);
    }
}

/*######################################################################  FIND INTEGER  ##############################################################################*/

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

/*######################################################################  IS EQUAL STR  ##############################################################################*/

int is_equal_str(const char * First_Str, const char * Second_Str){   // in function barabari do ta string ro check mikone
   for(int i = 0; First_Str[i] || Second_Str[i]; i++){
      if(First_Str[i] != Second_Str[i])return 0;
   }
   return 1;
}

/*######################################################################  PRINT  ##############################################################################*/

void print(){           // function print kardan hamoone
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

/*###################################################### TRANSFER TO USER ANIMALS ##########################################################*/

void TransferToUserAnimals(int trans_index){        // in func ye index az program animals migire va mohtavasho mirirze to user animals
    user_animals[user_animals_index] = program_animals[trans_index];
    program_animals_index--;
    user_animals_index++;
    for(int i = trans_index; i < program_animals_index; i++){
        program_animals[i] = program_animals[i + 1];
    }
}

/*###################################################### CREATE WORLD 3 ##########################################################*/

void CreateWorld3(int x,int y){
    int i,j,a,b,c;
    a = integer_world_copy[x][y];
    world3[x][y] = a;
   // printf("puted %d in %d %d \n", a , x , y);
   if(integer_world_copy[x + 1][y] == a - 1 && x < side - 1){
        if(a == 2){   //yani reside be behesht
            world3[x + 1][y] = 1;
            //printf("puted 1 in %d %d \n", x , y);
            return;
                    }
        else{
            CreateWorld3(x + 1, y);
        }
   }
    if(integer_world_copy[x - 1][y] == a - 1 && x > 0){
        if(a == 2){   //yani reside be behesht
            world3[x - 1][y] = 1;
           // printf("puted 1 in %d %d \n", x , y);
            return;
                    }
        else{
            CreateWorld3(x - 1, y);
        }
   }if(integer_world_copy[x + 1][y + 1] == a - 1 && x < side - 1 && y < side - 1){
        if(a == 2){   //yani reside be behesht
            world3[x + 1][y + 1] = 1;
           // printf("puted 1 in %d %d \n", x , y);
            return;
                    }
        else{
            CreateWorld3(x + 1, y + 1);
        }
   }if(integer_world_copy[x - 1][y + 1] == a - 1 && y < side - 1 && x > 0){
        if(a == 2){   //yani reside be behesht
            world3[x - 1][y + 1] = 1;
           // printf("puted 1 in %d %d \n", x , y);
            return;
                    }
        else{
            CreateWorld3(x - 1, y + 1);
        }
   }if(integer_world_copy[x][y + 1] == a - 1 && y < side - 1){
        if(a == 2){   //yani reside be behesht
            world3[x][y + 1] = 1;
           // printf("puted 1 in %d %d \n", x , y);
            return;
        }
        else{
            CreateWorld3(x, y + 1);
        }
   }if(integer_world_copy[x + 1][y - 1] == a - 1 && x < side - 1 && y > 0){
        if(a == 2){   //yani reside be behesht
            world3[x + 1][y - 1] = 1;
           // printf("puted 1 in %d %d \n", x , y);
            return;
                    }
        else{
            CreateWorld3(x + 1, y - 1);
        }
   }if(integer_world_copy[x - 1][y - 1] == a - 1 && x > 0 && y > 0){
        if(a == 2){   //yani reside be behesht
            world3[x - 1][y - 1] = 1;
            //printf("puted 1 in %d %d \n", x , y);
            return;
                    }
        else{
            CreateWorld3(x - 1, y - 1);
        }
   }if(integer_world_copy[x][y - 1] == a - 1  && y > 0){
        if(a == 2){   //yani reside be behesht
            world3[x][y - 1] = 1;
            //printf("puted 1 in %d %d \n", x , y);
            return;
                    }
        else{
            CreateWorld3(x, y - 1);
        }
   }











  /* for(i = -1; i <= 1 ; i++){
        for(j = -1 ;j <= 1; j++){
            if(j != 0 && i != 0){
                if((integer_world_copy[x + i][y + j] == a - 1) && (world[x + i][y + j] == '.' || world[x + i][y + j] == 'H')) {
                    if(a == 2){   //yani reside be behesht
                        /*printf("i am here in createworld3 and find heaven\n");
                        Sleep(3000);
                        world3[x + i][y + j] = 1;
                        printf("puted %d in %d %d \n", a , x , y);
                        return;
                    }
                    else{
                        CreateWorld3(x + i, y + j);
                    }
                }
            }
        }
    }*/
}

/*###################################################### MOVE WITH WORLD 3 ##########################################################*/

int Move(int *row, int *column){
    int x = *row, y = *column;
    int cur = world3[x][y], sw = 0;

    if(world3[x + 1][y] == cur - 1 && x < side - 1){
        if(single_move('2', row, column))return 1;
    }
   if(world3[x - 1][y] == cur - 1 && x > 0){
        if(single_move('8', row, column))return 1;
   }
   if(world3[x + 1][y + 1] == cur - 1 && x < side - 1 && y < side - 1){
        if(single_move('3', row, column))return 1;
   }
   if(world3[x - 1][y + 1] == cur - 1 && y < side - 1 && x > 0){
        if(single_move('9', row, column))return 1;
   }
   if(world3[x][y + 1] == cur - 1 && y < side - 1){
        if(single_move('6', row, column))return 1;
   }
   if(world3[x + 1][y - 1] == cur - 1 && x < side - 1 && y > 0){
        if(single_move('1', row, column))return 1;
   }
   if(world3[x - 1][y - 1] == cur - 1 && x > 0 && y > 0){
        if(single_move('7', row, column))return 1;
   }
   if(world3[x][y - 1] == cur - 1  && y > 0){
        if(single_move('4', row, column))return 1;
   }




       /*for(int i = -1; i <= 1; i++){
            for(int j = -1; j <= 1; j++){
                if((world3[x + i][y + i] == cur - 1) && (world[x + i][y + j] == '.' || world[x + i][y + j] == 'H')){
                    printf("my x is %d , my y is %d and i found %d %d ke tosh hast %d \n", x, y, x + i, y + j, world3[x + i][y + j]);
                    Sleep(8000);
                    if(world[x + i][y + i] == 'H'){
                        printf("im here find heaven\n");
                        Sleep(2000);
                        win(world[x][y]);
                    }
                    world[x + i][y + j] = world[x][y];
                    world[x][y] = '.';
                    *row += i;
                    *column += j;
                    sw = 1;
                    return 1;
                }
            }
        }*/





        if(1){
            printf("come to random section\n");
            cur = integer_world_copy[x][y];
            for(int i = -1; i <= 1; i++){
                for(int j = -1; j <= 1; j++){
                    if(integer_world_copy[x + i][y + i] == cur){
                        world[x + i][y + j] = world[x][y];
                        world[x][y] = '.';
                        *row += i;
                    	*column += j;
                        sw = 1;
                        return 0;
                    }
                }
            }
        }
        if(1){
            for(int i = 1; i < 10; i++){
                if(single_move(i + '0', row, column))return 0;
            }
        }
}
