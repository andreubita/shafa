/**
@file ModuloT.h
Main do ModuloT
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define CHARS 256

// TODO Comment the code for documentation
int moduloT (char *filename);
FILE *tilAt (FILE *file,LISTA l);
char *addCodFile(char *name);
void writeOnFile (LISTA l,FILE *file);
int getNumLL (char *lista,int fst,int lst);
FILE *writeNum(FILE *input,FILE *output,int *ret,LISTA l);
void getArPares (endPar arPares[],LISTA l);
int entrePV (LISTA l, int start, int *num);
int decresArray (endPar arPares[]);
int somaArray (endPar arrPares[],int i,int j);
int melhorDiv (endPar arrPares[],int i,int j);
void addBit (endPar SF [],int i,int j,int b);
void calcularSF (endPar arrPares[],endPar SF[],int i, int j);
FILE *printArParFile (endPar SF[],FILE *output);
void numToString (int num,char *string);
int sizeNum (int num);