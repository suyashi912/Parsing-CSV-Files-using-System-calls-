#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>

extern int errno;

int read_csv(char *a); 
int main()
{
	pid_t pid, wpid; 
	pid = fork(); 
	int status ;  
	if(pid==0) 
	{
		read_csv("A"); 
		exit(0); 
	}

	else if(pid>0)
	{

	 	wpid = waitpid(pid, &status, 0);
	 	if(waitpid<0)
	 	{
	 		printf("Error: %s", strerror(errno)); 
	 		return 0; 								//Error handling for waitpid()
	 	}
	 	if(WIFSIGNALED(status))
	 	{
	 		psignal(WTERMSIG(status), " : Exit signal"); 
	 	}
		read_csv("B");  
	}
	else 
	{
		printf("Error : %s \n", strerror(errno));
		return 0 ; 								    // Error handling for fork 
	}
	return 0; 

}

int read_csv(char *a)
{

	char q1[100] = ("The details for section "); 
	strcat(q1, a); 
	int w = 0; 
	strcat(q1, " are as follows: \n\n");
	w = write(1, q1, strlen(q1)+1);
	if(w==-1)			//Error handling for write 
	{
		printf("Error in write: %s \n", strerror(errno));
	}
	int f = open("csv-os.csv", O_RDONLY);
	if(f<0)					//Error handling for open system call 
	{
		printf("Error in opening file %s \n ", strerror(errno));
		return 0; 
	}
	
	int size = lseek(f, 0, SEEK_END); 
	if(size == (off_t)-1)		//Error handling for lseek 
	{
		printf("Error: %s\n", strerror(errno)); 
		return 0; 
	}
	int line = lseek(f, 90, SEEK_SET);
	if(line ==(off_t)-1)
	{
		printf("Error: %s\n", strerror(errno)); 
		return 0; 
	}
	char s[size]; 
	line = read(f, s, size); 
	if(line == -1)			//Error handling for read system call 
	{
		printf("Error in reading file: %s\n", strerror(errno));
		return 0; 
	}
		char *r, *r1, average[10], c[10]; 
		char s1[100]; 
		int chk = -1;
		int sum = 0; 
		float avg = 0; 
		int col = 0, row = 0; 
		char q[410][410]; 
		int count =0; 
		for(r = strtok(s, "\n"); r!=NULL; r = strtok(NULL, "\n"))
		{
				 
				strcpy(q[col], r); 
				col++;

		}
		int columnNo =0; 
		char p1[410] ; 
		char name[200]; 
		for(int i=0; i<400; i++)
		{
			columnNo = 0; 
			sum = 0; 
			avg = 0;  
			w = 0; 
			strcpy(p1, q[i]); 

			for(r1 = strtok(q[i], " "); r1!=NULL; r1 = strtok(NULL, " "))
				{
					columnNo++;
					if(columnNo == 1)
					{
						strcpy(name, r1); 
					}
					if(columnNo == 2)
					{
						chk = strcmp(r1, a);
					}
					if(chk == 0 && columnNo ==2)
					{
						count ++; 
						printf("%d) Student ID --> %s          ", count , name);
						printf("Section --> %s\n", a);
						printf("Marks : "); 
					}

					if(columnNo>2 && chk == 0)
					{
						printf("%s, ", r1);
						sum = sum + atoi(r1); 
					}
				
				}
				avg = (float)sum/4;
				sprintf(average, "%.2f", avg);
				

			if(chk == 0)
			{   
				printf("          Average marks - %s\n\n", average);
				
			}	
		}
		printf("\n");
	if(close(f) == -1)			//Error handling for close 
	{
		printf("Error in closing file: %s\n", strerror(errno));
	} 
	return 0; 
}