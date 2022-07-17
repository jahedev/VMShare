#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

int file_exists(char *pathToFile);
void cat_file(char *pathToFile);


int main(int argc, char **argv) {
	if (argc <= 1) {
		printf("my_cat: No such file name or path was provided.\n");
	}

	for (int i = 1; i < argc; i++) {
		char *fileName = argv[i];
		if (!file_exists(fileName)) {
			printf("my_cat: %s: No such file or directory.\n", fileName);
			exit(EXIT_FAILURE);
		}

		cat_file(fileName);
	}

	exit(EXIT_SUCCESS);
}

int file_exists(char *pathToFile) {
	if( access(pathToFile, F_OK ) == 0 ) {
	    return true;
	}

	return false;
}

void cat_file(char *pathToFile) {
	FILE * file;
	file = fopen(pathToFile, "r");

	char line[4*1024];

	while(true) {
		fgets(line, 4*1024, file);
		if (feof(file)) break;

		printf("%s", line);
	}
	printf("\n");

	fclose(file);
}

