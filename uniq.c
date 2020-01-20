#include "types.h"
#include "user.h"
#include "stat.h"

#ifndef NULL
#define NULL	((void *) 0)
#endif

#ifndef DEBUG
#define DEBUG	((int) 0)
#endif


char buff[512];
char prev[512];
char curr[512];

int c_check;
int d_check;
int i_check;
	

char*
gets2(int fd, char *buf, int max)
{
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
    cc = read(fd, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
  return buf;
}

int
getcmd2(int fd, char *buf, int nbuf) {
  printf(2, "$ ");
   printf(1, "aa\n");
  memset(buf, 0, nbuf);
   printf(1, "bb\n");
  gets(buf, nbuf);
   printf(1, "cc\n");
  if (buf[0] == 0)
    return -1;
  return 0;
}

void
toLower(char *p)
{
  while(*p != '\0') {
    if (*p >= 65 && *p <= 90)
	*p = *p + 32;
    p++;
  }
}


void dog6(int fd) {
  
  gets2(fd, prev, sizeof(prev));
  printf(1, "%s", prev);
  while(1) {
    gets2(fd, curr, sizeof(curr));
    
    if (curr[0] == '\0') {
    	break;
    }
    
    if (strcmp(prev, curr) != 0) {
      printf(1, "%s", curr);
    }
    
    strcpy(prev, curr);
  }
}

void preDog7(char* A) {

	if (A[0] == '-' && A[1]  == 'c') {
	  c_check = 1;
	}
	if (A[0] == '-' && A[1]  == 'd') {
	  d_check = 1;
	}
	if (A[0] == '-' && A[1]  == 'i') {
	  i_check = 1;
	}
	if(DEBUG) {printf(1, "cdi: %d %d %d\n", c_check, d_check, i_check);}
}

void dog7c(int fd) {
  
  gets2(fd, prev, sizeof(prev));
  //printf(1, "%s", prev);
  int num = 1;
   
  while(1) {
    gets2(fd, curr, sizeof(curr));
    
    if (curr[0] == '\0') {
        printf(1, "%d %s", num, prev);
    	break;
    }
    
    if (strcmp(prev, curr) != 0) {
      printf(1, "%d %s", num, prev);
      num = 1;
    } else {
      num++;
    }
    
    strcpy(prev, curr);
  }
}

void dog7d(int fd) {
  
  gets2(fd, prev, sizeof(prev));
  while(1) {
    gets2(fd, curr, sizeof(curr));
    
    if (curr[0] == '\0') {
        //printf(1, "%s", prev);
    	break;
    }
    
    if (strcmp(prev, curr) == 0) {
      printf(1, "%s", prev);
    }
    
    strcpy(prev, curr);
  }
}

void dog7i(int fd) {
  
  gets2(fd, prev, sizeof(prev));
  char prevLow[512];
  char currLow[512];
   
  while(1) {
    gets2(fd, curr, sizeof(curr));
    
    if (curr[0] == '\0') {
        printf(1, "%s", prev);
    	break;
    }
    strcpy(prevLow, prev);
    strcpy(currLow, curr);
    toLower(prevLow);
    toLower(currLow);

    if (strcmp(prevLow, currLow) != 0) {
      printf(1, "%s", prev);
    }
    
    strcpy(prev, curr);
  }
}


int main(int argc, char *argv[]){
        
        if(argc <= 1){
    		dog6(0);
    		exit();
	}
	////

	int fd;
	c_check = 0;
	d_check = 0;
	i_check = 0;
	
	////
	int i;
	for(i = 1; i < argc; i++){
	    if(DEBUG){printf(1, "argv[%d]:%s\n", i, argv[i]);}

	    if((i == argc - 1) && (fd = open(argv[i], 0)) < 0){
      		printf(1, "cannot open %s\n", argv[i]);
      		exit();
    	    }
	    
	    if (argc == 2) {
    	      dog6(fd);
	    }
	     
	    if (argc == 3) {
    	        if (i == 1)
		  preDog7(argv[1]);
	        if (i == 2) {
		  if (c_check == 1) {
	            dog7c(fd);
		  } else if (d_check == 1) {
	            dog7d(fd);
		  } else if (i_check == 1) {
	            dog7i(fd);
		  }
		}
	    }
	    
	    if (i == argc - 1) {
	      close(fd);
	    }
  	}

	if(DEBUG){printf(1, "Uniq done!!!\n");}
	exit();
}
