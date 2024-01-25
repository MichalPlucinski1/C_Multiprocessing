//
// Created by michael on 25.01.24.
//
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<time.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>

//kladka nad przepascia

#define N 50 //liczba procesow
#define MAX_WEIGHT 180 // maksymalna waga kladki

#define SHM_KEY 34121
#define SEM_KEY 37121

int waitForAll(pid_t proc[N]){
    for(int i = 0; i < N; i++){
        int status = 0;

        waitpid(proc[i],&status ,0);
    }
}

int * generateWeightTab(){
    static int r[N];
    srand(time(NULL));
    for(int i = 0; i < N; i++){
        r[i] = 30 + rand()%90;
    }
    return r;
}

int * generateSideTab(){
    static int r[N];
    srand(time(NULL));
    for(int i = 0; i < N; i++){
        r[i] = rand()%2;
    }
    return r;
}

static struct sembuf buf;



void podnies_swiatlo(int semid, int semnum, int sem_op){


    int wartosc = semctl(semid,semnum, GETVAL);
    if(wartosc + sem_op > 1)
        return;

    buf.sem_num = semnum;
    buf.sem_op = sem_op;
    buf.sem_flg = 0;
    if(semop(semid,&buf,1) == -1){
        perror("Blad podnoszenia wartosci semafora");
        exit(1);
    }
}

void podnies(int semid, int semnum, int sem_op){

    buf.sem_num = semnum;
    buf.sem_op = sem_op;
    buf.sem_flg = 0;
    if(semop(semid,&buf,1) == -1){
        perror("Blad podnoszenia wartosci semafora");
        exit(1);
    }
}

void opusc(int semid, int semnum, int sem_op){
    buf.sem_num = semnum;
    buf.sem_op = - sem_op;
    buf.sem_flg = 0;
    if(semop(semid,&buf,1) == -1){
        perror("Blad opuszczania wartosci semafora");
        exit(1);
    }

}




int main() {

    // semafor
    int semid_swiatlo_0 = semget(SEM_KEY, 1, IPC_CREAT|0600);
    int semid_swiatlo_1 = semget(SEM_KEY + 5, 1, IPC_CREAT|0600);
    int semid_waga = semget(SEM_KEY + 10, 1, IPC_CREAT|0600);
    int semid_osoby = semget(SEM_KEY + 15, 1, IPC_CREAT|0600);


    if(semid_swiatlo_0 == -1){
        perror("Blad utworzenia semafora");
        exit(1);
    }

    if(semctl(semid_swiatlo_0, 0, SETVAL, 1) == -1) {
        perror("Blad nadania wartosci semaforowi 0");
        exit(1);
    }

    if(semctl(semid_swiatlo_1, 0, SETVAL, 1) == -1) {
        perror("Blad nadania wartosci semaforowi 0");
        exit(1);
    }
    if(semctl(semid_waga, 0, SETVAL, MAX_WEIGHT) == -1) {
        perror("Blad nadania wartosci semaforowi 0");
        exit(1);
    }

    if(semctl(semid_osoby, 0, SETVAL, 0) == -1) {
        perror("Blad nadania wartosci semaforowi 0");
        exit(1);
    }

    //0, 1 - sem swiatla poln, pol. gdy wartosc 0 -> nie moze przejechc.druga strona bedzie probowala go opuscic, wiec ktos musi go podniesc
    // 2 - waga
    // 3 - ilosc osob na moscie


    printf("Tworzenie procesow\n");


    pid_t tablica_procesow[N];
    pid_t ppid = getpid();
    pid_t pid;

    int weight;
    int side;

    int *weighTab = generateWeightTab();
    int *sideTab = generateSideTab();

    printf("1 masa:%d strona:%d\n", weighTab[0], sideTab[0]);

    for(int i = 0; i < N; ++i){
        if(getpid() == ppid){
            pid = fork();
            if(pid == 0){
                weight = weighTab[i];
                side = sideTab[i];
                break;
            }

            if(pid < 0){
                fprintf(stderr,"Tworzenie procesu");
                return EXIT_FAILURE;
            }  else if(pid != 0){
                tablica_procesow[i] = pid;
            }

        }

    }

    //0, 1 - sem swiatla poln, pol. gdy wartosc 0 -> nie moze przejechc.druga strona bedzie probowala go opuscic, wiec ktos musi go podniesc
    // 2 - waga
    // 3 - ilosc osob na moscie

    //symulacja
    if(getpid() != ppid){
        printf("proc: %d  w:%d,  s:%d\n", getpid(), weight, side);

        if(weight < 30 || side > 1){
            printf("bledny proces usuwam\n");
            return 0;
        }



            if(side == 0){  //czekaj na swoje zielone swiatlo (niestety zgasi je...)

                printf("%d: czekam na moje swiatlo %d\n", getpid(), side);
                opusc(semid_swiatlo_0, 0, 1); //
                printf("%d: doczekalem sie na moje swiatlo %d\n", getpid(), side);
                if(semctl(semid_osoby, 0, GETVAL) == 0) // jezeli jeszcze nikogo nie ma na moscie
                    opusc(semid_swiatlo_1, 0, 1); // zgasza pozwolenie drugiej stronie

                podnies_swiatlo(semid_swiatlo_0, 0, 1); // ...wiec znowu musi zapalic swoje

            }
            else{ // dla drugiej strony
                printf("%d: czekam na moje swiatlo %d\n", getpid(), side);

                opusc(semid_swiatlo_1, 0, 1);
                printf("%d: doczekalem sie na moje swiatlo %d\n", getpid(), side);


                if(semctl(semid_osoby, 0, GETVAL) == 0)
                    opusc(semid_swiatlo_0, 0, 1);
                podnies_swiatlo(semid_swiatlo_1, 0, 1);

            }

            printf("czekam na wage\n");
            opusc(semid_waga, 0, weight); // probujemy wejsc po wadze
            podnies(semid_osoby, 0, 1); // wchodzimy
            printf("wchodzi %d ze strony: %d, masa procesu:%d\n", getpid(), side, weight);

            usleep(500); // przechodzenie

            podnies(semid_waga, 0, weight); // opuszczamy wage
            printf("opuszczam ilosc osob\n");
            opusc(semid_osoby, 0, 1); // schodzimy
            printf("z sukcesem opuscilem ilosc osob\n");
            printf("%d przeszedl\n", getpid());

            if(semctl(semid_osoby, 0, GETVAL) == 0){ // jezeli zszedl i nie ma nikogo wiecej
                printf("pozwalam drugiej stronie przejsc\n");
                if(side == 0){
                    podnies_swiatlo(semid_swiatlo_1, 0, 1); // zapala pozwolenie drugiej stronie
                }
                else{ // dla drugiej strony
                    podnies_swiatlo(semid_swiatlo_0, 0, 1);
                }
            }

            return 0; // proces szczesliwie przeszedl


        }




        /*
         * ilosc osob na moscie < 2
         * jezeli == 1, wchodzi, jezeli ida w ta sama strone i m1 + m2 < mMax

         */
    else{
        waitForAll(tablica_procesow);
        /*for(int i = 0; i < N; i++){
            printf("tab[%d]: [%d]\n", i, tablica_procesow[i]);
        }*/
    }

    printf("wszsycy przeszli!");
    return 0;
}
