#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <fcntl.h>

int main(int argc, char **argv) {

    char buff;
    char tmp;
    int flag = 1;
    char prev = 'r';
    int dev = open("/dev/my_gpio", O_RDWR); // if you want read-'O_RDONLY' write-'O WRONLY', read&write-'O RDUR•

    if (dev == -1) {
        printf("Opening was not possible!\n");
        return -1;
    }

    printf("Opening was successfull!\n");

    while(flag){
        read (dev, &buff, 1);
        printf("%c", buff);
        if(buff == '0'){
            printf("undetected\n");
        }
        else{
            printf("detected\n");
            flag = 0;
        }
    }

    close (dev);
    return 0;
}
