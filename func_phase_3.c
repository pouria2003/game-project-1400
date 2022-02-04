#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#include <time.h>

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
char User_Animal;
int primary_info[maxanimals][3];
int primary_info_index = 0;


Coordinate current_mojaver[40];
Coordinate previous_mojaver[40];
int current_mojaver_index = 0;
int previous_mojaver_index = 0;
int counter = 0;
int integer_world_copy[maxside][maxside];
int way_array[maxside][maxside];
int SpecifyWay_counter = 1;
Coordinate SpecifyWay_purpose;
int SpecifyWay_minimum = 20;
Coordinate FBW_purposes[5];
int FBW_purposes_distance[5];
Coordinate FBW_final_purposes[5];
int FBW_final_purposes_distance[5];
int minimum_distance = 50;
short FBW_return_value = 0;


int FindInteger(char *);
int IsEqualStr(const char *, const char *);
int Random(int, int);
void DeleteFood(int);
void CodeReverser(char *);
void CoorArrCpy(Coordinate *, Coordinate *, int);
void IntArrCpy(int *, int *, int);
void CreateIntegerWorldCopy(Coordinate);
void CreateWayArray(Coordinate);
void PrintW();
void PrintIWC();
void PrintWA();
void PrintFoodInfo();
void AddFoodToWorld();
int IsVacant(int, int);
int FindDistance(Coordinate, Coordinate *, int (*CheckStopCondition)(Coordinate, Coordinate *));
void Lose(Animal *, char);
void win(char);
void SpecifyWay(Coordinate, int);
int SingleMove(char, Animal *);
void MakeCodeAndMove(Animal *, Coordinate, int);
int IsAnyAnimalCloser(Coordinate, int);
int IsAnyFood(Coordinate coor);
void FindBestWay(Coordinate, int, int, int, int, int);
void SpecifyPurposes(Animal *);
void CheckAnimalsHasFood(Coordinate);
void AddFood(Coordinate, int);
void reproduction(Animal[], int *, int);
void MoveAnimal(int index_of_animal);

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

int IsAnimalAlive(const Animal * animal)
{
    if(animal->animal_coordinate.row == -1 || animal->animal_coordinate.column == -1)
        return 0;
    return 1;
}

int Random(int min, int max)
{
    return (rand() % (max - min + 1) + min);
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

void TransferToUserAnimals(int trans_index){
    user_animals[user_animals_index] = program_animals[trans_index];
    program_animals_index--;
    user_animals_index++;
    for(int i = trans_index; i < program_animals_index; i++){
        program_animals[i] = program_animals[i + 1];
    }
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
    //printf("%s", codes);
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
    counter = 0;
}

void CreateWayArray(Coordinate st_coor)
{
    for(int i = 0; i < side; i++)
        for(int j = 0; j < side; j++)
            way_array[i][j] = 0;
    current_mojaver_index = 0;
    previous_mojaver_index = 0;
    way_array[st_coor.row][st_coor.column] = 1;
}

void PrintW()
{
    AddFoodToWorld();
    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++)
            printf("%c ", world[i][j]);
        printf("\n");
    }
}

void PrintFoodInfo()
{
    printf("\nfoods : \n");
    for(int i = 0; i < foods_array_index; i++){
        printf("in %d %d have %d energy\n", foods_array[i].food_coordinate.row, foods_array[i].food_coordinate.column, foods_array[i].food_energy);
    }
}

void AddFoodToWorld()
{
    for(int i = 0; i < foods_array_index; i++){
        if(world[foods_array[i].food_coordinate.row][foods_array[i].food_coordinate.column] == '.')
            world[foods_array[i].food_coordinate.row][foods_array[i].food_coordinate.column] = 'F';
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
    if((world[row][column] == '.' || world[row][column] == 'H' || world[row][column] == 'F') && (way_array[row][column] == 0))return 1;
    return 0;
}

int CheckHeaven(Coordinate my_coor, Coordinate *heaven_coor){if(world[my_coor.row][my_coor.column] == 'H'){heaven_coor->row = my_coor.row; heaven_coor->column = my_coor.column; return 1;} return 0;}
int CheckAnimal(Coordinate st_coor, Coordinate *fi_coor){if(st_coor.row == fi_coor->row && st_coor.column == fi_coor->column)return 1; return 0;}
int CheckFood(Coordinate st_coor, Coordinate *fi_coor){if(st_coor.row == fi_coor->row && st_coor.column == fi_coor->column)return 1; return 0;}

int FindDistance(Coordinate current_coor, Coordinate *final_coor, int (*CheckStopCondition)(Coordinate, Coordinate *))
{
    //printf("st 1 %d %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
    if(CheckStopCondition(current_coor, final_coor))
        return integer_world_copy[current_coor.row][current_coor.column] - 1;
    int num = integer_world_copy[current_coor.row][current_coor.column] + 1;
    //printf("st 2 %d %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
    if(current_coor.row > 0 && integer_world_copy[current_coor.row - 1][current_coor.column] == 0){
        integer_world_copy[current_coor.row - 1][current_coor.column] = num;
        current_mojaver[current_mojaver_index].row = current_coor.row - 1;
        current_mojaver[current_mojaver_index].column = current_coor.column;
        current_mojaver_index++;
    }
    //printf("st 3 %d %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
    if(current_coor.row < side && current_coor.column > 0 && integer_world_copy[current_coor.row + 1][current_coor.column - 1] == 0){
        integer_world_copy[current_coor.row + 1][current_coor.column - 1] = num;
        current_mojaver[current_mojaver_index].row = current_coor.row + 1;
        current_mojaver[current_mojaver_index].column = current_coor.column - 1;
        current_mojaver_index++;
    }
    //printf("st 4 %d %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
    if(current_coor.row < side && current_coor.column < side && integer_world_copy[current_coor.row + 1][current_coor.column + 1] == 0){
        integer_world_copy[current_coor.row + 1][current_coor.column + 1] = num;
        current_mojaver[current_mojaver_index].row = current_coor.row + 1;
        current_mojaver[current_mojaver_index].column = current_coor.column + 1;
        current_mojaver_index++;
    }
    //printf("st 5 %d %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
    if(current_coor.row > 0 && current_coor.column > 0 && integer_world_copy[current_coor.row - 1][current_coor.column - 1] == 0){
        integer_world_copy[current_coor.row - 1][current_coor.column - 1] = num;
        current_mojaver[current_mojaver_index].row = current_coor.row - 1;
        current_mojaver[current_mojaver_index].column = current_coor.column - 1;
        current_mojaver_index++;
    }
    //printf("st 6 %d %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
    if(current_coor.row > 0 && current_coor.column < side && integer_world_copy[current_coor.row - 1][current_coor.column + 1] == 0){
        integer_world_copy[current_coor.row - 1][current_coor.column + 1] = num;
        current_mojaver[current_mojaver_index].row = current_coor.row - 1;
        current_mojaver[current_mojaver_index].column = current_coor.column + 1;
        current_mojaver_index++;
    }
    //printf("st 7 %d %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
    if(current_coor.column < side && integer_world_copy[current_coor.row][current_coor.column + 1] == 0){
        //printf("st 7.1 %d %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
        integer_world_copy[current_coor.row][current_coor.column + 1] = num;
        //printf("st 7.2 %d %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
        current_mojaver[current_mojaver_index].row = current_coor.row;
        //printf("st 7.3 %d %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
        current_mojaver[current_mojaver_index].column = current_coor.column + 1;
        //printf("st 7.4 %d %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
        current_mojaver_index++;
        //printf("st 7.5 %d %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
    }
    //printf("st 8 %d %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
    if(current_coor.column > 0 && integer_world_copy[current_coor.row][current_coor.column - 1] == 0){
        integer_world_copy[current_coor.row][current_coor.column - 1] = num;
        current_mojaver[current_mojaver_index].row = current_coor.row;
        current_mojaver[current_mojaver_index].column = current_coor.column - 1;
        current_mojaver_index++;
    }
    //printf("st 9 %d %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
    if(current_coor.row < side && integer_world_copy[current_coor.row + 1][current_coor.column] == 0){
        integer_world_copy[current_coor.row + 1][current_coor.column] = num;
        current_mojaver[current_mojaver_index].row = current_coor.row + 1;
        current_mojaver[current_mojaver_index].column = current_coor.column;
        current_mojaver_index++;
    }
    //printf("st 10 %d %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
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

void Lose(Animal *animal, char mode)
{

    system("cls");
    PrintW();
    if(mode == 'p')
        printf("\nAn animal of type %c died!\n", world[animal->animal_coordinate.row][animal->animal_coordinate.column]);
    else
        printf("\nyour animal died!\n");
    Sleep(1000);
    //printf("int %d %d\n", animal->animal_coordinate.row, animal->animal_coordinate.column);
    world[animal->animal_coordinate.row][animal->animal_coordinate.column] = '.';
    //printf("world khune %d %d kardam . \n", animal->animal_coordinate.row, animal->animal_coordinate.row);
    AddFood(animal->animal_coordinate, animal->animal_energy);
    //Sleep(5000);
    animal->animal_coordinate.row = -1;
    animal->animal_coordinate.row = -1;

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
         //printf ("%c",str[i]);
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
    if(SpecifyWay_counter == movement_number + 1)
        return;
    int number = integer_world_copy[current_coor.row][current_coor.column] - 1;
    //printf("1 %d %d\n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
    if(current_coor.row > 0 && IsVacant(current_coor.row - 1, current_coor.column)){
        way_array[current_coor.row - 1][current_coor.column] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row - 1][current_coor.column] < SpecifyWay_minimum && integer_world_copy[current_coor.row - 1][current_coor.column] != 0){
            SpecifyWay_purpose.row = current_coor.row - 1;
            SpecifyWay_purpose.column = current_coor.column;
            //printf("sp pur changed to %d %d\n", SpecifyWay_purpose.row, SpecifyWay_purpose.column);
            SpecifyWay_minimum = integer_world_copy[current_coor.row - 1][current_coor.column];
        }
        //printf("%d putted in %d %d\n", SpecifyWay_counter + 1, current_coor.row - 1, current_coor.column);
        current_mojaver[current_mojaver_index].row = current_coor.row - 1;
        current_mojaver[current_mojaver_index].column = current_coor.column;
        current_mojaver_index++;
    }
    //printf("2 %d %d\n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
    if(current_coor.row + 1 < side && current_coor.column > 0 && IsVacant(current_coor.row + 1, current_coor.column - 1)){
        way_array[current_coor.row + 1][current_coor.column - 1] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row + 1][current_coor.column - 1] < SpecifyWay_minimum && integer_world_copy[current_coor.row + 1][current_coor.column - 1] != 0){
            SpecifyWay_purpose.row = current_coor.row + 1;
            SpecifyWay_purpose.column = current_coor.column - 1;
            SpecifyWay_minimum = integer_world_copy[current_coor.row + 1][current_coor.column - 1];
            //printf("sp pur changed to %d %d\n", SpecifyWay_purpose.row, SpecifyWay_purpose.column);
        }
        //printf("%d putted in %d %d\n", SpecifyWay_counter + 1, current_coor.row - 1, current_coor.column - 1);
        current_mojaver[current_mojaver_index].row = current_coor.row + 1;
        current_mojaver[current_mojaver_index].column = current_coor.column - 1;
        current_mojaver_index++;
    }
    //printf("3 %d %d\n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
    if(current_coor.row + 1< side && current_coor.column + 1 < side && IsVacant(current_coor.row + 1, current_coor.column + 1)){
        way_array[current_coor.row + 1][current_coor.column + 1] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row + 1][current_coor.column + 1] < SpecifyWay_minimum && integer_world_copy[current_coor.row + 1][current_coor.column + 1] != 0){
            SpecifyWay_purpose.row = current_coor.row + 1;
            SpecifyWay_purpose.column = current_coor.column + 1;
            SpecifyWay_minimum = integer_world_copy[current_coor.row + 1][current_coor.column + 1];
            //printf("sp pur changed to %d %d\n", SpecifyWay_purpose.row, SpecifyWay_purpose.column);
        }
        //printf("%d putted in %d %d\n", SpecifyWay_counter + 1, current_coor.row - 1, current_coor.column + 1);
        current_mojaver[current_mojaver_index].row = current_coor.row + 1;
        current_mojaver[current_mojaver_index].column = current_coor.column + 1;
        current_mojaver_index++;
    }
    //printf("4 %d %d\n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
    if(current_coor.row > 0 && current_coor.column > 0 && IsVacant(current_coor.row - 1, current_coor.column - 1)){
        way_array[current_coor.row - 1][current_coor.column - 1] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row - 1][current_coor.column - 1] < SpecifyWay_minimum && integer_world_copy[current_coor.row - 1][current_coor.column - 1] != 0){
            SpecifyWay_purpose.row = current_coor.row - 1;
            SpecifyWay_purpose.column = current_coor.column - 1;
            SpecifyWay_minimum = integer_world_copy[current_coor.row - 1][current_coor.column - 1];
            //printf("sp pur changed to %d %d\n", SpecifyWay_purpose.row, SpecifyWay_purpose.column);
        }
        //printf("%d putted in %d %d\n", SpecifyWay_counter + 1, current_coor.row - 1, current_coor.column - 1);
        current_mojaver[current_mojaver_index].row = current_coor.row - 1;
        current_mojaver[current_mojaver_index].column = current_coor.column - 1;
        current_mojaver_index++;
    }
    //printf("5 %d %d\n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
    if(current_coor.row > 0 && current_coor.column + 1 < side && IsVacant(current_coor.row - 1, current_coor.column + 1)){
        way_array[current_coor.row - 1][current_coor.column + 1] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row - 1][current_coor.column + 1] < SpecifyWay_minimum && integer_world_copy[current_coor.row - 1][current_coor.column + 1] != 0){
            SpecifyWay_purpose.row = current_coor.row - 1;
            SpecifyWay_purpose.column = current_coor.column + 1;
            SpecifyWay_minimum = integer_world_copy[current_coor.row - 1][current_coor.column + 1];
            //printf("sp pur changed to %d %d\n", SpecifyWay_purpose.row, SpecifyWay_purpose.column);
        }
        //printf("%d putted in %d %d\n", SpecifyWay_counter + 1, current_coor.row - 1, current_coor.column + 1);
        current_mojaver[current_mojaver_index].row = current_coor.row - 1;
        current_mojaver[current_mojaver_index].column = current_coor.column + 1;
        current_mojaver_index++;
    }
    //printf("6 %d %d\n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
    if(current_coor.column + 1 < side && IsVacant(current_coor.row, current_coor.column + 1)){
        way_array[current_coor.row][current_coor.column + 1] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row][current_coor.column + 1] < SpecifyWay_minimum && integer_world_copy[current_coor.row][current_coor.column + 1] != 0){
            SpecifyWay_purpose.row = current_coor.row;
            SpecifyWay_purpose.column = current_coor.column + 1;
            SpecifyWay_minimum = integer_world_copy[current_coor.row][current_coor.column + 1];
            //printf("sp pur changed to %d %d\n", SpecifyWay_purpose.row, SpecifyWay_purpose.column);
        }
        //printf("%d putted in %d %d\n", SpecifyWay_counter + 1, current_coor.row, current_coor.column + 1);
        current_mojaver[current_mojaver_index].row = current_coor.row;
        current_mojaver[current_mojaver_index].column = current_coor.column + 1;
        current_mojaver_index++;
    }
    //printf("7 %d %d\n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
    if(current_coor.column > 0 && IsVacant(current_coor.row, current_coor.column - 1)){
        way_array[current_coor.row][current_coor.column - 1] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row][current_coor.column - 1] < SpecifyWay_minimum && integer_world_copy[current_coor.row][current_coor.column - 1] != 0){
            SpecifyWay_purpose.row = current_coor.row;
            SpecifyWay_purpose.column = current_coor.column - 1;
            SpecifyWay_minimum = integer_world_copy[current_coor.row][current_coor.column - 1];
            //printf("sp pur changed to %d %d\n", SpecifyWay_purpose.row, SpecifyWay_purpose.column);
        }
        //printf("%d putted in %d %d\n", SpecifyWay_counter + 1, current_coor.row, current_coor.column - 1);
        current_mojaver[current_mojaver_index].row = current_coor.row;
        current_mojaver[current_mojaver_index].column = current_coor.column - 1;
        current_mojaver_index++;
    }
    //printf("8 %d %d\n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
    if(current_coor.row + 1 < side && IsVacant(current_coor.row + 1, current_coor.column)){
        way_array[current_coor.row + 1][current_coor.column] = SpecifyWay_counter + 1;
        if(integer_world_copy[current_coor.row + 1][current_coor.column] < SpecifyWay_minimum && integer_world_copy[current_coor.row + 1][current_coor.column] != 0){
            SpecifyWay_purpose.row = current_coor.row + 1;
            SpecifyWay_purpose.column = current_coor.column;
            SpecifyWay_minimum = integer_world_copy[current_coor.row + 1][current_coor.column];
            //printf("sp pur changed to %d %d\n", SpecifyWay_purpose.row, SpecifyWay_purpose.column);
        }
        //printf("%d putted in %d %d\n", SpecifyWay_counter + 1, current_coor.row + 1, current_coor.column);
        current_mojaver[current_mojaver_index].row = current_coor.row + 1;
        current_mojaver[current_mojaver_index].column = current_coor.column;
        current_mojaver_index++;
    }
    //printf("9 %d %d\n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
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

int SingleMove(char code, Animal *animal)
{
    int index_of_food;
    switch (code) {
        case '6':
            if(world[animal->animal_coordinate.row][animal->animal_coordinate.column + 1] == '.' || world[animal->animal_coordinate.row][animal->animal_coordinate.column + 1] == 'F'){
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
                //printf("ngle move energy hast %d\nenergy animal bood %d ", animal->single_move_energy, animal->animal_energy);
                animal->animal_energy -= animal->single_move_energy;
                //printf("shod %d\n", animal->animal_energy);
                //Sleep(4000);
                if(animal->animal_energy < animal->single_move_energy)
                    Lose(animal, ((User_Animal == world[animal->animal_coordinate.row][animal->animal_coordinate.column]) ? 'u' : 'p'));
            }
            else if(world[animal->animal_coordinate.row][animal->animal_coordinate.column + 1] == 'H'){
                win(world[animal->animal_coordinate.row][animal->animal_coordinate.column]);
                return 1;
            }
            else return 0;
            break;

        case '9':
            if(world[animal->animal_coordinate.row - 1][animal->animal_coordinate.column + 1] == '.' || world[animal->animal_coordinate.row - 1][animal->animal_coordinate.column + 1] == 'F'){
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
                //printf("ngle move energy hast %d\nenergy animal bood %d ", animal->single_move_energy, animal->animal_energy);
                animal->animal_energy -= animal->single_move_energy;
                //printf("shod %d\n", animal->animal_energy);
                //Sleep(4000);
                if(animal->animal_energy < animal->single_move_energy)
                    Lose(animal, ((User_Animal == world[animal->animal_coordinate.row][animal->animal_coordinate.column]) ? 'u' : 'p'));
            }
            else if(world[animal->animal_coordinate.row - 1][animal->animal_coordinate.column + 1] == 'H'){
                win(world[animal->animal_coordinate.row][animal->animal_coordinate.column]);
                return 1;
            }
            else return 0;
            break;

        case '8':
            if(world[animal->animal_coordinate.row - 1][animal->animal_coordinate.column] == '.' || world[animal->animal_coordinate.row - 1][animal->animal_coordinate.column] == 'F'){
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
                //printf("ngle move energy hast %d\nenergy animal bood %d ", animal->single_move_energy, animal->animal_energy);
                animal->animal_energy -= animal->single_move_energy;
                //printf("shod %d\n", animal->animal_energy);
                //Sleep(4000);
                if(animal->animal_energy < animal->single_move_energy)
                    Lose(animal, ((User_Animal == world[animal->animal_coordinate.row][animal->animal_coordinate.column]) ? 'u' : 'p'));
            }
            else if(world[animal->animal_coordinate.row - 1][animal->animal_coordinate.column] == 'H'){
                win(world[animal->animal_coordinate.row][animal->animal_coordinate.column]);
                return 1;
            }
            else return 0;
            break;

        case '7':
            if(world[animal->animal_coordinate.row - 1][animal->animal_coordinate.column - 1] == '.' || world[animal->animal_coordinate.row - 1][animal->animal_coordinate.column - 1] == 'F'){
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
                //printf("ngle move energy hast %d\nenergy animal bood %d ", animal->single_move_energy, animal->animal_energy);
                animal->animal_energy -= animal->single_move_energy;
                //printf("shod %d\n", animal->animal_energy);
                //Sleep(4000);
                if(animal->animal_energy < animal->single_move_energy)
                    Lose(animal, ((User_Animal == world[animal->animal_coordinate.row][animal->animal_coordinate.column]) ? 'u' : 'p'));
            }
            else if(world[animal->animal_coordinate.row - 1][animal->animal_coordinate.column - 1] == 'H'){
                win(world[animal->animal_coordinate.row][animal->animal_coordinate.column]);
                return 1;
            }
            else return 0;
            break;

        case '4':
            if(world[animal->animal_coordinate.row][animal->animal_coordinate.column - 1] == '.' || world[animal->animal_coordinate.row][animal->animal_coordinate.column - 1] == 'F'){
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
                //printf("ngle move energy hast %d\nenergy animal bood %d ", animal->single_move_energy, animal->animal_energy);
                animal->animal_energy -= animal->single_move_energy;
                //printf("shod %d\n", animal->animal_energy);
                //Sleep(4000);
                if(animal->animal_energy < animal->single_move_energy)
                    Lose(animal, ((User_Animal == world[animal->animal_coordinate.row][animal->animal_coordinate.column]) ? 'u' : 'p'));
            }
            else if(world[animal->animal_coordinate.row][animal->animal_coordinate.column - 1] == 'H'){
                win(world[animal->animal_coordinate.row][animal->animal_coordinate.column]);
                return 1;
            }
            else return 0;
            break;

        case '1':
            if(world[animal->animal_coordinate.row + 1][animal->animal_coordinate.column - 1] == '.' || world[animal->animal_coordinate.row + 1][animal->animal_coordinate.column - 1] == 'F'){
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
                //printf("ngle move energy hast %d\nenergy animal bood %d ", animal->single_move_energy, animal->animal_energy);
                animal->animal_energy -= animal->single_move_energy;
                //printf("shod %d\n", animal->animal_energy);
                //Sleep(4000);
                if(animal->animal_energy < animal->single_move_energy)
                    Lose(animal, ((User_Animal == world[animal->animal_coordinate.row][animal->animal_coordinate.column]) ? 'u' : 'p'));
            }
            else if(world[animal->animal_coordinate.row + 1][animal->animal_coordinate.column - 1] == 'H'){
                win(world[animal->animal_coordinate.row][animal->animal_coordinate.column]);
                return 1;
            }
            else return 0;
            break;

        case '2':
            if(world[animal->animal_coordinate.row + 1][animal->animal_coordinate.column] == '.' || world[animal->animal_coordinate.row + 1][animal->animal_coordinate.column] == 'F'){
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
                //printf("ngle move energy hast %d\nenergy animal bood %d ", animal->single_move_energy, animal->animal_energy);
                animal->animal_energy -= animal->single_move_energy;
                //printf("shod %d\n", animal->animal_energy);
                //Sleep(4000);
                if(animal->animal_energy < animal->single_move_energy)
                    Lose(animal, ((User_Animal == world[animal->animal_coordinate.row][animal->animal_coordinate.column]) ? 'u' : 'p'));
            }
            else if(world[animal->animal_coordinate.row + 1][animal->animal_coordinate.column] == 'H'){
                win(world[animal->animal_coordinate.row][animal->animal_coordinate.column]);
                return 1;
            }
            else return 0;
            break;

        case '3':
            if(world[animal->animal_coordinate.row + 1][animal->animal_coordinate.column + 1] == '.' || world[animal->animal_coordinate.row + 1][animal->animal_coordinate.column + 1] == 'F'){
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
                //printf("ngle move energy hast %d\nenergy animal bood %d ", animal->single_move_energy, animal->animal_energy);
                animal->animal_energy -= animal->single_move_energy;
                //printf("shod %d\n", animal->animal_energy);
                //Sleep(4000);
                if(animal->animal_energy < animal->single_move_energy)
                    Lose(animal, ((User_Animal == world[animal->animal_coordinate.row][animal->animal_coordinate.column]) ? 'u' : 'p'));
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

void MakeCodeAndMove(Animal *animal, Coordinate purpose_coor, int index_of_animal)
{
    //PrintIWC();
    //printf("\n\n");
    //();
    //printf("purpose is %d %d", purpose_coor.row, purpose_coor.column);
    //S//leep(5000);
    //printf("animal oomad inja alan to khune %d %d e va energy %d\n", animal->animal_coordinate.row, animal->animal_coordinate.column, animal->animal_energy);
    char move_codes[7];
    int move_codes_index = 0;
    //printf("%d\n", way_array[purpose_coor.row][purpose_coor.column]);
    for(int i = 0; way_array[purpose_coor.row][purpose_coor.column] != 1 ; i++){

        int number = way_array[purpose_coor.row][purpose_coor.column] - 1;
        //printf("number is %d\n", number);
        //printf("i am here\n");
        if(purpose_coor.column < side - 1 && way_array[purpose_coor.row][purpose_coor.column + 1] == number){
            move_codes[move_codes_index] = '6';
            move_codes_index++;
            purpose_coor.column += 1;
            //printf("code shod %s\n", move_codes);
        }
        else if(purpose_coor.row > 0 && purpose_coor.column < side - 1 && way_array[purpose_coor.row - 1][purpose_coor.column + 1] == number){
            move_codes[move_codes_index] = '9';
            move_codes_index++;
            purpose_coor.row -= 1;
            purpose_coor.column += 1;
            //printf("code shod %s\n", move_codes);
        }
        else if(purpose_coor.row > 0 && way_array[purpose_coor.row - 1][purpose_coor.column] == number){
            move_codes[move_codes_index] = '8';
            move_codes_index++;
            move_codes[move_codes_index] = '\0';
            purpose_coor.row -= 1;
            //printf("code shod %s\n", move_codes);
        }
        else if(purpose_coor.row > 0 && purpose_coor.column > 0 && way_array[purpose_coor.row - 1][purpose_coor.column - 1] == number){
            move_codes[move_codes_index] = '7';
            move_codes_index++;
            purpose_coor.row -= 1;
            purpose_coor.column -= 1;
            //printf("code shod %s\n", move_codes);
        }
        else if(purpose_coor.column > 0 && way_array[purpose_coor.row][purpose_coor.column - 1] == number){
            move_codes[move_codes_index] = '4';
            move_codes_index++;
            purpose_coor.column -= 1;
            //printf("code shod %s\n", move_codes);
        }
        else if(purpose_coor.row < side - 1 && purpose_coor.column > 0 && way_array[purpose_coor.row + 1][purpose_coor.column - 1] == number){
            move_codes[move_codes_index] = '1';
            move_codes_index++;
            purpose_coor.row += 1;
            purpose_coor.column -= 1;
            //printf("code shod %s\n", move_codes);
        }
        else if(purpose_coor.row < side - 1 && way_array[purpose_coor.row + 1][purpose_coor.column] == number){
            move_codes[move_codes_index] = '2';
            move_codes_index++;
            purpose_coor.row += 1;
            //printf("code shod %s\n", move_codes);
        }
        else if(purpose_coor.row < side - 1 && purpose_coor.column < side -1 && way_array[purpose_coor.row + 1][purpose_coor.column + 1] == number){
            move_codes[move_codes_index] = '3';
            move_codes_index++;
            purpose_coor.row += 1;
            purpose_coor.column += 1;
            //printf("code shod %s\n", move_codes);
        }
    }
    //printf("ta tahesh omadim\n");
    //Sleep(2000);
    move_codes[move_codes_index] = '\0';
    //PrintWA();
    //printf("purpose is %d %d\n", SpecifyWay_purpose.row, SpecifyWay_purpose.column);
    //Sleep(2000);
   //printf("codes is %s and move code index is %d\n", move_codes, move_codes_index);
    //Sleep(2000);
    CodeReverser(move_codes);
    //printf("codes is %s and move code index is %d\n", move_codes, move_codes_index);
    //Sleep(2000);
    for(int i = 0; i < move_codes_index; i++){
        SingleMove(move_codes[i], animal);
        if(!IsAnimalAlive(animal))
            return;
        printf("in ghablesh \n");
        reproduction(program_animals, &program_animals_index, index_of_animal);
        printf("in badesh \n");
        Sleep(2000);
    }
}

int IsAnyAnimalCloser(Coordinate food_coor, int rounds_to_food)
{
    for(int i = 0; i < program_animals_index; i++){
        if(!program_animals[i].is_way_specified)
            continue;
        for(int j = 0; program_animals[i].purposes_distance[j] != -1; j++){
            if(food_coor.row == program_animals[i].purposes[j].row, food_coor.column == program_animals[i].purposes[j].column){
                if(rounds_to_food > ceil(program_animals[i].purposes_distance[j] / program_animals[i].movement_number)){
                    //printf("heyvooni nazdik tar hast\n");
                    return 1;
                }
                else
                    program_animals[i].is_way_specified = 0;
            }
        }
    }
    //printf("heyvooni nazdik tar nist\n");
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
    //printf("omadam to tabea jadid ba index = %d , distace %d energy %d\n", index, my_distance, energy);
    int const_distance = my_distance;
    for(int i = 0; i < foods_array_index; i++){
        if(foods_array[i].temp_food_energy == 0)
            continue;
        CreateIntegerWorldCopy(st_coor);
        //printf("faselam ta inja has %d\n", my_distance);
        CreateIntegerWorldCopy(st_coor);
        my_distance += FindDistance(st_coor, &foods_array[i].food_coordinate, CheckFood);
        //printf("faselam ba ghazaye %d %d shode %d\n", foods_array[i].food_coordinate.row, foods_array[i].food_coordinate.column, my_distance);
        if( (my_distance * single_move_energy > energy) || (my_distance > minimum_distance) || (IsAnyAnimalCloser(foods_array[i].food_coordinate, ceil(my_distance / movement_number))) ){
            //printf("if 1\n");
            my_distance = const_distance;
            continue;
        }
        energy += foods_array[i].temp_food_energy;
        if(((my_distance + foods_array[i].closest_heaven_distance) * single_move_energy < energy) && (my_distance + foods_array[i].closest_heaven_distance < minimum_distance)){
            //printf("if 2\n");
            minimum_distance = my_distance + foods_array[i].closest_heaven_distance;
            CoorArrCpy(FBW_final_purposes, FBW_purposes, index);
            IntArrCpy(FBW_final_purposes_distance, FBW_purposes_distance, index);
            FBW_final_purposes[index] = foods_array[i].food_coordinate;
            FBW_final_purposes[index + 1] = foods_array[i].closest_heaven_coordinate;
            FBW_final_purposes_distance[index] = my_distance;
            FBW_final_purposes_distance[index + 1] = -1;
            //printf("minimum changed to : \n");
            //for(int i = 0; i < 5; i++){
            //    printf("%d %d\n" ,FBW_final_purposes[i].row, FBW_final_purposes[i].column);
            //}
            FBW_return_value = 1;
        }
        else{
            //printf("else \n");
            foods_array[i].temp_food_energy = 0;
            FBW_purposes[index] = foods_array[i].food_coordinate;
            FBW_purposes_distance[index] = my_distance;
            //printf("ba dis %d ferestadam raft\n", my_distance);
            FindBestWay(foods_array[i].food_coordinate, single_move_energy, movement_number, energy - (my_distance * single_move_energy), my_distance, index + 1);
            //printf("bargashtam tabea ghabli ba index %d va distance bood %d ", index, my_distance);
        }
        my_distance = const_distance;
        foods_array[i].temp_food_energy = foods_array[i].food_energy;
        energy -= foods_array[i].temp_food_energy;
        //printf("vali bayad bashe %d", my_distance);
    }
}

void SpecifyPurposes(Animal *animal)
{
    //printf("\nvasat sp =====>  animal 0 is in %d  %d ba energy %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column, program_animals[0].animal_energy);
    int distance = 0;
    //printf("dar aval sp animal 0 is in %d  %d\n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
    CreateIntegerWorldCopy(animal->animal_coordinate);
    //printf("\nvasat sp =====>  animal 0 is in %d  %d ba energy %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column, program_animals[0].animal_energy);
    distance = FindDistance(animal->animal_coordinate, &animal->purposes[0], CheckHeaven);
    //printf("\nvasat sp =====>  animal 0 is in %d  %d ba energy %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column, program_animals[0].animal_energy);

    //printf("now purpose is %d %d\n", program_animals->purposes[0].row, program_animals->purposes[0].column);
    if(animal->single_move_energy * distance < animal->animal_energy){
        //printf("animal can go to heaven in %d %d\n", animal->purposes[0].row, animal->purposes[0].column);
        //printf("distace is %d single move energy is %d and total energy is %d\n", distance, animal->single_move_energy, animal->animal_energy);
    }
    else{
        FBW_return_value = 0;
        //printf("dar badane elsim\n");
        //CreateIntegerWorldCopy(animal->animal_coordinate);
        distance = 0;
        minimum_distance = 100;
        //printf("\nvasat sp =====>  animal 0 is in %d  %d ba energy %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column, program_animals[0].animal_energy);
        FindBestWay(animal->animal_coordinate, animal->single_move_energy, animal->movement_number, animal->animal_energy, 0, 0);
        //printf("\nvasat sp =====>  animal 0 is in %d  %d ba energy %d \n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column, program_animals[0].animal_energy);
        if(FBW_return_value){
            CoorArrCpy(animal->purposes, FBW_final_purposes, 5);
            IntArrCpy(animal->purposes_distance, FBW_final_purposes_distance, 5);
        }
    }
    animal->is_way_specified = 1;
    //printf("dar khar sp animal 0 is in %d  %d\n", program_animals[0].animal_coordinate.row, program_animals[0].animal_coordinate.column);
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

void AddFood(Coordinate fcoor, int fenergy)
{
    foods_array[foods_array_index].food_coordinate = fcoor;
    foods_array[foods_array_index].food_energy = fenergy;
    CreateIntegerWorldCopy(fcoor);
    foods_array[foods_array_index].closest_heaven_distance = FindDistance(fcoor, &foods_array[foods_array_index].closest_heaven_coordinate, CheckHeaven);
    foods_array[foods_array_index].temp_food_energy = fenergy;
    foods_array_index++;
}

int isAnyAnimal(int c, int r,char mode)
{
    int i;
    if(mode == 'p'){
        for(i = 0 ; i < program_animals_index ; i++){
            if(c == program_animals[i].animal_coordinate.row && r == program_animals[i].animal_coordinate.column)
                return(i);
        }
    }
    else{
        for(i = 0 ; i< user_animals_index ; i++){
            if(c == user_animals[i].animal_coordinate.row && r == user_animals[i].animal_coordinate.column)
                return(i);
        }
    }
    return(-1);
}

int findPrimaryInfo(int kind, char mode)
{
    for(int i = 0; i < primary_info_index; i++){
        if(kind == primary_info[i][0]){
            switch (mode)
            {
            case 'i':
                return i;
                break;
            case 'n':
                return primary_info[i][1];
            case 'e':
                return primary_info[i][2];
            default:
                break;
            }
            return -1;
        }
    }
}

void reproduction(Animal animal_arr[], int *animal_arr_index, int animal_index)
{
    //printf("%p\n", animal_arr);
    //Sleep(5000);
    //printf("man heyvoon khune %d %d omadam bbinam mishe reproduct konam ya na\n", animal_arr[animal_index].animal_coordinate.row, animal_arr[animal_index].animal_coordinate.column);
    //Sleep(5000);
    int j,r,c,sw=0,a,b,index,xR,yR; //sw byad avale tabe sefr beshe
    char kind;
    if(Random(0, 1) == 0)  return;
    //if(animal_arr[animal_index].animal_energy < animal_arr[animal_index].reproduction_energy) return;
    int x = animal_arr[animal_index].animal_coordinate.row;
    int y = animal_arr[animal_index].animal_coordinate.column;
    kind = world[x][y];
    for(a = -1; a <= 1; a++){
       for(b = -1; b <= 1; b++){
            if(a == 0 && b == 0)
                continue;
            if(kind == world[x + a][y + b]){
                index = isAnyAnimal(x + a, y + b, 'u');
                if(index==-1)
                    index = isAnyAnimal(x + a, y + b, 'p');
                if(animal_arr[index].animal_energy >= animal_arr[index].reproduction_energy){
                    //printf("khb heyvoon khune %d %d ro peyda kardam :)\n", x + a, y + b);
                    r = x + a;
                    c = y + b;
                    //Sleep(5000);
                    sw = 1;
                    break;
                }
            }
        }
        if(sw)        //// har do halghe break beshe
            break;
    }
    if(sw == 1){
        printf("$$$$$$$$$$$  dige mikham shoro konime:)  $$$$$$$$$$$$$$$$\n");
        Sleep(5000);
        animal_arr[animal_index].animal_energy -= animal_arr[animal_index].reproduction_energy / 2;
        animal_arr[index].animal_energy -= animal_arr[index].reproduction_energy / 2;
        animal_arr[*animal_arr_index].animal_energy = findPrimaryInfo(kind, 'e');
        animal_arr[*animal_arr_index].single_move_energy = Random(20,200);
        animal_arr[*animal_arr_index].movement_number = Random(1,3);
        animal_arr[*animal_arr_index].reproduction_energy = Random(60,600);
        animal_arr[*animal_arr_index].attack_energy = Random(20,500);
        animal_arr[*animal_arr_index].defense_energy = Random(20,500);
        int k = 0;
        while(++k){
            for(int i = -k; i <= k; i++){
                for(int j = -k; j <= k; j++){
                    //printf("r = %d , c = %d, k = %d\n", r, c, k);
                    //Sleep(5000);
                    if(world[r + i][c + j] == '.' || world[r + i][c + j] == 'F'){
                        //printf("khune %d %d baraye bachamon khalie XD\n", r + i, c + j);
                        animal_arr[*animal_arr_index].animal_coordinate.row = r + i;
                        animal_arr[*animal_arr_index].animal_coordinate.column = c + j;
                        //printf("animal %d to %d %d ba ene %d, attack energy %d , single move energy %d, movement number %d, \n", *animal_arr_index, animal_arr[*animal_arr_index].animal_coordinate.row,
                         //animal_arr[*animal_arr_index].animal_coordinate.column, animal_arr[*animal_arr_index].animal_energy, animal_arr[*animal_arr_index].attack_energy, animal_arr[*animal_arr_index].single_move_energy, animal_arr[*animal_arr_index].movement_number);
                        (*animal_arr_index) += 1;
                        world[r + i][c + j] = kind;
                        //printf("done \n");
                        //Sleep(10000);
                        return;
                    }
                }
            }
        }
        // do{
        //     int k=1;
        //     do{
        //         xR=random(-k,k);
        //         yR=random(-k,k);
        //     }while(xR != 0 && yR != 0);
        //     r = x + xR;
        //     c = y +yR;
        //     k++;
        // }while(world[r][c]!='.');
        // animal_arr[*animal_arr_index].animal_coordinate.row=r;
        // animal_arr[*animal_arr_index].animal_coordinate.column=c;
        // *animal_arr_index++;
        // world[r][c]=kind;
    }
}

void MoveAnimal(int index_of_animal)
{
    if(!IsAnimalAlive(&program_animals[index_of_animal]))
        return;
    //printf("heyvoon %d oomad inja \n", index_of_animal);
    //Sleep(1000);

    PrintW();
    Sleep(3000);
    //printf("step 1 %d %d \n", program_animals[index_of_animal].animal_coordinate.row, program_animals[index_of_animal].animal_coordinate.column);
    //Sleep(1000);
    if(!program_animals[index_of_animal].is_way_specified)
        SpecifyPurposes(&program_animals[index_of_animal]);
    //printf("step 2 %d %d \n", program_animals[index_of_animal].animal_coordinate.row, program_animals[index_of_animal].animal_coordinate.column);
    //Sleep(1000);
    CreateIntegerWorldCopy(program_animals[index_of_animal].animal_coordinate);
    //printf("step 3 %d %d \n", program_animals[index_of_animal].animal_coordinate.row, program_animals[index_of_animal].animal_coordinate.column);
    //Sleep(1000);
    FindDistance(program_animals[index_of_animal].purposes[program_animals[index_of_animal].current_purpose_index], &program_animals[index_of_animal].animal_coordinate,  CheckFood);
    //printf("step 4 %d %d \n", program_animals[index_of_animal].animal_coordinate.row, program_animals[index_of_animal].animal_coordinate.column);
    //Sleep(1000);
    CreateWayArray(program_animals[index_of_animal].animal_coordinate);
    SpecifyWay_minimum = 100;
    SpecifyWay_counter = 1;
    SpecifyWay(program_animals[index_of_animal].animal_coordinate, program_animals[index_of_animal].movement_number);
    //printf("step 5 %d %d \n", program_animals[index_of_animal].animal_coordinate.row, program_animals[index_of_animal].animal_coordinate.column);
    //Sleep(1000);
    //PrintWA();
    MakeCodeAndMove(&program_animals[index_of_animal], SpecifyWay_purpose, index_of_animal);
    //printf("step 6 %d %d \n", program_animals[index_of_animal].animal_coordinate.row, program_animals[index_of_animal].animal_coordinate.column);
    //Sleep(1000);
    system("cls");
}


