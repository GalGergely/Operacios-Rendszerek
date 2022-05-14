#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


int main(int argc, char *argv[])
{
    int fd;
    char pipename[] = {"/tmp/jo3em3_pipe"};
    int fid = mkfifo(pipename, S_IRUSR | S_IWUSR); // creating named pipe file
    if (fid == -1)
    {
        printf("Error number: %i", errno);
        perror("Gaz van:");
        exit(EXIT_FAILURE);
    }
    printf("Csonyitas eredmenye fogadoban: %d!\n", fid);
    fd = open(pipename, O_RDONLY);
    int number = -1;
    while (number != 0)
    {
        read(fd, &number, sizeof(int));
        printf("Ezt olvastam a csobol: %d \n", number);
    }

    close(fd);
    unlink(pipename);
    return 0;
}
