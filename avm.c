#include <stdio.h>
#include <stdlib.h>

#include "avm.h"

int main(int argc,char** argv){
    FILE *f=fopen("binFile.abc","rb");
    readAll(f);

    while(executionFinished==0){
        execute_cycle();
    }
    fclose(f);
}