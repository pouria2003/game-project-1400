#include "functions_phase_2.c"
int primary_info[20][3];
int a,b,f=0,r,c,attacker,attackerR,attackerC,attacker_index,attacker_wins,defender_index,defenderR,defenderC;
char winner;  //a,d
void fight(int animal_index){
    if(random(0, 1) == 0) return;
    for(a = -1; a <= 1; a++){
        for(b = -1; b <= 1; b++){
            if(world[program_animals[animal_index].animal_coordinate.row][program_animals[animal_index].animal_coordinate.column] != world[program_animals[animal_index].animal_coordinate.row + a][program_animals[animal_index].animal_coordinate.column + b]) {
                r = program_animals[animal_index].animal_coordinate.row + a;
                c = program_animals[animal_index].animal_coordinate.column + b;
                attacker = random(1,2);
                if(attacker==1){
                    attackerR=program_animals[animal_index].animal_coordinate.row;
                    attackerC=program_animals[animal_index].animal_coordinate.column;
                    attacker_index=animal_index;
                    defender_index=isAnyAnimal(attackerR,attackerC,'p');
                    defenderR=program_animals[animal_index].animal_coordinate.row+a;
                    defenderC=program_animals[animal_index].animal_coordinate.column+b;
                }
                else{
                    attackerR=program_animals[animal_index].animal_coordinate.row+a;
                    attackerC=program_animals[animal_index].animal_coordinate.column+b;
                    attacker_index=isAnyAnimal(attackerR,attackerC,'p');
                    defender_index=animal_index;
                    defenderR=program_animals[animal_index].animal_coordinate.row;
                    defenderC=program_animals[animal_index].animal_coordinate.column;
                }
            }
        }
    }
    program_animals[attacker_index].animal_energy=program_animals[attacker_index].animal_energy-(program_animals[attacker_index].single_move_energy*3);
    if(program_animals[attacker_index].animal_energy>program_animals[defender_index].animal_energy) winner='a';
    else winner='d';
    if(winner=='d') world[attackerR][attackerC]='.';
    else world[defenderR][defenderC]='.';
    //lose() baraye heyvuni ke mord
}
int giveEnergy(int i){
    int index = 0;
    if(random(0,1)==0) return(0);
    int x=program_animals[i].animal_coordinate.row;
    int y=program_animals[i].animal_coordinate.column;
        for(a=-1;a<=1;a++){
            for(b=-1;b<=1;b++){
                if(world[x][y]==world[x+a][y+b]){
                    index=isAnyAnimal(x+a,y+b,'p');
                    program_animals[index].animal_energy=program_animals[index].animal_energy+program_animals[i].single_move_energy;
                    return(1);
                }

            }
        }
    return(0);
}
//tuye main:if(giveEnergy==0) move()

//######################################################################################################################

int isAnyAnimal(int c, int r,char mode){
    int i;
    if(mode=='p'){
        for(i=0 ; i< program_animals_index ; i++){
            if(c==program_animals[i].animal_coordinate.row && r==program_animals[i].animal_coordinate.column)
                return(i);
        }
    }
    else{
        for(i=0 ; i< program_animals_index ; i++){
            if(c==user_animals[i].animal_coordinate.row && r==user_animals[i].animal_coordinate.column)
                return(i);
        }
    }
    return(-1);
}

int findPrimaryInfo(int kind,char mode){
    int i;
    if(mode=='e'){
        for(i=0; ;i++){
            if(primary_info[i][0]==kind) return(primary_info[i][2]);
        }
    }
    else{
        for(i=0; ;i++){
            if(primary_info[i][0]==kind) return(primary_info[i][1]);
        }
    }
    return(-1);
}

void reproduction(struct Animal * animal_arr, int *animal_arr_index, int animal_index){
    int j,r,c,sw=0,a,b,index,xR,yR; //sw byad avale tabe sefr beshe
    char kind;
    if(random(0, 1) == 0)  return;
    if(animal_arr[animal_index].animal_energy < animal_arr[animal_index].reproduction_energy) return;
    int x = animal_arr[animal_index].animal_coordinate.row;
    int y = animal_arr[animal_index].animal_coordinate.column;
    kind = world[x][y];
    for(a = -1; a <= 1; a++){
       for(b = -1; b <= 1; b++){
            if(a == 0 && b == 0)
                continue;
            if(kind == world[x+a][y+b]){           //// user_animals[i] == world[][] ?
                index = isAnyAnimal(x + a, y + b, 'u');
                if(index==-1)
                    index = isAnyAnimal(x + a, y + b, 'p');
                else if(animal_arr[index].animal_energy >= animal_arr[index].reproduction_energy) sw = 1;
                break;
            }
        }
        if(sw)        //// har do halghe break beshe
            break;
    }
    if(sw == 1){
        animal_arr[animal_index].animal_energy -= animal_arr[animal_index].reproduction_energy / 2;
        animal_arr[index].animal_energy -= animal_arr[index].reproduction_energy / 2;
        animal_arr[*animal_arr_index].animal_energy = findPrimaryInfo(kind,'e');
        animal_arr[*animal_arr_index].single_move_energy = random(20,200);
        animal_arr[*animal_arr_index].movement_number = random(1,3);
        animal_arr[*animal_arr_index].reproduction_energy = random(60,600);
        animal_arr[*animal_arr_index].attack_energy = random(20,500);
        animal_arr[*animal_arr_index].defense_energy = random(20,500);
        int k = 0;
        while(++k){
            for(int i = -k; i <= k; i++){
                for(int j = -k; j <= k; j++){
                    if(world[r + i][c + j] == '.'){
                        animal_arr[*animal_arr_index].animal_coordinate.row=r;
                        animal_arr[*animal_arr_index].animal_coordinate.column=c;
                        *animal_arr_index++;
                        world[r ][c]=kind;
                        return;
                    }
                }
            }
        }
        // do{
        //     int k=1;
        //     do{
        //         xR=random(-k,k);
        //         yR=random(-k,k);
        //     }while(xR != 0 && yR != 0);
        //     r = x + xR;
        //     c = y +yR;
        //     k++;
        // }while(world[r][c]!='.');
        // animal_arr[*animal_arr_index].animal_coordinate.row=r;
        // animal_arr[*animal_arr_index].animal_coordinate.column=c;
        // *animal_arr_index++;
        // world[r][c]=kind;
    }
}
//tuye main baad az harkate har heyvun

void print_info(char mode){
if(mode=='f'){
  printf("Foods:\n");
  for(int i=0 ; i<foods_array_index ; i++)
  printf("F(%d,%d):energy=%d\n", foods_array[i].food_coordinate.row+1,foods_array[i].food_coordinate.column+1,foods_array[i].food_energy);
  }
  else{
    int i=0;
    printf("Your animals:\n");
    do{
    char user=world[user_animals[i].animal_coordinate.row][user_animals[i].animal_coordinate.column];
    }while(user_animals[i].animal_coordinate.row==-1);
    for( i=0 ; i<user_animals_index ; i++)
    if(user_animals[i].animal_coordinate.row!=-1)
    printf("%c(%d,%d):energy=%d\n",user,user_animals[i].animal_coordinate.row,user_animals[i].animal_coordinate.column,user_animals[i].animal_energy);
  }
}

void LogGame(FILE * gamelog, char mode, int round_number, char animal, int animal_number, int array_index, char whos_animal,char animal2)  // mode s ==> start a new round   and   mode f ==> fill from section
{                                                                                                                                          // and  mode a ==>  fill to section  and  mode k fill kind section
    if(mode == 's')                                                                                                                        // mode  w  ==> win mode r==> reproduction  g==>give energy mode b==> battle
        fprintf(gamelog, "%s%d%s", "__Round", round_number, "__\n");             
    else if(mode == 'k')
        fprintf(gamelog, "%s %c %s %d %s","Kind", animal, "has", animal_number, "animal(s), look at how their coordinate changed in this round:\n");
    else if(mode == 'w')
        fprintf(gamelog, "%s%d%c%d%s %c %s"," to (", round_number, ',', animal_number,")\nand in this movement type", animal, "won!");
    else if(mode=='r')
        fprintf(gamelog,"Reproduction of type %c", animal);
    else if(mode=='g')
        fprintf(gamelog,"An animal of type %c gave its energy to another animal of its kind");
    else if (mode=='b')
    fprintf(gamelog,"Two animals of types %c & %c fought and type %c won",animal,animal2,animal2);
    else{
        if(whos_animal == 'p'){
            if(mode == 'f'){
                fprintf(gamelog, "%s%d%c%d%c", "From (", program_animals[array_index].animal_coordinate.row, ',', program_animals[array_index].column, ')');
            }
            else {
                fprintf(gamelog, "%s%d%c%d%s", " to (", program_animals[array_index].row, ',', program_animals[array_index].column, ")\n");
            }
        }
        else{
            if(mode == 'f'){
                fprintf(gamelog, "%s%d%c%d%c", "From (", user_animals[array_index].row, ',', user_animals[array_index].column, ')');
            }
            else {
                fprintf(gamelog, "%s%d%c%d%s", " to (", user_animals[array_index].row, ',', user_animals[array_index].column, ")\n");
            }
        }
    }
}


void beepNtimes(int n){
    for(int i=0 ; i<n ; i++){
        Beep(600,900);
    }
}


/*
int warning(char move){
x=user_animals[i].animal_coordinate.row;
y=user_animals[i].animal_coordinate.column;   
if(move=='5'||(move=='1' &&(x+1>=side||y-1<0))||(move=='2'&& x+1>=side)||(move=='3'&&(x+1>=side||y+1>=side))||(move=='4'&&y-1<0)||(move=='6'&&y+1>=side)|| (move=='7'&&(x-1<0 || y-1<0))||if(move=='8'&& x-1<0)||(move=='9'&&(x-1<0||y+1>=side))){
beepNtimes(4);
printf("you can't choose this move, choose again:");
return(0);
}
else return(1);
}   
*/

Animal* FightOrNo(Animal *animal)
{
    Animal *animal_arr = NULL;
	for(int drow = -1; drow <= 1; drow++){
		for(int dcol = -1; dcol <= 1; dcol++){
			if(world[animal->animal_coordinate.row][animal->animal_coordinate.column] != world[animal->animal_coordinate.row + drow][animal->animal_coordinate.column + dcol]){
				int index_of_defender = isAnyAnimal(animal->animal_coordinate.row + drow, animal->animal_coordinate.column + dcol, 'p');
                animal_arr = program_animals;
				if(index_of_defender == -1){
					index_of_defender = isAnyAnimal(animal->animal_coordinate.row + drow, animal->animal_coordinate.column + dcol, 'u');
                    animal_arr = user_animals;
				}
				if((animal->attack_energy > animal_arr[index_of_defender].defense_energy) && (animal_arr[index_of_defender].animal_energy > 3 * animal->single_move_energy))
                    return (&animal_arr[index_of_defender]);
            }
        }
    }
    return NULL;
}