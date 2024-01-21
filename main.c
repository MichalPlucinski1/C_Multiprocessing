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



void podnies(int semid, int semnum){
    buf.sem_num = semnum;
    buf.sem_op = 1;
    buf.sem_flg = 0;
    if(semop(semid,&buf,1) == -1){
        perror("Blad podnoszenia wartosci semafora");
        exit(1);
    }

}

void opusc(int semid, int semnum){
    buf.sem_num = semnum;
    buf.sem_op = -1;
    buf.sem_flg = 0;
    if(semop(semid,&buf,1) == -1){
        perror("Blad opuszczania wartosci semafora");
        exit(1);
    }

}





int main() {

    //pamiec wspoldzielona

    int shmid;
    int *smhbuf;

    shmid = shmget(SHM_KEY, 3 * sizeof(int), IPC_CREAT|0600);
    if (shmid == -1){
        perror("Blad utworzenia segmentu pamieci wspoldzielonej");
        exit(1);
    }

    smhbuf = (int*)shmat(shmid, NULL, 0);
    if (smhbuf == NULL){
        perror("Blad przylaczenia pamieci wspoldzielonej");
        exit(1);
    }

    smhbuf[0] = 0; // kierunek marszu
    smhbuf[1] = 0; // ilosc osob
    smhbuf[2] = 0; // waga

    // semafor

    int semid_0 = semget(SEM_KEY, 1, IPC_CREAT|0600);

    if(semid_0 == -1){
        perror("Blad utworzenia semafora");
        exit(1);
    }

    if(semctl(semid_0, 0, SETVAL, 2) == -1) {
        perror("Blad nadania wartosci semaforowi 0");
        exit(1);
    }




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
    //symulacja
    if(getpid() != ppid){
        printf("proc: %d  w:%d,  s:%d\n", getpid(), weight, side);

        if(weight < 30 || side > 1){
            printf("bledny proces usuwam\n");
            return 0;
        }
        while(1){
            opusc(semid_0, 0);
            if(smhbuf[1] == 0 || (smhbuf[1] == 1 && smhbuf[0] == side && smhbuf[2] + weight < MAX_WEIGHT)){
                smhbuf[0] = side;
                smhbuf[1] += 1;
                smhbuf[2] += weight;
                printf("wchodzi %d. ilosc na moscie: %d, masa mostu: %d, ze strony: %d, masa procesu:%d\n", getpid(), smhbuf[1], smhbuf[2], smhbuf[0], weight);
                sleep(1); // czas przechodzenia to sekunda
                printf("%d przeszedl\n", getpid());

                smhbuf[1] -= 1;
                smhbuf[2] -= weight;

                podnies(semid_0, 0);
                return 0;
            }

            podnies(semid_0,0);

        }



        /*
         * ilosc osob na moscie < 2
         * jezeli == 1, wchodzi, jezeli ida w ta sama strone i m1 + m2 < mMax

         */

    }
    else{
        waitForAll(tablica_procesow);
        /*for(int i = 0; i < N; i++){
            printf("tab[%d]: [%d]\n", i, tablica_procesow[i]);
        }*/
    }


    return 0;
}
