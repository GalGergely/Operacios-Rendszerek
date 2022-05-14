#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h> // for errno, the number of last error

int int_read()
{
    printf("Kerek egy szamot.\n");
    int number = -1;
    int result = scanf("%d", &number);
    if (result == 0)
    {
        printf("Helytelen\n");
    }
    else if (result == 1)
    {
        printf("Sikeres: %d\n", number);
    }
    while (fgetc(stdin) != '\n');
    return number;
}
int main(int argc, char *argv[])
{
    int fd;
    char pipename[20];
    sprintf(pipename, "/tmp/jo3em3_pipe", getpid());

    int number = -1;
    fd = open(pipename, O_WRONLY);
    while (number != 0)
    {
        number = int_read();
        write(fd, &number, sizeof(int));
        printf("Gyerek vagyok, beirtam a kovetkezo szamot: %d!\n", number);
    }

    close(fd);

    return 0;
}
