//
// Created by jay on 9/8/21.
//

#include "improved_merge.h"
#include <iostream>
#include "Clock.h"

void selection_sort(unsigned long *source, unsigned long n) {
    for (unsigned long i = 0; i < n; ++i) {
        unsigned long min_ind = i;
        unsigned long min_val = source[i];
        for (unsigned long j = i + 1; j < n; ++j)
            if (source[j] < min_val) {
                min_ind = j;
                min_val = source[j];
            }
        std::swap(source[i], source[min_ind]);
    }
}

void merge_sort(unsigned long *source, const unsigned long n) {
    if (n <= 32) {
        selection_sort(source, n);
        return;
    }
    unsigned long *source_2 = source + n / 2;
    merge_sort(source, n / 2);
    merge_sort(source_2, n - n / 2);
    unsigned long *buffer = new unsigned long[n];
// Merge sorted halves into buffer:
    unsigned long i = 0, j = 0, buffer_ind = 0;
    while (i < n / 2 && j < (n - n / 2)) {
        if (source[i] < source_2[j]) {
            buffer[buffer_ind] = source[i];
            ++i;
        } else {
// In case of equality, order doesn’t matter, so use this case:
            buffer[buffer_ind] = source_2[j];
            ++j;
        }
        ++buffer_ind;
    }
// Copy remaining values:
    for (; i < n / 2; ++i, ++buffer_ind)
        buffer[buffer_ind] = source[i];
    for (; j < n - n / 2; ++j, ++buffer_ind)
        buffer[buffer_ind] = source_2[j];
// Copy back sorted list from buffer:
    for (i = 0; i < n; ++i)
        source[i] = buffer[i];
    delete[] buffer;
}


int main(int argc, char **argv) {
    if (argc == 2) {
        const unsigned long N = atoi(argv[1]);
        unsigned long *x = new unsigned long[N];
        for (unsigned long i = 0; i < N; ++i)
            x[i] = rand() % 10000;
        Clock c;
        merge_sort(x, N);
        c.ptock();
    } else
        std::cerr << "Usage: sort <n>" << std::endl;
    return 0;
}
