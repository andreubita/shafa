#include "ModuloT.h"

int moduloT (char *filename) {
    LISTA l = listaVazia();
    endPar arPares[CHARS];
    int numBlocos;
    // Abrir o file de input
    FILE *input = fopen (filename,"r");
    if (input == NULL) return 1;
    // Criar e abrir o file de output
    char *outName = addCodFile (filename);
    FILE *output = fopen (outName,"w");
    free (outName);
    // Ler se o File está comprimido ou não
    fgetc (input);
    input = writeNum(input,output,NULL,l);
    // Ler nº blocos
    input = writeNum(input,output,&numBlocos,l);
    // For pra ler os blocos e escrever
    for(int i = 0; i < 1; i++){
        //Tamanho do bloco
        input = writeNum(input,output,NULL,l);
        //Passar o bloco pra array onde arPares[n] = end -> (Sim,Freq) pra depois ordenar
        // g[] = [121323124,32141412] = 121323124 -> (1,2) = 32141412 -> (2,3)
        input = tilAt(input,l);
        getArPares (arPares,l);
        //Ordenar po ordem dercresente
        //Shanon fanon

        //reordenar o array array[n] = codigo shanon fanon desse numero
        //escrever no file
    }
}

FILE *writeNum(FILE *input,FILE *output,int *ret,LISTA l){
    input = tilAt(input,l);
    if(ret != NULL) *ret = getNumLL (l->lista, 0, (l->last)-1);
    writeOnFile (l,output);
    return input;
}

FILE *tilAt (FILE *file,LISTA l){
    int temp = fgetc(file);
    while (temp != 64 && temp >= EOF){
        addToLista (l,(char) (temp));
        temp = fgetc (file);
    } 
    return file;
}

char *addCodFile (char *name){
    int length = strlen (name) + 7;
    char *new = malloc(length * sizeof(char));
    strcpy (new,name);
    strcat (new,".cod");
    return new;
}

void writeOnFile (LISTA l,FILE *file){ 
    fputc('@',file);
    for(int i = 0, last = l -> last; i < last; i++) fputc (l->lista[i],file);
    l -> last = 0;
}

int getNumLL (char *lista,int fst,int lst){
    int result = 0;
    for (int i = 0;lst >= fst; i++ , lst--){ 
    result += (lista[lst] - 48) * (pow (10.0,i));
    } 
    return result;
}

//WIP
void getArPares (endPar arPares[],LISTA l){
    //int last = getNumLL();
    //setPar (arPares[0],0,0);
    for (int i = 1; i < CHARS; i++){

    }
}

/*int nextValue (char *lista,int i){
    for (;)
}*/

/*
void decresArray (int arrPares[],int N)
{
    int maior = 0;
    int ind = 0;
    for (int i=0;i<N;i++)
    {
        int maior = v[i] -> snd;
        for(int j=i+1,j<N,j++)
        {
            if ((v[j]->snd)>maior)
            maior = v[j]->snd;
            ind = j;
        }
        if (maior != (v[i]->snd))
        {
        v[ind] -> snd = v[i] -> snd;
        v[i] -> snd = maior;
        }
    }
}

int somaArray (int arrPares[],int i,int j)
{
    int soma = 0;
    for(;j>=i;i++) soma += (v[i] -> snd);
    return soma;
}

int melhorDiv (int arrPares[],int i,int j)
{
    int mtotal = (somaArray (arrPares,i,j)/2;
    int soma;
    for (int ind=i;ind<=j;ind++){
        soma=(somaArray (arrPares,i,ind);
      if(soma>mtotal)
      break;
    }
    if (((j-i)>1)&&(soma-mtotal)>(abs(somaArray (arrPares,ind,j)-mtotal)))ind=ind-1;
    return ind;
}
*/