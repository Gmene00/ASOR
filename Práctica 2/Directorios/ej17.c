#undef _POSIX_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char ** argv) {
	DIR * directorio;
	struct dirent * entry;
	int tam = 0;
	char path[PATH_MAX];
	int bytes;

	if (argc != 2) {
		printf("Argumentos incorrectos\n");
		return -1;
	}
	directorio = opendir(argv[1]);
	if (directorio == NULL) {
		perror("Error");
		return -1;
	}
    /*
        struct dirent {
            ino_t          d_ino;       // inode number 
            off_t          d_off;       // offset to the next dirent 
            unsigned short d_reclen;    // length of this record 
            unsigned char  d_type;      // type of file; not supported by all file system types 
            char           d_name[256]; // filename 
        };
    */
    struct stat ino;
	while ((entry = readdir(directorio)) != NULL) {
		printf("%s", entry->d_name);
		if (entry->d_type == DT_REG) {
            stat(entry->d_name, &ino);
            if(S_IEXEC==ino.st_mode||
				S_IXGRP==ino.st_mode||
				S_IXOTH==ino.st_mode){
                printf("*");
            }
			printf("\n");
			tam += entry->d_reclen;
		}
		if (entry->d_type == DT_DIR) {
			printf("/\n");
		}
		if (entry->d_type == DT_LNK) {
			if ((bytes = readlink(entry->d_name, path, PATH_MAX)) == -1) {
				printf("Error readlink");
				return -1;
			}
			path[bytes] = '\0';
			printf("->%s\n", path);
		}	
	
	}
	printf("Tamaño total: %d kbytes\n", tam);
	closedir(directorio);
	return 0;
}