#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define THE_ADDR (0x11000000)
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
    char* mem;
    char *buff = "HELLO";
    //open /dev/mem with read and write mode

    if((fd = open ("/dev/mem", O_RDWR)) < 0)
    {
        perror ("open error");
        return -1;
    }
	printf("open ok\n");
	size_t addr=(size_t)THE_ADDR;
	if(args>=3)
	{
		addr=atox(arg[2]);
	}
    //map physical memory 0-10 bytes
    mem = mmap (0, 10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, addr);
    if (mem == MAP_FAILED)
    {
        perror ("mmap error:");
        return 1;
    }

    if(arg[1][0]=='r')
    {
    //Read old value
    for (i = 0; i < 5; i++)
    {
        printf("\nold mem[%d]:%d", i, mem[i]);
    }
    printf("The value is 0x%x\n", *((int *)mem));
    }
    else if(arg[1][0]=='w')
    {
    //write memory
    memcpy(mem, buff, 5);
    //Read new value
    for (i = 0; i<5 ; i++)
    {
        printf("\nnew mem[%d]:%c", i, mem[i]);
    }
    }
    printf("\n");
    munmap (mem, 10); //destroy map memory
    close (fd);   //close file*/
    return 0;
}
