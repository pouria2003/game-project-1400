#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include "functions.c"

#define maxside 20
#define maxanimals 20

char world[maxside][maxside];
int integer_world_copy[20][20];
int energys[maxside][maxside] = {{0}};
int animals_coordinate[maxanimals][2];
int side;
int lastmojaver[100][2] = {{0,0}};
int currentmojaver[100][2];
int lastmojaveindex = 1;
int currentmojaverindex = 0;
int counter = 0;
int hx;
int hy;


int main(){
   for(int i = 0; i <20; i++){      // inja hame khune ha . mishe
      for(int j = 0; j < 20; j++){
         world[i][j] = '.';
      }
   }
   char MyAnimal;
   int separator_counter = 0, animals_coordinate_index = 0;
   char temp[100];
   scanf("%d", &side);     // size jahane
   while(separator_counter < 4){       // in halghe hame vorodi haro mibare to world
      scanf("%s", temp);
      if(temp[0] == 'F'){
         int food_energy, row, col;
         scanf("%d", &food_energy);
         scanf("%s", temp);
         row = find_integer(temp);
         col = find_integer(temp);
         energys[row][col] += food_energy;
      }

      else if(temp[0] == '#'){
         int number, row, col;
         scanf("%d", &number);
         scanf("%s", temp);
         for(int k = 0; k < number; k++){
            row = find_integer(temp);
            col = find_integer(temp);
            world[row][col] = '#';
         }
      }

      else if(temp[0] == 'H'){
         int number, row, col;
         scanf("%d", &number);
         scanf("%s", temp);
         for(int k = 0; k < number; k++){
            row = find_integer(temp);
            col = find_integer(temp);
            world[row][col] = 'H';
         }
      }

      else if(is_equal_str(temp, "===")){
         separator_counter++;
      }

      else{
         int row, column;
         if(separator_counter == 2){
            char animal = temp[0];
            int number;
            scanf("%d", &number);
            scanf("%s", temp);
            for(int i = 0; i < number; i++){
               row = find_integer(temp);
               column = find_integer(temp);
               world[row][column] = animal;
               animals_coordinate[animals_coordinate_index][0] = row;
               animals_coordinate[animals_coordinate_index][1] = column;
               animals_coordinate_index++;
            }
         }
         else{
            MyAnimal = temp[0];
            separator_counter++;
         }
      }
   }

   while(1){
      for(int i = 0; i < animals_coordinate_index; i++){
         CreateWorldCopy(animals_coordinate[i][0], animals_coordinate[i][1]);
         num(animals_coordinate[i][0], animals_coordinate[i][1], &animals_coordinate[i][0], &animals_coordinate[i][1], 'f');
         printf("heaven is on %d %d\n", hx, hy);
         CreateWorldCopy(animals_coordinate[i][0], animals_coordinate[i][1]);
         num(hx, hy, &animals_coordinate[i][0], &animals_coordinate[i][1], 'g');
         printf("Animal went to %d %d\n", animals_coordinate[i][0], animals_coordinate[i][1]);
      }

      print();
      Sleep(5000);
      system("cls");
   }
   return 0;
}

