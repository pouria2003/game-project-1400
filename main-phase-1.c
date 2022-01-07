#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include "functions_phase-1.c"

#define esc 27

char ResumeTheGame(FILE *);

int main()
{
   FILE * gamelog = fopen("gamelog.txt", "w");
   FILE * savedgame = fopen("savedgame.txt", "r");
   fscanf(savedgame, " ");
   char User_Animal;
   char user_move;
   int kind_animals_number[20][2];
    int kind_animals_number_index = 0;
   for(int i = 0; i <20; i++){
      for(int j = 0; j < 20; j++){
         world[i][j] = '.';
      }
   }
   int g = 0;
   if(!feof(savedgame)){
      printf("Hello player,welcome to the game!\nBefore we start choose how you want to play.\npress 1 if you want to resume your previous game\n\
Press 2 if you want to start a new game.\nEnter here : ");
      scanf("%d", &g);
   }
    if(g == 1 && !feof(savedgame)){
        User_Animal = ResumeTheGame(savedgame);
        system("cls");
        printf("if you are ready press number 5 : ");
        user_move = getch();
        if(user_move != '5'){
		      printf("see you later");
		      exit(0);
        }
    }

   else{
      
   /* #########################################   GEREFTAN DATA AZ MAP  ##########################################*/

      int seprator_counter = 0, index_for_add_genetic = 0;// user move harkat karbaro migire
      FILE * inputs = fopen("map_phase1.txt", "r");
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
               kind_animals_number[kind_animals_number_index][0] = (int)animal;
               kind_animals_number[kind_animals_number_index][1] = number;
               kind_animals_number_index += 1;
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


      printf("Hello player!\nWelcome to our game.\nHere's how the game works:\nYou can choose your move based on this\n1 2 3\n\
4 5 6\n7 8 9\nConsider 5 as your current location and choose your move.\nYou can stop the game and resume it when you play again by pressing \"Esc\".\nYour type is %c.\nIf you are ready press number 5 : ", User_Animal);
      while ((getchar()) != '\n');
	   user_move = getch();
	   if(user_move != '5'){
	      printf("see you later!");
	      exit(0);
	   }

    }

/* #########################################   JODA KARDAN GONE HAYE KARBAR   ##########################################*/
   user_animals_index = 0;
   for(int i = 0; i < program_animals_index; i++){
      if(world[program_animals[i].row][program_animals[i].column] == User_Animal){
         TransferToUserAnimals(i);
         i--;
      }
   }


// /* ##################################################   SHORO BAZI   ##################################################*/

   system("Cls");
	int sw = 1;
	int counter_round = 1, check_reapeted_animal_for_log = 0;

   while(1){
    kind_animals_number_index = 0;
    LogGame(gamelog, 's', counter_round, 'C', 1, 1, 'p');
    counter_round += 1;
   	print();
   	LogGame(gamelog, 'k', 0, User_Animal, user_animals_index, 0, 'u');
      for(int i = 0; i < user_animals_index; i++){
        LogGame(gamelog, 'f', counter_round, User_Animal, user_animals_index, i, 'u');
         for(int k = 0; k < user_animals[i].movement_number; k++){
            do{
               if(!sw){
                  printf("\a");
                  system("cls");
                  print();
               }
               printf("choose your move : ");
               user_move = getch();
               if(user_move == esc){
                  SaveTheGame(User_Animal);
                  printf("\ngame saved. you can continue your game later.");
                  exit(0);
               }
               sw = single_move(user_move, &user_animals[i].row, &user_animals[i].column);
            }while(!sw);
            system("cls");
            print();
         }
         LogGame(gamelog, 't', counter_round, 'A', 0, i, 'u');
      }
      Sleep(1500);
      system("cls");
      check_reapeted_animal_for_log = 0;
      for(int i = 0; i < program_animals_index; i++){
        if(i >= check_reapeted_animal_for_log){
            if(kind_animals_number[kind_animals_number_index][0] == User_Animal) kind_animals_number_index += 1;
            LogGame(gamelog, 'k', 0, world[program_animals[i].row][program_animals[i].column], kind_animals_number[kind_animals_number_index][1], i, 'p');
            check_reapeted_animal_for_log += kind_animals_number[kind_animals_number_index][1];
            kind_animals_number_index += 1;
        }
         LogGame(gamelog, 'f', 0, 'E', 0, i, 'p');
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
            Sleep(1500);
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
         LogGame(gamelog, 't', 0, 'E', 0, i, 'p');
      }
   }

    fclose(gamelog);
    return 0;
}

char ResumeTheGame(FILE * savedgame)
{
   program_animals_index = 0;
   char c, User_Animal;
   int i=0,row,column;
   savedgame = fopen("savedgame.txt","r");
   fscanf(savedgame, "%d ", &side);
   fscanf(savedgame, "%c ", &User_Animal);
   fscanf(savedgame,"%c ", &c);
   do{
       fscanf(savedgame,"%d %d ",&row, &column);
       world[row][column] = c;
       fscanf(savedgame,"%c ", &c);
   }while(c=='H'||c=='#');
   fseek(savedgame, -2, SEEK_CUR);
   while(!feof(savedgame)){
       fscanf(savedgame,"%c ", &c);
       fscanf(savedgame,"%d %d %d %d %d %d %d %d ",&program_animals[i].row,&program_animals[i].column,&program_animals[i].energy,&program_animals[i].single_move_energy,
       &program_animals[i].movement_number, &program_animals[i].reproduction_energy
       ,&program_animals[i].attack_energy, &program_animals[i].defense_energy);
       world[program_animals[i].row][program_animals[i].column]=c;
       i++;
       program_animals_index++;
   }
    fclose(savedgame);
   return User_Animal;
}
