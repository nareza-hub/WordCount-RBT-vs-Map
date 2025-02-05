/*Name: Neoma Reza
  Email: nareza@crimson.ua.edu
  Course Section: Fall 2024 CS 201 - 001
  Homework#: 2
  To Compile: Click "Terminal", then "New Terminal" and enter this: g++ -std=c++20 parsetext.cpp -o parsetext.exe
  To Run: Click "Terminal", then "New Terminal" and enter this (change the inputName to the name of text file): ./parsetext.exe inputName.txt
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>
#include <chrono> //for timing
#include "ST.hpp" // for ST (SymbolTable)

//define a structure to store word counts for sorting
struct WordCount {
    std::string word;
    int count;
    WordCount(const std::string& w, int c) : word(w), count(c) {}
};
//comparison function for sorting
bool comp(const WordCount& x, const WordCount& y) {
    if (x.count == y.count) {
        return x.word < y.word; //sort alphabetically (a - z)
    } else{
    return x.count > y.count; //sort by frequency (from highest to lowest of frequency the word)
    }
}


int main(int argc, char* argv[]) {
    if (argc < 2) { //check file
        return 1;
    }
    std::ifstream file(argv[1]); //open input file
    if (!file) { //file can't open
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now(); //for timing
    //----------------------------------------------------------------------
    ST<std::string, int> word_counts; // Use ST 
    std::string text;
    const std::regex delim("\\s+"); //regex for splitting the whitespace
    int total_words = 0; //counter for total words
    
    //read file by each line
    while (std::getline(file, text)) {
        //tokenize the line into words
        auto begin = std::sregex_token_iterator(text.begin(), text.end(), delim, -1);
        auto end = std::sregex_token_iterator();
        for (std::sregex_token_iterator word = begin; word != end; ++word) {
            std::string token = *word;
            if (!token.empty()) {
                word_counts[token]++;
                total_words++;
            }
        }
    }
    file.close();

    //convert word_counts to vector for sorting
    std::vector<std::pair<std::string, int>> pairs = word_counts.toVector(); //get the vector of pairs
    std::vector<WordCount> word_counts_vector; //initialize a vector of WordCount

    for (const auto& pair : pairs) {
        word_counts_vector.emplace_back(pair.first, pair.second); //construct WordCount from each pair
    }

    std::sort(word_counts_vector.begin(), word_counts_vector.end(), comp); //sort by count and words with same count for alphabetically

    auto end_time = std::chrono::high_resolution_clock::now(); //stop timing
    std::chrono::duration<double> duration = end_time - start;

    //cutput the sorted word counts
    for (const auto& wc : word_counts_vector) {
        std::cout << wc.word << ": " << wc.count << std::endl; //output the words with the frequency
    }
    //word_counts.displayTree();
    std::cout << "Total words: " << total_words << std::endl; //output total words
    std::cout << "\nTime taken: " << duration.count() << " seconds" << std::endl; //output time taken
    return 0;
}