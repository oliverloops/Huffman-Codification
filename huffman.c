#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void scanner(char *string,  char *abc, char *ABC);
void order(char *string);

int main()
{

    FILE *ptr_file = fopen("./tale.txt","r");
    FILE *ptr_bin = fopen("tale.dat","wb");
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
    while(i < 10){
        fscanf(ptr_file, "%s", text);
        printf("%c",text[i]);
        i++;
    }
    scanner(text, abc, ABC);
    order(text);

    free(text);
    free(abc);
    free(ABC);
    fclose(ptr_file);
    fclose(ptr_bin);

    return 0;
}

void order(char *string)
{
    int a;
    for(a = 0; a < 10; a++){
        if((int)string[a] < (int)string[a + 1]){
            string[a] = string[a + 1];
        }
    }
    for(int b; b < 10; b++){
        printf("%c",string[b]);
    }
}

void scanner(char *string, char *abc, char *ABC){

    int k, n = 0, size = strlen(string);
    
    /*for(k = 0; k < size; k++){
        if(string[k] == ' '){
            string[k] = '-';
        }
        printf("%c", string[k]);
    }*/

        printf("\n");
    }