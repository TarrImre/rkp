#ifndef RKP_header_
#define RKP_header_
//1.feladat
int commands(int* send_mode, int* file_mode, int argc, char *argv[]);
//2.feladat
int Measurement(int **Values);
//3.feladat
void BMPcreator(int *Values, int NumValues);
//4.feladat
int FindPID();
//5.feladat
void SendViaFile(int *Values, int NumValues);
//6.feladat
void ReceiveViaFile(/*int sig*/);
//7.feladat
void SendViaSocket(int *Values, int NumValues);
//8.feladat
void ReceiveViaSocket();
//9.feladat
void SignalHandler(int sig);
#endif // RKP_header_