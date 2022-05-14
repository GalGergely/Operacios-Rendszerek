#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <wait.h>

void printMenu();

void StartGame();

void PassingDataToChild(const int *pipe1, int pInt[4], int i);

void ChildrenDuty(const int *pipe1, const int *resPipe1);

void OperationWithResoult(int *result1, int *resPipe1);

int main()
{

    while (true)
    {

        int operation;
        // menu
        //--------------------
        printMenu();
        fflush(stdin);
        scanf("%d", &operation);
        switch (operation)
        {
            case 1:
                StartGame();
                break;
            case 0:
                // kilepes
                //--------------------
                return 0;
                break;
            default:
                printf("Na hat ez nem sikerult.\n");
        }
    }
    return 0;
}

void checkFork(pid_t pid) {
    if(pid == -1){
        perror("anya miez");
        exit(1);
    }
}
//alapgondolat,a gyerek adja vissza a szám négyzetét amit kap
void StartGame() {
    //gyerek 1 pipek
    int pipe1[2];
    pipe(pipe1);
    int resPipe1[2];
    pipe(resPipe1);
    //gyerek 1 fork
    pid_t pid = fork();

    checkFork(pid);
    if(pid == 0) {
        //gyerek 1
        ChildrenDuty(pipe1, resPipe1);
    } else {
        //gyerek 2 pipek
        int pipe2[2];
        pipe(pipe2);
        int resPipe2[2];
        pipe(resPipe2);
        //gyerek 2 fork
        pid_t pid2 = fork();

        checkFork(pid2);
        if(pid2 == 0) {
            //2.gyerek
            //gyerek 1 pipek lezarasa
            close(pipe1[0]);
            close(pipe1[1]);
            close(resPipe1[0]);
            close(resPipe1[1]);

            ChildrenDuty(pipe2, resPipe2);
        } else {
            //mama
            int numbers1[] = {1, 2, 4, 7};
            int const numbers1_size=4;
            PassingDataToChild(pipe1, numbers1, numbers1_size);
            int numbers2[] = {3,5,6};
            int numbers2_size=3;
            PassingDataToChild(pipe2, numbers2, numbers2_size);
            //varakozas a gyerek 1 valaszara
            wait(NULL);
            //varakozas a gyerek 2 valaszara
            wait(NULL);
            int result1[numbers1_size];
            int result2[numbers2_size];
            OperationWithResoult(result1, resPipe1);
            OperationWithResoult(result2, resPipe2);
            printf("Vegeredmeny:\n");
            for(int i=0; i<numbers1_size; i++) {
                printf("%d, ", result1[i]);
            }
            printf("\n");
            for(int i=0; i<numbers2_size; i++) {
                printf("%d, ", result2[i]);
            }
            printf("\n");
        }
    }
}

void OperationWithResoult(int *result, int *resPipe) {
    close(resPipe[1]);
    int i = 0;
    printf("A szulo amit kiszed a csobol: ");
    while(read(resPipe[0], &result[i], sizeof(int)) > 0) {
        printf("%d, ", result[i]);
        i++;
    }
    printf("\n");
}

void ChildrenDuty(const int *pipe1, const int *resPipe1) {
    sleep(1);
    close(pipe1[1]);
    close(resPipe1[0]);
    int res;
    printf("A gyereknek szamitasai: ");
    while(read(pipe1[0], &res, sizeof(int)) > 0) {
        res += res;
        printf("%d, ", res);
        write(resPipe1[1], &res, sizeof(int));
    }
    printf("\n");
    close(pipe1[0]);
    close(resPipe1[1]);
    exit(0);
}

void PassingDataToChild(const int *pipe1, int numbers[], int n) {
    close(pipe1[0]);
    printf("A gyereknek adtam: ");
    int res;
    for (int i = 0; i < n; i++) {
        write(pipe1[1], &numbers[i], sizeof(int));
        printf("%d, ",numbers[i]);
    }
    printf("\n");
    close(pipe1[1]);
}

void printMenu() {
    printf("---------------------------------------------------------\n");
    printf("1. Inditas\n");
    printf("0. Kilepes\n");
}