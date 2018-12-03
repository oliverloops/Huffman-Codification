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
    /*
    for(i = 97; i <= 122; i++){
        abc[i] = i;
    }*/

    int j;
    /*
    for(j = 65; j <= 90; j++){
        ABC[j] = j;
    }*/
    //¿Cómo contar cuántas palabras tiene el archivo de texto?
    char *count = malloc(sizeof(char) * 100);
    int c = 0;

    char *text = malloc(sizeof(char) * 20);
    
    //Esta wea es para almacenar todas las cadenas del texto
    for(i = 0; i < 3; i++){
        fscanf(ptr_file, "%s", text);
        printf("%s",text);
    }

    char *saver = malloc(sizeof(char) * 100);
    fwrite(text,sizeof(char),28,ptr_bin);
    fclose(ptr_bin);

    FILE *ptr_again = fopen("tale.dat","rb");
    
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