#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include "functions_phase-1.c"

// struct Animal{
//    int row;
//    int column;
//    int energy;
//    int single_move_energy;
//    int movement_number;
//    int reproduction_energy;
//    int attack_energy;
//    int defense_energy;
// };

// #define maxside 20
// #define maxanimals 50
// #define maxuseranimals 10

// extern char world[maxside][maxside];
// extern int integer_world_copy[maxside][maxside];
// extern int energys[maxside][maxside] = {{0}};
// extern struct Animal program_animals[maxanimals];
// extern struct Animal user_animals[maxuseranimals];
// extern int side;
// extern int lastmojaver[100][2];
// extern int currentmojaver[100][2];
// extern int lastmojaveindex = 0;
// extern int currentmojaverindex = 0;
// extern int counter = 0;
// extern int hx;
// extern int hy;

// extern int integer_world_copy[20][20];
// extern char world[20][20];
// extern int energys[20][20];
// //struct Animal program_animals[20];
// //struct Animal user_animals[10];
// extern int side;
// extern int lastmojaver[100][2];
// extern int currentmojaver[100][2];
// extern int lastmojaveindex;
// extern int currentmojaverindex;
// extern int counter;
// extern int hx;
// extern int hy;

int main(){
   for(int i = 0; i <20; i++){
      for(int j = 0; j < 20; j++){
         world[i][j] = '.';
      }
   }
   char MyAnimal;
   int seprator_counter = 0, index_for_add_genetic = 0, program_animals_index = 0;
   FILE * inputs = fopen("map-phase1.txt", "r");
   fscanf(inputs, "%d", &side);
   char temp[100];
   while(fscanf(inputs, "%s", temp) != EOF){
      printf("temp is %s\n", temp);
      if(temp[0] == 'F'){
         int food_energy, row, col;
         fscanf(inputs, "%d", &food_energy);
         fscanf(inputs, "%s", temp);
         row = find_integer(temp);
         col = find_integer(temp);
         energys[row][col] += food_energy;
      }

      else if(temp[0] == '#'){
         int number, row, col;
         fscanf(inputs, "%d", &number);
         fscanf(inputs, "%s", temp);
         for(int k = 0; k < number; k++){
            row = find_integer(temp);
            col = find_integer(temp);
            world[row][col] = '#';
         }
      }

      else if(temp[0] == 'H'){
         int number, row, col;
         fscanf(inputs, "%d", &number);
         fscanf(inputs, "%s", temp);
         for(int k = 0; k < number; k++){
            row = find_integer(temp);
            col = find_integer(temp);
            world[row][col] = 'H';
         }
      }

      else if(is_equal_str(temp, "===")){
         seprator_counter++;
         printf("sep changed to %d\n", seprator_counter);
      }

      else{
         printf("i am here and sep is %d\n", seprator_counter);
         int number, row, col;
         if(seprator_counter == 4){
            char animal = temp[0];
            int current_energy;
            fscanf(inputs, "%d", &program_animals[index_for_add_genetic].energy);
            fscanf(inputs, "%d$%d$%d$%d$%d", &program_animals[index_for_add_genetic].single_move_energy,
            &program_animals[index_for_add_genetic].movement_number, &program_animals[index_for_add_genetic].reproduction_energy
            , &program_animals[index_for_add_genetic].attack_energy, &program_animals[index_for_add_genetic].defense_energy);

            index_for_add_genetic++;
            for( ; world[program_animals[index_for_add_genetic].row][program_animals[index_for_add_genetic].column] == animal; index_for_add_genetic++){
               program_animals[index_for_add_genetic] = program_animals[index_for_add_genetic - 1];
            }
         }
         else{
            if(fscanf(inputs, "%d", &number) == EOF){
               MyAnimal = temp[0];
            }
            else{
               char animal = temp[0];
               fscanf(inputs, "%s", temp);
               for(int i = 0; i < number; i++){
                  row = find_integer(temp);
                  col = find_integer(temp);
                  world[row][col] = animal;
                  program_animals[program_animals_index].row = row;
                  program_animals[program_animals_index].column = col;
                  program_animals_index++;
               }
            }
         }
      }

   }
   fclose(inputs);
    printf("hello");
   for(int i = 0; i < program_animals_index; i++){
      printf("hevoon %c e va gen => %d %d %d %d %d\n",world[program_animals[i].row][program_animals[i].column] , program_animals[i].single_move_energy,
            program_animals[i].movement_number, program_animals[i].reproduction_energy
            , program_animals[i].attack_energy, program_animals[i].defense_energy);
   }

    for(int i = 0; i < side; i++){
       for(int j = 0; j < side; j++){
          printf("%c", world[i][j]);
       }
       printf("\n");
    }
    printf("\n");
    for(int i = 0; i < side; i++){
      for(int j = 0; j < side; j++){
         printf("%d  ", energys[i][j]);
       }
      printf("\n");
    }
   return 0;
}
