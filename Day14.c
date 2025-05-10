/**
 * This is my solution for part 1 of Day 14.
 * It was also meant to be a solution to part 2, and I have left my attempt
 * here for future reference, but the code does not work. From debugging, it
 * seems this is due to isssues with using integers > 2^31. These issues
 * have occurred even when I switched all the functions to use `long long
 * int`, or `int64_t`, or even `uint64_t`. The bug occurs when setting the
 * `or_mask` in `run_part2`.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define LINE_LEN 100
#define VALUE_WIDTH 36
#define MEMORY_SIZE 100000


/// Some Useful Debugging Functions
/**
 * Converts a given number into a string, in binary form.
 *     @param num: the given number
 *     @param binstr: a character array. this is where the string will be put
 *     @param width: the expected width of num in binary, at most the size
 *     of binstr minus one. if num is too big for its binary form to fit in
 *     width characters, then only the first {width}th characters will be
 *     included. if it is smaller, there will be leading zeroes.
 */
void longtobinstr(long num, char *binstr, int width) {
    *(binstr + width) = '\0';
    char *bufref = binstr + width - 1;
    while(bufref - binstr >= 0) {
        if(num & 1) {
            *bufref = '1';
        } else {
            *bufref = '0';
        }
        --bufref;
        num >>= 1;
    }
}

/**
 * Converts a given null-terminated character array to a long,
 * where the char* is a positive integer written in binary.
 *  @param binstr: char* - the given char*
 */
long binstrtolong(char *binstr) {
    long result = 0;
    long power = 1;
    while(power > 0 && *binstr != '\0') {
        if(*binstr == '1') result += power;
        power <<= 1;
    }
    return result;
}

/// Solutions
typedef struct {
    long address;
    long value;
} LOCATION;

typedef struct {
    LOCATION locations[MEMORY_SIZE];
    int size;
} MEMORY;


long* get_val_ref(MEMORY* m, long address) {
    for(int i=0; i<m->size; i++) {
        if(m->locations[i].address == address) {
            return &m->locations[i].value;
        }
    }
    return NULL;
}

void add_loc(MEMORY* m, long address, long value) {
    for(int i=0; i<m->size; i++) {
        if(m->locations[i].address == address) {
            m->locations[i].value = value;
            return;
        }
    }
    if(m->size >= MEMORY_SIZE-1) {
        printf("Error: Memory is over capacity!\n");
        abort();
    }
    m->locations[m->size].address = address;
    m->locations[m->size].value = value;
    m->size++;
}

long sum(MEMORY* m) {
    long result = 0;
    for(int i=0; i<m->size; i++) {
        result += m->locations[i].value;
    }
    return result;
}

long run_part1(char *path) {
    MEMORY m;
    m.size = 0;
    long mask0 = 0;
    long mask1 = 0;
    FILE *fp, *fopen(const char*, const char*);
    int fclose(FILE*);
    fp = fopen(path,"r");
    char line[LINE_LEN];
    while(fgets(line, sizeof line, fp) != NULL) {
        // this next bit is a little hacky, but hey, it works!
        if(line[1] == 'a') {
            // mask stuff
            // cleanup
            mask0 = 0; mask1 = 0;
            char mask[VALUE_WIDTH+1];
            long power = 1;
            sscanf(line, "mask = %s", mask);
            for(int i=VALUE_WIDTH-1; i>=0; i--) {
                switch(mask[i]) {
                    case 'X':
                        mask0 += power;
                        break;
                    case '1':
                        mask1 += power;
                        mask0 += power;
                        break;
                    case '0':
                        break;
                    default:
                        printf("Error in text processing:\n<<%c>>", mask[i]);
                        abort();
                }
                power <<= 1;
            }
        } else if(line[1] == 'e') {
            // mem stuff
            long address, value;
            sscanf(line, "mem[%ld] = %ld", &address, &value);
            value |= mask1;
            value &= mask0;
            add_loc(&m, address, value);
        } else {
            printf("An error has occurred.\nYou wrote this program badly."); 
        }
    }
    fclose(fp);
    return sum(&m);
}

long run_part2(char* path) {
    MEMORY m;
    m.size = 0;
    FILE* fp = fopen(path, "r");
    char line[LINE_LEN];
    long or_mask = 0;
    int floating_bits[VALUE_WIDTH];
    int num_floating_bits = 0;
    while(fgets(line, LINE_LEN, fp) != NULL) {
        if(line[1] == 'a') {
            char mask[VALUE_WIDTH+1];
            sscanf(line, "mask = %s", mask);
            num_floating_bits = 0;
            or_mask = 0;
            for(int i=0; i<VALUE_WIDTH; i++) {
                switch(mask[VALUE_WIDTH-i-1]) {
                    case 'X':
                        floating_bits[num_floating_bits] = i;
                        num_floating_bits++;
                        break;
                    case '1':
                        or_mask |= (1LL << i);
                        break;
                }
            }
        } else if(line[1] == 'e') {
            long address, value;
            sscanf(line, "mem[%ld] = %ld", &address, &value);
            address |= or_mask;
            long address_pre_floating = address;
            for(int i=0; i<(1<<num_floating_bits); i++) {
                address = address_pre_floating;
                for(int index=0; index<num_floating_bits; index++) {
                    long mask = 1 << floating_bits[index];
                    // I.e. if the index'th digit of i is not zero
                    if((1 << index) & i) {
                        address |= mask;
                    } else {
                        address &= ~mask;
                    }
                }
                add_loc(&m, address, value);
            }
        }
    }
    fclose(fp);
    return sum(&m);
}


int main() {
    char* input = "./Day14-input";
    printf("Part 1: %ld\n", run_part1(input));
    printf("Part 2: %ld\n", run_part2(input));
}
