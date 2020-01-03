#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 150
//store line information in struct
typedef struct {
  char*  city;
  double population;
  char* country;
} Class;
//finds all commas in string
void findCommas(char *strhold, int *com11, int *com12, int *com21, int *com22, int *com31, int *com32){
    
    int check = 1;
    for (int ind = 0; ind < strlen(strhold); ind++) {
        if (strhold[ind] == ',') {
            //finds a given comma and decides which comma in the line it is by incrimenting variable check
            //ind is location in the string of th comma
            
            if(check == 1){
                *com11 == 0;
                *com12 = ind;// com11 to com32 are variables that hold address values and so by changing the value at this address here, that variable can be referenced outside of this void function
                check++;
            }
            
            else if(check == 2){
            
                check++;
            }
            else if(check == 3){
                check++;
            }
            else if(check == 4){
                *com21 = ind;
                check++;

            }
            else if(check == 5){
                *com22 = ind;
                *com31 = ind;
                check++;
            }
            else if(check == 6){
                *com32 = ind;
                check++;
            }
        }
    }
    return;
}
//takes two lines and their pop values and returns them sorted based on which has the bigger pop value
int compare(const void* a, const void* b)
{
    const City *first = a, *second = b;
      return -(i->population - j->population);
}
int main() {
    FILE* fileopen = fopen("cities.csv", "r");
    int counter = 0;
    int index = 0;
    char *strhold2 = malloc(N);
    //incriments through file to determine number of lines
    do {
        fgets(strhold2, N, fileopen);
        index++;//equal to number of lines after loop
    } while (!feof(fileopen));
    
    
    fclose(fileopen);
    Class *line[index];//makes a 2D struct of type class to hold multiple entires of information, indexed through the for loop

    FILE* fileopen2 = fopen("cities.csv", "r");
    char *strhold = malloc(N);
    fgets(strhold, N, fileopen2);
    for(int i = 0; i <= index - 2; i++){
        
        fgets(strhold, N, fileopen2);
        int com11, com12, com21, com22, com31, com32;
        //passes string to findCommas to get important indexing values
        //passes address of com variables to findCommas to make passing new variable values easier
        findCommas(strhold, &com11, &com12, &com21, &com22, &com31, &com32);
        Class* cityrow = malloc(sizeof(Class));//1D array that gets rewritten each loop through as data is perminently stored in 2d line class

        char* cit = malloc(com12 - com11 + 1);
        char* pop = malloc(com22 - com21 + 1);
        char* country = malloc(com32 - com31 + 1);
        
        memcpy(cit, strhold + com11, com12 - com11);
        
        memcpy(pop, strhold + com21 + 1, com22 - com21 - 1);
        
        memcpy(country, strhold + com31 + 1, com32 - com31 - 1);
        
        cityrow->city = cit;
        cityrow->population = atof(pop);
        cityrow->country = country;
        line[i] = cityrow;
    }
    fclose(fileopen2);
    
    qsort(line, index, sizeof(Class*), check);//submits entire 2D line class to q sort to be rewritten in proper order using compair function
    FILE* fileopen3 = fopen("sorted.csv", "w");
    //write sorted line Class into sorted.csv
    for (int r = 0; r <= index - 2; r++){
        
        fprintf(fileopen3, "%s, %.20g, %s\n", line[r]->city, line[r]->population, line[r]->country);
    }
    
    fclose(fileopen3);
    
    return 0;
}
