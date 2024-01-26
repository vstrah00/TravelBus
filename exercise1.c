//Created by
//Vito Strahinjic and Duje Perisin

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define getName(var)  #var 

void printData(char* name) {
	printf("My name is %s, my id is %d and my parents ID is %d.\n", name, getpid(), getppid());
}


int main() {
	pid_t p0 = 0, p1 = 0, p2 = 0, p3 = 0, p4 = 0, p5 = 0, p6 = 0;

	p1 = fork();
	if (p1 != 0) {
		//we are in p0
		p0=getpid();
		waitpid(p1, NULL, 0);
		printData(getName(p0));
		if (fork() == 0) {
			//in p2
			int fd[2];
			if (pipe(fd) == -1) {                       //opening pipe so p5 can share its id with p2
				printf("ERROR opening pipe\n");     //since they are not directly related
			}


			if (fork() == 0) {
				//in p4
				printData(getName(p4));
				if (fork() == 0) {
					//in p5
					p5 = getpid();
					close(fd[0]);
					write(fd[1], &p5, sizeof(pid_t));
					close(fd[1]);
					printData(getName(p5));
				}
			}
			else {
				//we are still in p2 here
				if (fork() == 0) {
					//in p6 now
					printData(getName(p6));
				}
				else {
					//still in p2
					close(fd[1]);
					read(fd[0], &p5, sizeof(pid_t));
					waitpid(p5, NULL, 0);               //waiting for p5
					wait(NULL);                        //waiting for p4 or p6
					printData(getName(p2));
				}
			}
		}
	}
	else {
		//in p1
		printData(getName(p1));
		if (fork() == 0) {
			//in p3
			printData(getName(p3));
		}
	}
	
	if(p0==getpid()){
	    //back in p0
	    execlp("cat", "cat", __FILE__, NULL);
	}

	return 0;
}