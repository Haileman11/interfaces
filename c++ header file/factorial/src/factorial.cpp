#include "factorial.h"

void factorial::set(int num)
{
    fact=1;
    for(int i=1;i<=num;++i){
        fact*=i;
    }
}

int factorial::get()
{
    return fact;
}
