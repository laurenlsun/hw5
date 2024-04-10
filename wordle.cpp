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

        // assume all floating letters are in our guess
        // FLOATING CHECK
        // bool floatingOK = true;
        // // loop through floating letters
        // for (int i=0; i< floating.length(); i++) {
        //     // if can't find one of the letters
        //     if (in.find(floating[i])==string::npos)
        //         floatingOK = false; // not ok
        // }

        // word in dict AND uses all floating letters
        if (dict.find(in) != dict.end()) // word exists in dictionary
            words.insert(in); // add it
        return;
    }

    // else need to fill another blank in
    int curr = in.find("-"); // know there's at least 1 - left

    // need to start trying the floating letters
    if (count<=floating.length()) {
        for (int i=0; i< floating.length(); i++) {
            // sub this letter
            in[curr] = floating[i];
            // delete floating[i] from floating
            floating = floating.substr(0, i-1) + floating.substr(i+1, floating.length()-i-1);
            wordleHelper(words, in, floating, dict, count-1);
        }
    }
    // else more blanks than floating letters
    // try all the letters
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for (int i=0; i< alphabet.length(); i++) {
        // sub this letter
        in[curr] = alphabet[i];

        // if it was in the floating string remove it from the string
        int floatingindex = floating.find(alphabet[i]);
        floating = floating.substr(0, floatingindex-1) + floating.substr(floatingindex+1, floating.length()-floatingindex-1);
        wordleHelper(words, in, floating, dict, count-1);
    }

    // tried all letters and added all the combos that worked, so reset to -
    in[curr] = '-';
}