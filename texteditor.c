#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]){
	
	if(!argv[1]) {
		printf("File argument is missing.\nPlease specify the file you want to access.\n");
		return 0;
	}
	printf("\n\n\n\n\t\tBonjour!! WELCOME TO ESPRESSO TEXT\n\nPress 'h' for help or any valid command to continue.\n");
	char * fileName = argv[1];
	char * mode = "w+";
	FILE * readS = fopen(fileName,mode);				//printf("%p",readS); Stream is correctly opened.
	char ** bufferArray = (char**) malloc(sizeof(char*)*10);
	int count = 0;
	while(count<10){
		bufferArray[count]=NULL;
		//printf("%p %s", &bufferArray[count], bufferArray[count]);
		count++;
	}
	count=0;
	size_t capacity=0;
	while(count<10)
	{
		capacity=0;
		int x = getline(&bufferArray[count], &capacity, readS);
		if(x == -1) break;
		//printf("%s %d", bufferArray[count],count);
		count++;
	}		

							/* for(int i=0;i<10;i++)
								{
									if(bufferArray[i]!=NULL) printf("%s", bufferArray[i]);
								} This loop was used to check if the entire file is being read */
	int flag = 1;
	while(flag){
		char* buffer = (char*) malloc(sizeof(char*));
		size_t cap = 0;
		getline(&buffer,&cap,stdin);
		char firstC[1];
		//char m[999];
		int result = sscanf(buffer, "%s",firstC);
		//printf("Result: %s", firstC);
		if(firstC[0]=='q'){printf("\nExiting the program....\n");flag = 0;}

		else if (firstC[0]=='p') {
			printf("\n\t\tContents of the File:\n");
			for(int i=0;i<10;i++){
				if(bufferArray[i])printf("%d %s", i+1 , bufferArray[i]);}
				printf("\n");
			for(int i=0;i<10;i++){
				if(!bufferArray[i])printf("%d\n", i+1);}
				printf("\n");
			}
		
		else if(firstC[0]=='a'){
			char *line = &buffer[4];
			int lineNo;	
			int res = sscanf(buffer, "%1s %d", firstC, &lineNo);
			//printf("%d",strlen(line));
			//printf("\n%d %s \n", lineNo, line);
			char *appStr;
			if(!bufferArray[lineNo-1]) {
					appStr = (char*) malloc (strlen(line) + 2);
					strcat(appStr, line);
				}
			else {
				appStr = (char*) malloc (strlen(bufferArray[lineNo-1])+strlen(line) +1);
				strcpy (appStr, bufferArray[lineNo-1]);
				appStr[strlen(appStr)-1]=0;
				strcat (appStr, line);
			}	
			printf("The new string after appending is: %s\n", appStr);
			free(bufferArray[lineNo-1]);
			bufferArray[lineNo-1] = appStr;
			//printf("%s", bufferArray[lineNo-1]);
			free(appStr);
		}

		else if(firstC[0]=='/'){
			char *lineFind = &buffer[2];
			lineFind[strlen(lineFind)-1]=0;
			for(int j=0;j<10;j++){
				if(bufferArray[j]){
					char *val = strstr(bufferArray[j], lineFind);
					if(val) printf("\n%d %s", j+1 , bufferArray[j]);
					//printf("%s", bufferArray[j]);
 				}
			}
			printf("\n");
 			//printf("%s....", lineFind);
		}
		else if(firstC[0]=='w'){
			FILE * writeS = fopen(fileName,"w");
			for(int k=0;k<10;k++){
				if(bufferArray[k]){
					fprintf(writeS, "%s", bufferArray[k]);
				}
			}
			printf("Successfully written to file %s\n\n", fileName);
			fclose(writeS);
			readS = fopen(fileName, "r");
		}
		else if(firstC[0]=='h'){
			printf("\n\tList of Commands for Espresso Text:\n \np : Print the first 10 lines of the file\nw : Write to file \na : Append string to given line. Caution: Does not put a space before appending.    Usage: a lineNo TEXT_TO_APPEND\n\\ : Searches the file and prints out all lines that contain the string following \\. Usage: \\ STRING_TO_FIND\nq : Quit Espresso Text\n\n");
		}

	

	}

	while(bufferArray[count]!=NULL){
		free(bufferArray[count]);
		bufferArray[count]=NULL;
		count++;
	}
	
	free(bufferArray);
	fclose(readS);
	//printf("%s\n" , strin);	
	return 0;

}