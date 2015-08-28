#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "signal.h"

char *id = "terminal\n";
int count = 0;

static void do_termal(int sig) {
    ++count;
    //write(1,id,strlen(id));
    printf("aaaaa\n");
}

static void do_stop(int sig) {
    ++count;
    //write(1,id,strlen(id));
    printf("stop\n");
}
int main() {
    struct sigaction sa_oact;
    struct sigaction sa_nact;
    sigset_t pendmask;

    sa_nact.sa_handler = do_termal;
    sa_nact.sa_flags = 0;
    sigemptyset(&sa_nact.sa_mask);	//����źż�
    sigaddset(&sa_nact.sa_mask, SIGTSTP);	// ��SIGTSTP	�����źż���SIGTSTP ��ctrl+z,ʹ���̽���suspend
    sigprocmask(SIG_BLOCK, &sa_nact.sa_mask, &sa_nact.sa_mask);
    sigaction(SIGINT, &sa_nact, &sa_oact);
    sa_nact.sa_handler = do_stop;
    sa_nact.sa_flags = 0;
    sigaction(SIGTSTP, &sa_nact, &sa_oact);
    puts("sig!");
    do {
        if (count == 2) {
            sigprocmask(SIG_UNBLOCK, &sa_nact.sa_mask, &sa_nact.sa_mask);
            printf("un_block ctrl_z\n");
        }
        sigpending(&pendmask);
        if (sigismember(&pendmask, SIGTSTP)) {//SIGINT������δ���ġ���ν����δ������ָSIGQUIT��������û�б�����
            printf("SIGTSTP pending\n");
        }
        sleep(2);
		printf("2 sec pass \n");
    } while (count < 5);
    puts("end");
    return 0;
}