#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/dir.h> 
#include <dirent.h> 
#include <string.h> 
#include <stdlib.h> 
#include <math.h> 

#define FILE_LENGTH 256 
#define PATH_LENGTH 2048 
#define SEARCH_DEPTH 8 

int searchfile(char *fileName, char *dirName, int depth, char* result) 
{ 
	DIR *dir = opendir(dirName);  

	struct dirent *use ; 
	struct stat buf; 
	char *end = strchr(dirName, '\0'); 
	while ((use = readdir(dir)) != NULL) 
	{ 
		char path[PATH_LENGTH] = "";
		strcpy(path, dirName);
		strcat(path, "/");
		strcat(path, use->d_name);
		
		stat(path, &buf); 

		if (S_ISREG(buf.st_mode) && strcmp(fileName, use->d_name) == 0)
		{ 
			
			strcpy(result, path);
			return 1; 
		} 
		if (S_ISDIR(buf.st_mode) && strcmp(use->d_name, ".") != 0 && strcmp(use->d_name, "..") != 0) 
		{ 
			if (searchfile(fileName, path, depth - 1, result)) return 1;  
		} 
	} 

	return 0; 
} 



int main(int argc, char *argv[]) 
{ 
	char s[FILE_LENGTH], way[PATH_LENGTH] = "", result[PATH_LENGTH] = ""; 

	int maxDepth = SEARCH_DEPTH; 
	if (argc > 1) 
	{ 
		strcpy(s, argv[1]); 
		strcpy(way, argv[3]);
		if (argc > 2) 
			maxDepth = atoi(argv[2]); 
	} 
	else 
	{ 
		printf("Enter name of file to be searched:\n"); 
		scanf("%s", s); 
	} 

	if (searchfile(s, way, maxDepth, result) > 0) 
		printf("%s\n", result); 
	else 
		printf("No such file or directory.\n"); 

	return 0; 
}
