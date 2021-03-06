//
// Created by jay on 9/8/21.
//

#include "improved_merge.h"
#include <iostream>
#include <assert.h>
#include "Clock.h"

void show(long *x, long N) {
    for (long i = 0; i < N; ++i)
        std::cout << x[i] << " " << std::endl;
}


int isSorted(long *a, long lo, long hi) {
    for (long i = lo + 1; i < hi; i++)
        if (a[i] < a[i-1]) return 0;
    return 1;
}

void selection_sort(long *source, long n) {
    for (long i = 0; i < n; ++i) {
        long min_ind = i;
        long min_val = source[i];
        for (long j = i + 1; j < n; ++j)
            if (source[j] < min_val) {
                min_ind = j;
                min_val = source[j];
            }
        std::swap(source[i], source[min_ind]);
    }
}
// Do i need n?  Check vids
void merge_sort(long *source, const long n, long *buffer) {
    if (n <= 32) {
        selection_sort(source, n);
        return;
    }
    long *source_2 = source + n / 2;
    long *buffer_2 = buffer + n / 2;
    merge_sort(source, n / 2, buffer);
    merge_sort(source_2, n - n / 2, buffer_2);
    //long *buffer = new long[n];
// Merge sorted halves into buffer:
    long i = 0, j = 0, buffer_ind = 0;
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

int partition(long *source, long lo, long hi ) {
    long i = lo;
    long j = hi + 1;
    long peak_i = *(source+lo);
    long peak_j = *(source+hi);
    long v = source[lo];
    while(true) {
        while(source[++i] < v) {
            peak_i = *(source+i);
            // added a minus one
            //i >= ? ??
            if (i == hi) break;
        }
        while( v < source[--j]) {
            peak_j = *(source+j);
            if (j == lo) break;
        }
        if (i >= j) break;
        std::swap(source[i], source[j]);
      }
    std::swap(source[lo], source[j]);
    return j;
}

void quick_sort(long *source, const long lo, long hi) {
// zero length array
    if (hi < lo) return;
    unsigned long j = partition(source, lo, hi);
    quick_sort(source, lo, j - 1);
    quick_sort(source, j + 1, hi);
}
double average(double * times, long n) {
    double sum=0.0;
    for (long i = 0; i<n; ++i) {
        sum+=times[i];
    }
    return sum/n;
}
int main(int argc, char **argv) {
    if (argc == 2) {
        const unsigned long N = atoi(argv[1]);
        long *x = new long[N];
//        long x[10] = {60,10,20,70,90,50,40,80,30,100};
        long *buffer = new long[N];
        double times[60];
        srand (time(NULL));

            for (long i2 = 0; i2 < 60; ++i2) {
                for (unsigned long i = 0; i < N; ++i)
                    x[i] = rand() % 10000;
                Clock c;
                quick_sort(x,0,N-1);
                times[i2] = c.tock();
            }
        assert(isSorted(x,0,N));
        std::cout << average(times,60) << std::endl;
        delete[] buffer;
    } else
        std::cerr << "Usage: sort <n>" << std::endl;
    return 0;
}
