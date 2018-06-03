#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SHMSZ 27

void main(){
	int shmid,i;
	key_t key;
	char *shm,*s;
	key=1000;
    shmid=shmget(key,SHMSZ, IPC_CREAT | 0666);
	if(shmid< 0){
		perror("shmget");
		exit(1);
	}
    shm=shmat(shmid,NULL,0);
	if(shm==(char*)-1){
		perror("shmat");
		exit(1);
	}

	*shm='!';
	while(*shm!='*'){
		char a[1024];
		printf("%s*","Message: ");
        for(s=shm+1;*s!='\n'; s++)
    		putchar(*s);
		putchar('\n');
		fgets(a,100,stdin);
        if (a[0]!='*'){
		    s=shm+1;
		    for(i=0;i<strlen(a);i++)
			    *s++=a[i];	
            *shm='!';
        }
		else {
            *shm='*';
            printf(" %s","connection closed by client");
        }
        while(*shm=='!')
            sleep(1);   
			
	}
        
		shmid=shmdt(shm);
		exit(0);
}
