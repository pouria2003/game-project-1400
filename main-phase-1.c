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
               
               
               //printf("animal added with row = %d , column = %d\n", row , col);
               
               
               
               world[row][col] = animal;
               program_animals[program_animals_index].row = row;
               program_animals[program_animals_index].column = col;
               program_animals_index++;
               
               
              // printf("in dor injoorie ke : ");
              // for(int i = 0; i < program_animals_index; i++){
	//	printf("%d %d\n", program_animals[i].row, program_animals[i].column);
	//}

	
            }
         }
      }
   }

   fclose(inputs);
	
//	for(int i = 0; i < program_animals_index; i++){
//		printf("%d %d\n", program_animals[i].row, program_animals[i].column);
//	}
	
   for(int i = 0; i < program_animals_index; i++){
      if(world[program_animals[i].row][program_animals[i].column] == User_Animal){
         TransferToUserAnimals(i);
         i--;
      }
   }



   printf("Hello player\nWelcome to our game\nHere's how the game works.\nYou can choose your move based on this\n1 2 3\n\
4 5 6\n7 8 9\nConsider 5 as yout current location and choose your move.\nif you are ready press number 5 : ");

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
         do{
         if(!sw)printf("\a");
         printf("choose your momve : ");
         scanf("%d", &user_move);
         //printf("changing animal in %d %d", user_animals[i].row, user_animals[i].column);
         sw = single_move(user_move + '0', &user_animals[i].row, &user_animals[i].column);
         }while(!sw);
         system("cls");
         print();
      }
      Sleep(2500);
      system("cls");
      for(int i = 0; i < program_animals_index; i++){
         CreateWorldCopy(program_animals[i].row, program_animals[i].column);
         FindWay(program_animals[i].row, program_animals[i].column, &program_animals[i].row, &program_animals[i].column, 'f');
         printf("im animal in %d %d and my heaven is %d %d\n", program_animals[i].row, program_animals[i].column, hx, hy);
         CreateWorldCopy(program_animals[i].row, program_animals[i].column);
         FindWay(hx, hy, &program_animals[i].row, &program_animals[i].column, 'g');
         if(i == 1){
         	for(int  i = 0 ; i < side ; i ++){
         		for ( int j = 0 ; i < side ; j++){
         			printf("%d ", integer_world_copy[i][j]);
				 }
				 printf("\n");
			 }
		 }
         print();
      	 Sleep(9500);
      	 system("cls");
      }
   }







	
//    for(int i = 0; i < program_animals_index; i++){
//       printf("hevoon man %c e va gen => %d %d %d %d %d\n",world[program_animals[i].row][program_animals[i].column] , program_animals[i].single_move_energy,
//             program_animals[i].movement_number, program_animals[i].reproduction_energy
//             , program_animals[i].attack_energy, program_animals[i].defense_energy);
//    }
//    for(int i = 0; i < user_animals_index; i++){
//        printf("hevoon karbar %c e to khune %d %d va gen => %d %d %d %d %d\n",world[user_animals[i].row][user_animals[i].column] , user_animals[i].row, user_animals[i].column, user_animals[i].single_move_energy,
//             user_animals[i].movement_number, user_animals[i].reproduction_energy
//             , user_animals[i].attack_energy, user_animals[i].defense_energy);
//    }

   return 0;
}
