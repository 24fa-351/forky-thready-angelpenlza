#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]) {

    if(argc < 3) {
        printf("not enough values\n");
        return 1;
    }

    FILE *out = fopen("results.txt", "a");

    pid_t my_pid = 0;

    int things = atoi(argv[1]);
    int pattern_num = atoi(argv[2]);

    srand(time(0));

    // pattern 1

    if(pattern_num == 1) {

        fprintf(out, "----------- pattern 1 -----------\n");

        for(int ix = 1; ix <= things; ix++) {

            fprintf(out, "main process creating process %i\n", ix);

        // ----- will make the following code run twice -------------------

            my_pid = fork();

        // ----- for the parent case: do nothing, only create -------------

            if(my_pid > 0) {
                return 0; 
            }
        // ----- for the child case: sleep, then output created process ---

            else if(my_pid == 0) {
                sleep(rand() % 8);
                fprintf(out, "process %i beginning, with PID: %d\n", ix, my_pid);
            } 
        // ----- in this case, the parent failed to create a child --------

            else {
                fprintf(out, "failed\n");
                return 0;
            }
        }
        fprintf(out, "--------------------------------\n");

    }

    // pattern 2

    else if(pattern_num == 2) {

        fprintf(out, "----------- pattern 2 -----------\n");

        for(int ix = 1; ix <= things; ix++) {

        // ----- parent: state the process it is creating, the return --------------------------------------

            if(my_pid > 0) {
                fprintf(out, "process %i (%d) creating process %i\n", ix, my_pid, ix + 1);
                return 0;
            }
        
        // ----- child: state that the parent created the child, then make child fork another process ------
            else if(my_pid == 0) {
                fprintf(out, "process %i created process %i\n", ix, ix + 1);
                my_pid = fork();

            }
            else 
                fprintf(out, "fail\n");

        }

        fprintf(out, "--------------------------------\n");
    } 

    // patter 3
    else if(pattern_num == 3) {
        printf("----------- pattern 3 -----------\n");


    }

    fclose(out);

    return 0;
}