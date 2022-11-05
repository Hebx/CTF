#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hamming_calc.c"

int main(int argc,char** argv){
    
    if(argc<2){
        puts("[-]Usage: hamming <file>");
        return 0;
    }
    
    char datain[15],*dataout;
    
    FILE *fin,*fout;
    struct stat st;
    
    fin=fopen(argv[1],"r");
    
    if(fin==NULL){
        printf("[-]This file \"%s\" doesn't exist\n",argv[1]);
        exit(EXIT_FAILURE);
    }
    stat(argv[1],&st);//st.st_size contain the size of the file
    
    fout=fopen("hamming.out","w");

    for(int j=0;j<st.st_size/15;j++){

        for(int k=0;k<15;k++) datain[k]=fgetc(fin);//reading a block of data from the input
        dataout=hamm_dec_15_11(datain);//decoding them 
        for(int i=0;i<11;i++) fputc(dataout[i],fout);//writing the output block
        free(dataout);

    }
    fclose(fout);
    fclose(fin);
    
    return 0;
}
