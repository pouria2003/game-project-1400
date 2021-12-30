#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include "functions_phase-1.c"


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
      }

      else{
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
         else if(seprator_counter == 3){
               MyAnimal = temp[0];
         }
         else{
            char animal = temp[0];
            fscanf(inputs, "%d", &number);
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

   fclose(inputs);
   // for(int i = 0; i < program_animals_index; i++){
   //    printf("hevoon %c e va gen => %d %d %d %d %d\n",world[program_animals[i].row][program_animals[i].column] , program_animals[i].single_move_energy,
   //          program_animals[i].movement_number, program_animals[i].reproduction_energy
   //          , program_animals[i].attack_energy, program_animals[i].defense_energy);
   // }

   return 0;
}
