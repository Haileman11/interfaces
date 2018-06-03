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

	if((shmid=shmget(key,SHMSZ,0666))<0){
		perror("shmget");
		exit(1);
	}
	if((shm=shmat(shmid,NULL,0))== (char *) -1){
		perror("shmat");
		exit(1);
	}
	*shm='#';
	while(*shm!='*'){
			printf("server: ");
			for(s=shm+1;*s!='\n';s++)
			putchar(*s);
			putchar('\n');
			char a[100];
			printf("Message: ");
			fgets(a,100,stdin);
			if(a[0]!='*'){
				s=shm+1;
				for(i=0;i<strlen(a);i++)
					*s++=a[i];
				*shm='#';
			} else
				*shm='*';
            while(*shm=='#')
                sleep(1);
	}
	printf("%s","connection closed by server");		
	shmid=shmdt(shm);
	exit(0);
}


