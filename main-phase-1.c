#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>

#define maxside 20

char world[maxside][maxside];
int energys[maxside][maxside] = {{0}};

int find_integer(char * );
int is_equal_str(const char * , const char * );

int main(){
   for(int i = 0; i <20; i++){
      for(int j = 0; j < 20; j++){
         world[i][j] = '.';
      }
   }
   char MyAnimal;
   int side;
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
         world[row][col] =  'F';
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

      else if(is_equal_str(temp, "==="));

      else{
         int number, row, col;
         if(fscanf(inputs, "%d", &number) == EOF){
            MyAnimal = temp[0];
         }
         else{
            char Animal = temp[0];
            fscanf(inputs, "%s", temp);
            for(int i = 0; i < number; i++){
               row = find_integer(temp);
               col = find_integer(temp);
               world[row][col] = Animal;
            }
         }
      }

   }
   fclose(inputs);
   // for(int i = 0; i < side; i++){
   //    for(int j = 0; j < side; j++){
   //       printf("%c", world[i][j]);
   //    }
   //    printf("\n");
   // }
   // printf("\n");
   // for(int i = 0; i < side; i++){
   //    for(int j = 0; j < side; j++){
   //       printf("%d  ", energys[i][j]);
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