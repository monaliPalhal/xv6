#include ”types.h”
#include ”stat.h”
#include ”user.h”
#include ”fcntl.h”
int main(int argc,char *argv[5]){
	char str[512] ; 
	int sz,i;
	//open filename
	int fd = open(argv[1], O_RDONLY);
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

