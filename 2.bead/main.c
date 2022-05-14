#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <wait.h>


typedef struct Result {
    char name[150];
    int number;
} Result;

void ListRabbitsByCities();

void ListRabbits();

int ChoseWitchCity(int operationVaros, char *m, FILE *out_file);

char *inputString(FILE *fp, size_t size);

void printMenu();

int SaveRabbit();

void StartGame();

bool contains(int city, int pInt[4], int i);

void PassingNameToChild(const int *pipe1, int pInt[4], int i);

void DeleteRabbit();

void SwitchFilesAndCleanup();

void NameChange(FILE *out_file2);

char *ReadName();

void CityChange(char *m, FILE *out_file);

void ChildrenDuty(const int *pipe1, const int *resPipe1);

Result RegionMax(const int *resPipe1);

int main()
{

    while (true)
    {
        int RabbitCreationReturn;
        int cntr = 0;
        int firstprint = 0;
        char c;
        int operation;
        int operationVaros;
        int alkalom;
        int mitAkarszModositani;
        char *m;
        char *m2;
        FILE *in_file = fopen("rabbits.txt", "r");
        FILE *out_file = fopen("rabbits.txt", "a");
        FILE *out_file2;
        char singleline[150];
        char saveTheName[150];
        char inttostringhelper[150];
        // menu
        //--------------------
        printMenu();
        fflush(stdin);
        scanf("%d", &operation);
        switch (operation)
        {
            case 1:
                // nyuszi nev hozzaadas
                //--------------------
                fflush(stdin);
                RabbitCreationReturn = SaveRabbit();
                if(RabbitCreationReturn==1) {
                    perror("A nyuszi kreacio elhasalt");
                    return 1;
                }
                break;

            case 2:
                // nyuszi torles
                //--------------------
                DeleteRabbit();
                // temperary filek eltakaritasa es kicsere az eredetire
                //--------------------
                SwitchFilesAndCleanup();
                break;

            case 3:
                // nyuszi modositas
                //--------------------
                m = ReadName();
                in_file = fopen("rabbits.txt", "r");
                out_file = fopen("rabbitstmp.txt", "w");
                while (!feof(in_file))
                {
                    fgets(singleline, 150, in_file);
                    singleline[strcspn(singleline, "\n")] = 0;
                    if (strcmp(singleline, m) == 0)
                    {
                        printf("1.Nev modositas\n2.Lakhely modositas\n3.Versenyszam modositas\n");
                        scanf("%d", &mitAkarszModositani);
                        switch (mitAkarszModositani)
                        {
                            case 1:
                                NameChange(out_file);
                                break;
                            case 2:
                                fprintf(out_file, "\n%s", singleline);
                                fgets(singleline, 150, in_file);
                                CityChange(m, out_file);
                                break;
                            case 3:
                                fflush(stdin);
                                fprintf(out_file, "\n%s", singleline);

                                fgets(singleline, 150, in_file);
                                singleline[strcspn(singleline, "\n")] = 0;
                                fprintf(out_file, "\n%s", singleline);

                                printf("Hanyadik alkalommal indul a versenyen?\n");
                                scanf("%d", &alkalom);
                                fprintf(out_file, "\n%d", alkalom);
                                fgets(singleline, 150, in_file);
                                fflush(stdin);
                                break;
                            default:
                                printf("Na hat ez nem sikerult.\n");
                        }
                    }
                    else
                    {
                        fprintf(out_file, "\n%s", singleline);
                    }
                }
                fclose(in_file);
                fclose(out_file);
                firstprint = 0;
                in_file = fopen("rabbitstmp.txt", "r");
                out_file = fopen("rabbits.txt", "w");
                c = fgetc(in_file);
                while (c != EOF)
                {
                    if (firstprint == 0)
                    {
                        c = fgetc(in_file);
                        firstprint++;
                    }
                    fputc(c, out_file);
                    c = fgetc(in_file);
                }
                fclose(in_file);
                fclose(out_file);
                free(m);
                remove("rabbitstmp.txt");
                remove("rabbitstmpdeleted.txt");
            case 4:
                // listazas, kedvencem
                //--------------------
                ListRabbits();
                break;
            case 5:
                // listazas varos szerint
                //--------------------
                ListRabbitsByCities();
                break;
            case 6:
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

void CityChange(char *m, FILE *out_file) {
    int operationVaros;
    printf("Melyik varosban indul:\n");
    printf("1.Baratfa\n2.Lovas\n3.Szula\n4.Kigyos-patak\n5.Malom telek\n6.Paskom\n7.Kaposztas kert\n");
    scanf("%d", &operationVaros);
    switch (operationVaros)
    {
        case 1:
            fprintf(out_file, "\n%d", 1);
            break;
        case 2:
            fprintf(out_file, "\n%d", 2);
            break;
        case 3:
            fprintf(out_file, "\n%d", 3);
            break;
        case 4:
            fprintf(out_file, "\n%d", 4);
            break;
        case 5:
            fprintf(out_file, "\n%d", 5);
            break;
        case 6:
            fprintf(out_file, "\n%d", 6);
            break;
        case 7:
            fprintf(out_file, "\n%d", 7);
            break;
        default:
            free(m);
            perror("Adatbeviteli hiba");
            exit(1);
    }
}

char *ReadName() {
    fflush(stdin);
    printf("Nev: ");
    scanf("%d", stdin);
    return inputString(stdin, 10);
}

void NameChange(FILE *out_file2) {
    fflush(stdin);
    printf("Milyen nevre szeretnel modositani?\n");
    char *m = ReadName();
    fprintf(out_file2, "\n%s", m);
    free(m);
}

void SwitchFilesAndCleanup() {
    remove("rabbitstmpdeleted.txt");
    FILE *in_file = fopen("rabbitstmp.txt", "r");
    FILE *out_file2 = fopen("rabbits.txt", "w");
    char c = fgetc(in_file);
    while (c != EOF)
    {
        fputc(c, out_file2);
        c = fgetc(in_file);
    }

    fclose(in_file);
    fclose(out_file2);
    remove("rabbitstmp.txt");
}


void checkFork(pid_t pid) {
    if(pid == -1){
        perror("anya miez");
        exit(1);
    }
}

void StartGame() {

     int pipe1[2];
     pipe(pipe1);
     int resPipe1[2];
     pipe(resPipe1);

     pid_t pid = fork();
     checkFork(pid);
 if(pid == 0) {
     //gyerek
     ChildrenDuty(pipe1, resPipe1);
 } else {
     int pipe2[2];
     pipe(pipe2);
     int resPipe2[2];
     pipe(resPipe2);
     pid_t pid2 = fork();
     checkFork(pid2);
     if(pid2 == 0) {
         //2.gyerek
         close(pipe1[0]);
         close(pipe1[1]);
         close(resPipe1[0]);
         close(resPipe1[1]);
         ChildrenDuty(pipe2, resPipe2);
     } else {
         //mama
         int cities1[] = {1, 2, 4, 7};
         PassingNameToChild(pipe1, cities1, 4);
         int cities2[] = {3,5,6};
         PassingNameToChild(pipe2, cities2, 3);
         wait(NULL);
         wait(NULL);
         Result region1Max = RegionMax(resPipe1);
         Result region2Max = RegionMax(resPipe2);
         if(region1Max.number > region2Max.number) {
             printf("A gyoztes nem más mint %s, %d ponttal!\n ",region1Max.name, region1Max.number);
         } else if(region1Max.number < region2Max.number) {
             printf("A gyoztes nem más mint %s, %d ponttal!\n ",region2Max.name, region2Max.number);
         } else {
             printf("Dontetlen volt :C\n ");

         }
     }
 }
}

Result RegionMax(const int *resPipe) {
    Result temp;
    close(resPipe[1]);
    Result maximax;
    maximax.number=0;
    while(read(resPipe[0], &temp, sizeof(Result)) > 0) {
       if(maximax.number < temp.number) {
           maximax.number = temp.number;
           strcpy(maximax.name,temp.name);
       }
    }
    return maximax;
}

void ChildrenDuty(const int *pipe1, const int *resPipe1) {
    srand(time(NULL) + (getpid())); // hozzadadjuk a process id t
    sleep(1);
    close(pipe1[1]);
    close(resPipe1[0]);
    Result res;
    while(read(pipe1[0], res.name, 150*sizeof(char)) > 0) {
        res.number = rand()%100+1;
        write(resPipe1[1], &res, sizeof(Result));
        printf("%s %d\n", res.name, res.number);
    }
    close(pipe1[0]);
    close(resPipe1[1]);
    exit(0);
}

void PassingNameToChild(const int *pipe1, int ctities[], int n) {
    FILE *in_file = fopen("rabbits.txt", "r");
    close(pipe1[0]);
    char name[150];
    int city;
    int entryTimes;
    char TmpString[150];
    while (!feof(in_file))
    {
        fgets(name, 150, in_file);
        name[strcspn(name, "\n")] = 0;

        fgets(TmpString, 150, in_file);
        sscanf(TmpString, "%d", &city);

        fgets(TmpString, 150, in_file);
        sscanf(TmpString, "%d", &entryTimes);

       if(contains(city, ctities, n)) {
           write(pipe1[1], name, 150*sizeof(char));
       }
    }
    fclose(in_file);
    close(pipe1[1]);
}

    bool contains(int city, int* arr, int n) {
    for(int i=0; i<n; i++) {
        if(city == arr[i]) {
            return true;
        }
    }
    return false;
}

int SaveRabbit() {
    FILE *out_file = fopen("rabbits.txt", "a");
    int operationVaros;
    int alkalom;
    char *m = ReadName();
    // nyuszi varos hozzaadas
    //--------------------
    printf("Melyik varosban indul:\n");
    printf("1.Baratfa\n2.Lovas\n3.Szula\n4.Kigyos-patak\n5.Malom telek\n6.Paskom\n7.Kaposztas kert\n");
    scanf("%d", &operationVaros);
    int cityIsFalse=ChoseWitchCity(operationVaros, m, out_file);
    if(cityIsFalse==0){
        fclose(out_file);
        return 1;
    } else {
        // nyuszi alkalom hozzaadas
        //--------------------
        printf("Hanyadik alkalommal indul a versenyen?\n");
        scanf("%d", &alkalom);
        fprintf(out_file, "\n%d", alkalom);
        fclose(out_file);
        return 0;
    }
}

void DeleteRabbit() {
    int firstprint = 0;
    char singleline[150];
    FILE *in_file = fopen("rabbits.txt", "r");
    FILE *out_file = fopen("rabbitstmp.txt", "w");
    char *m = ReadName();
    int cntr = 0;
    while (!feof(in_file))
    {
        fgets(singleline, 150, in_file);
        singleline[strcspn(singleline, "\n")] = 0;
        if (strcmp(singleline, m) == 0)
        {
            cntr++;
        }
        else if (cntr == 1)
        {
            cntr++;
        }
        else if (cntr == 2)
        {
            cntr = 0;
        }
        else
        {
            if (firstprint == 0)
            {
                fprintf(out_file, "%s", singleline);
                firstprint++;
            }
            else
            {
                fprintf(out_file, "\n%s", singleline);
            }
        }
    }
    free(m);
    fclose(in_file);
    fclose(out_file);
}

void printMenu() {
    printf("---------------------------------------------------------\n");
    printf("1. Nyul hozzaadasa\n");
    printf("2. Nyul torlese\n");
    printf("3. Nyul modositasa\n");
    printf("4. Nyulak listazasa\n");
    printf("5. Nyulak listazasa teruleti alapon\n");
    printf("6. Gyoztes?!\n");
    printf("0. Kilepes\n");
}

char *inputString(FILE *fp, size_t size)
{
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str) * size);
    if (!str)
        return str;
    while (EOF != (ch = fgetc(fp)) && ch != '\n')
    {
        str[len++] = ch;
        if (len == size)
        {
            str = realloc(str, sizeof(*str) * (size += 16));
            if (!str)
                return str;
        }
    }
    str[len++] = '\0';

    return realloc(str, sizeof(*str) * len);
}

int ChoseWitchCity(int operationVaros, char *m, FILE *out_file) {
    switch (operationVaros)
    {

        case 1:
            fprintf(out_file, "\n%s", m);
            free(m);
            fprintf(out_file, "\n%d", 1);
            return 1;
        case 2:
            fprintf(out_file, "\n%s", m);
            free(m);
            fprintf(out_file, "\n%d", 2);
            return 1;
        case 3:
            fprintf(out_file, "\n%s", m);
            free(m);
            fprintf(out_file, "\n%d", 3);
            return 1;
        case 4:
            fprintf(out_file, "\n%s", m);
            free(m);
            fprintf(out_file, "\n%d", 4);
            return 1;
        case 5:
            fprintf(out_file, "\n%s", m);
            free(m);
            fprintf(out_file, "\n%d", 5);
            return 1;
        case 6:
            fprintf(out_file, "\n%s", m);
            free(m);
            fprintf(out_file, "\n%d", 6);
            return 1;
        case 7:
            fprintf(out_file, "\n%s", m);
            free(m);
            fprintf(out_file, "\n%d", 7);
            return 1;
        default:
            free(m);
            printf("Adatbeviteli hiba\n");
            return 0;
    }
}

void ListRabbits() {
    FILE *in_file = fopen("rabbits.txt", "r");
    char singleline[150];
    while (!feof(in_file))
    {
        fgets(singleline, 150, in_file);
        singleline[strcspn(singleline, "\n")] = 0;
        printf("%s, ", singleline);
        fgets(singleline, 150, in_file);
        singleline[strcspn(singleline, "\n")] = 0;
        printf("%s, ", singleline);
        fgets(singleline, 150, in_file);
        singleline[strcspn(singleline, "\n")] = 0;
        printf("%s\n", singleline);
    }
}

void ListRabbitsByCities() {
    FILE *in_file = fopen("rabbits.txt", "r");
    char singleline[150];
    char saveTheName[150];
    char inttostringhelper[150];
    for (int i = 1; i < 8; i++)
    {
        while (!feof(in_file))
        {
            fgets(singleline, 150, in_file);
            singleline[strcspn(singleline, "\n")] = 0;
            strcpy(saveTheName, singleline);

            fgets(singleline, 150, in_file);
            singleline[strcspn(singleline, "\n")] = 0;
            sprintf(inttostringhelper, "%d", i);
            if (strcmp(singleline, inttostringhelper) == 0)
            {
                printf("%s, ", saveTheName);
                printf("%s, ", singleline);
                fgets(singleline, 150, in_file);
                singleline[strcspn(singleline, "\n")] = 0;
                printf("%s\n", singleline);
            }
            else
            {
                fgets(singleline, 150, in_file);
                singleline[strcspn(singleline, "\n")] = 0;
            }
        }
        rewind(in_file);
    }
}
