#include "lis.h"

int main(int argc, char **argv) {
    lis_initialize(&argc, &argv);
    lis_finalize();
    return 0;
}