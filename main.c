#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>

#include "hexdump.h"
int main(int argc, char *argv[])
{
    int fd;
    struct stat stFileStat;
    char *pucBuf = NULL;
    unsigned int uiBufSize=0;
    int x=0;

    if ((argc<0) | (argc>2)){
	printf("Usage: hexdump filename\n");
	return 0;
    }

    if((fd=(open(argv[1], O_RDONLY))) < 0){
	perror("open");
	goto lException;
    }

    if(fstat(fd, &stFileStat) < 0){
	perror("fstat");
	goto lException;
    }

    if( (uiBufSize = (unsigned int)(stFileStat.st_size)) > 0){
	pucBuf=malloc(uiBufSize * sizeof(char));
	if((x = read(fd, pucBuf, uiBufSize)) < 0){
	    perror("read");
	    goto lException;    
	}
	else
	    hexdump(pucBuf, uiBufSize);
    }
    else{
	printf("Zero length file\n");
	goto lException;
    }
    
    printf("\n");
    free(pucBuf);
    close(fd);
    return 0;    

lException:
    printf("Exiting...\n");
    if(pucBuf != NULL)
	free(pucBuf);
    close(fd);
    return -1;

}


