#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include ”fcntl.h”
int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
void sys_Lseek1(char *name,int offset,int len,char *string){
  char str[512] ; 
	int sz;
  int fd = open(name, O_RDONLY);
	//does lseek offset
	lseek(fd,offset,SEEK_CUR);
	//reads data of length len
	read(fd, str,len);
	//verify that data is same as string
	if(string == str){
		printf("they data and string are same");
	}
	else{
		printf("they data and string are not same");
	}
	close(fd);
	
	exit();
  
}
void sys_Lseek2(char *name){
  char str[512] ; 
	int sz,i;
	//open filename
	int fd = open(name, O_RDONLY);
	int fd1 = open("copy.txt",O_CREAT|O_RDWR);
	//get size of file
	int size = lseek(fd,0,SEEK_END);
	// dived file in 10 part
	int part = size / 10;
	int rem=size%10;
	int offset = 0;
	//set pointer at begining
	lseek(fd,0,SEEK_CUR);
	for(i=0;i<10;i++){
		//read part and write in file
		sz = read(fd, str,part);
		write(fd1,str,sz);
		//add offset
		offset = offset + part;
		//set pointer to offset of file 
		lseek(fd,offset,SEEK_CUR);
	}
	if(rem != 0){
		//read rem from fd and write in fd1
		sz = read(fd, str,rem);
		write(fd1,str,sz);
	}
	close(fd);
	close(fd1);
	exit(); 
}
