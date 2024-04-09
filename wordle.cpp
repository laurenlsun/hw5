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


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    
    // make new set
    std::set<std::string> words;
    
    wordleHelper(words, in, floating, dict);

    return words;
}

// Define any helper functions here

void wordleHelper(
    std::set<std::string>& words, // set to which to insert
    const std::string& in, // current state of guessed word
    const std::string& floating, // letters needed
    const std::set<std::string>& dict
)
{
    // base case: filled all the blanks. now check if valid
    if (in.find("-")==string::npos) { // no - left in the word

        // assume all floating letters are in our guess
        bool floatingOK = true;
        // loop through floating letters
        for (int i=0; i< floating.length(); i++) {
            // if can't find one of the letters
            if (in.find(floating[i])==string::npos)
                floatingOK = false; // not ok
        }

        // word in dict AND uses all floating letters
        if ((dict.find(in) != dict.end()) && (floatingOK)) // word exists in dictionary
            words.insert(in); // add it
        return;
    }

    // else need to fill another blank in
    int curr = in.find("-"); // know there's at least 1 - left

    // try all the letters
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for (int i=0; i< alphabet.length(); i++) {
        // sub this letter
        in[curr] = alphabet[i];
        wordleHelper(words, in, floating, dict);
    }

    // tried all letters and added all the combos that worked, so reset to -
    in[curr] = "-";
}