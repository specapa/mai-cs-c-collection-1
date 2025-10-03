#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "args.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, 
"Usage: %s  <-nd>|</nd>|<-ni>|</ni>|<-ns>|</ns>|<-na>|</na> <filepath> <with -n : file out pathname>\n\
", argv[0]);
        return 1;
    }
}
