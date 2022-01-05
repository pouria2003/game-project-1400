#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include "functions_phase-1.c"

int main()
{
   for(int i = 0; i <20; i++){
      for(int j = 0; j < 20; j++){
         world[i][j] = '.';
      }
   }
/* #########################################   GEREFTAN DATA AZ MAP  ##########################################*/
   char User_Animal;
   int seprator_counter = 0, index_for_add_genetic = 0, user_move = 0; // user move harkat karbaro migire
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
               program_animals[index_for_add_genetic].energy = program_animals[index_for_add_genetic - 1].energy;
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


/* #########################################   JODA KARDAN GONE HAYE KARBAR   ##########################################*/

   for(int i = 0; i < program_animals_index; i++){
      if(world[program_animals[i].row][program_animals[i].column] == User_Animal){
         TransferToUserAnimals(i);
         i--;
      }
   }

// /* ##################################################   SHORO BAZI   ##################################################*/

   printf("Hello player\nWelcome to our game\nHere's how the game works.\nYou can choose your move based on this\n1 2 3\n\
4 5 6\n7 8 9\nConsider 5 as yout current location and choose your move.\nyour type is %c.\nif you are ready press number 5 : ", User_Animal);

	scanf("%d", &user_move);
	if(user_move != 5){
		printf("see you later");
		exit(0);
	}

	system("cls");

	int sw = 1;

   while(1){
   	print();
      for(int i = 0; i < user_animals_index; i++){
         for(int k = 0; k < user_animals[i].movement_number; k++){
            do{
            if(!sw)printf("\a");
            printf("choose your momve : ");
            scanf("%d", &user_move);
            sw = single_move(user_move + '0', &user_animals[i].row, &user_animals[i].column);
            }while(!sw);
            system("cls");
            print();
         }
      }
      Sleep(2000);
      system("cls");
      for(int i = 0; i < program_animals_index; i++){
         CreateWorldCopy();
         counter = 0;
         lastmojaveindex = 0;
         currentmojaverindex = 0;
         FindWay(program_animals[i].row, program_animals[i].column, &program_animals[i].row, &program_animals[i].column, 'f');
         CreateWorldCopy();
         integer_world_copy[hx][hy] = 1;
         counter = 0;
         lastmojaveindex = 0;
         currentmojaverindex = 0;
         FindWay(hx, hy, &program_animals[i].row, &program_animals[i].column, 'g');

         for(int i = 0; i < side; i++){
            for(int j = 0; j < side; j++){
                world3[i][j] = 0;
            }
        }
        CreateWorld3(program_animals[i].row, program_animals[i].column);
         for(int k = 0; k < program_animals[i].movement_number; k++){
            int move_result = Move(&program_animals[i].row, &program_animals[i].column);
            print();
            Sleep(2000);
            system("cls");
            if(!move_result){
                for(int i = 0; i < side; i++){
                    for(int j = 0; j < side; j++){
                        world3[i][j] = 0;
                    }
                }
                CreateWorld3(program_animals[i].row, program_animals[i].column);
           }
         }
      }
   }
   return 0;
}
