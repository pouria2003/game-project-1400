#include <stdio.h>
#include <stdlib.h>

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
    struct Coordinate the_closest_heaven_coordinate;
    int food_energy;

};

struct Animal{
    struct Coordinate animal_coordinate;
    int animal_energy;
    int single_move_energy;
};

typedef struct Coordinate Coordinate;
typedef struct Animal Animal;
typedef struct Food Food;

Animal program_animals[maxanimals];
Animal user_animals[maxkindanimals];
Food foods[maxfood];
Coordinate current_mojaver[20];
Coordinate previous_mojaver[20];
int current_mojaver_index = 0;
int previous_mojaver_index = 0;
int counter = 0;
int side = 5;
int integer_world_copy[maxside][maxside];
char world[maxside][maxside];
int distance = 0;

void CreateIntegerWorldCopy()
{
    for(int i = 0; i < side; i++)
        for(int j = 0; j < side; j++)
            if(world[i][j] != '#')
                integer_world_copy[i][j] = 0;
}

int CheckHeaven(Coordinate my_coor, int index){if(world[my_coor.row][my_coor.column] == 'H') return 1; return 0;}
int CheckAnimal(Coordinate st_coor, Coordinate fi_coor){if(st_coor.row == fi_coor.row && st_coor.column == fi_coor.column)return 1; return 0;}
int CheckFood(Coordinate st_coor, Coordinate fi_coor){if(st_coor.row == fi_coor.row && st_coor.column == fi_coor.column)return 1; return 0;}

void FindDistance(Coordinate current_coor, Coordinate final_coor, int (*CheckStopCondition)(Coordinate, Coordinate))
{
    if(CheckStopCondition(current_coor, final_coor))
        return;
    int num = integer_world_copy[current_coor.row][current_coor.column];
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
            return;
        for(int i = 0; i < current_mojaver_index; i++)
            previous_mojaver[i] = current_mojaver[i];
        counter = 0;
        previous_mojaver_index = current_mojaver_index;
        current_mojaver_index = 0;
        FindDistance(previous_mojaver[0], final_coor, CheckStopCondition);
    }
}

int main()
{

}
