#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define maxside 20
#define maxanimals 30
#define maxkindanimals 10
#define maxfood 20

struct Coordinate{
   int row;
   int column;
};

struct Food{
    struct Coordinate food_coordinate;
    Coordinate closest_heaven_coordinate;
    int closest_heaven_distance;
    int food_energy;
    int tempp_food_energy;
};

struct Animal{
    struct Coordinate animal_coordinate;
    int animal_energy;
    int single_move_energy;
    int  movement_number;
    int attack_energy;
    int defense_energy;
    int reproduction_energy;
    Coordinate porposes[5];
};

typedef struct Coordinate Coordinate;
typedef struct Animal Animal;
typedef struct Food Food;

char world[maxside][maxside] = {{'H','.','.','.','H'}, {'#','C','.','.','#'}, {'.','.','#','.','.'}, {'.','.','.','.','.'}, {'A','.','.','.','.','B'}};
Animal program_animals[maxanimals];
int program_animals_index;
Animal user_animals[maxkindanimals];
int user_animals_index;
int side = 5;




Food foods[maxfood];
Coordinate current_mojaver[20];
Coordinate previous_mojaver[20];
int current_mojaver_index = 0;
int previous_mojaver_index = 0;
int counter = 0;
int integer_world_copy[maxside][maxside];
int way_array[maxside][maxside];
int distance = 0;
int SpecifyWay_counter = 0;
Coordinate SpecifyWay_porpose;
int SpecifyWay_minimum = 20;
Coordinate PORPOSE;
int DISTANCE;
Food foods_array[10];
int foods_array_index = 0;
Coordinate FBW_porposes[5];
Coordinate FBW_final_porposes[5];
int FBW_porposes_index = 0;
int minimum_distance = 50;


void CodeReverser(char *codes)
{
    int length = strlen(codes);
    for(int i = 0; i < length / 2; i++){
        char temp = codes[i];
        codes[i] = codes[length - i - 1];
        codes[length - i - 1] = temp;
    }
    for(; *codes; codes+= 1){
        *codes = 106 - *codes;
    }
    printf("%s", codes);
}

void intcpy(int *arr, int *source_arr, int num)
{
    for(; num > 0; num--){
        *arr = *source_arr;
        arr++;
        source_arr++;
    }
}

void CreateIntegerWorldCopy(Coordinate coor)
{
    for(int i = 0; i < side; i++)
        for(int j = 0; j < side; j++)
            if(world[i][j] != '#')
                integer_world_copy[i][j] = 0;
            else
                integer_world_copy[i][j] = -1;
    integer_world_copy[coor.row][coor.column] = 1;
}

void CreateWayArray()
{
    for(int i = 0; i < side; i++)
        for(int j = 0; j < side; j++)
            way_array[i][j] = 0;
}

void PrintW()
{
    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++)
            printf("%c ", world[i][j]);
        printf("\n");
    }
}

void PrintIWC()
{
    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++)
            printf("%d ", integer_world_copy[i][j]);
        printf("\n");
    }
}

void PrintWA()
{
    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++)
            printf("%d ", way_array[i][j]);
        printf("\n");
    }
}

int IsVacant(int row, int column)
{
    if((world[row][column] == '.' || world[row][column] == 'H') && (way_array[row][column] == 0))return 1;
    return 0;
}

int CheckHeaven(Coordinate my_coor, Coordinate *heaven_coor){if(world[my_coor.row][my_coor.column] == 'H'){heaven_coor->row = my_coor.row; heaven_coor->column = my_coor.column; return 1;} return 0;}
int CheckAnimal(Coordinate st_coor, Coordinate *fi_coor){if(st_coor.row == fi_coor->row && st_coor.column == fi_coor->column)return 1; return 0;}
int CheckFood(Coordinate st_coor, Coordinate *fi_coor){if(st_coor.row == fi_coor->row && st_coor.column == fi_coor->column)return 1; return 0;}

int FindDistance(Coordinate current_coor, Coordinate *final_coor, int (*CheckStopCondition)(Coordinate, Coordinate *))
{
    if(CheckStopCondition(current_coor, final_coor))
        return integer_world_copy[current_coor.row][current_coor.column];
    int num = integer_world_copy[current_coor.row][current_coor.column] + 1;
    if(current_coor.row > 0 && integer_world_copy[current_coor.row - 1][current_coor.column] == 0){
        integer_world_copy[current_coor.row - 1][current_coor.column] = num;
        current_mojaver[current_mojaver_index].row = current_coor.row - 1;
        current_mojaver[current_mojaver_index].column = current_coor.column;
        current_mojaver_index++;
    }
    if(current_coor.row < side && current_coor.column > 0 && integer_world_copy[current_coor.row + 1][current_coor.column-1] == 0){
        integer_world_copy[current_coor.row + 1][current_coor.column - 1] = num;
        current_mojaver[current_mojaver_index].row = current_coor.row + 1;
        current_mojaver[current_mojaver_index].column = current_coor.column - 1;
        current_mojaver_index++;
    }
    if(current_coor.row < side && current_coor.column < side && integer_world_copy[current_coor.row + 1][current_coor.column + 1] == 0){
        integer_world_copy[current_coor.row + 1][current_coor.column + 1] = num;
        current_mojaver[current_mojaver_index].row = current_coor.row + 1;
        current_mojaver[current_mojaver_index].column = current_coor.column + 1;
        current_mojaver_index++;
    }
    if(current_coor.row > 0 && current_coor.column > 0 && integer_world_copy[current_coor.row - 1][current_coor.column - 1] == 0){
        integer_world_copy[current_coor.row - 1][current_coor.column - 1] = num;
        current_mojaver[current_mojaver_index].row = current_coor.row - 1;
        current_mojaver[current_mojaver_index].column = current_coor.column - 1;
        current_mojaver_index++;
    }
    if(current_coor.row > 0 && current_coor.column < side && integer_world_copy[current_coor.row - 1][current_coor.column + 1] == 0){
        integer_world_copy[current_coor.row - 1][current_coor.column + 1] = num;
        current_mojaver[current_mojaver_index].row = current_coor.row - 1;
        current_mojaver[current_mojaver_index].column = current_coor.column + 1;
        current_mojaver_index++;
    }
    if(current_coor.column < side && integer_world_copy[current_coor.row][current_coor.column + 1] == 0){
        integer_world_copy[current_coor.row][current_coor.column + 1] = num;
        current_mojaver[current_mojaver_index].row = current_coor.row;
        current_mojaver[current_mojaver_index].column = current_coor.column + 1;
        current_mojaver_index++;
    }
    if(current_coor.column > 0 && integer_world_copy[current_coor.row][current_coor.column - 1] == 0){
        integer_world_copy[current_coor.row][current_coor.column - 1] = num;
        current_mojaver[current_mojaver_index].row = current_coor.row;
        current_mojaver[current_mojaver_index].column = current_coor.column - 1;
        current_mojaver_index++;
    }
    if(current_coor.row < side && integer_world_copy[current_coor.row+1][current_coor.column] == 0){
        integer_world_copy[current_coor.row + 1][current_coor.column] = num;
        current_mojaver[current_mojaver_index].row = current_coor.row + 1;
        current_mojaver[current_mojaver_index].column = current_coor.column;
        current_mojaver_index++;
    }
    counter++;
    if(counter < previous_mojaver_index)
        FindDistance(previous_mojaver[counter], final_coor, CheckStopCondition);
    else{
        if(current_mojaver_index == 0)
            return -1;
        for(int i = 0; i < current_mojaver_index; i++)
            previous_mojaver[i] = current_mojaver[i];
        counter = 0;
        previous_mojaver_index = current_mojaver_index;
        current_mojaver_index = 0;
        FindDistance(previous_mojaver[0], final_coor, CheckStopCondition);
    }
}

void win( char A )
{
    FILE *cleansavedgame = fopen("savedgame.txt", "w");
    fclose(cleansavedgame);
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

void SpecifyWay(Coordinate current_coor, int movement_number)
{
    if(SpecifyWay_counter == movement_number)
        return;
    int number = integer_world_copy[current_coor.row][current_coor.column] - 1;
    if(current_coor.row > 0 && IsVacant(current_coor.row - 1, current_coor.column)){
        way_array[current_coor.row - 1][current_coor.column] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row - 1][current_coor.column] < SpecifyWay_minimum){
            SpecifyWay_porpose.row = current_coor.row - 1;
            SpecifyWay_porpose.column = current_coor.column;
            SpecifyWay_minimum = integer_world_copy[current_coor.row - 1][current_coor.column];
        }
        printf("%d putted in %d %d\n", SpecifyWay_counter + 1, current_coor.row - 1, current_coor.column);
        current_mojaver[current_mojaver_index].row = current_coor.row - 1;
        current_mojaver[current_mojaver_index].column = current_coor.column;
        current_mojaver_index++;
    }
    if(current_coor.row < side && current_coor.column > 0 && IsVacant(current_coor.row + 1, current_coor.column - 1)){
        way_array[current_coor.row + 1][current_coor.column - 1] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row + 1][current_coor.column - 1] < SpecifyWay_minimum){
            SpecifyWay_porpose.row = current_coor.row + 1;
            SpecifyWay_porpose.column = current_coor.column - 1;
            SpecifyWay_minimum = integer_world_copy[current_coor.row + 1][current_coor.column - 1];
        }
        printf("%d putted in %d %d\n", SpecifyWay_counter + 1, current_coor.row - 1, current_coor.column - 1);
        current_mojaver[current_mojaver_index].row = current_coor.row + 1;
        current_mojaver[current_mojaver_index].column = current_coor.column - 1;
        current_mojaver_index++;
    }
    if(current_coor.row < side && current_coor.column < side && IsVacant(current_coor.row + 1, current_coor.column + 1)){
        way_array[current_coor.row + 1][current_coor.column + 1] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row + 1][current_coor.column + 1] < SpecifyWay_minimum){
            SpecifyWay_porpose.row = current_coor.row + 1;
            SpecifyWay_porpose.column = current_coor.column + 1;
            SpecifyWay_minimum = integer_world_copy[current_coor.row + 1][current_coor.column + 1];
        }
        printf("%d putted in %d %d\n", SpecifyWay_counter + 1, current_coor.row - 1, current_coor.column + 1);
        current_mojaver[current_mojaver_index].row = current_coor.row + 1;
        current_mojaver[current_mojaver_index].column = current_coor.column + 1;
        current_mojaver_index++;
    }
    if(current_coor.row > 0 && current_coor.column > 0 && IsVacant(current_coor.row - 1, current_coor.column - 1)){
        way_array[current_coor.row - 1][current_coor.column - 1] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row - 1][current_coor.column - 1] < SpecifyWay_minimum){
            SpecifyWay_porpose.row = current_coor.row - 1;
            SpecifyWay_porpose.column = current_coor.column - 1;
            SpecifyWay_minimum = integer_world_copy[current_coor.row - 1][current_coor.column - 1];
        }
        printf("%d putted in %d %d\n", SpecifyWay_counter + 1, current_coor.row - 1, current_coor.column - 1);
        current_mojaver[current_mojaver_index].row = current_coor.row - 1;
        current_mojaver[current_mojaver_index].column = current_coor.column - 1;
        current_mojaver_index++;
    }
    if(current_coor.row > 0 && current_coor.column < side && IsVacant(current_coor.row - 1, current_coor.column + 1)){
        way_array[current_coor.row - 1][current_coor.column + 1] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row - 1][current_coor.column + 1] < SpecifyWay_minimum){
            SpecifyWay_porpose.row = current_coor.row - 1;
            SpecifyWay_porpose.column = current_coor.column + 1;
            SpecifyWay_minimum = integer_world_copy[current_coor.row - 1][current_coor.column + 1];
        }
        current_mojaver[current_mojaver_index].row = current_coor.row - 1;
        current_mojaver[current_mojaver_index].column = current_coor.column + 1;
        current_mojaver_index++;
    }
    if(current_coor.column < side && IsVacant(current_coor.row, current_coor.column + 1)){
        way_array[current_coor.row][current_coor.column + 1] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row][current_coor.column + 1] < SpecifyWay_minimum){
            SpecifyWay_porpose.row = current_coor.row;
            SpecifyWay_porpose.column = current_coor.column + 1;
            SpecifyWay_minimum = integer_world_copy[current_coor.row][current_coor.column + 1];
        }
        printf("%d putted in %d %d\n", SpecifyWay_counter + 1, current_coor.row, current_coor.column + 1);
        current_mojaver[current_mojaver_index].row = current_coor.row;
        current_mojaver[current_mojaver_index].column = current_coor.column + 1;
        current_mojaver_index++;
    }
    if(current_coor.column > 0 && IsVacant(current_coor.row, current_coor.column - 1)){
        way_array[current_coor.row][current_coor.column - 1] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row][current_coor.column - 1] < SpecifyWay_minimum){
            SpecifyWay_porpose.row = current_coor.row;
            SpecifyWay_porpose.column = current_coor.column - 1;
            SpecifyWay_minimum = integer_world_copy[current_coor.row][current_coor.column - 1];
        }
        printf("%d putted in %d %d\n", SpecifyWay_counter + 1, current_coor.row, current_coor.column - 1);
        current_mojaver[current_mojaver_index].row = current_coor.row;
        current_mojaver[current_mojaver_index].column = current_coor.column - 1;
        current_mojaver_index++;
    }
    if(current_coor.row < side && IsVacant(current_coor.row + 1, current_coor.column)){
        way_array[current_coor.row + 1][current_coor.column] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row + 1][current_coor.column] < SpecifyWay_minimum){
            SpecifyWay_porpose.row = current_coor.row + 1;
            SpecifyWay_porpose.column = current_coor.column;
            SpecifyWay_minimum = integer_world_copy[current_coor.row + 1][current_coor.column];
        }
        printf("%d putted in %d %d\n", SpecifyWay_counter + 1, current_coor.row + 1, current_coor.column);
        current_mojaver[current_mojaver_index].row = current_coor.row + 1;
        current_mojaver[current_mojaver_index].column = current_coor.column;
        current_mojaver_index++;
    }
    counter++;
    if(counter < previous_mojaver_index)
        SpecifyWay(previous_mojaver[counter], movement_number);
    else{
        if(current_mojaver_index == 0)
            return;
        for(int i = 0; i < current_mojaver_index; i++)
            previous_mojaver[i] = current_mojaver[i];
        counter = 0;
        previous_mojaver_index = current_mojaver_index;
        current_mojaver_index = 0;
        SpecifyWay_counter++;
        SpecifyWay(previous_mojaver[0], movement_number);
    }
}

int single_move(char code, Coordinate *curr_coor){
    switch (code) {
        case '6':
            if(world[curr_coor->row][curr_coor->column + 1] == '.'){
                world[curr_coor->row][curr_coor->column + 1] = world[curr_coor->row][curr_coor->column];
                world[curr_coor->row][curr_coor->column] = '.';
                curr_coor->column += 1;
            }
            else if(world[curr_coor->row][curr_coor->column + 1] == 'H'){
                win(world[curr_coor->row][curr_coor->column]);
                return 1;
            }
            else return 0;
            break;

        case '9':
            if(world[curr_coor->row - 1][curr_coor->column + 1] == '.'){
                world[curr_coor->row - 1][curr_coor->column + 1] = world[curr_coor->row][curr_coor->column];
                world[curr_coor->row][curr_coor->column] = '.';
                curr_coor->row -= 1;
                curr_coor->column += 1;
            }
            else if(world[curr_coor->row - 1][curr_coor->column + 1] == 'H'){
                win(world[curr_coor->row][curr_coor->column]);
                return 1;
            }
            else return 0;
            break;

        case '8':
            if(world[curr_coor->row - 1][curr_coor->column] == '.'){
                world[curr_coor->row - 1][curr_coor->column] = world[curr_coor->row][curr_coor->column];
                world[curr_coor->row][curr_coor->column] = '.';
                curr_coor->row -= 1;
            }
            else if(world[curr_coor->row - 1][curr_coor->column] == 'H'){
                win(world[curr_coor->row][curr_coor->column]);
                return 1;
            }
            else return 0;
            break;

        case '7':
            if(world[curr_coor->row - 1][curr_coor->column - 1] == '.'){
                world[curr_coor->row - 1][curr_coor->column - 1] = world[curr_coor->row][curr_coor->column];
                world[curr_coor->row][curr_coor->column] = '.';
                curr_coor->row -= 1;
                curr_coor->column -= 1;
            }
            else if(world[curr_coor->row - 1][curr_coor->column - 1] == 'H'){
                win(world[curr_coor->row][curr_coor->column]);
                return 1;
            }
            else return 0;
            break;

        case '4':
            if(world[curr_coor->row][curr_coor->column - 1] == '.'){
                world[curr_coor->row][curr_coor->column - 1] = world[curr_coor->row][curr_coor->column];
                world[curr_coor->row][curr_coor->column] = '.';
                curr_coor->column -= 1;
            }
            else if(world[curr_coor->row][curr_coor->column - 1] == 'H'){
                win(world[curr_coor->row][curr_coor->column]);
                return 1;
            }
            else return 0;
            break;

        case '1':
            if(world[curr_coor->row + 1][curr_coor->column - 1] == '.'){
                world[curr_coor->row + 1][curr_coor->column - 1] = world[curr_coor->row][curr_coor->column];
                world[curr_coor->row][curr_coor->column] = '.';
                curr_coor->row += 1;
                curr_coor->column -= 1;
            }
            else if(world[curr_coor->row + 1][curr_coor->column - 1] == 'H'){
                win(world[curr_coor->row][curr_coor->column]);
                return 1;
            }
            else return 0;
            break;

        case '2':
            if(world[curr_coor->row + 1][curr_coor->column] == '.'){
                world[curr_coor->row + 1][curr_coor->column] = world[curr_coor->row][curr_coor->column];
                world[curr_coor->row][curr_coor->column] = '.';
                curr_coor->row += 1;
            }
            else if(world[curr_coor->row + 1][curr_coor->column] == 'H'){
                win(world[curr_coor->row][curr_coor->column]);
                return 1;
            }
            else return 0;
            break;

        case '3':
            if(world[curr_coor->row + 1][curr_coor->column + 1] == '.'){
                world[curr_coor->row + 1][curr_coor->column + 1] = world[curr_coor->row][curr_coor->column];
                world[curr_coor->row][curr_coor->column] = '.';
                curr_coor->row += 1;
                curr_coor->column += 1;
            }
            else if(world[curr_coor->row + 1][curr_coor->column + 1] == 'H'){
                win(world[curr_coor->row][curr_coor->column]);
                return 1;
            }
            else return 0;
            break;

        default :
            return 0;
    }

    return 1;
}

void MoveAnimal(Coordinate *animal_coor, Coordinate porpose_coor, int movement_number)
{
    char *move_codes;
    int move_codes_index = 0;
    for(int i = 0; i < movement_number; i++){
        int number = integer_world_copy[porpose_coor.row][porpose_coor.column] + 1;
        printf("number is %d\n", number);
        printf("i am here\n");
        if(porpose_coor.column < side - 1 && integer_world_copy[porpose_coor.row][porpose_coor.column + 1] == number){
            move_codes[move_codes_index] = '6';
            move_codes_index++;
            porpose_coor.column += 1;

        }
        else if(porpose_coor.row > 0 && porpose_coor.column < side - 1 && integer_world_copy[porpose_coor.row - 1][porpose_coor.column + 1] == number){
            move_codes[move_codes_index] = '9';
            move_codes_index++;
            porpose_coor.row -= 1;
            porpose_coor.column += 1;
        }
        else if(porpose_coor.row > 0 && integer_world_copy[porpose_coor.row - 1][porpose_coor.column] == number){
            move_codes[move_codes_index] = '8';
            move_codes_index++;
            move_codes[move_codes_index] = '\0';
            printf("codes is %s\n", move_codes);
            porpose_coor.row -= 1;
        }
        else if(porpose_coor.row > 0 && porpose_coor.column > 0 && integer_world_copy[porpose_coor.row - 1][porpose_coor.column - 1] == number){
            move_codes[move_codes_index] = '7';
            move_codes_index++;
            porpose_coor.row -= 1;
            porpose_coor.column -= 1;
        }
        else if(porpose_coor.column > 0 && integer_world_copy[porpose_coor.row][porpose_coor.column - 1] == number){
            move_codes[move_codes_index] = '4';
            move_codes_index++;
            porpose_coor.column -= 1;
        }
        else if(porpose_coor.row < side - 1 && porpose_coor.column > 0 && integer_world_copy[porpose_coor.row + 1][porpose_coor.column - 1] == number){
            move_codes[move_codes_index] = '1';
            move_codes_index++;
            porpose_coor.row += 1;
            porpose_coor.column -= 1;
        }
        else if(porpose_coor.row < side - 1 && integer_world_copy[porpose_coor.row + 1][porpose_coor.column] == number){
            move_codes[move_codes_index] = '2';
            move_codes_index++;
            porpose_coor.row += 1;
        }
        else if(porpose_coor.row < side - 1 && porpose_coor.column < side -1 && integer_world_copy[porpose_coor.row + 1][porpose_coor.column + 1] == number){
            move_codes[move_codes_index] = '3';
            move_codes_index++;
            porpose_coor.row += 1;
            porpose_coor.column += 1;
        }
    }
    move_codes[move_codes_index] = '\0';
    printf("codes is %s\n", move_codes);
    CodeReverser(move_codes);
    printf("codes is %s\n", move_codes);
    for(int i = 0; i < move_codes_index; i++)
        single_move(move_codes[i], animal_coor);
}

void FindBestWay(Coordinate st_coor, int single_move_energy, int energy, int my_distance, int index) // distance name should change
{
    for(int i = 0; i < foods_array_index; i++){
        CreateIntegerWorldCopy(st_coor);
        my_distance += FindDistance(st_coor, &foods_array[i].food_coordinate, CheckFood);
        if(my_distance * single_move_energy > energy)
            continue;
        energy += foods_array[i].tempp_food_energy;
        if(((my_distance + foods_array[i].closest_heaven_distance) * single_move_energy < energy) && (my_distance + foods_array[i].closest_heaven_distance < minimum_distance)){
            minimum_distance = my_distance + foods_array[i].closest_heaven_distance;
            intcpy(FBW_final_porposes, FBW_porposes, index);
            FBW_final_porposes[ind] = foods_array[i].food_coordinate;
            FBW_final_porposes[ind + 1] = foods_array[i].closest_heaven_coordinate;
        }
        else if(my_distance < minimum_distance){
            foods_array[i].tempp_food_energy = 0;
            FBW_porposes[index] = foods_array[i].food_coordinate;
            FindBestWay(foods_array[i].food_coordinate, single_move_energy, (energy + foods_array[i].food_energy) - (my_distance * single_move_energy));
        }
        my_distance -= integer_world_copy[foods_array[i].food_coordinate.row][foods_array[i].food_coordinate.column];
        foods_array[i].tempp_food_energy = foods_array[i].food_energy;
    }
}

void noname(Animal *animal)
{
    DISTANCE = FindDistance(animal->animal_coordinate, &PORPOSE, CheckHeaven);
    if(animal->single_move_energy * DISTANCE < animal->animal_energy)
        MoveAnimal(&animal->animal_coordinate, PORPOSE, animal->movement_number);
    else{
        DISTANCE = 0;
        FindBestWay(animal->animal_coordinate, animal->single_move_energy, animal->animal_energy);
    }
}
/*
int main()
{
    PrintW();
    printf("---------------------------------------\n");
    Coordinate st, fi;
    st.row = 4;
    st.column = 0;
    fi.row = 0;
    fi.column = 0;
    CreateIntegerWorldCopy();
    ReadyForFD(fi);
    FindDistance(fi, &st, CheckAnimal);
    PrintIWC();
    current_mojaver_index = 0;
    previous_mojaver_index = 0;
    printf("--------------------------------------\n");
    CreateWayArray();
    SpecifyWay(st, 3);
    PrintWA();
    printf("our destination is %d %d\n", SpecifyWay_porpose.row, SpecifyWay_porpose.column);
    MoveAnimal(&st, SpecifyWay_porpose, 2);
    PrintW();
}*/
