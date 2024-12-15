#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void startPatternTwoProcess(int things, const int total_things) {
    if (things == 0) return;
    int parent_index = total_things - things;
    int child_index = total_things - things + 1;
    sleep(rand() % 8);
    pid_t pid = fork();
    if (pid > 0) {
        printf("process %d beginning...\n", parent_index);
        printf("process %d creating process %d\n", parent_index,
                child_index);
        wait(NULL);
        printf("process %d exiting...\n", parent_index);
    } else if (pid == 0) {
        printf("process %d (%d) created process %d (%d)\n", parent_index,
                getppid(), child_index, getpid());
        startPatternTwoProcess(things - 1, total_things);
    } else {
        printf("fork failed\n");
    }
}

void startPatternThreeProcess(int index, int things) {
    if (things <= 0) return;
    printf("process %d beginning...\n", index);
    sleep(rand() % 8);
    pid_t left_pid, right_pid;
    int left_index = index * 2;
    int right_index = index * 2 + 1;
    int left_things = (int)ceil(things / 2.0);
    int right_things = things / 2;

    left_pid = fork();
    if (left_pid < 0) {
        printf("failed to create left child\n");
        return;
    } else if (left_pid == 0 && left_things > 0) {
        printf("process %d (%d) started process %d (%d)\n", index, getppid(),
               left_index, getpid());
        if (left_things > 1)
            startPatternThreeProcess(left_index, left_things - 1);
    } else {
        if (left_things > 0)
            printf("process %d creating process %d...\n", index, left_index);
        wait(NULL);
        if (left_things > 0) printf("process %d exiting\n", left_index);

        right_pid = fork();
        if (right_pid < 0) {
            printf("failed to create right child\n");
            return;
        } else if (right_pid == 0 && right_things > 0) {
            printf("process %d (%d) started process %d (%d)\n", index,
                   getppid(), right_index, getpid());
            startPatternThreeProcess(right_index, right_things - 1);
        } else {
            if (right_things > 0)
                printf("process %d creating process %d...\n", index,
                       right_index);
            wait(NULL);
            if (right_things > 0) printf("process %d exiting\n", right_index);
        }
        wait(NULL);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("insufficient values\n");
        return 1;
    }
    pid_t my_pid = getpid();
    int things = atoi(argv[1]);
    const int total_things = things;
    int pattern_num = atoi(argv[2]);
    srand(time(0));

    if (pattern_num == 1) {
        printf("----- pattern 1 -----\n");
        for(int ix = 1; ix <= things; ix++) {
            printf("process %d beginning\n", ix);
            my_pid = fork();
            if(my_pid < 0) {
                printf("failed to fork\n");
                return 0;
            } else if(my_pid == 0) {
                printf("main process (%d) created process %d (%d)\n",
                getppid(), ix, getpid());
                printf("process %d exiting\n", ix);
                return 0;
            } else {
                printf("main process creating process %d...\n", ix);
                wait(NULL);
            }
        }
    } else if (pattern_num == 2) {
        printf("----- pattern 2 -----\n");
        printf("main process creating process 1\n");
        startPatternTwoProcess(things - 1, total_things);
    } else if (pattern_num == 3) {
        printf("----- pattern 3 -----\n");
        printf("main process creating process 1 with %d things\n",
               total_things);
        startPatternThreeProcess(1, things - 1);
    }
    return 0;
}