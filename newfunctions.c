#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>

#define maxside 20
#define maxanimals 30
#define maxkindanimals 10
#define maxfood 30

// 0 kardan current purpose index

struct Coordinate{
   int row;
   int column;
};

struct Food{
    struct Coordinate food_coordinate;
    struct Coordinate closest_heaven_coordinate;
    int closest_heaven_distance;
    int food_energy;
    int temp_food_energy;
};

struct Animal{
    struct Coordinate animal_coordinate;
    int animal_energy;
    int single_move_energy;
    int movement_number;
    int attack_energy;
    int defense_energy;
    int reproduction_energy;
    struct Coordinate purposes[5];
    int current_purpose_index;
    int purposes_distance[5];
    short is_way_specified;
};

typedef struct Coordinate Coordinate;
typedef struct Animal Animal;
typedef struct Food Food;

char world[maxside][maxside];
Animal program_animals[maxanimals];
int program_animals_index;
Animal user_animals[maxkindanimals];
int user_animals_index;
int side = 5;
Food foods_array[maxfood];
int foods_array_index = 0;


Coordinate current_mojaver[20];
Coordinate previous_mojaver[20];
int current_mojaver_index = 0;
int previous_mojaver_index = 0;
int counter = 0;
int integer_world_copy[maxside][maxside];
int way_array[maxside][maxside];
int SpecifyWay_counter = 0;
Coordinate SpecifyWay_purpose;
int SpecifyWay_minimum = 20;
int DISTANCE;
Coordinate FBW_purposes[5];
int FBW_purposes_distance[5];
Coordinate FBW_final_purposes[5];
int FBW_final_purposes_distance[5];
int minimum_distance = 50;
short FBW_return_value = 0;


int FindInteger(char *);
int IsEqualStr(const char *, const char *);
void DeleteFood(int);
void CodeReverser(char *);
void CoorArrCpy(Coordinate *, Coordinate *, int);
void IntArrCpy(int *, int *, int);
void CreateIntegerWorldCopy(Coordinate);
void CreateWayArray();
void PrintW();
void PrintIWC();
void PrintWA();
int IsVacant(int, int);
int FindDistance(Coordinate, Coordinate *, int (*CheckStopCondition)(Coordinate, Coordinate *));
void win(char);
void SpecifyWay(Coordinate, int);
int single_move(char, Animal *);
void MakeCodeAndMove(Animal *, Coordinate);
int IsAnyAnimalCloser(Coordinate, int);
int IsAnyFood(Coordinate coor);
void FindBestWay(Coordinate, int, int, int, int, int);
void SpecifyPurposes(Animal *);
void CheckAnimalsHasFood(Coordinate);
void MoveAnimal(int);

int FindInteger(char * str)
{
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

int IsEqualStr(const char *str1, const char *str2)
{
    while(*str1){
        if(*str1 != *str2)
            return 0;
        str1++;
        str2++;
    }
    if(!(*str2))
        return 1;
    return 0;
}

void DeleteFood(int index)
{
    for(int i = index; i < foods_array_index - 1; i++){
        foods_array[i] = foods_array[i + 1];
    }
    foods_array_index--;
}

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

void CoorArrCpy(Coordinate *arr, Coordinate *source_arr, int num)
{
    for(; num > 0; num--){
        *arr = *source_arr;
        arr++;
        source_arr++;
    }
}

void IntArrCpy(int *arr, int *source_arr, int num)
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
    current_mojaver_index = 0;
    previous_mojaver_index = 0;
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
        return integer_world_copy[current_coor.row][current_coor.column] - 1;
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

void win(char A)
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
            SpecifyWay_purpose.row = current_coor.row - 1;
            SpecifyWay_purpose.column = current_coor.column;
            SpecifyWay_minimum = integer_world_copy[current_coor.row - 1][current_coor.column];
        }
        current_mojaver[current_mojaver_index].row = current_coor.row - 1;
        current_mojaver[current_mojaver_index].column = current_coor.column;
        current_mojaver_index++;
    }
    if(current_coor.row < side && current_coor.column > 0 && IsVacant(current_coor.row + 1, current_coor.column - 1)){
        way_array[current_coor.row + 1][current_coor.column - 1] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row + 1][current_coor.column - 1] < SpecifyWay_minimum){
            SpecifyWay_purpose.row = current_coor.row + 1;
            SpecifyWay_purpose.column = current_coor.column - 1;
            SpecifyWay_minimum = integer_world_copy[current_coor.row + 1][current_coor.column - 1];
        }
        current_mojaver[current_mojaver_index].row = current_coor.row + 1;
        current_mojaver[current_mojaver_index].column = current_coor.column - 1;
        current_mojaver_index++;
    }
    if(current_coor.row < side && current_coor.column < side && IsVacant(current_coor.row + 1, current_coor.column + 1)){
        way_array[current_coor.row + 1][current_coor.column + 1] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row + 1][current_coor.column + 1] < SpecifyWay_minimum){
            SpecifyWay_purpose.row = current_coor.row + 1;
            SpecifyWay_purpose.column = current_coor.column + 1;
            SpecifyWay_minimum = integer_world_copy[current_coor.row + 1][current_coor.column + 1];
        }
        current_mojaver[current_mojaver_index].row = current_coor.row + 1;
        current_mojaver[current_mojaver_index].column = current_coor.column + 1;
        current_mojaver_index++;
    }
    if(current_coor.row > 0 && current_coor.column > 0 && IsVacant(current_coor.row - 1, current_coor.column - 1)){
        way_array[current_coor.row - 1][current_coor.column - 1] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row - 1][current_coor.column - 1] < SpecifyWay_minimum){
            SpecifyWay_purpose.row = current_coor.row - 1;
            SpecifyWay_purpose.column = current_coor.column - 1;
            SpecifyWay_minimum = integer_world_copy[current_coor.row - 1][current_coor.column - 1];
        }
        current_mojaver[current_mojaver_index].row = current_coor.row - 1;
        current_mojaver[current_mojaver_index].column = current_coor.column - 1;
        current_mojaver_index++;
    }
    if(current_coor.row > 0 && current_coor.column < side && IsVacant(current_coor.row - 1, current_coor.column + 1)){
        way_array[current_coor.row - 1][current_coor.column + 1] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row - 1][current_coor.column + 1] < SpecifyWay_minimum){
            SpecifyWay_purpose.row = current_coor.row - 1;
            SpecifyWay_purpose.column = current_coor.column + 1;
            SpecifyWay_minimum = integer_world_copy[current_coor.row - 1][current_coor.column + 1];
        }
        current_mojaver[current_mojaver_index].row = current_coor.row - 1;
        current_mojaver[current_mojaver_index].column = current_coor.column + 1;
        current_mojaver_index++;
    }
    if(current_coor.column < side && IsVacant(current_coor.row, current_coor.column + 1)){
        way_array[current_coor.row][current_coor.column + 1] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row][current_coor.column + 1] < SpecifyWay_minimum){
            SpecifyWay_purpose.row = current_coor.row;
            SpecifyWay_purpose.column = current_coor.column + 1;
            SpecifyWay_minimum = integer_world_copy[current_coor.row][current_coor.column + 1];
        }
        current_mojaver[current_mojaver_index].row = current_coor.row;
        current_mojaver[current_mojaver_index].column = current_coor.column + 1;
        current_mojaver_index++;
    }
    if(current_coor.column > 0 && IsVacant(current_coor.row, current_coor.column - 1)){
        way_array[current_coor.row][current_coor.column - 1] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row][current_coor.column - 1] < SpecifyWay_minimum){
            SpecifyWay_purpose.row = current_coor.row;
            SpecifyWay_purpose.column = current_coor.column - 1;
            SpecifyWay_minimum = integer_world_copy[current_coor.row][current_coor.column - 1];
        }
        current_mojaver[current_mojaver_index].row = current_coor.row;
        current_mojaver[current_mojaver_index].column = current_coor.column - 1;
        current_mojaver_index++;
    }
    if(current_coor.row < side && IsVacant(current_coor.row + 1, current_coor.column)){
        way_array[current_coor.row + 1][current_coor.column] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row + 1][current_coor.column] < SpecifyWay_minimum){
            SpecifyWay_purpose.row = current_coor.row + 1;
            SpecifyWay_purpose.column = current_coor.column;
            SpecifyWay_minimum = integer_world_copy[current_coor.row + 1][current_coor.column];
        }
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

int single_move(char code, Animal *animal)
{
    int index_of_food;
    switch (code) {
        case '6':
            if(world[animal->animal_coordinate.row][animal->animal_coordinate.column + 1] == '.'){
                world[animal->animal_coordinate.row][animal->animal_coordinate.column + 1] = world[animal->animal_coordinate.row][animal->animal_coordinate.column];
                world[animal->animal_coordinate.row][animal->animal_coordinate.column] = '.';
                animal->animal_coordinate.column += 1;
                index_of_food = IsAnyFood(animal->animal_coordinate);
                if(index_of_food != -1){
                    if(animal->animal_coordinate.row == animal->purposes[animal->current_purpose_index].row && animal->animal_coordinate.column == animal->purposes[animal->current_purpose_index].column)
                        animal->current_purpose_index++;
                    else
                        CheckAnimalsHasFood(foods_array[index_of_food].food_coordinate);
                    animal->animal_energy += foods_array[index_of_food].food_energy;
                    DeleteFood(index_of_food);
                }
            }
            else if(world[animal->animal_coordinate.row][animal->animal_coordinate.column + 1] == 'H'){
                win(world[animal->animal_coordinate.row][animal->animal_coordinate.column]);
                return 1;
            }
            else return 0;
            break;

        case '9':
            if(world[animal->animal_coordinate.row - 1][animal->animal_coordinate.column + 1] == '.'){
                world[animal->animal_coordinate.row - 1][animal->animal_coordinate.column + 1] = world[animal->animal_coordinate.row][animal->animal_coordinate.column];
                world[animal->animal_coordinate.row][animal->animal_coordinate.column] = '.';
                animal->animal_coordinate.row -= 1;
                animal->animal_coordinate.column += 1;
                index_of_food = IsAnyFood(animal->animal_coordinate);
                if(index_of_food != -1){
                    if(animal->animal_coordinate.row == animal->purposes[animal->current_purpose_index].row && animal->animal_coordinate.column == animal->purposes[animal->current_purpose_index].column)
                        animal->current_purpose_index++;
                    else
                        CheckAnimalsHasFood(foods_array[index_of_food].food_coordinate);
                    animal->animal_energy += foods_array[index_of_food].food_energy;
                    DeleteFood(index_of_food);
                }
            }
            else if(world[animal->animal_coordinate.row - 1][animal->animal_coordinate.column + 1] == 'H'){
                win(world[animal->animal_coordinate.row][animal->animal_coordinate.column]);
                return 1;
            }
            else return 0;
            break;

        case '8':
            if(world[animal->animal_coordinate.row - 1][animal->animal_coordinate.column] == '.'){
                world[animal->animal_coordinate.row - 1][animal->animal_coordinate.column] = world[animal->animal_coordinate.row][animal->animal_coordinate.column];
                world[animal->animal_coordinate.row][animal->animal_coordinate.column] = '.';
                animal->animal_coordinate.row -= 1;
                index_of_food = IsAnyFood(animal->animal_coordinate);
                if(index_of_food != -1){
                    if(animal->animal_coordinate.row == animal->purposes[animal->current_purpose_index].row && animal->animal_coordinate.column == animal->purposes[animal->current_purpose_index].column)
                        animal->current_purpose_index++;
                    else
                        CheckAnimalsHasFood(foods_array[index_of_food].food_coordinate);
                    animal->animal_energy += foods_array[index_of_food].food_energy;
                    DeleteFood(index_of_food);
                }
            }
            else if(world[animal->animal_coordinate.row - 1][animal->animal_coordinate.column] == 'H'){
                win(world[animal->animal_coordinate.row][animal->animal_coordinate.column]);
                return 1;
            }
            else return 0;
            break;

        case '7':
            if(world[animal->animal_coordinate.row - 1][animal->animal_coordinate.column - 1] == '.'){
                world[animal->animal_coordinate.row - 1][animal->animal_coordinate.column - 1] = world[animal->animal_coordinate.row][animal->animal_coordinate.column];
                world[animal->animal_coordinate.row][animal->animal_coordinate.column] = '.';
                animal->animal_coordinate.row -= 1;
                animal->animal_coordinate.column -= 1;
                index_of_food = IsAnyFood(animal->animal_coordinate);
                if(index_of_food != -1){
                    if(animal->animal_coordinate.row == animal->purposes[animal->current_purpose_index].row && animal->animal_coordinate.column == animal->purposes[animal->current_purpose_index].column)
                        animal->current_purpose_index++;
                    else
                        CheckAnimalsHasFood(foods_array[index_of_food].food_coordinate);
                    animal->animal_energy += foods_array[index_of_food].food_energy;
                    DeleteFood(index_of_food);
                }
            }
            else if(world[animal->animal_coordinate.row - 1][animal->animal_coordinate.column - 1] == 'H'){
                win(world[animal->animal_coordinate.row][animal->animal_coordinate.column]);
                return 1;
            }
            else return 0;
            break;

        case '4':
            if(world[animal->animal_coordinate.row][animal->animal_coordinate.column - 1] == '.'){
                world[animal->animal_coordinate.row][animal->animal_coordinate.column - 1] = world[animal->animal_coordinate.row][animal->animal_coordinate.column];
                world[animal->animal_coordinate.row][animal->animal_coordinate.column] = '.';
                animal->animal_coordinate.column -= 1;
                index_of_food = IsAnyFood(animal->animal_coordinate);
                if(index_of_food != -1){
                    if(animal->animal_coordinate.row == animal->purposes[animal->current_purpose_index].row && animal->animal_coordinate.column == animal->purposes[animal->current_purpose_index].column)
                        animal->current_purpose_index++;
                    else
                        CheckAnimalsHasFood(foods_array[index_of_food].food_coordinate);
                    animal->animal_energy += foods_array[index_of_food].food_energy;
                    DeleteFood(index_of_food);
                }
            }
            else if(world[animal->animal_coordinate.row][animal->animal_coordinate.column - 1] == 'H'){
                win(world[animal->animal_coordinate.row][animal->animal_coordinate.column]);
                return 1;
            }
            else return 0;
            break;

        case '1':
            if(world[animal->animal_coordinate.row + 1][animal->animal_coordinate.column - 1] == '.'){
                world[animal->animal_coordinate.row + 1][animal->animal_coordinate.column - 1] = world[animal->animal_coordinate.row][animal->animal_coordinate.column];
                world[animal->animal_coordinate.row][animal->animal_coordinate.column] = '.';
                animal->animal_coordinate.row += 1;
                animal->animal_coordinate.column -= 1;
                index_of_food = IsAnyFood(animal->animal_coordinate);
                if(index_of_food != -1){
                    if(animal->animal_coordinate.row == animal->purposes[animal->current_purpose_index].row && animal->animal_coordinate.column == animal->purposes[animal->current_purpose_index].column)
                        animal->current_purpose_index++;
                    else
                        CheckAnimalsHasFood(foods_array[index_of_food].food_coordinate);
                    animal->animal_energy += foods_array[index_of_food].food_energy;
                    DeleteFood(index_of_food);
                }
            }
            else if(world[animal->animal_coordinate.row + 1][animal->animal_coordinate.column - 1] == 'H'){
                win(world[animal->animal_coordinate.row][animal->animal_coordinate.column]);
                return 1;
            }
            else return 0;
            break;

        case '2':
            if(world[animal->animal_coordinate.row + 1][animal->animal_coordinate.column] == '.'){
                world[animal->animal_coordinate.row + 1][animal->animal_coordinate.column] = world[animal->animal_coordinate.row][animal->animal_coordinate.column];
                world[animal->animal_coordinate.row][animal->animal_coordinate.column] = '.';
                animal->animal_coordinate.row += 1;
                index_of_food = IsAnyFood(animal->animal_coordinate);
                if(index_of_food != -1){
                    if(animal->animal_coordinate.row == animal->purposes[animal->current_purpose_index].row && animal->animal_coordinate.column == animal->purposes[animal->current_purpose_index].column)
                        animal->current_purpose_index++;
                    else
                        CheckAnimalsHasFood(foods_array[index_of_food].food_coordinate);
                    animal->animal_energy += foods_array[index_of_food].food_energy;
                    DeleteFood(index_of_food);
                }
            }
            else if(world[animal->animal_coordinate.row + 1][animal->animal_coordinate.column] == 'H'){
                win(world[animal->animal_coordinate.row][animal->animal_coordinate.column]);
                return 1;
            }
            else return 0;
            break;

        case '3':
            if(world[animal->animal_coordinate.row + 1][animal->animal_coordinate.column + 1] == '.'){
                world[animal->animal_coordinate.row + 1][animal->animal_coordinate.column + 1] = world[animal->animal_coordinate.row][animal->animal_coordinate.column];
                world[animal->animal_coordinate.row][animal->animal_coordinate.column] = '.';
                animal->animal_coordinate.row += 1;
                animal->animal_coordinate.column += 1;
                index_of_food = IsAnyFood(animal->animal_coordinate);
                if(index_of_food != -1){
                    if(animal->animal_coordinate.row == animal->purposes[animal->current_purpose_index].row && animal->animal_coordinate.column == animal->purposes[animal->current_purpose_index].column)
                        animal->current_purpose_index++;
                    else
                        CheckAnimalsHasFood(foods_array[index_of_food].food_coordinate);
                    animal->animal_energy += foods_array[index_of_food].food_energy;
                    DeleteFood(index_of_food);
                }
            }
            else if(world[animal->animal_coordinate.row + 1][animal->animal_coordinate.column + 1] == 'H'){
                win(world[animal->animal_coordinate.row][animal->animal_coordinate.column]);
                return 1;
            }
            else return 0;
            break;

        default :
            return 0;
    }

    return 1;
}

void MakeCodeAndMove(Animal *animal, Coordinate purpose_coor)
{
    char *move_codes;
    int move_codes_index = 0;
    for(int i = 0; i < animal->movement_number; i++){
        int number = integer_world_copy[purpose_coor.row][purpose_coor.column] + 1;
        if(purpose_coor.column < side - 1 && integer_world_copy[purpose_coor.row][purpose_coor.column + 1] == number){
            move_codes[move_codes_index] = '6';
            move_codes_index++;
            purpose_coor.column += 1;

        }
        else if(purpose_coor.row > 0 && purpose_coor.column < side - 1 && integer_world_copy[purpose_coor.row - 1][purpose_coor.column + 1] == number){
            move_codes[move_codes_index] = '9';
            move_codes_index++;
            purpose_coor.row -= 1;
            purpose_coor.column += 1;
        }
        else if(purpose_coor.row > 0 && integer_world_copy[purpose_coor.row - 1][purpose_coor.column] == number){
            move_codes[move_codes_index] = '8';
            move_codes_index++;
            move_codes[move_codes_index] = '\0';
            purpose_coor.row -= 1;
        }
        else if(purpose_coor.row > 0 && purpose_coor.column > 0 && integer_world_copy[purpose_coor.row - 1][purpose_coor.column - 1] == number){
            move_codes[move_codes_index] = '7';
            move_codes_index++;
            purpose_coor.row -= 1;
            purpose_coor.column -= 1;
        }
        else if(purpose_coor.column > 0 && integer_world_copy[purpose_coor.row][purpose_coor.column - 1] == number){
            move_codes[move_codes_index] = '4';
            move_codes_index++;
            purpose_coor.column -= 1;
        }
        else if(purpose_coor.row < side - 1 && purpose_coor.column > 0 && integer_world_copy[purpose_coor.row + 1][purpose_coor.column - 1] == number){
            move_codes[move_codes_index] = '1';
            move_codes_index++;
            purpose_coor.row += 1;
            purpose_coor.column -= 1;
        }
        else if(purpose_coor.row < side - 1 && integer_world_copy[purpose_coor.row + 1][purpose_coor.column] == number){
            move_codes[move_codes_index] = '2';
            move_codes_index++;
            purpose_coor.row += 1;
        }
        else if(purpose_coor.row < side - 1 && purpose_coor.column < side -1 && integer_world_copy[purpose_coor.row + 1][purpose_coor.column + 1] == number){
            move_codes[move_codes_index] = '3';
            move_codes_index++;
            purpose_coor.row += 1;
            purpose_coor.column += 1;
        }
    }
    move_codes[move_codes_index] = '\0';
    CodeReverser(move_codes);
    for(int i = 0; i < move_codes_index; i++)
        single_move(move_codes[i], animal);
}

int IsAnyAnimalCloser(Coordinate food_coor, int rounds_to_food)
{
    for(int i = 0; i < program_animals_index; i++){
        for(int j = 0; program_animals[i].purposes_distance[j] != -1; j++){
            if(food_coor.row == program_animals[i].purposes[j].row, food_coor.column == program_animals[i].purposes[j].column){
                if(rounds_to_food > ceil(program_animals[i].purposes_distance[j] / program_animals[i].movement_number))
                    return 1;
                else
                    program_animals[i].is_way_specified = 0;
            }
        }
    }
    return 0;
}

int IsAnyFood(Coordinate coor)
{
    for(int i = 0; i < foods_array_index; i++){
        if(coor.row == foods_array[i].food_coordinate.row && coor.column == foods_array[i].food_coordinate.column)
            return i;
    }
    return -1;
}

void FindBestWay(Coordinate st_coor, int single_move_energy, int movement_number, int energy, int my_distance, int index)
{
    int const_distance = my_distance;
    for(int i = 0; i < foods_array_index; i++){
        if(foods_array[i].temp_food_energy == 0)
            continue;
        CreateIntegerWorldCopy(st_coor);
        my_distance += FindDistance(st_coor, &foods_array[i].food_coordinate, CheckFood);
        if(my_distance * single_move_energy > energy || my_distance > minimum_distance || IsAnyAnimalCloser(foods_array[i].food_coordinate, ceil(my_distance / movement_number))){
            my_distance = const_distance;
            continue;
        }
        energy += foods_array[i].temp_food_energy;
        if(((my_distance + foods_array[i].closest_heaven_distance) * single_move_energy < energy) && (my_distance + foods_array[i].closest_heaven_distance < minimum_distance)){
            minimum_distance = my_distance + foods_array[i].closest_heaven_distance;
            CoorArrCpy(FBW_final_purposes, FBW_purposes, index);
            IntArrCpy(FBW_final_purposes_distance, FBW_purposes_distance, index);
            FBW_final_purposes[index] = foods_array[i].food_coordinate;
            FBW_final_purposes[index + 1] = foods_array[i].closest_heaven_coordinate;
            FBW_final_purposes_distance[index] = my_distance;
            FBW_final_purposes_distance[index + 1] = -1;
            FBW_return_value = 1;
        }
        else{
            foods_array[i].temp_food_energy = 0;
            FBW_purposes[index] = foods_array[i].food_coordinate;
            FBW_purposes_distance[index] = my_distance;
            FindBestWay(foods_array[i].food_coordinate, single_move_energy, movement_number, energy - (my_distance * single_move_energy), my_distance, index + 1);
        }
        my_distance = const_distance;
        foods_array[i].temp_food_energy = foods_array[i].food_energy;
        energy -= foods_array[i].temp_food_energy;
    }
}

void SpecifyPurposes(Animal *animal)
{
    DISTANCE = FindDistance(animal->animal_coordinate, &animal->purposes[0], CheckHeaven);
    if(animal->single_move_energy * DISTANCE < animal->animal_energy)
    else{
        CreateIntegerWorldCopy(animal->animal_coordinate);
        DISTANCE = 0;
        minimum_distance = 100;
        FindBestWay(animal->animal_coordinate, animal->single_move_energy, animal->movement_number, animal->animal_energy, 0, 0);
        if(FBW_return_value){
            CoorArrCpy(animal->purposes, FBW_final_purposes, 5);
            IntArrCpy(animal->purposes_distance, FBW_final_purposes_distance, 5);
        }
    }
    animal->is_way_specified = 1;
}

void CheckAnimalsHasFood(Coordinate food_coor)
{
    for(int animal = 0; animal < program_animals_index; animal++){
        for(int i = 0; program_animals[animal].purposes_distance[i] != -1 && i < 5; i++){
            if(program_animals[animal].purposes[i].row == food_coor.row && program_animals[animal].purposes[i].column == food_coor.column){
                program_animals[animal].is_way_specified = 0;
            }
        }
    }
}

void MoveAnimal(int index_of_animal)
{
    if(!program_animals[index_of_animal].is_way_specified)
        SpecifyPurposes(&program_animals[index_of_animal]);
    FindDistance(program_animals[index_of_animal].animal_coordinate, &program_animals[index_of_animal].purposes[program_animals[index_of_animal].current_purpose_index], CheckFood);
    SpecifyWay(program_animals[index_of_animal].animal_coordinate, program_animals[index_of_animal].movement_number);
    MakeCodeAndMove(&program_animals[index_of_animal], SpecifyWay_purpose);
}
