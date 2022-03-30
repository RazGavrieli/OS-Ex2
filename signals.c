#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
void sig_handler(int signum)
{
	int zero=0;
	
    char *text = ">>>T<<<";
    if (signum == SIGCHLD) {
        printf("1.\tSIGCHLD handled\n");
		printf("prepare for alarm!\n");
		alarm(3);
		printf("\t3.. \n");
		sleep(1);
		printf("\t2.. \n");
		sleep(1);
		printf("\t1.. \n");
		sleep(1);
    } else if (signum == SIGALRM) {
		printf("2.\tSIGALARM handled\n");
		printf("lets replace T: %s\n", text);
		printf("\t3.. \n");
		sleep(1);
		printf("\t2.. \n");
		sleep(1);
		printf("\t1.. \n");
		sleep(1);
		text[3] = 'A';
	} else if (signum == SIGSEGV) {
        printf("3.\tSIGSEGV handled\n");
		printf("lets calculate: 5/0\n");
		printf("\t3.. \n");
		sleep(1);
		printf("\t2.. \n");
		sleep(1);
		printf("\t1.. \n");
		sleep(1);
		int x = 5/zero;
    } else if (signum == SIGFPE) {
		printf("4.\tSIGFPE handled\n");
		printf("lets terminate the program using system call 'kill'\n");
		printf("\t3.. \n");
		sleep(1);
		printf("\t2.. \n");
		sleep(1);
		printf("\t1.. \n");
		sleep(1);
		kill(getpid(), 15);
		
	} else if (signum == SIGTERM) {
		printf("5.\tSIGTERM handled\n");
		printf("lets raise our own user defiend signal\n");
		printf("\t3.. \n");
		sleep(1);
		printf("\t2.. \n");
		sleep(1);
		printf("\t1.. \n");
		sleep(1);
		raise(10 /*= SIGUSR1*/);
	} else if (signum == SIGUSR1) {
		printf("6.\tSIGUSR1 handled\n");
		printf("press CTRL+C!\n");
		while (1) {
			sleep(1);
			printf("press CTRL+C!\n");
		}
	}else if(signum == SIGINT){
		printf("   7.\tSIGINT handled\n");
		printf("program has terminated by ctrl+c, have a nice day(:\n");
		exit(EXIT_SUCCESS);

	}
}

int main(void){
	int status;
	signal (SIGCHLD, sig_handler);
	signal (SIGSEGV, sig_handler);
	signal (SIGFPE, sig_handler);
	signal (SIGALRM,sig_handler);
	signal (SIGTERM,sig_handler);
	signal (SIGUSR1,sig_handler);
	signal (SIGINT,sig_handler);


	if (!(fork())) {
        exit(1);
	}
	wait(&status);

	
	return 0;
}


