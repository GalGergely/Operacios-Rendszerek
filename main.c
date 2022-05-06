#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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
int main()
{

    while (true)
    {
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
        FILE *out_file3;
        char singleline[150];
        char saveTheName[150];
        char inttostringhelper[150];
        // menu
        //--------------------
        printf("---------------------------------------------------------\n");
        printf("1. Nyul hozzaadasa\n");
        printf("2. Nyul torlese\n");
        printf("3. Nyul modositasa\n");
        printf("4. Nyulak listazasa\n");
        printf("5. Nyulak listazasa teruleti alapon\n");
        printf("0. Kilepes\n");
        fflush(stdin);
        scanf("%d", &operation);
        switch (operation)
        {
        case 1:
            // nyuszi nev hozzaadas
            //--------------------
            fflush(stdin);
            printf("Nev: ");
            scanf("%d", stdin);
            m = inputString(stdin, 10);
            // nyuszi varos hozzaadas
            //--------------------
            printf("Melyik varosban indul:\n");
            printf("1.Baratfa\n2.Lovas\n3.Szula\n4.Kigyos-patak\n5.Malom telek\n6.Paskom\n7.Kaposztas kert\n");
            scanf("%d", &operationVaros);
            switch (operationVaros)
            {
            case 1:
                fprintf(out_file, "\n%s", m);
                free(m);
                fprintf(out_file, "\n%d", 1);
                break;
            case 2:
                fprintf(out_file, "\n%s", m);
                free(m);
                fprintf(out_file, "\n%d", 2);
                break;
            case 3:
                fprintf(out_file, "\n%s", m);
                free(m);
                fprintf(out_file, "\n%d", 3);
                break;
            case 4:
                fprintf(out_file, "\n%s", m);
                free(m);
                fprintf(out_file, "\n%d", 4);
                break;
            case 5:
                fprintf(out_file, "\n%s", m);
                free(m);
                fprintf(out_file, "\n%d", 5);
                break;
            case 6:
                fprintf(out_file, "\n%s", m);
                free(m);
                fprintf(out_file, "\n%d", 6);
                break;
            case 7:
                fprintf(out_file, "\n%s", m);
                free(m);
                fprintf(out_file, "\n%d", 7);
                break;
            default:
                free(m);
                printf("Adatbeviteli hiba\n");
                return 0;
            }
            // nyuszi alkalom hozzaadas
            //--------------------
            printf("Hanyadik alkalommal indul a versenyen?\n");
            scanf("%d", &alkalom);
            fprintf(out_file, "\n%d", alkalom);
            fclose(out_file);
            break;

        case 2:
            // nyuszi torles
            //--------------------
            firstprint = 0;
            in_file = fopen("rabbits.txt", "r");
            out_file2 = fopen("rabbitstmp.txt", "w");
            out_file3 = fopen("rabbitstmpdeleted.txt", "w");
            printf("Nev: ");
            fflush(stdin);
            scanf("%d", stdin);
            m = inputString(stdin, 10);
            cntr = 0;
            while (!feof(in_file))
            {
                fgets(singleline, 150, in_file);
                singleline[strcspn(singleline, "\n")] = 0;
                if (strcmp(singleline, m) == 0)
                {
                    fprintf(out_file3, "\n%s", singleline);
                    cntr++;
                }
                else if (cntr == 1)
                {
                    fprintf(out_file3, "\n%s", singleline);
                    cntr++;
                }
                else if (cntr == 2)
                {
                    fprintf(out_file3, "\n%s", singleline);
                    cntr = 0;
                }
                else if (strcmp(singleline, "\n") == 0)
                {
                    fprintf(out_file3, "\n%s", singleline);
                }
                else
                {
                    if (firstprint == 0)
                    {
                        fprintf(out_file2, "%s", singleline);
                        firstprint++;
                    }
                    else
                    {
                        fprintf(out_file2, "\n%s", singleline);
                    }
                }
            }
            free(m);
            fclose(in_file);
            fclose(out_file2);
            fclose(out_file3);
            // temperary filek eltakaritasa es kicsere az eredetire
            //--------------------
            remove("rabbitstmpdeleted.txt");
            in_file = fopen("rabbitstmp.txt", "r");
            out_file2 = fopen("rabbits.txt", "w");
            c = fgetc(in_file);
            while (c != EOF)
            {
                fputc(c, out_file2);
                c = fgetc(in_file);
            }

            fclose(in_file);
            fclose(out_file2);
            remove("rabbitstmp.txt");
            break;

        case 3:
            // nyuszi modositas
            //--------------------
            fflush(stdin);
            printf("Nev: ");
            scanf("%d", stdin);
            m = inputString(stdin, 10);
            in_file = fopen("rabbits.txt", "r");
            out_file2 = fopen("rabbitstmp.txt", "w");
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
                        fflush(stdin);
                        printf("Milyen nevre szeretnel modositani?\nNev: ");
                        scanf("%d", stdin);
                        m2 = inputString(stdin, 10);
                        fprintf(out_file2, "\n%s", m2);
                        free(m2);
                        break;
                    case 2:
                        fprintf(out_file2, "\n%s", singleline);
                        fgets(singleline, 150, in_file);
                        printf("Melyik varosban indul:\n");
                        printf("1.Baratfa\n2.Lovas\n3.Szula\n4.Kigyos-patak\n5.Malom telek\n6.Paskom\n7.Kaposztas kert\n");
                        scanf("%d", &operationVaros);
                        switch (operationVaros)
                        {
                        case 1:
                            fprintf(out_file2, "\n%d", 1);
                            break;
                        case 2:
                            fprintf(out_file2, "\n%d", 2);
                            break;
                        case 3:
                            fprintf(out_file2, "\n%d", 3);
                            break;
                        case 4:
                            fprintf(out_file2, "\n%d", 4);
                            break;
                        case 5:
                            fprintf(out_file2, "\n%d", 5);
                            break;
                        case 6:
                            fprintf(out_file2, "\n%d", 6);
                            break;
                        case 7:
                            fprintf(out_file2, "\n%d", 7);
                            break;
                        default:
                            free(m);
                            printf("Adatbeviteli hiba\n");
                            return 0;
                        }
                        break;
                    case 3:
                        fflush(stdin);
                        fprintf(out_file2, "\n%s", singleline);

                        fgets(singleline, 150, in_file);
                        singleline[strcspn(singleline, "\n")] = 0;
                        fprintf(out_file2, "\n%s", singleline);

                        printf("Hanyadik alkalommal indul a versenyen?\n");
                        scanf("%d", &alkalom);
                        fprintf(out_file2, "\n%d", alkalom);
                        fgets(singleline, 150, in_file);
                        fflush(stdin);
                        break;
                    default:
                        printf("Na hat ez nem sikerult.\n");
                    }
                }
                else
                {
                    fprintf(out_file2, "\n%s", singleline);
                }
            }
            fclose(in_file);
            fclose(out_file2);
            firstprint = 0;
            in_file = fopen("rabbitstmp.txt", "r");
            out_file2 = fopen("rabbits.txt", "w");
            out_file3 = fopen("rabbitstmpdeleted.txt", "w");
            c = fgetc(in_file);
            while (c != EOF)
            {
                if (firstprint == 0)
                {
                    fputc(c, out_file3);
                    c = fgetc(in_file);
                    firstprint++;
                }
                fputc(c, out_file2);
                c = fgetc(in_file);
            }
            fclose(in_file);
            fclose(out_file2);
            fclose(out_file3);
            free(m);
            remove("rabbitstmp.txt");
            remove("rabbitstmpdeleted.txt");
        case 4:
            // listazas, kedvencem
            //--------------------
            in_file = fopen("rabbits.txt", "r");
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
            fclose(in_file);
            break;
        case 5:
            // listazas varos szerint
            //--------------------
            in_file = fopen("rabbits.txt", "r");
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
            fclose(in_file);
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