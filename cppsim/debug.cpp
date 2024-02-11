#include "debug.h"

/* Show X
*   Prints the binary of an X-bit value in cout
*/

void show32(uint32_t a){
    bitset<32> x(a);
    cout << x << "\n";
    return;
}

void show64(uint64_t a){
    bitset<64> x(a);
    cout << x << "\n";
    return;
}

void show8(int a){
    bitset<8> x(a);
    cout << x << "\n";
    return;
}

void show2(int a){
    bitset<2> x(a);
    cout << x << "\n";
    return;
}

/* Show AFA
*   Prints in binary the full output of an AFA by id
*/

void show_AFA(int id){
    printf("%d %d %d ", 0, 0, 0);
    show2(ax_full_adder(0,0,0,id));
    printf("%d %d %d ", 0, 0, 1);
    show2(ax_full_adder(0,0,1,id));
    printf("%d %d %d ", 0, 1, 0);
    show2(ax_full_adder(0,1,0,id));
    printf("%d %d %d ", 0, 1, 1);
    show2(ax_full_adder(0,1,1,id));
    printf("%d %d %d ", 1, 0, 0);
    show2(ax_full_adder(1,0,0,id));
    printf("%d %d %d ", 1, 0, 1);
    show2(ax_full_adder(1,0,1,id));
    printf("%d %d %d ", 1, 1, 0);
    show2(ax_full_adder(1,1,0,id));
    printf("%d %d %d ", 1, 1, 1);
    show2(ax_full_adder(1,1,1,id));
    return;
}
