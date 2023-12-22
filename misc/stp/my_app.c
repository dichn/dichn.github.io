#include <stdlib.h>
#include <limits.h>

short next_number(){
    static short counter = 0;
    return counter++;
}

void main(void)
{
    int i, state;
    for(i = 0; i < INT_MAX; i++){
        state = next_number();
        if (state < 0){
            system("date");
        }
    }
}
