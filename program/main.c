#include "rkp_header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include<signal.h>

int main(int argc, char *argv[])
{
    if (strcmp(argv[0], "./chart") != 0){
        fprintf(stderr,"HIBA!\n A program neve nem megfelelő! (chart)\n");
        return EXIT_FAILURE;
    }

    int send_mode = 0; int file_mode = 0;

    int *ERTEKEK = NULL;
    int meret;

    commands(&send_mode, &file_mode, argc, argv);    //1.Feladat

    signal(SIGINT,SignalHandler); signal(SIGUSR1,SignalHandler);

    if (send_mode < 0 || file_mode < 0){ //ERROR
        return EXIT_FAILURE;
    }
        //send - file
    if (send_mode == 0 && file_mode == 0){
        meret = Measurement(&ERTEKEK);  //2.Feladat
        printf("\nTömb generálása.\n");
        SendViaFile(ERTEKEK, meret);
        printf("\nSend file\n");
        free(ERTEKEK);
        exit(0);
    }
        //send - socket
    else if (send_mode == 0 && file_mode == 1) {
        meret = Measurement(&ERTEKEK);  //2.Feladat 
        printf("\nTömb generálása.\n");
        SendViaSocket(ERTEKEK, meret);
        free(ERTEKEK);
        exit(0);
    }
        //receive - file
    else if (send_mode == 1 && file_mode == 0){
        while (1){
        /**/  //ReceiveViaFile(signal(SIGUSR1, SignalHandler));
        /**///  pause();
            signal(SIGUSR1, ReceiveViaFile); 
        }
        pause();  
    }
        //receive - socket
    else if (send_mode == 1 && file_mode == 1) {
        ReceiveViaSocket();   
    }
    
    return EXIT_SUCCESS;
}