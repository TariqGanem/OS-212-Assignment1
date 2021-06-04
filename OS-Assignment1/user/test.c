#include "../kernel/types.h"
#include "../user/user.h"
#include "../kernel/fcntl.h"
void
main (){
    int status = 0;
    int pid;
    if ((pid = fork()) < 0){
        exit(-1);
    }
    if (pid == 0){
        sleep(5);
        uint64 a = 0;
        for(uint64 i = 0 ; i < 0xFFFFFFFF;i++){
            a++;
        }
        exit(0);
    } else {
        struct perf x = {0,0,0,0,0,0};
        int rv = wait_stat(&status,&x);
        printf("%d\n",rv);
        printf("ct=%d tt=%d st=%d re=%d ru=%d avg=%d\n",x.ctime,x.ttime,x.stime,x.retime,x.rutime,x.average_bursttime);
    }
    int pid1;
    pid1 = fork();
    if (pid1 == 0){
        sleep(5);
        uint64 a = 0;
        for(uint64 i = 0; i < 0xFFFFFFFF; i++){
            a++;
        }
        exit(0);
    } else {
        int status1 = 0;
        struct perf x = {0,0,0,0,0,0};
        int rv = wait_stat(&status1,&x);
        printf("%d\n",rv);
        printf("ct=%d tt=%d st=%d re=%d ru=%d avg=%d\n",x.ctime,x.ttime,x.stime,x.retime,x.rutime,x.average_bursttime);
    }
    exit(0);
}
#define SYS_fork    1
#define SYS_kill    6
#define SYS_sbrk   12
#define SYS_write  16

/*void 
main(){
    int mask=(1<< SYS_fork)|( 1<< SYS_kill)| ( 1<< SYS_sbrk) | ( 1<< SYS_write);
    trace(mask,2);
    int pid = fork();
    if (pid == 0){
        exit(0);
    } 
    exit(0);
}*/
