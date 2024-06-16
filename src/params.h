#ifndef PARAMS_H_
#define PARAMS_H_

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void print_about() {

    char _list[][50] = {"About this program:\n",
    "- A simple version of LS for Linux.\n",
    "- Coded by John Cartwright\n",
    "- 0.3. Release date: Dec 22.\n",
    "- Pass a folder to list contents, e,g\n",
    "- my_ls Documents.\n"};

    // Animate a line drawing character by character
    char line[] = "\n*--#--^^^^^^--#--* Simple LS clone. *--#--^^^^^^--#--*\n";
    for (long unsigned int i = 0; i < sizeof(line); i++) {
        printf("%c", line[i]);
        fflush(stdout);
        usleep(99000);  // Delay between characters
    }

    int num_lines = sizeof(_list) / sizeof(_list[0]);

    srand(time(NULL));  // Seed the random number generator

    for (int i = 0; i < num_lines; i++) {
        printf("%s\n", _list[i]);
        fflush(stdout);  // Ensure immediate output
        usleep(rand() % 2000000 + 500000);  // Random delay between 0.5 and 2.5 seconds
    }

};

#endif
// Path: src/params.h
