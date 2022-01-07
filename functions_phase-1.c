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

/*############################################################## LOG THE GAME ######################################################*/

void LogGame(FILE * gamelog, char mode, int round_number, char animal, int animal_number, int array_index, char whos_animal)  // mode s ==> start a new round   and   mode f ==> fill from section
{                                                                                          // and  mode a ==>  fill to section  and  mode k fill kind section
    if(mode == 's')                                                                         // mode  w  ==> win
        fprintf(gamelog, "%s%d%s", "__Round", round_number, "__\n");
    else if(mode == 'k')
        fprintf(gamelog, "%s %c %s %d %s","Kind", animal, "has", animal_number, "animal(s), look at how their coordinate changed in this round:\n");
    else if(mode == 'w')
        fprintf(gamelog, "%s%d%c%d%s %c %s"," to (", round_number, ',', animal_number,")\nand in this movement type", animal, "won!");
    else{
        if(whos_animal == 'p'){
            if(mode == 'f'){
                fprintf(gamelog, "%s%d%c%d%c", "From (", program_animals[array_index].row, ',', program_animals[array_index].column, ')');
            }
            else {
                fprintf(gamelog, "%s%d%c%d%s", " to (", program_animals[array_index].row, ',', program_animals[array_index].column, ")\n");
            }
        }
        else{
            if(mode == 'f'){
                fprintf(gamelog, "%s%d%c%d%c", "From (", user_animals[array_index].row, ',', user_animals[array_index].column, ')');
            }
            else {
                fprintf(gamelog, "%s%d%c%d%s", " to (", user_animals[array_index].row, ',', user_animals[array_index].column, ")\n");
            }
        }
    }
}

/*######################################################################  WIN  ##############################################################################*/

void win( char A )
{
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
                FILE * gamelog = fopen("gamelog.txt", "a");
                LogGame(gamelog, 'w', row, world[row][col], col + 1, 0, 'p');
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
                FILE * gamelog = fopen("gamelog.txt", "a");
                LogGame(gamelog, 'w', row - 1, world[row][col], col + 1, 0, 'p');
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
                FILE * gamelog = fopen("gamelog.txt", "a");
                LogGame(gamelog, 'w', row - 1, world[row][col], col, 0, 'p');
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
                FILE * gamelog = fopen("gamelog.txt", "a");
                LogGame(gamelog, 'w', row - 1, world[row][col], col - 1, 0, 'p');
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
                FILE * gamelog = fopen("gamelog.txt", "a");
                LogGame(gamelog, 'w', row, world[row][col], col - 1, 0, 'p');
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
                FILE * gamelog = fopen("gamelog.txt", "a");
                LogGame(gamelog, 'w', row + 1, world[row][col], col - 1, 0, 'p');
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
                FILE * gamelog = fopen("gamelog.txt", "a");
                LogGame(gamelog, 'w', row + 1, world[row][col], col, 0, 'p');
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
                FILE * gamelog = fopen("gamelog.txt", "a");
                LogGame(gamelog, 'w', row + 1, world[row][col], col + 1, 0, 'p');
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

void FindWay(int start_x, int start_y, int * pstop_x, int * pstop_y, char mode){ // f => finde heaven , g => go
    int stop_x = *pstop_x, stop_y = *pstop_y;
    if((start_x == stop_x) && (start_y == stop_y) && (mode == 'g'))return;        // inja mal tamom kardan tabea dar halatie ke ro mode g bashe ke mige age

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
   if(integer_world_copy[x + 1][y] == a - 1 && x < side - 1){
        if(a == 2){
            world3[x + 1][y] = 1;
            return;
                    }
        else{
            CreateWorld3(x + 1, y);
        }
   }
    if(integer_world_copy[x - 1][y] == a - 1 && x > 0){
        if(a == 2){
            world3[x - 1][y] = 1;
            return;
                    }
        else{
            CreateWorld3(x - 1, y);
        }
   }if(integer_world_copy[x + 1][y + 1] == a - 1 && x < side - 1 && y < side - 1){
        if(a == 2){
            world3[x + 1][y + 1] = 1;
            return;
                    }
        else{
            CreateWorld3(x + 1, y + 1);
        }
   }if(integer_world_copy[x - 1][y + 1] == a - 1 && y < side - 1 && x > 0){
        if(a == 2){
            world3[x - 1][y + 1] = 1;
            return;
                    }
        else{
            CreateWorld3(x - 1, y + 1);
        }
   }if(integer_world_copy[x][y + 1] == a - 1 && y < side - 1){
        if(a == 2){
            world3[x][y + 1] = 1;
            return;
        }
        else{
            CreateWorld3(x, y + 1);
        }
   }if(integer_world_copy[x + 1][y - 1] == a - 1 && x < side - 1 && y > 0){
        if(a == 2){
            world3[x + 1][y - 1] = 1;
            return;
                    }
        else{
            CreateWorld3(x + 1, y - 1);
        }
   }if(integer_world_copy[x - 1][y - 1] == a - 1 && x > 0 && y > 0){
        if(a == 2){
            world3[x - 1][y - 1] = 1;
            return;
                    }
        else{
            CreateWorld3(x - 1, y - 1);
        }
   }if(integer_world_copy[x][y - 1] == a - 1  && y > 0){
        if(a == 2){
            world3[x][y - 1] = 1;
            return;
                    }
        else{
            CreateWorld3(x, y - 1);
        }
   }
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

    if(integer_world_copy[x + 1][y] == integer_world_copy[x][y] && x < side - 1){
        if(single_move('2', row, column))return 0;
    }
   if(integer_world_copy[x - 1][y] == integer_world_copy[x][y] && x > 0){
        if(single_move('8', row, column))return 0;
   }
   if(integer_world_copy[x + 1][y + 1] == integer_world_copy[x][y] && x < side - 1 && y < side - 1){
        if(single_move('3', row, column))return 0;
   }
   if(integer_world_copy[x - 1][y + 1] == integer_world_copy[x][y] && y < side - 1 && x > 0){
        if(single_move('9', row, column))return 0;
   }
   if(integer_world_copy[x][y + 1] == integer_world_copy[x][y] && y < side - 1){
        if(single_move('6', row, column))return 0;
   }
   if(integer_world_copy[x + 1][y - 1] == integer_world_copy[x][y] && x < side - 1 && y > 0){
        if(single_move('1', row, column))return 0;
   }
   if(integer_world_copy[x - 1][y - 1] == integer_world_copy[x][y] && x > 0 && y > 0){
        if(single_move('7', row, column))return 0;
   }
   if(integer_world_copy[x][y - 1] == integer_world_copy[x][y] && y > 0){
        if(single_move('4', row, column))return 0;
   }

    for(int i = 1; i < 10; i++)
        if(single_move(i + '0', row, column))
            return 0;


}

/*############################################################## SAVE THE GAME ###########################################333#*/

void SaveTheGame(char User_Animal)
{
    FILE * savedgame = fopen("savedgame.txt","w");
    fprintf(savedgame, "%d%c", side, '\n');
    fprintf(savedgame, "%c%c", User_Animal, '\n');
    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++){
            if(world[i][j] == 'H' || world[i][j] == '#'){
                fprintf(savedgame,"%c ", world[i][j]);
                fprintf(savedgame,"%d %d ", i, j);
            }
        }
    }
    fprintf(savedgame, "%c", '\n');
    for(int i = 0; i < user_animals_index; i++){
        fprintf(savedgame,"%c ",world[user_animals[i].row][user_animals[i].column]);
        fprintf(savedgame,"%d %d %d %d %d %d %d %d", user_animals[i].row, user_animals[i].column, user_animals[i].energy, user_animals[i].single_move_energy,
                user_animals[i].movement_number, user_animals[i].reproduction_energy
                , user_animals[i].attack_energy, user_animals[i].defense_energy);
        fprintf(savedgame, "%c",'\n');
    }
    for(int i = 0; i < program_animals_index; i++){
        fprintf(savedgame,"%c ",world[program_animals[i].row][program_animals[i].column]);
        fprintf(savedgame,"%d %d %d %d %d %d %d %d", program_animals[i].row, program_animals[i].column, program_animals[i].energy, program_animals[i].single_move_energy,
                program_animals[i].movement_number, program_animals[i].reproduction_energy
                , program_animals[i].attack_energy, program_animals[i].defense_energy);
        fprintf(savedgame, "%c",'\n');
    }
    fclose(savedgame);
}
