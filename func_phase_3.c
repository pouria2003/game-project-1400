int a,b,f=0,r,c,attacker,attackerR,attackerC,attacker_index,attacker_wins,defender_index,defenderR,defenderC;
char winner;  //a,d
void fight(){
if(random(0,1)==0) return();
for(a=-1;a<=1;a++){
    for(b=-1;b<=1;b++){
        if(word[program_animals[i].row][program_animals[i].column]!=world[program_animals[i].row+a][program_animals[i].column+b]) {
            r=program_animals[i].row+a;
            c=program_animals[i].column+b;
            attacker=random(1,2);
            if(attacker==1){
                attackerR=program_animals[i].row;
                attackerC=program_animals[i].column;
                attacker_index=i;
                defender_index=isAnyAnimal(attackerR,attackerC,'p');
                defenderR=program_animals[i].row+a;
                defenderC=program_animals[i].column+b;
            }
            else{
                attackerR=program_animals[i].row+a;
                attackerC=program_animals[i].column+b;
                attacker_index=isAnyAnimal(attackerR,attackerC,'p');
                defender_index=i;
                defenderR=program_animals[i].row;
                defenderC=program_animals[i].column;
            }
        }
    }
} 
program_animals[attacker_index].energy=program_animals[attacker_index].energy-(program_animals[attacker_index].single_move_energy*3)
if(program_animals[attacker_index].energy>program_animals[defender_index].energy) winner='a';
else winner='d';
if(winner=='d') world[attackerR][attackerC]='.';
else world[defenderR][defenderC]='.';
//lose() baraye heyvuni ke mord
}
int giveEnergy(){
if(random(0,1)==0) return(0);
x=program_animals[i].row;
y=program_animals[i].column;
    for(a=-1;a<=1;a++){
        for(b=-1;b<=1;b++){
            if(word[x][y]==world[x+a][y+b]){
                index=isAnyAnimal(x+a,y+b,'p');
                program_animals[index].energy=program_animals[index].energy+program_animals[i].single_move_energy;
                return(1);
            }
             
        }
    }
    return(0);
}
//tuye main:if(giveEnergy==0) move()

######################################################################################################################

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
void reproduction(char mode){ 
int i,j,r,c,sw=0,a,b,index,xR,yR; //sw byad avale tabe sefr beshe
char kind;
if(random(0,1)==0)  return();
if(mode=='u'){
if(user_animals[i].energy<user_animals[i].reproduction_energy) return();
int x=user_animals[i].animal_coordinate.row;
int y=user_animals[i].animal_coordinate.column;
kind=world[x][y];
for(a=-1;a<=1;a++){
   for(b=-1;b<=1;b++){                       
      if(user_animals[i]==world[x+a][y+b]){
          index=isAnyAnimal(x+a,y+b,'u');
          if(index==-1)return(); //in niaz nist bashe  
          else if(user_animals[index].energy>=user_animals[index].reproduction_energy) sw=1;
          break;
      }
   }
}
if(sw==1){
user_animals[i].animal_energy=user_animals[i].animal_energy-user_animals[i].reproduction_energy/2;
user_animals[index].animal_energy=user_animals[index].animal_energy-user_animals[index].reproduction_energy/2;
user_animals[user_animals_index].energy=findPrimaryInfo(kind,'e');
user_animals[user_animals_index].single_move_energy=random(20,200);
user_animals[user_animals_index].movment_number=random(1,3);
user_animals[user_animals_index].reproduction_energy=random(60,600);
user_animals[user_animals_index].attack_energy=random(20,500);
user_animals[user_animals_index].defense_energy=random(20,500);
do{
int k=1; 
do{
xR=random(-k,k);  
yR=random(-k,k); 
}while(xR!=-k||yR!=k||xR!=k||yR!=-k);
r=x+xR;
c=y+yR;
k++;
}while(world[r][c]!='.');
user_animals[user_animals_index].coordinate.row=r;
user_animals[user_animals_index].coordinate.column=c;
user_animal_index++;
world[r][c]=kind;
}
}
else{ 
if(program_animals[i].energy<program_animals[i].reproduction_energy) return();
int x=program_animals[i].animal_coordinate.row;
int y=program_animals[i].animal_coordinate.column;
kind=world[x][y];
for(a=-1;a<=1;a++){
   for(b=-1;b<=1;b++){
        if(program_animals[i]==world[x+a][y+b]){
            index=isAnyAnimal(x+a,y+b,'p');
            if(index==-1)return(); //in niaz nist bashe  
            else if(program_animals[index].energy>=program_animals[index].reproduction_energy) sw=1;
            break;
      }
   }
}
if(sw==1){
program_animal[i].animal_energy=program_animal[i].animal_energy-program_animal[i].reproduction_energy/2;
program_animals[index].animal_energy=program_animals[index].animal_energy-program_animals[index].reproduction_energy/2;
program_animals[program_animals_index].energy=findPrimaryInfo(kind,'e');
program_animals[program_animals_index].single_move_energy=random(20,200);
program_animals[program_animals_index].movment_number=random(1,3);
program_animals[program_animals_index].reproduction_energy=random(60,600);
program_animals[program_animals_index].attack_energy=random(20,500);
program_animals[program_animals_index].defense_energy=random(20,500);
do{
int k=1; 
do{
xR=random(-k,k);  
yR=random(-k,k); 
}while(xR!=-k||yR!=k||xR!=k||yR!=-k);
r=x+xR;
c=y+yR;
k++;
}while(world[r][c]!='.');
program_animals[program_animals_index].coordinate.row=r;
program_animals[program_animals_index].coordinate.column=c;
program_animals_index++;
world[r][c]=kind;
}
}
}
//tuye main baad az harkate har heyvun
