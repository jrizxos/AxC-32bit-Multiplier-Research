#ifndef AFA_H    
#define AFA_H

#include <stdexcept>
#include <bitset>
#include <stdint.h>
using namespace std;

uint8_t half_adder(uint8_t a, uint8_t b);
uint8_t ax_full_adder(uint8_t a, uint8_t b, uint8_t c, uint8_t id);
void partial_products(uint32_t A, uint32_t B, uint8_t size, bitset<32>* partials);

#endif
