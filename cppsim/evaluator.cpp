#include "evaluator.h"

void read_vars(uint8_t* vars){
    char buf;                                           // input buffer
    int chk;                                            // reach check value

    for(int i=0; i<VAR_NUM; i++){                       // for every variable
        chk = fread(&buf, sizeof(uint8_t), 1, stdin);   // read it
        if(chk==0){                                     // if there is an error
            if(feof(stdin)){                            // report it
                fwrite("[EOF error]", sizeof(char), 12, stderr);
                return;                                 
            }
            if(ferror(stdin)){
                fwrite("[stdin ERROR]", sizeof(char), 14, stderr);
                return;                                 // and exit
            }
        }
        vars[i] = (uint8_t)buf;                         // place it in the array
    }
    return;                                             // return when done
}

uint64_t evaluate_MAE_32x32(uint8_t* vars){
    /* - uint64 is just barely good for 32x32, fits by 
    * just by one order of magnitude in our case.
    * - Never trust intuition about the default C++ primitives
    * when doing serious calculations, numbers beyond 32-bits
    * don't always work as you'd expect!  
    */
    ifstream inp_file("inp.bin", ios::binary );         // file that contains test values
    uint64_t res, exp, mae = 0;                         // result value, expected value and MAE
    int64_t delta;                                      // delta of expected - result
    uint32_t a,b;                                       // input test values              
                                                                
    for(int i=0; i<TEST_INP; i++){                      // for every pair of test values
        inp_file.read(reinterpret_cast<char *>(&a), 4); // read them from the file
        inp_file.read(reinterpret_cast<char *>(&b), 4); // !!! Beware that the endianess is depended on your system architecture !!!
        exp = (uint64_t)a*(uint64_t)b;                  // multiply (32-bit numbers still need to be casted to 64 because mult overflows)
        res = ARCWM_32x32(a, b, vars);                  // get the result of the approximate multiplier
        delta = res - exp;                              // get the error
        mae = mae + (abs(delta)/TEST_INP);              // add it's absolute value to the mean
    }

    inp_file.close();                                   // close the test value file
    return mae;                                         // and return the resulting MAE
}   

/////////////////////////////////////////// main //////////////////////////////////////////
int main(){  
    uint8_t* vars = (uint8_t*) malloc(VAR_NUM*sizeof(uint8_t));     // allocate an array for variables
    for(int i=0; i<VAR_NUM; i++) vars[i] = 0;
    read_vars(vars);                                    // read variables from stdin into array

    uint64_t mae = evaluate_MAE_32x32(vars);            // calculate MAE
    fwrite(&mae, sizeof(uint64_t),   1, stdout);        // return MAE into stdout

    fflush(stdout);                                     // flush output
    free(vars);                                         // free array for variables
    return 0;                                           // exit
}