#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include "func_phase_3.c"
#include <conio.h>
#include <time.h>

#define esc 27

//char ResumeTheGame(FILE *);


int main()
{
    srand(time(0));
   char user_move;
   int sw = 1;
   for(int i = 0; i <20; i++)
      for(int j = 0; j < 20; j++)
         world[i][j] = '.';

/* #########################################   GEREFTAN DATA AZ MAP  ##########################################*/
    int seprator_counter = 0, index_for_add_genetic = 0;// user move harkat karbaro migire
    FILE * inputs = fopen("map_phase2.txt", "r");
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
                primary_info[findPrimaryInfo(animal, 'i')][2] = program_animals[index_for_add_genetic].animal_energy;
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
                primary_info[primary_info_index][0] = (int)animal;
                primary_info[primary_info_index][1] = number;
                primary_info_index++;
                fscanf(inputs, "%s", temp);
                for(int i = 0; i < number; i++){
                    row = FindInteger(temp);
                    col = FindInteger(temp);
                    world[row][col] = animal;
                    program_animals[program_animals_index].animal_coordinate.row = row;
                    program_animals[program_animals_index].animal_coordinate.column = col;
                    for(int i = 0; i < 5; i++) program_animals[program_animals_index].purposes_distance[i] = -1;
                    program_animals[program_animals_index].is_way_specified = 0;
                    program_animals[program_animals_index].current_purpose_index = 0;
                    program_animals_index++;
                }
            }
        }
    }
    fclose(inputs);

   printf("Hello player!\nWelcome to our game.\nHere's how the game works:\nYou can choose your move based on this\n1 2 3\n\
4 5 6\n7 8 9\nConsider 5 as your current location and choose your move.\nYou can stop the game and resume it when you play again by pressing \"Esc\".\nYour type is %c.\nIf you are ready press number 5 : ", User_Animal);
	user_move = getch();
	if(user_move != '5'){
	   printf("see you later!");
	   exit(0);
	}

    user_animals_index = 0;
    for(int i = 0; i < program_animals_index; i++){
      if(world[program_animals[i].animal_coordinate.row][program_animals[i].animal_coordinate.column] == User_Animal){
         TransferToUserAnimals(i);
         i--;
      }
   }

   while(1){

      for(int animalIndex = 0; animalIndex < user_animals_index; animalIndex++){
         if(!IsAnimalAlive(&user_animals[animalIndex])){
            continue;
         }
         for(int nmove = 0; nmove < user_animals[animalIndex].movement_number; nmove++){
            if(!IsAnimalAlive(&user_animals[animalIndex])){
                continue;
            }
            do{
                system("cls");
                PrintW();
                printf("for animal in %d %d whith energy %d adn single move energy %d\nchoose your move : ", user_animals[animalIndex].animal_coordinate.row, 
                user_animals[animalIndex].animal_coordinate.column, user_animals[animalIndex].animal_energy, user_animals[animalIndex].single_move_energy);
                PrintFoodInfo();
                user_move = getch();
                sw = SingleMove(user_move, &user_animals[animalIndex]);
                if(user_move == esc)
                    exit(0);
                if(!sw || WrongUserMove(user_move, animalIndex))
                    beepNtimes(3);
            }while(!sw);
        }
      }
      system("cls");
      for(int animalIndex = 0; animalIndex < program_animals_index; animalIndex++){
            MoveAnimal(animalIndex);
      }
   }
   return 0;
}
