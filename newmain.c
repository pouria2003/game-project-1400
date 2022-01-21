#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include "newfunc.c"

#define esc 27

char ResumeTheGame(FILE *);

int main()
{
   char User_Animal;
   char user_move;
   for(int i = 0; i <20; i++)
      for(int j = 0; j < 20; j++)
         world[i][j] = '.';

/* #########################################   GEREFTAN DATA AZ MAP  ##########################################*/

      int seprator_counter = 0, index_for_add_genetic = 0;// user move harkat karbaro migire
      FILE * inputs = fopen("map_phase1.txt", "r");
      fscanf(inputs, "%d", &side);
      char temp[100];

      while(fscanf(inputs, "%s", temp) != EOF){
         if(temp[0] == 'F'){
            fscanf(inputs, "%d", &foods_array[foods_array_index].food_energy);
            fscanf(inputs, "%s", temp);
            foods_array[foods_array_index].food_coordinate.row = FindInteger(temp);
            foods_array[foods_array_index].food_coordinate.column = FindInteger(temp);
            foods_array[foods_array_index].temp_food_energy = foods_array[foods_array_index].food_energy;
            CreateIntegerWorldCopy(foods_array[foods_array_index].food_coordinate);
            foods_array[foods_array_index].closest_heaven_distance = FindDistance(foods_array[foods_array_index].food_coordinate, &foods_array[foods_array_index].closest_heaven_coordinate, CheckHeaven);
            foods_array_index++;
         }

         else if(temp[0] == '#'){
            int number, row, col;
            fscanf(inputs, "%d", &number);
            fscanf(inputs, "%s", temp);
            for(int i = 0; i < number; i++){
                row = FindInteger(temp);
                col = FindInteger(temp);
                world[row][col] = '#';
            }
         }

         else if(temp[0] == 'H'){
            int number, row, col;
            fscanf(inputs, "%d", &number);
            fscanf(inputs, "%s", temp);
            for(int i = 0; i < number; i++){
                row = FindInteger(temp);
                col = FindInteger(temp);
                world[row][col] = 'H';
            }
         }

         else if(IsEqualStr(temp, "===")){
            seprator_counter++;
         }

         else{
            int number, row, col;

            if(seprator_counter == 4){
               char animal = temp[0];
               int current_energy;
               fscanf(inputs, "%d", &program_animals[index_for_add_genetic].animal_energy);
               fscanf(inputs, "%d$%d$%d$%d$%d", &program_animals[index_for_add_genetic].single_move_energy,
               &program_animals[index_for_add_genetic].movement_number, &program_animals[index_for_add_genetic].reproduction_energy
               , &program_animals[index_for_add_genetic].attack_energy, &program_animals[index_for_add_genetic].defense_energy);

               index_for_add_genetic++;

               for( ; world[program_animals[index_for_add_genetic].animal_coordinate.row][program_animals[index_for_add_genetic].animal_coordinate.column] == animal; index_for_add_genetic++){
                  program_animals[index_for_add_genetic].animal_energy = program_animals[index_for_add_genetic - 1].animal_energy;
                  program_animals[index_for_add_genetic].movement_number = program_animals[index_for_add_genetic - 1].movement_number;
                  program_animals[index_for_add_genetic].reproduction_energy = program_animals[index_for_add_genetic - 1].reproduction_energy;
                  program_animals[index_for_add_genetic].single_move_energy = program_animals[index_for_add_genetic - 1].single_move_energy;
                  program_animals[index_for_add_genetic].attack_energy = program_animals[index_for_add_genetic - 1].attack_energy;
                  program_animals[index_for_add_genetic].defense_energy = program_animals[index_for_add_genetic - 1].defense_energy;
               }
            }

            else if(seprator_counter == 3){
                  User_Animal = temp[0];
            }

            else{
               char animal = temp[0];
               fscanf(inputs, "%d", &number);
               fscanf(inputs, "%s", temp);
               for(int i = 0; i < number; i++){
                  row = FindInteger(temp);
                  col = FindInteger(temp);
                  world[row][col] = animal;
                  program_animals[program_animals_index].animal_coordinate.row = row;
                  program_animals[program_animals_index].animal_coordinate.column = col;
                  program_animals_index++;

               }
            }
         }
      }
      fclose(inputs);
      PrintW();
      for(int i = 0; i < foods_array_index; i++){
        printf("food is in %d %d and heaven is in %d %d \n", foods_array[i].food_coordinate.row, foods_array[i].food_coordinate.column, foods_array[i].closest_heaven_coordinate.row, foods_array[i].closest_heaven_coordinate.column);
      }

      noname(&program_animals[0]);
      printf("purposes is : \n");
      for(int i = 0; i < 5; i++){
        printf("%d %d\n", program_animals[0].purposes[i].row, program_animals[0].purposes[i].column);
      }

      return 0;
}
