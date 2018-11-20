#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void scanner(char *string,  char *abc, char *ABC);

int main(){

    FILE *ptr_file = fopen("./tale.txt","r");
    char *abc = (char *)malloc(sizeof(char) * 25);
    char *ABC = (char *)malloc(sizeof(char) * 25);

    //Alphabet Generators...
    int i;
    for(i = 97; i <= 122; i++){
        abc[i] = i;
    }

    int j;
    for(j = 65; j <= 90; j++){
        ABC[j] = j;
    }

    char *text = malloc(sizeof(char) * 256);

    i = 0;
    do{
        fscanf(ptr_file, "%s", text);
        printf("%c", text[i]);
        i++;
    }while(i <= 58);

    scanner(text, abc, ABC);

    free(text);
    free(abc);
    free(ABC);
    fclose(ptr_file);

    return 0;
}

void scanner(char *string, char *abc, char *ABC){

    int k, n = 0, size = strlen(string);
    
    for(k = 0; k < size; k++){
        if(string[k] == ' '){
            string[k] = '-';
        }
        printf("%c", string[k]);
    }

        printf("\n");
    }