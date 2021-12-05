#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char sorok[20][20];
int matrix[20][20];

int sor;
int oszlop;
int sorDb = 0;
int db = 0;
int darab = 0;

void fajlbeolvas(){
    
    char c[1000];
    FILE *fptr;
    fptr = fopen("be.txt","r");
    if (!(fptr = fopen("be.txt", "r"))) { 
            return;
    }
    while(EOF != fscanf(fptr, "%s", c)){
        if(db == 0){
            sor = c[0] -'0';
            oszlop = c[2] - '0';
        } else {
            if(strcmp(c, "-") == 0){
                break;
            }else{
                strcpy(sorok[sorDb], c);
                sorDb++;
            }
        }
        db++;
    }
    fclose(fptr);
}

void tombfeltoltes(){
    for (int i = 0; i < 20; i++){
      for (int j = 0; j < 20; j++){
          matrix[i][j] = -1;
      }
    }
    char delim[] = ",";
    for (int i = 0; i < sorDb; i++){
        char *ptr = strtok(sorok[i], delim);
        int db = 0;
        while(ptr != NULL){
           matrix[i][db] = atoi(ptr);
           ptr = strtok(NULL, delim);
           db++;
           darab++;
       }  
    } 
}


void kiir(){
    int vege=0;
    FILE *outfile;   
    outfile = fopen("ki.txt", "w"); 
    
    if (!(outfile = fopen("ki.txt", "w"))) {
            fclose(outfile);
            return;
    } 
    int i, j;
    i = sor - 1;
    j = oszlop - 1;
    int irany = 0; //0 fel 1 jobra 2 le 3 balra
    int kovetkezo = 2;
    while(darab > vege){
        for (int ketto = 0; ketto < 2; ++ketto){
            for (int kulso = 1; kulso < kovetkezo; ++kulso){
                    if(j < 0 || i < 0 || j > 20 || i > 20){
                    }else if (matrix[i][j] != -1){
                        ++vege;
                        if(vege==darab){
                            fprintf(outfile,"%lc", matrix[i][j]+'0');
                        }else{
                            fprintf(outfile,"%lc,", matrix[i][j]+'0');
                        }
                    } 
                    if(irany == 0){
                        ++j;
                    }else if(irany == 1){
                        --i;
                    }else if(irany == 2){
                        --j;
                    }else if(irany == 3){
                        ++i;
                    } 
                }
                if(irany == 0){
                     irany=1;
                }else if(irany == 1){
                    irany=2;
                }else if(irany == 2){
                    irany=3;
                }else if(irany == 3){
                    irany=0;
                }
            }
            ++kovetkezo;
        }       
    fprintf(outfile,"\n");
    fclose(outfile);                 
}

int main() {
    fajlbeolvas();
    tombfeltoltes();
    kiir();
    return 0;
}
