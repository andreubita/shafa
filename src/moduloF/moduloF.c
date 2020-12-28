#include "moduloF.h"

char *dotfreq(char *filename){
    int length = strlen(filename) *2;
    char *newfilename = malloc(length* sizeof(char));
    strcpy (newfilename, filename);
    strcat (newfilename, ".freq");
return newfilename;
}

char *dotrle(char *filename){
    int length = strlen(filename) *2;
    char *newfilename = malloc(length* sizeof(char));
    strcpy (newfilename, filename);
    strcat (newfilename, ".rle");
return newfilename;
}

void createfreqfile(long long n_blocks, char *filename, int flagoriginal){
    FILE *fp;
    fp = fopen (filename, "wb");
    if (flagoriginal) fprintf(fp, "@N@%lld@", n_blocks);
    else fprintf (fp, "@R@%lld@", n_blocks);
    fclose(fp);
}

void createrlefile(char *filename){
    FILE *fp;
    fp = fopen (filename, "wb");
    fclose(fp);
}

void freqs(unsigned char *buffer, int sizebuffer, long long n_blocks, int flaginit, int onlyoneblock, char *filename, int flagoriginal){
    FILE *orifreqs;
    if (flaginit) createfreqfile(n_blocks, filename, flagoriginal);
    orifreqs = fopen (filename, "ab");  
    fprintf(orifreqs, "%d@", sizebuffer);
    int i, j, counter=0, counterant;
    for (j=0; j<256; j++){
        for (i=0; i<sizebuffer; i++){
            if (*(buffer+i) == j) counter++;
        }
    if (j==0){
       counterant = counter;
       fprintf(orifreqs, "%d;",counter);
    }
    else if (counterant==counter){
        if(j!=255) fprintf(orifreqs, ";");
        counterant=counter;
    }
    else{ 
        fprintf(orifreqs, "%d", counter);
        if(j!=255) fprintf(orifreqs, ";");
        counterant=counter;
    }
    counter=0;
    }
    fprintf(orifreqs, "@");
    if(!flaginit || onlyoneblock) fprintf(orifreqs, "0");
    fclose(orifreqs);
}

int simbcount(char *buffer, int sizebuffer){
    int i, counter=1, simbs=0;
    for (i = 0; i<sizebuffer; i++)
    {
        while (*((buffer)+i) == *((buffer)+i+1))
        {
            counter++;
            i++;
        }
        if (counter >= 3)  simbs+=3;
        else simbs += counter;
        counter=1;
}
return simbs;
}

int rlecheck(char *buffer, int sizebuffer){
    int ret = 0, simbs;
    float taxacomp;
    simbs = simbcount (buffer, sizebuffer);
    taxacomp =  (sizebuffer-simbs);
    taxacomp /= sizebuffer;
    if (taxacomp > 0.05) ret = 1;
return ret;
}

unsigned char *rlebuffertransformation(unsigned char *buffer, int sizebuffer){
    int i, j=0, counter = 1;
    unsigned char *rlebuffer = malloc (sizebuffer* sizeof(unsigned char));
    unsigned char c, zero=0;
    for (i = 0; i < sizebuffer; i++)
    {
        c= *((buffer)+i);
        while (*((buffer)+i) == *((buffer)+i+1))
        {
            counter++;
            i++;
        }
        if (counter >3){ 
                unsigned char cont = counter;
                *(rlebuffer + j)=zero;
                *(rlebuffer + j+1)=c;
                *(rlebuffer + j+2)=cont;
                j+=3;            
        }
        else if (counter == 3){ 
            *(rlebuffer + j)=c;
            *(rlebuffer + j+1)=c;
            *(rlebuffer + j+2)=c;
            j+=3;
        }
        else if (counter == 2) {
            *(rlebuffer + j)=c;
            *(rlebuffer + j+1)=c;
            j+=2;
        }
        else{
            *(rlebuffer + j)=c;
            j++;
        }
        counter=1;
    }
return rlebuffer;
}

void rlecompressing(char *buffer , int flaginit, int sizebuffer, int simbs, char *filename){
    FILE *rle;
    if (flaginit) createrlefile(filename);
    rle = fopen (filename, "ab"); 
    int i, counter=1;
    unsigned char c, zero=0;
    for (int z = 0; z < sizebuffer; z++)
        {
            fprintf (rle,"%c", *(buffer+z));
        }
fclose (rle);
}

float split (char *filename, unsigned long block_size) {
    unsigned long long total;
    long long n_blocks;
    unsigned long size_of_last_block;
    int bytesRead, flaginit=1, simbs=0; 
    float taxacomp; 
    char *filenamefreq = dotfreq(filename), *filenamerle = dotrle(filename), *filenamerlefreq = dotfreq(filenamerle);
    FILE *exsistingFile;
    exsistingFile = fopen(filename,"rb"); 
    int i = 1, flag = 1, onlyoneblock, flagrle;
    n_blocks = fsize(exsistingFile, NULL, &block_size, &size_of_last_block);
    total = (n_blocks-1) * block_size + size_of_last_block;
    if (n_blocks==1) onlyoneblock = 1;
    else onlyoneblock = 0;
    do
    {   
        int workSize = total;
        while (workSize)
        {
            int chunkSize = workSize > block_size ? block_size : workSize;
            unsigned char * buffer = (unsigned char *)malloc(chunkSize);
            bytesRead = fread( buffer, sizeof( unsigned char ), chunkSize, exsistingFile );
            workSize -= bytesRead;
            if (bytesRead == 0)
            {
                printf("The reading has finished or the file has no data inside\n");
                return 0;
            } 
            if (flaginit && rlecheck(buffer, chunkSize)){
               unsigned char *rlebuff = rlebuffertransformation(buffer, chunkSize);
               int rlesimbs = simbcount(buffer, chunkSize);
               simbs += simbcount(buffer, chunkSize);
               rlecompressing(rlebuff, flaginit, rlesimbs, simbs, filenamerle);
               freqs(rlebuff, rlesimbs, n_blocks, flaginit, onlyoneblock, filenamerlefreq, 0);
               flagrle = 1;
            }
            else if (flagrle){
                unsigned char *rlebuff = rlebuffertransformation(buffer, chunkSize);
                int rlesimbs = simbcount(buffer, chunkSize);
                simbs += simbcount(buffer, chunkSize);
                rlecompressing (rlebuff, flaginit, rlesimbs, simbs, filenamerle);
                freqs(rlebuff, rlesimbs, n_blocks, flaginit, onlyoneblock, filenamerlefreq, 0);
            }
            freqs(buffer, chunkSize, n_blocks, flaginit, onlyoneblock, filenamefreq, 1);
            flaginit = 0;
        }
        flag = 0;
} while ( bytesRead > 0 && flag);

taxacomp =  (total-simbs);
taxacomp /= total;

fclose(exsistingFile);
return taxacomp;
}

long long number_of_blocks (char *filename, unsigned long block_size){
    FILE *fp;
    fp = fopen (filename, "rb");
    unsigned long size_of_last_block;
    long long n_blocks = fsize(fp, NULL, &block_size, &size_of_last_block);
    fclose (fp);
return n_blocks;
}

int main(){
   clock_t start_time = clock();
   time_t now;
   time(&now);
   struct tm *data = localtime(&now);
   int day, month, year;
   day = data->tm_mday;            
   month = data->tm_mon + 1;       
   year = data->tm_year + 1900;;
   unsigned long block_size=64000;
  
   char *filename = "aaa.txt";

   long long n_blocks = number_of_blocks(filename, block_size);
   float taxacomp;

   taxacomp = split (filename, block_size)*100;

   clock_t stop_time = clock();
   double elapsed = (double)(stop_time-start_time)/CLOCKS_PER_SEC*1000;
   time_t t = time(NULL);

   printf ("Daniela Carvalho (a93224) e Eduardo Magalhães (a93301), MIEI-CD, %02d/%02d/%d\n", day, month, year);
   printf ("Módulo: f (cálculo das frequências dos símbolos)\n");
   printf ("Número de blocos: %lld\n", n_blocks); // preencher com return da funcao que divide em blocos
   printf ("Tamanho dos blocos analisados no ficheiro original: \n"); // ex = 65536/ 2013 bytes
   printf ("Compressão RLE : %f%c de compressão\n", taxacomp, '%'); // ex = aaaaaa.txt.rle (13% de compressão)
   printf ("Tamanho dos blocos analisados no ficheiro RLE: \n"); // ex = 57444/ 1620 bytes
   printf ("Tempo de execução do módulo (milissegundos) : %fms\n", elapsed);
   printf ("Ficheiros gerados: \n"); // ex = aaaaaa.txt.freq, aaaaaa.txt.rle.freq 

   return 0;
}