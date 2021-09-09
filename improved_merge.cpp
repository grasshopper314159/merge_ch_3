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
// Do i need n?  Check vids
void merge_sort(unsigned long *source, const unsigned long n, unsigned long *buffer, long k) {
    if (n < k) {
        selection_sort(source, n);
        return;
    }
    unsigned long *source_2 = source + n / 2;
    unsigned long *buffer_2 = buffer + n / 2;
    merge_sort(source, n / 2, buffer, k);
    merge_sort(source_2, n - n / 2, buffer_2, k);
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
double average(double * times, long n) {
    double sum=0.0;
    for (long i = 0; i<n; ++i) {
        sum+=times[i];
    }
//    std::cout<< sum/n << std::endl;
    return sum/n;
}

//int main(int argc, char **argv) {
//    if (argc == 2) {
//        const unsigned long N = atoi(argv[1]);
//        unsigned long *x = new unsigned long[N];
//        unsigned long *buffer = new unsigned long[N];
//        srand (time(NULL));
//        for (unsigned long i = 0; i < N; ++i)
//            x[i] = rand() % 10000;
//        Clock c;
//        merge_sort(x, N, buffer);
//        c.ptock();
//        for (unsigned long i = 0; i < N; ++i)
//            std::cout << x[i] << " " << std::endl;
//        delete[] buffer;
//    } else
//        std::cerr << "Usage: sort <n>" << std::endl;
//    return 0;
//}
int main(int argc, char **argv) {
    if (argc == 2) {
        const unsigned long N = atoi(argv[1]);
        unsigned long *x = new unsigned long[N];
        unsigned long *buffer = new unsigned long[N];
        double times[60];
        double k_times[200];
        for (long i3 = 1; i3<200; ++i3) {
            for (long i2 = 0; i2 < 60; ++i2) {
                for (unsigned long i = 0; i < N; ++i)
                    x[i] = rand() % 10000;
                Clock c;
                merge_sort(x, N, buffer, i3*5);
                times[i2] = c.tock();
            }
            k_times[i3]=average(times,60);
        }
        for (long i4=0; i4<200; ++i4) {
            std::cout << k_times[i4] << std::endl;
        }
    } else
        std::cerr << "Usage: sort <n>" << std::endl;
    return 0;
}