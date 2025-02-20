#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include "HeapSort.h"

template <typename T>
void print_sequence(const std::vector<T>& sequence) {
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << " "; 
    }
    std::cout << std::endl; 
}


/**
 * @brief check the correctness of the sorting results
 * 
 * @param seqence a sorted vector referrence
 * @return true or false
 */
template <typename T>
bool check(const std::vector<T>& sequence) {
    for (size_t i = 0; i < sequence.size() - 1; ++i) {
        if (sequence[i] > sequence[i + 1]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief generate diffrent types of test sequences
 * 
 * @param size number of elements in the sequence
 * @param mode generate types: 0 for random sequence, 1 for ordered sequence
 *                             2 for reverse sequence, 3 for partial repetitive sequence
 * @return the generated test sequence
 */
std::vector<unsigned int> generateSequence(int size, int mode) {
    std::vector<unsigned int> sequence;
    sequence.reserve(size);

    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<__int128_t> distrib(0, 4294967295);

    switch (mode) {
        case 0: { // random sequence
            for (int i = 0; i < size; ++i) {
                sequence.push_back(distrib(gen));
            }
            break;
        }
        case 1: { // ordered sequence
            for (int i = 0; i < size; ++i) {
                sequence.push_back(i);
            }
            break;
        }
        case 2: { // reverse sequence
            for (int i = 0; i < size; ++i) {
                sequence.push_back(size - i - 1);
            }
            break;
        }
        case 3: { // partial repetitive sequence
            for (int i = 0; i < size; ++i) {
                sequence.push_back(distrib(gen) % (size / 10));
            }
            break;
        }
    }
    return sequence;
}

/**
 * @brief test function for all kinds of sequences
 * 
 * @param seqence a vector referrence
 */
template <typename T>
void testSequence(std::vector<T>& sequence) {
    // test by my heapsort function
    std::vector<T> copy = sequence;
    auto start = std::chrono::high_resolution_clock::now();
    heapsort(copy);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    if (check(copy)) {
        // print_sequence(copy);
        std::cout << "heapsort correct. Time: " << duration.count() << " ms" << std::endl;
    } else {
        std::cout << "heapsort incorrect." << std::endl;
    }

    // test by std::sort_heap function
    copy = sequence;
    std::make_heap(copy.begin(), copy.end());
    start = std::chrono::high_resolution_clock::now();
    std::sort_heap(copy.begin(), copy.end());
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    if (check(copy)) {
        std::cout << "std::sort_heap correct. Time: " << duration.count() << " ms" << std::endl;
    } else {
        std::cout << "std::sort_heap incorrect." << std::endl;
    }
}


int main() {
    const size_t size = 1000000;
    std::vector<unsigned int> randomSeq = generateSequence(size, 0);
    // print_sequence(randomSeq);
    std::vector<unsigned int> orderedSeq = generateSequence(size, 1);
    // print_sequence(orderedSeq);
    std::vector<unsigned int> reverseSeq = generateSequence(size, 2);
    // print_sequence(reverseSeq);
    std::vector<unsigned int> partialRepeatSeq = generateSequence(size, 3);
    // print_sequence(partialRepeatSeq);

    std::cout << "Testing random sequence..." << std::endl;
    testSequence(randomSeq);
    std::cout << std::endl; 

    std::cout << "Testing ordered sequence..." << std::endl;
    testSequence(orderedSeq);
    std::cout << std::endl; 

    std::cout << "Testing reverse sequence..." << std::endl;
    testSequence(reverseSeq);
    std::cout << std::endl; 

    std::cout << "Testing partial repeat sequence..." << std::endl;
    testSequence(partialRepeatSeq);
    std::cout << std::endl; 

    return 0;
}

