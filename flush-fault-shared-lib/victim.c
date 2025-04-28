#include "mylib.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int secret = argc > 1 ? atoi(argv[1]) : 0;

    printf("Repeatedly calling shared_lib_func with secret=%i\nCtrl+C to cancel...\n", secret);

    while (1)
    {
        shared_lib_func(secret);
    }
}
