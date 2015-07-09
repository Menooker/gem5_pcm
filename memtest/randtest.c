#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#define THE_ADDR (0x11000000)

long out;

float timedelta(struct timeval* t1,struct timeval* t2)
{
	float use=1000*(t2->tv_sec - t1->tv_sec)+(t2->tv_usec - t1->tv_usec)/1000.0;
	return use;
}


void randtest(void* start,long len)
{
	struct timeval t1,t2;
	gettimeofday(&t1,0);
	int i;
	len=len/sizeof(long);
	for(i=0;i<1000000;i++)
	{
		long rnd=rand()%len;
		long* addr=(long*)start+rnd;
		*addr=rand();
	}
	gettimeofday(&t2,0);
	printf("Write time : %f\n",timedelta(&t1,&t2));

	gettimeofday(&t1,0);
	for(i=0;i<1000000;i++)
	{
		long rnd=rand()%len;
		long* addr=(long*)start+rnd;
		out=*addr;
	}
	gettimeofday(&t2,0);
	printf("Read time : %f\n",timedelta(&t1,&t2));
}

unsigned long atox(char *s)
{
  unsigned long sum;
  while (isspace(*s)) ++s;
  for (sum = 0L; isxdigit(*s); ++s)
  {
    unsigned long digit;
    if (isdigit(*s))
      digit = *s - '0';
    else
      digit = toupper(*s) - 'A' + 10;
    sum = sum*16L + digit;
  }

  return sum;
}
int main (int args, char* arg[])
{
    int i;
    int fd;
	int len;
    char* mem;
    
    //open /dev/mem with read and write mode
	srand(time(0));
	printf("rand=%d\n",rand());

    if((fd = open ("/dev/mem", O_RDWR)) < 0)
    {
        perror ("open error");
        return -1;
    }
	printf("open ok\n");

	size_t addr=(size_t)THE_ADDR;
	
	
	addr=atox(arg[1]);
	len=atoi(arg[2]);


    //map physical memory 0-10 bytes
    mem = mmap (0, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, addr);
    if (mem == MAP_FAILED)
    {
        perror ("mmap error:");
        return 1;
    }

    randtest(mem,len);

    printf("\n");
    munmap (mem, 10); //destroy map memory
    close (fd);   //close file*/
    return 0;
}
