#include "afa.h"

/* AFAs
*   args: ints a, b and carry
*   returns: an uint8_t containing the carry of the addition in the 2nd lsb and the sum in the lsb
*/

uint8_t half_adder(uint8_t a, uint8_t b){
    uint8_t sum = (a ^ b);
    uint8_t carry = (a & b); 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = (a ^ b ^ c);
    uint8_t carry = (a & b) | (c & (a ^ b)); 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_i(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = (a ^ b ^ c);
    uint8_t carry = !sum; 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_ii(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = (a ^ b ^ c);
    uint8_t carry = a; 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_iii(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = (a ^ b ^ c);
    uint8_t carry = b; 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_1(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = (!a) | (b & c);
    uint8_t carry = a;
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_2(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = ((!a) & (b | c)) | (b & c);
    uint8_t carry = (a & b) | (c & (a ^ b)); 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_3(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = ((!a) | b) & c;
    uint8_t carry = (a & b) | (c & (a ^ b)); 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_4(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = ((!a) & (!b)) | ((!a) & (!c)) | ((!b) & (!c)) | (a & b & c);
    uint8_t carry = (a & b) | (c & (a ^ b)); 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_5(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = (!a) | (b & c);
    uint8_t carry = (a & b) | (c & (a ^ b)); 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_6(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = ((!a) & (!b)) | ((!a) & (!c)) | ((!b) & (!c));
    uint8_t carry = (a & b) | (c & (a ^ b)); 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_7(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = ((!b) & (!c)) | ((!a) & (!c)) | ((!a) & (!b)) | ((!a) & (!b) & c);
    uint8_t carry = (a & b) | (c & (a ^ b)); 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_8(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = ((!a) & (!b) & c) | (a & b & c);
    uint8_t carry = b | (a & c);
    sum = sum | (carry << 1);
    return sum;
}

//uint8_t full_adder_9 NOT IMPLEMENTED! (SAME AS full_adder_6)

uint8_t full_adder_10(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = ((!a) & (!b)) | ((!b) & (!c));
    uint8_t carry = b | (a & c);
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_11(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = ((!a) | b) & c;
    uint8_t carry = a; 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_12(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = a;
    uint8_t carry = a; 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_13(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = (a ^ b ^ c);
    uint8_t carry = c; 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_14(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = c | ((!a) & b) | (a & (!b));
    uint8_t carry = (a & b) | (c & (a ^ b)); 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_15(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = ((!a) & (!c)) | ((!b) & (!c));
    uint8_t carry = c | (a & b);
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_16(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = ((!a) & (!b)) | ((!a) & (!c));
    uint8_t carry = (a & b) | (c & (a ^ b)); 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_17(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = ((!a) & (!c)) | ((!b) & (!c)) | (a & b & c);
    uint8_t carry = ((!a) & c) | ((!b) & c) | (a & b & (!c));
    sum = sum | (carry << 1);
    return sum;
}

//uint8_t full_adder_18 NOT IMPLEMENTED! (SAME AS full_adder_6)

uint8_t full_adder_19(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = c | ((!a) & b) | (a & (!b));
    uint8_t carry = a & b; 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_20(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = (!c) | (a & b);
    uint8_t carry = c | (a & b);
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_21(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = (b & (!c)) | (a & (!c)) | (a & b);
    uint8_t carry = c; 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_22(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = b;
    uint8_t carry = a; 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_23(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = c;
    uint8_t carry = (b & (!c)) | (a & (!c)) | (a & b);
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_24(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = ((!a) & (!b)) | (a & b);
    uint8_t carry = (a & b) | (c & (a ^ b)); 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_25(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = ((!a) & (!b) & c) | (a & b & c);
    uint8_t carry = (a & b) | (c & (a ^ b)); 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_26(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = a | b | c;
    uint8_t carry = (a & b) | (c & (a ^ b)); 
    sum = sum | (carry << 1);
    return sum;
}

uint8_t full_adder_27(uint8_t a, uint8_t b, uint8_t c){
    uint8_t sum = a & b & c;
    uint8_t carry = (a & b) | (c & (a ^ b)); 
    sum = sum | (carry << 1);
    return sum;
}

//uint8_t full_adder_28 NOT IMPLEMENTED! (SAME AS full_adder_6)

/* Approximate full adder interface
*   Invokes one of the AFAs above with an id
*   passes other args and returns it's return value directly
*/

uint8_t ax_full_adder(uint8_t a, uint8_t b, uint8_t c, uint8_t id){
    switch(id){
        case  0: return full_adder(a,b,c);
        case  1: return full_adder_i(a,b,c);
        case  2: return full_adder_ii(a,b,c);
        case  3: return full_adder_iii(a,b,c);
        case  4: return full_adder_1(a, b, c);
        case  5: return full_adder_2(a, b, c);
        case  6: return full_adder_3(a, b, c);
        case  7: return full_adder_4(a, b, c);
        case  8: return full_adder_5(a, b, c);
        case  9: return full_adder_6(a, b, c);
        case 10: return full_adder_7(a, b, c);
        case 11: return full_adder_8(a, b, c);
        case 12: return full_adder_10(a, b, c);
        case 13: return full_adder_11(a, b, c);
        case 14: return full_adder_12(a, b, c);
        case 15: return full_adder_13(a, b, c);
        case 16: return full_adder_14(a, b, c);
        case 17: return full_adder_15(a, b, c);
        case 18: return full_adder_16(a, b, c);
        case 19: return full_adder_17(a, b, c);
        case 20: return full_adder_19(a, b, c);
        case 21: return full_adder_20(a, b, c);
        case 22: return full_adder_21(a, b, c);
        case 23: return full_adder_22(a, b, c);
        case 24: return full_adder_23(a, b, c);
        case 25: return full_adder_24(a, b, c);
        case 26: return full_adder_25(a, b, c);
        case 27: return full_adder_26(a, b, c);
        case 28: return full_adder_27(a, b, c);
    }
    throw std::invalid_argument( "Invalid AFA ID: "+ to_string(id));
    return -1;
}

/* Partial products generator
*   Generates the partial products of two ints A and B
*   and places them in a bitset array, size is the length of the bitset array
*/

void partial_products(uint32_t A, uint32_t B, uint8_t size, bitset<32>* partials){
    uint8_t current;
    bitset<32> zero(0);
    for(uint8_t i=0; i<size; i++){
        current = (A>>i) & 1;
        if(current){
            bitset<32> x(B);
            partials[i] = x;
        }
        else partials[i] = zero;
    }
    return;
}