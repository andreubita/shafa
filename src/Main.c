/**
 * @file Shafa
 * @brief Shafa tool for data compression
 * @version 0.1
 * @date 2020-12-19
 * 
 * @copyright Copyright (c) 2020
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moduloD/manual.h"
//#include "moduloT/ModuloT.h"
#include "moduloC/ModuloC.h"
#include "moduloF/moduloF.h"
#include "moduloD/moduloD.h"


int main(int argc, char **argv){
    if (argc == 2 && (!strcmp("--help", argv[1]) || !strcmp("-h", argv[1]))) {
        help_menu();
        return EXIT_SUCCESS;
    }

    if (argc >= 3 && !strcmp("-m", argv[2])){
        // Modulo F
        if(argc == 4  && !strcmp("f", argv[3])){
        unsigned long block_size= 65536;
        int forcecompression = 0;
        moduloF(argc, argv, block_size, forcecompression);
    }

      
        // Modulo T
        if(argc == 4  && !strcmp("t", argv[3])){
        }


        // Modulo C
        if((argc == 4 || argc == 5) && !strcmp("c", argv[3])){
            return moduloC(argc, argv);
        }
        // Moduloc D
        if((argc == 4 && !strcmp("d", argv[3])) || (argc == 5 && !strcmp ("-d",argv[3]))){
            return moduloD(argc,argv);
        }
    }
    else error_messages(1,"");
    return EXIT_FAILURE;
}
