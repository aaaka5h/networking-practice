#include "compute.h"

#include <unistd.h>

int compute(int n)
{
    usleep(50000);
    if (n <= 1) return n;
    return compute(n - 2) + compute(n - 1);
}
