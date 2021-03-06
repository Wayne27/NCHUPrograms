#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
 
struct flock* file_lock(short type,short whence)
{
        static struct flock ret;
        ret.l_type = type;
        ret.l_start = 0;
        ret.l_whence = whence;
        ret.l_len = 0;
        ret.l_pid = getpid();
        return &ret;
}
 
int main()
{
        printf("1.exclusive lock(write lock)\n");
        printf("2.share lock(read lock)\n");
        printf("3.not use lock\n");
        printf("Choose lock type -> ");
        int ia;
        scanf("%d",&ia);
        int fd = open("mandlock.txt",O_RDWR|O_APPEND);
        if(ia==1)
        {
                if(fcntl(fd, F_SETLK, file_lock(F_WRLCK, SEEK_SET))!=0)
                        printf("F_WRLCK fail.\n");
                else
                        printf("F_WRLCK success.\n");
        }
        else if(ia==2)
        {
                if(fcntl(fd, F_SETLK, file_lock(F_RDLCK, SEEK_SET))!=0)
                        printf("F_RDLCK fail.\n");
                else
                        printf("F_RDLCK success.\n");
        }
        char ca[10000];
        if(read(fd, ca, 10000)<0)printf("Can't read file.\n");
        else
        {
                printf("Read file:\n");
                puts(ca);
        }
        strcpy(ca,"\n\nab write success.\n");
        if(write(fd, ca, strlen(ca))<0)printf("Can't write file.\n");
        else
        {
                printf("write file success.\n");
        }
        fcntl(fd, F_SETLK, file_lock(F_UNLCK, SEEK_SET));
        close(fd);
}

