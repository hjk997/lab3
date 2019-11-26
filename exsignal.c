#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void p_handler(int signo);
int i;

main(){
	pid_t pid;
	struct sigaction act;
	i=0;

	pid = fork();
	if(pid==0){

		while(1){
			sleep(1);
			i = i + 1;
			printf("sleep for %d sec(s).\n", i);
		}
	}
	else if (pid>0){
		act.sa_handler = p_handler;
		sigfillset(&(act.sa_mask));
		sigaction(SIGINT, &act, NULL);

		while(1){
			printf("next\n");
			sleep(1);
		}
	}
	else
		perror("Error");
}

void p_handler(int signo){
	printf("exit\n");
	exit(1);
}
