#include "rkp_header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <dirent.h>
#include<signal.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

//--1. feladat
/*
Hozd létre a C program fő programegységét, amely a parancssori argumentumokat is képes kezelni!
Ha a ”--version” parancssori argumentummal indítjuk el a programot, akkor írja ki a program
verziószámát, elkészültének dátumát és a fejlesztő nevét (esetleg tetszőleges további információkat,
mindegyiket külön sorba)! Ha a ”--help” argumentummal indul a program, akkor adjon
tájékoztatást a felhasználónak a futtatás lehetséges opcióiról, a lehetséges parancssori
argumentumok jelentéséről! A fenti esetekben a végrehajtás ezután fejeződjön is be! A program
üzemmódját a ”-send” vagy a ”-receive” parancssori argumentummal, adhatjuk meg. Az előbbi
legyen az alapértelmezett azaz, ha egyik sincs megadva explicit üzemmód, akkor küldőként
viselkedjen a rendszer! A kommunikáció módját a ”-file” vagy a ”-socket” parancssori
argumentummal, adhatjuk meg. Az előbbi legyen az alapértelmezett azaz, ha egyik sincs megadva
egyik sem, akkor fájlt használjon a kommunikáció során! Az üzemmód és a kommunikációs mód
kapcsolók együttes használata esetén a sorrendjük tetszőleges. Amennyiben a program nem
érvényes argumentumot kap, akkor viselkedjen ugyanúgy, mint a ”--help” kapcsoló estén!
Amennyiben a futtatható állomány neve nem ”chart”, akkor a program írjon ki egy erre vonatkozó
hibaüzenetet és álljon le!
A főprogram fejléce legyen a szokásos:
int main(int argc, char* argv[]);
*/
void Help(){

    printf("************HELP***********\n");
    printf("A program a következő parancssori argumentumokkal képes működni:\n");
    printf(": --help : segítség\n");
    printf(": --version : program verziója\n");
    printf("***************************\n");
    printf("Kommunikáció módjára vonatkozó argumegtumok:\n");
    printf(": -file : kommunikáció fájlkezeléssel\n");
    printf(": -socket : kommunikáció hálózaton keresztül\n");
    printf("***************************\n");
    printf("Üzemmódok:\n");
    printf(": -send : a program küldő üzemmódban indul\n");
    printf(": -receive : a program fogadó üzemmódban indul\n");
    printf("***************************\n");
    printf("A program alapértelmezett indítási paraméterei:\n");
    printf(": ./chart -send -file\n");
    printf("A paraméterek sorrendje tetszőleges!\n");
    printf("***************************\n");
}
void Version(){
    printf("************Verzió************\n");
    printf("Verziószám: 0.8\n");
    printf("Kiadás dátuma: 2022.02.22 19:48\n");
    printf("Fejlesztő: Tarr Imre : IGXWVJ\n");
    printf("******************************\n");
}


int commands(int* send_mode, int* file_mode, int argc, char *argv[])
{
    char *arg[] = {"--version", "--help", "-send", "-receive", "-file", "-socket"};
    //arg=48
    //size 6
    //arg0 = 8
    //karaktertömb 8 bit
    //Kapcsoló lehetséges számai
    int size = sizeof arg / sizeof arg[0];
    
    int check_count = 0;
    
        if (argc > 1)
            {
                for (int k = 0; k < size; ++k)
                    {   
                        for (int i = 1;  i < argc; ++i)
                            {
                                if (strcmp(arg[k], argv[i]) == 0){
                                        //check_count mindig nő egyel, ha jó kapcsolót adok le, ha nem jó akkor else ág
                                        check_count++;
                                    }
                                else{
                                    *send_mode = -1;
                                    *file_mode = -1;
                                }
                            }
                    }
                    //argc 2ből kivonok egyet, ha nulla, mert rossz név, akkor Help();
                    if (check_count != argc-1){
                            Help();
                
                            *send_mode = -1;
                            *file_mode = -1;
                     }
                //1től indul 2ig
                for (int i = 1;  i < argc; ++i)
                    {
                        //strcmp megvizsgálja az argumentumot, ha az argv[i] --version és, ha 0 akkor jó 
                        if (strcmp(argv[i],"--help") == 0){   
                                Help();
                                *send_mode = -1;
                                *file_mode = -1;
                            }
                        if (strcmp(argv[i],"--version") == 0){
                                Version();                               
                                *send_mode = -1;
                                *file_mode = -1;
                            }
                        ///////////
                        if (strcmp(argv[i],"-send") == 0){   
                                *send_mode = 0;
                            }
                        if (strcmp(argv[i],"-receive") == 0){   
                                *send_mode = 1;
                            }
                        if (strcmp(argv[i],"-file") == 0){   
                                *file_mode = 0;
                            }
                        if (strcmp(argv[i],"-socket") == 0){   
                                *file_mode = 1;
                            }
                    }
            }
        else
        {
            return EXIT_FAILURE;
        }
}

//--2. feladat
/*1. lépés
Egy képzeletbeli szenzor által rendszeres időközönként mért értékeket egy függvénnyel állítjuk elő. Ez
a függvény egy 3 állapotú 1 dimenziós bolyongást implementál, azaz véletlenszerűen előállítja egész
számok egy véges sorozatát, ahol bármely két szomszédos elem különbségének az abszolút érteke
maximum 1. A kezdő érték legyen az x0=0! A további elemeknél az xi+1=xi+1 eset 42,8571%
eséllyel forduljon elő! Az esetek 11/31-ed részében xi+1=xi-1 állítás teljesüljön! A szomszédos
értékek néha lehetnek azonosak is (xi+1=xi). A „mért” értékek darabszáma egyezzen meg a hívás
pillanatában az adott negyedórából eltelt másodpercek számának és a 100-nak a maximumával!
(Például délelőtt 9 óra 41 perc 27 másodperckor 687 darab egész számot kell generálni, de 10 óra 15
perc 24 másodperckor 100 darab egész számot.) A program minden futtatás esetén másik számsort
állítson elő!
A függvény fejléce a következő legyen:
int Measurement(int **Values);
Az egyetlen paraméter egy int* típusú pointer címe legyen, mivel ez majd output paraméteként
szolgál (pszeudocím szerinti paraméterátadású mutató). Ebben a függvényben foglalj le dinamikus
memóriafoglalás segítségével egy megfelelő méretű tömböt, ebben legyen tárolva az előállított
véletlenszerű adatsorozat és a terület címe legyen elmentve azon a memóriacímen, amit
paraméterként kap a függvény (ezáltal az itt lefoglalt és inicializált terület címe visszajut a hívó
programegységbe, ami így el tudja érni az adatsort). Végül a függvény térjen vissza az előállított
értékek számával!
2. lépés
A küldő üzemmódban futó program esetén hívd meg a main-ben fenti Measurement függvényt!
Ideiglenes tesztként itt a főprogramban (a hívás után) írasd ki a képernyőre az adatsort! (A végső
verziónak nem kell tartalmaznia ezt a tesztet.)
*/
int Measurement(int **Values)
{
    //Idő kezelés
    //=074i
    time_t Time;
    struct tm *T2;

    time(&Time);
    T2 = localtime(&Time);
    //Measuerment szám
    int meres_szam = 0;

    int perc = (*T2).tm_min;
    int masodperc = (*T2).tm_sec;

    if (perc == 0){
        meres_szam = 100;
    }
    else if(perc < 15){
         if((perc * 60) + masodperc < 100){
            meres_szam = 100;
        }else{
            meres_szam = (perc * 60) + masodperc;
        }
    }
    //Kivonok belőle, átalakítom másodpercé és száznak a maximuma
    else if(perc < 30){
         if((((perc - 15) * 60) + masodperc) < 100){
            meres_szam = 100;
        }else{
            meres_szam = ((perc - 15) * 60) + masodperc;
        }
    }
    else if(perc < 45){
         if((((perc - 30) * 60) + masodperc) < 100){
            meres_szam = 100;
        }else{
            meres_szam = ((perc - 30) * 60) + masodperc;
        }
    }
    else if(perc < 59){
         if((((perc - 45) * 60) + masodperc) < 100){
            meres_szam = 100;
        }else{
            meres_szam = ((perc - 45) * 60) + masodperc;
        }
    }

    srand(time(NULL)); 

    /*"Ebben a függvényben foglalj le dinamikus
    memóriafoglalás segítségével egy megfelelő méretű tömböt, ebben legyen tárolva az előállított
    véletlenszerű adatsorozat és a terület címe legyen elmentve azon a memóriacímen, amit
    paraméterként kap a függvény"*/
    *Values = (int *)malloc(meres_szam * sizeof(int));
    //(int *)realloc(*Values, ms_szam * sizeof(int));
    //Lenullazom
    *(*Values + 0) = 0;

    double rnd;

  for(int i = 1; i < meres_szam; i++){
    
    //0-1 kozott
    rnd = (double)rand()/((unsigned)RAND_MAX+1);
    if(rnd<=0.428571){
        //i-edik érték a for ciklusban, egyenlő az előző érték előző értékével és plusz egy
        *(*Values + i) = *(*Values + (i - 1)) + 1;
    }
    // 11/31+0.428571
    else if (rnd <= 0.783409){
        *(*Values + i) = *(*Values + (i - 1)) - 1;
    }
    else{
        *(*Values + i) = *(*Values + (i - 1));
    }
  }
    return meres_szam;
}


//--3. feladat
/* Az adatsort úgy jelenítsd meg,
hogy a legelső érték (x0=0) az első oszlopnak a (függőlegesen) középső pixele legyen és ennek
megfelelően jelenjen meg a többi érték is! (Amennyiben a kép magassága páros érték, akkor a két
középső pixel bármelyike használható.) Ha valamelyik megjelenítendő érték túl nagy vagy túl kicsi
lenne (azaz kilógna a képből), akkor azt a legfelső, illetve a legalsó pixel segítségével jelenítsd meg.
tömb és méret (érték, darabszám)*/
void BMPcreator(int* Values, int NumValues)
{
    unsigned long int fsize = (62 + (NumValues * NumValues));
    unsigned int pad = 0;
    int file = open("chart.bmp", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IROTH);
    unsigned char** tomb = (unsigned char**)calloc(NumValues, sizeof(unsigned char*));
    

    unsigned char f_headder[] = { 0x42, 0x4d,                 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,                                 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x0f,
    0x00, 0x00, 0x61, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0xff, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff,           };

    for (int i = 0; i < NumValues; ++i) {
        tomb[i] = (unsigned char*)calloc(NumValues, sizeof(unsigned char));
    }
    for(int i = 0; i < NumValues; ++i){
        int elem = (NumValues/2) + Values[i];
        if (elem > NumValues){
            elem = NumValues-1;
        }
        else if (elem < -(NumValues/2)){
            elem = 0;
        }
        tomb[elem][i] = 0x01;
    }

    write(file, f_headder, sizeof(unsigned char) * 2);     
    write(file, &fsize, sizeof(int));      
    write(file, &f_headder[2], sizeof(unsigned char) * 12); 
    write(file, &NumValues, sizeof(int));  
    write(file, &NumValues, sizeof(int));  
    write(file, &f_headder[14], sizeof(unsigned char) * 36);    

    for (int i = 0; i < NumValues; i++){
        int x = 7;
        for (int j = 0; j < NumValues; ++j){           
            if (tomb[i][j] == 0x01){
                int ps = 1 << x;
                pad = pad + ps;
            }
            if (x == 24){                
                write(file, &pad, sizeof(int));
                pad = 0;                
                x = 7;
                continue;
            }
            if (x % 8 == 0){
                x = (j % 32) + 9;
            }
            --x;
        }    
        write(file, &pad, sizeof(int));       
        pad = 0;
    }
    free(tomb);
}
//--4. feladat
/*
Írj egy függvényt, amely a Linux fájlrendszer gyökerében lévő ”/proc” könyvtárnak az
alkönyvtáraiban található ”status” nevű fájloknak a tartalmát vizsgálja meg. (Azok az alkönyvtárak
tartalmaznak ilyen fájlokat, amelyek neve számjegy karakterrel kezdődik.) A fájl első sorának a
formátuma: ”Name:\t%s\n”. Ha a tabulátor és az újsor karakter között a ”bash”
karaktersorozatot található, akkor keressen az adott fájlban olyan sort, amely a ”Pid:\t” sztriggel
kezdődik majd ezt egy egész szám követi. A függvény térjen vissza ezzel az egész számmal, ha pedig
egyáltalán nem talál ilyen fájlt egyik alkönyvtárban sem, akkora -1 értékkel! 
Process ID*/
int FindPID()
{
    DIR *dir, *dir2;
    struct dirent *entry, *entry2;
    FILE *file;
    char line[100];
    char* ask_name = "Name:\tchart\n";
    char* ask_pid = "Pid:";
    int check_bash = 0;
    char tomb[4];

    dir=opendir("/proc");  
    
    //=074i
    while((entry=readdir(dir))!=NULL)
    {  
        if(isdigit((*entry).d_name[0]))
        {
            //pointert ráállítok a d_name-ra
            char *new_path = (char *)malloc(strlen(entry->d_name) + 5);
            sprintf(new_path, "%s/%s", "/proc", entry->d_name);

            dir2 = opendir(new_path);

            while ((entry2 = readdir(dir2)) != NULL)
            {
                if ((strcmp(entry2->d_name,"status") == 0))
                {
                    char *new_path2 = (char *)malloc(strlen(entry2->d_name) + 5);
                    sprintf(new_path2, "%s/%s", new_path, "status");

                    file = fopen(new_path2, "r");
                    if (file == NULL){
	                    return -1;
                    }

                    while (fgets(line, sizeof(line), file) != NULL){
                        if (strcmp(line, ask_name) == 0){
                            check_bash = 1;
                        }

                        if ((strncmp(line,ask_pid,4) == 0) && (check_bash == 1)){
                            memcpy(tomb,&line[5],4);
                            closedir(dir);
                            closedir(dir2);
                            return atoi(tomb);
                        }       
                    }
                }
            }
            closedir(dir2);
        }
    }
    closedir(dir);
    return -1;
}
//--5. feladat
/*
3. lépés
Írj egy eljárást, amely az adott felhasználó alapértelmezett könyvtárában lévő
”Measurement.txt” nevű szöveges fájlt megnyitja, a tartalmát beolvassa és eltárolja egy
memóriaterületre, melyet szükség esetén dinamikus memóriafoglalással bővít (mivel nem tudjuk
előre az elemek számát). Ezt követően az eljárás hívja meg a BMPcreator eljárást és adja át neki a
beolvasott értékeket és azok darabszámát! Végül a dinamikusan lefoglalt memóriaterület legyen
felszabadítva! Az eljárás fejléce, legyen az alábbi (a paraméter értékét nem fogjuk felhasználni, de
szükséges):
void ReceiveViaFile(int sig);
*/
void ReceiveViaFile(int sig)
{
    puts("Receive file");

    char *filename = "/Measurement.txt";
    char *home_dir = getenv("HOME");
    char *filepath = malloc(strlen(home_dir) + strlen(filename) + 1);
    /*
    dest − Ez a mutató arra a céltömbre, ahová a tartalmat másolni kell.
    src − Ez a kezelendő karakterlánc.
    n − A forrásból másolandó karakterek száma.
    */
    strncpy(filepath, home_dir, strlen(home_dir) + 1);
    /*
    dest: az a karakterlánc, ahová hozzá akarjuk fűzni.
    src: az a karakterlánc, amelyből az „n” karaktert hozzá kell fűzni.
    n: a hozzáfűzhető karakterek maximális számát jelenti.
    */
    strncat(filepath, filename, strlen(filename) + 1);
    FILE *file = fopen(filepath, "r");
    char line[100];
    //X számolja a measurement sorait
    int x = 0;

    int *result = (int *)malloc(sizeof(int));

    while (fgets(line, sizeof(int), file) != NULL){
        *(result + x) = atoi(line);
        x++;
        result = (int *)realloc(result, (sizeof(int) * (x + 1)));
    }
    puts("BMP file generálása...");
    BMPcreator(result, x);
    puts("Generálás kész!");

    free(result);

}
/*
2. lépés
Hozz létre egy eljárást, az alábbi paraméterezéssel:
void SendViaFile(int *Values, int NumValues);
A Values mutató egy egészeket tartalmazó tömb kezdőcímét kapja paraméterátadás során, míg a
NumValues változó fogja tárolni a tömbben lévő egészek darabszámát. Az eljárás hozzon létre egy
”Measurement.txt” nevű szöveges fájlt az adott felhasználó saját alapértelmezett könyvtárában
és soronként írja bele a tömbben lévő értékeket a fájlba (”%d\n” formátummal)! Miután bezárta a
fájlt, hívja meg az eljárás a FindPID nevű függvényt! Ha a függvény -1 értékkel tér vissza, akkor a
program írjon ki egy hibaüzenetet, arra vonatkozóan, hogy nem talál fogadó üzemmódban működő
folyamatot (process-t) majd a program álljon le egy hibakóddal (nem 0 visszatérési értékkel)!
Amennyiben a FindPID más értékkel tér vissza, az eljárás küldjön neki egy felhasználói 1-es szignált
(SIGUSR1)! */
void SendViaFile(int *Values, int NumValues)
{
    char *filename = "/Measurement.txt";
    char *home_dir = getenv("HOME");
    char *filepath = malloc(strlen(home_dir) + strlen(filename) + 1);
    strncpy(filepath, home_dir, strlen(home_dir) + 1);
    strncat(filepath, filename, strlen(filename) + 1);
    FILE *myFile = fopen(filepath, "w");
    for (int i = 0; i < NumValues; i++){
        fprintf(myFile,"%d\n",*(Values + i));
    }
    fclose(myFile);
    free(filepath);

    pid_t pid = FindPID();
    if(pid == -1){
        puts("Nem találtam fogadó üzemmódban működő folyamatot!");
        exit(-1);
    }else{
        kill(pid, SIGUSR1);
    }
}
//--6. feladat
/*
1. lépés
Írj egy eljárást, amely UDP protokoll segítségével a localhost (IPv4 cím: 127.0.0.1) 3333-as
portját figyelő fogadó üzemmódú szoftverrel kommunikál. Az eljárás fejléce így nézzen ki:
void SendViaSocket(int *Values, int NumValues);
Itt az első paraméterként kapott memóriacím egy tömb kezdőcíme, a második pedig a tömbben lévő
egész típusú értékek száma. Az eljárás a socketen keresztül küldje el a fogadónak a NumValues
változó értékét (32 bites fix pontos egészként)! Ezután várjon a szerver válaszára, ami szintén
egyetlen 4 bájtos egész szám lesz (int). Ha a küldött és a kapott értékek eltérőek, akkor egy
hibaüzenet után a program egy eddigiektől eltérő hibakóddal álljon le! Ha az értékek megegyeznek,
akkor az eljárás a Values címen kezdődő tömb NumValues darab int típusú értékét küldje át
egyetlen üzenetben a fogadónak. Ezután ismét várjon egy válaszüzenetre, ami egy 4 bájtos egész
szám lesz. Ha a küldött adatok bájtban megadott mérete és a most kapott értékek eltérőek, akkor is
egy hibaüzenet után hibakóddal álljon le a program!*/
void SendViaSocket(int *Values, int NumValues){
    //=0741
    int s;
    int bytes;
    int flag;
    char on;
    unsigned int server_size;
    struct sockaddr_in server;
    int valasz;

    //Inicializálás
    on   = 1;
    flag = 0;
    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port        = htons(3333);
    server_size = sizeof server;

    //Socket készítés
    s = socket(AF_INET, SOCK_DGRAM, 0 );
    if ( s < 0 ) {fprintf(stderr, "Socket creation error.\n"); exit(2);}
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);
    setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, &on, sizeof on);

    //Küldő tömb mérete
    bytes = sendto(s, &NumValues, sizeof(int), flag, (struct sockaddr *) &server, server_size);
    puts("Send array size!");
    if ( bytes <= 0 ) { fprintf(stderr, "Sending error.\n"); exit(3); }
    signal(SIGALRM,SignalHandler);
    /*"a az eljárás alarm szignált (SIGALRM) kap, akkor írjon ki egy hibaüzenetet arra vonatkozóan, hogy a
    szerver nem válaszol (időkereten belül), majd a program egy hibakóddal álljon le"*/
    sleep(1);
    signal(SIGALRM, SIG_IGN);

    //Fogadás mérete
    bytes = recvfrom(s, &valasz, sizeof(int), flag, (struct sockaddr *) &server, &server_size);
    puts("Receive allocation size!");
    if ( bytes < 0 ) {fprintf(stderr, "Receiving error.\n"); exit(3);}

    
    
    //Méret teszt
    if (NumValues != valasz){
        fprintf(stderr, "Size error.\n");
        exit(4);
    }
    puts("Send size and receive size is equal!");

    //Tömbadatok küldése
    bytes = sendto(s, Values, (NumValues * sizeof(int)), flag, (struct sockaddr *) &server, server_size);
    if ( bytes <= 0 ) {fprintf(stderr, "Sending error.\n"); exit(5);}
    puts("Sending array data!");

    //Küldött fogadási bájtok mérete
    int s_bytes = recvfrom(s, &valasz, sizeof(int), flag, (struct sockaddr *) &server, &server_size);
    if (bytes <= 0)
    {
        fprintf(stderr,"Error size!\n");
        exit(7);
    }
    if (valasz != bytes)
        {
        fprintf(stderr, "Size error.\n");
        exit(5);
    }
    puts("Send bytes and receive bytes is equal!");
    
    close(s);
}

/*
2. lépés
Írj egy másik socket programozáson alapuló eljárást is, amely egy végtelen ciklusban UDP
szegmenseket vár a 3333-as porton. Az első kapott szegmensben feltételezzük, hogy mindig egy 4
bájtos hasznos tartalom van (egy int változó értéke). Az eljárás nyugtaként küldje vissza a kapott
értéket a küldő üzemmódú kliens folyamatnak, valamint dinamikusan foglaljon le ennyi darab egész
szám számára egy folyamatos memóriaterületet! Ide tárolja el a második üzenetben kapott adatokat,
amelyeknek a bájtban megadott méretét nyugtaként juttassa vissza a küldőnek! A kapott adatokkal
kerüljön meghívásra a BMPcreator eljárás, végül a lefoglalt memóriaterületek legyenek
felszabadítva és az eljárás várjon újabb üzenetet egy küldőtől! (Feltehetjük, hogy egy adott
pillanatban csak egyetlen küldő aktív és az mindig elküldi mind a két üzenetet.). Az eljárás fejléce
egyszerűen legyen ez:
void ReceiveViaSocket();
*/
void ReceiveViaSocket()
{
    int bytes;
    int err;
    int flag;
    char on;
    unsigned int server_size;
    unsigned int client_size;
    struct sockaddr_in server;
    struct sockaddr_in client;
    int valasz;

    //Inicializálás
    on   = 1;
    flag = 0;
    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port        = htons(3333);
    server_size = sizeof server;
    client_size = sizeof client;
    //signal(SIGINT, stop);
    //signal(SIGTERM, stop);

    //Készítés
    int s = socket(AF_INET, SOCK_DGRAM, 0 );
    if ( s < 0 ) {
        fprintf(stderr, "Socket creation error.\n");
        exit(2);
        }
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);
    setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, &on, sizeof on);

    // Binding socket
    err = bind(s, (struct sockaddr *) &server, server_size);
    if ( err < 0 ) {
      fprintf(stderr,"Binding error.\n");
      exit(3);
    }

    while(1){
        puts("Adatok várása...\n");

        //Fogadási tömb mérete
        bytes = recvfrom(s, &valasz, sizeof(int), flag, (struct sockaddr *) &client, &client_size );
        if ( bytes < 0 ) {fprintf(stderr, "Receiving error.\n");exit(4);}

        //Tömb kiosztás
        int* ERTEKEK = malloc(valasz * sizeof(int));
        puts("Array allocation is done!");

        //Tömbkiosztási méret elküldése
        bytes = sendto(s, &valasz, sizeof(int), flag, (struct sockaddr *) &client, client_size);
        puts("Send array allocation size!");
        if ( bytes <= 0 ) {fprintf(stderr,"Sending error.\n");exit(4);}

        //Tömbadatok fogadása
        bytes = recvfrom(s, ERTEKEK, valasz * sizeof(int), flag, (struct sockaddr *) &client, &client_size );
        puts("Receive array data!");
        if ( bytes < 0 ){fprintf(stderr, "Receiving error.\n"); exit(4);}

        //Fogadási bájtok küldése
        bytes = sendto(s, &bytes, sizeof(int), flag, (struct sockaddr *) &client, client_size);
        puts("Send receive data bytes siize!");
        if ( bytes < 0 ) {fprintf(stderr,"Sending error.\n");exit(11);}

        //BMP fájl készítés
        puts("BMP file generálása...");
        BMPcreator(ERTEKEK, valasz);
        puts("Generálás kész!");

        free(ERTEKEK);
        puts("");
    }

    close(s);   
}
//--7. feladat
/*1. lépés
Írj egy szignálkezelő eljárást (természetesen ez is a header állományba kerüljön), amely háromféle
szignál kezelésére képes és az alábbi fejléccel rendelkezik:
void SignalHandler(int sig);
Ha az eljárás megszakítási szignált (SIGINT) kap, akkor írjon ki egy elköszönő üzenetet és a program
álljon le és adjon vissza egy 0 értéket!
Ha az eljárás felhasználói 1-es szignált (SIGUSR1) kap, akkor írjon ki egy hibaüzenetet arra
vonatkozóan, hogy a fájlon keresztüli küldés szolgáltatás nem elérhető!
Ha az eljárás alarm szignált (SIGALRM) kap, akkor írjon ki egy hibaüzenetet arra vonatkozóan, hogy a
szerver nem válaszol (időkereten belül), majd a program egy hibakóddal álljon le*/
void SignalHandler(int sig)
{
    if(sig==SIGINT){
        puts("\nA program leállt.\nViszlát!");
        exit(0);
    }
    if(sig==SIGUSR1){
        puts("A fájlon keresztüli küldés szolgáltatás nem elérhető!");
        exit(1);
    /**///return;
    }if(sig==SIGALRM){
        puts("Server timeout!");
        exit(4);
    }
}