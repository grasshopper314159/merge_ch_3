//
// Created by jay on 9/8/21.
//

#include "improved_merge.h"
#include <iostream>
#include "Clock.h"

void show(unsigned long *x, unsigned long N) {
    for (unsigned long i = 0; i < N; ++i)
        std::cout << x[i] << " " << std::endl;
}


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
// Do i need n?  Check vids
void merge_sort(unsigned long *source, const unsigned long n, unsigned long *buffer) {
    if (n <= 32) {
        selection_sort(source, n);
        return;
    }
    unsigned long *source_2 = source + n / 2;
    unsigned long *buffer_2 = buffer + n / 2;
    merge_sort(source, n / 2, buffer);
    merge_sort(source_2, n - n / 2, buffer_2);
    //unsigned long *buffer = new unsigned long[n];
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

}

int partition(unsigned long *source, unsigned long lo, unsigned long hi ) {
    unsigned long i = lo+1;
    if (i >= hi) return -99;
    unsigned long j = hi - 1;
    unsigned long peak_i = *(source+i);
    unsigned long peak_j = *(source+j);
    unsigned long v = source[lo];
    while(true) {
        while(*(source+i) < v) {
            i++;
            peak_i = *(source+i);
            // added a minus one
            //i >= ? ??
            if (i == hi-1) break;
        }
        while( v < *(source+j)) {
            j--;
            peak_j = *(source+j);
            if (j == lo) break;
        }
        if (i >= j) break;
        std::swap(source[i], source[j]);
      }
    std::swap(source[lo], source[j]);

//        for (unsigned long k = lo; k < hi+1; ++k) {
//            std::cout << source[k] << " \t";
//        }
//        std::cout << std::endl;
//        std::cout << v << " " << *(source+i) << " " << *(source+j) << " " << std::endl;

    show(source, 10);
    return j;
}

void quick_sort(unsigned long *source, const unsigned long lo, unsigned long hi) {
//    if (n <= 32) {
//        selection_sort(source, n);
//        return;
//    }
// zero length array
    if (hi < lo) return;
    unsigned long j = partition(source, lo, hi);
//    quick_sort(source, lo, j - 1);
    quick_sort(source, lo, j);
    show(source, 10);
    quick_sort(source, j + 1, hi);
//    return 0;
}

int main(int argc, char **argv) {
    if (argc == 2) {
        const unsigned long N = atoi(argv[1]);
//        unsigned long *x = new unsigned long[N];
        unsigned long x[10] = {60,10,20,70,90,50,40,80,30,100};

        unsigned long *buffer = new unsigned long[N];
        srand (time(NULL));
//        for (unsigned long i = 0; i < N; ++i)
//            x[i] = rand() % 10000;
//        Clock c;
//        merge_sort(x, N, buffer);
//
//        c.ptock();
        show(x, 10);
        //unsigned long v = partition(x, 0, N);
        // Uses n-1 in book
        quick_sort(x,0,N);
        show(x, 10);
        delete[] buffer;
    } else
        std::cerr << "Usage: sort <n>" << std::endl;
    return 0;
}
