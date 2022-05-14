#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //fork
#include <sys/wait.h> //waitpid
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void handler(int signumber){

}

typedef struct message
{
    long msg_type;
    char msg_text [1024];
} message;

int send(int mq, message msg)
{
    int status;
    status = msgsnd(mq, &msg,  sizeof(msg.msg_text), 0 );

    if ( status < 0 )
        perror("msgsnd");
    return 0;
}

int recive(int mq)
{
    message msg;
    int status;
    status = msgrcv(mq, &msg, sizeof(msg.msg_text), 5, 0 );

    if ( status < 0 )
        perror("msgsnd");
    else
        printf( "A kapott terület:  %s\n",  msg.msg_text);
    return 0;
}

int main(int argc, char** argv[])
{
    pid_t child1, child2;
    int msg_queue1, msg_queue2;

    key_t key;

    key = ftok(argv[0], 1);
    msg_queue1 = msgget(key, 0600 | IPC_CREAT);
    key = ftok(argv[0], 2);
    msg_queue2 = msgget(key, 0600 | IPC_CREAT);
    signal(SIGTERM, handler);

    child1=fork();
    if (child1>0)
        child2=fork();

    if (child1==0)
    {
        sleep(1);
        kill(getppid(), SIGTERM);

        char* area;

        printf("Child1's area: ");
        recive(msg_queue1);
        exit(EXIT_SUCCESS);
    }
    else if(child2==0)
    {
        sleep(1);
        kill(getppid(), SIGTERM);

        char* area;

        printf("Child2's area: ");
        recive(msg_queue2);
        exit(EXIT_SUCCESS);
    }
    else // Főnyuszi
    {
        pause();
        pause();

        const message msg_1 = { 5, "Lovas" };
        send(msg_queue1,msg_1);

        const message msg_2 = { 5, "Nemtom" };
        send(msg_queue2,msg_2);

        int status;
        wait(&status);
        exit(EXIT_SUCCESS);
    }

    return 0;
}