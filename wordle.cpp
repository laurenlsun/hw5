#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <string>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(std::set<std::string>& words, 
    std::string& input,
    const std::string floating,
    const std::set<std::string>& dict,
    int count);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    
    // make new set
    std::set<std::string> words;
    std::string input = in; // make editable copy that's not const

    int count = 0;

    for(int i=0; i<in.length(); i++) {
        if (in[i]=='-')
            count++;
    }

    std::string floatingcopy = floating;
    wordleHelper(words, input, floatingcopy, dict, count);

    return words;
}

// Define any helper functions here

void wordleHelper(
    std::set<std::string>& words, // set to which to insert
    std::string& in, // current state of guessed word
    std::string floating, // letters needed
    const std::set<std::string>& dict,
    int count
)
{
    // base case: filled all the blanks. now check if valid
    if (count==0) { // no - left in the word
        // cout << "base case: all blanks filled" << endl;
        
        if (dict.find(in) != dict.end()) {// word exists in dictionary
            // cout << in << " added" << endl;
            words.insert(in); // add it
        }
        return;
    }
    else {
        // else need to fill another blank in
        // cout << "there are " << count << "blanks left" << endl;
        int curr = in.find("-"); // know there's at least 1 - left

        // need to start trying the floating letters
        if (count<=floating.length()) {
            // cout << "there are " << floating.length() << " floating letters left to use" << endl;
            // cout << "trying floating letters " << endl;
            for (int i=0; i< floating.length(); i++) {
                // sub this letter
                in[curr] = floating[i];
                // delete floating[i] from floating
                string floatingcopy = floating;
                floatingcopy.erase(i, 1);
                // cout << "calling wordleHelper with in=" << in << ", floating=" << floatingcopy << ", count=" << count-1 << endl;
                wordleHelper(words, in, floatingcopy, dict, count-1);
            }
        }
        else {
            // else more blanks than floating letters
            // try all the letters
            // cout << "trying alphabet" << endl;
            string alphabet = "abcdefghijklmnopqrstuvwxyz";
            for (int i=0; i< alphabet.length(); i++) {
                // sub this letter
                in[curr] = alphabet[i];
                // if it was in the floating string remove it from the string
                string floatingcopy = floating;
                if (floating.find(alphabet[i])!=string::npos) { // we tried a letter from the floating string
                    floatingcopy.erase(floating.find(alphabet[i]),1);
                }
                // cout << "calling wordleHelper with in=" << in << ", floating=" << floating << ", count=" << count-1 << endl;
                wordleHelper(words, in, floatingcopy, dict, count-1);
            }
        }

        // tried all letters and added all the combos that worked, so reset to -
        // cout << "all combos failed" << endl;
        in[curr] = '-';
    }
}