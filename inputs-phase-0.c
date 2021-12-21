#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>

#define maxside 20

char world[maxside][maxside];
int energys[maxside][maxside] = {{0}};
int side;


int find_integer(char * );
int is_equal_str(const char * , const char * );

int main(){
   for(int i = 0; i <20; i++){      // inja hame khune ha . mishe
      for(int j = 0; j < 20; j++){
         world[i][j] = '.';
      }
   }
   char MyAnimal;
   int separator_counter = 0;
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
         world[row][col] =  'F';
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
            }

         }
         else{
            MyAnimal = temp[0];
            separator_counter++;
         }
      }
   }
   // for(int i = 0; i < side; i++){
   //    for(int j = 0; j < side; j++){
   //       printf("%c", world[i][j]);
   //    }
   //    printf("\n");
   // }
   return 0;
}

int find_integer(char * str){    // int function yek string migire va avalin addi ke dakhel string peyda kone barmigardone va  
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

int is_equal_str(const char * First_Str, const char * Second_Str){   // in function barabari do ta string ro check mikone
   for(int i = 0; First_Str[i] || Second_Str[i]; i++){
      if(First_Str[i] != Second_Str[i])return 0;
   }
   return 1;
}
