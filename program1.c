#include ”types.h”
#include ”stat.h”
#include ”user.h”
#include ”fcntl.h”
int main(int argc,char *argv[5]){
	char str[512] ; 
	int sz;
	int offset = argv[2];
	int len = argv[3];
	//open filename
	int fd = open(argv[1], O_RDONLY);
	//int fd1 = open(argv[2],OCREATE|ORDWR);
	//does lseek offset
	lseek(fd,offset,SEEK_CUR);
	//reads data of length len
	read(fd, str,len);
	//verify that data is same as string
	if(argv[4] == str){
		printf("they data and string are same");
	}
	else{
		printf("they data and string are not same");
	}
	//while((sz=read(fd, str,512))>0)
	//write(fd1,str,sz);
	close(fd);
	//close(fd1);
	exit();
}
