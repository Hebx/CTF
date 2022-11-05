char* hamm_dec_15_11(char* datain){
    
    /* One block 
        
        k1 : b0 b0 b0 b0 b0 b0 b0 b0         (keybyte)
        k2 : b1 b1 b1 b1 b1 b1 b1 b1         (keybyte)
        m1 : b2 b2 b2 b2 b2 b2 b2 b2         (databyte)
        k3 : b3 b3 b3 b3 b3 b3 b3 b3         (keybyte)
        m2 : b4 b4 b4 b4 b4 b4 b4 b4         (databyte)
        m3 : b5 b5 b5 b5 b5 b5 b5 b5         (databyte)
        m4 : b6 b6 b6 b6 b6 b6 b6 b6         (databyte)
        k4 : b7 b7 b7 b7 b7 b7 b7 b7         (keybyte)
        m5 : b8 b8 b8 b8 b8 b8 b8 b8         (databyte)
        m6 : b9 b9 b9 b9 b9 b9 b9 b9         (databyte)
        m7 : b10 b10 b10 b10 b10 b10 b10 b10 (databyte)
        m8 : b11 b11 b11 b11 b11 b11 b11 b11 (databyte)
        m9 : b12 b12 b12 b12 b12 b12 b12 b12 (databyte)
        m10: b13 b13 b13 b13 b13 b13 b13 b13 (databyte)
        m11: b14 b14 b14 b14 b14 b14 b14 b14 (databyte)
        
        */
    
    
    
    
    int k,k1,k2,k3,k4;
    char bits[120],data_bits[88];
    int filter;
    
    char* dataout;
    if((dataout=malloc(11*sizeof(char)))==NULL){
        puts("[-]Probleme while allocating memory");
        exit(EXIT_FAILURE);
    }
    
    filter=128;
    
    for(int i=0;i<8;i++){//extracting 15bits per tour (bit number i of each byte)
        for(int j=0;j<15;j++) bits[i*15+j]=((datain[j]&filter)==0)?0:1;
        filter/=2;
    }
    
    
    for(int i=0;i<8;i++){// checking mistake
        do{
            k1=bits[i*15]^bits[i*15+2]^bits[i*15+4]^bits[i*15+6]^bits[i*15+8]^bits[i*15+10]^bits[i*15+12]^bits[i*15+14];
            k2=bits[i*15+1]^bits[i*15+2]^bits[i*15+5]^bits[i*15+6]^bits[i*15+9]^bits[i*15+10]^bits[i*15+13]^bits[i*15+14];
            k3=bits[i*15+3]^bits[i*15+4]^bits[i*15+5]^bits[i*15+6]^bits[i*15+11]^bits[i*15+12]^bits[i*15+13]^bits[i*15+14];
            k4=bits[i*15+7]^bits[i*15+8]^bits[i*15+9]^bits[i*15+10]^bits[i*15+11]^bits[i*15+12]^bits[i*15+13]^bits[i*15+14];
            k=k1+2*k2+4*k3+8*k4;
            
            if(k!=0) bits[i*15+k-1]=bits[i*15+k-1]^1;
            
        }while(k!=0);
    }
    
    filter=0;
    for(int i=0;i<8;i++){//extracting only data_bits
        for(int j=0;j<15;j++){
            if(j>1&&j!=3&&j!=7){
                data_bits[filter]=bits[i*15+j];
                filter++;
            }
        }
    }
    
    for(int i=0;i<11;i++) dataout[i]=0;
    
    filter=128;
    
    for(int i=0;i<11;i++){// writting dataout
        for(int j=0;j<8;j++){
            dataout[i]|=data_bits[j*11+i]*filter;
            filter/=2;
        }
    filter=128;
    }
    
    return dataout;
}
