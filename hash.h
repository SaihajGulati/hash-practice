#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <vector>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        
        int start = 0; //variable unused for now, will be start of sixnum string
        int end = -1; //needs to be negative 1 because incrementing below and otherwise get one extra

        //make array to hold. Max size 28
        unsigned long long nums[28];
        for (size_t i = 0; i < k.length(); ++i)
        {
            //fill nums array with number version
            nums[i] = letterDigitToNumber(k[i]);
            //increment end so we know were end is
            end++;
        } 

        //substrings of 6
        //use numerical variables to keep track

        //set appropiate start, 5 less than end
        if (end-start >= 6)
        {
            start = end-5;
        }
        //starts at 4 because that's last index of w array
        int w_index = 4;
        //create w array
        unsigned long long w[5] = {0};
        
        //while loop to handle filling of w array
        while (end-start >= 0)
        {
            //array to hold a values and starter index for that
            unsigned long long sixnums[6] = {0};
            int s_index = 5;
            while (end >= start)
            {
                //end-start starts at 5, and goes down to 0
                sixnums[s_index] = nums[end];
                end--;
                s_index--;
            }

            //update w
            w[w_index] = calcW(sixnums);
            w_index--;

            //set the start index to new
            if (start - 6 < 0)
            {
                start = 0;
            }
            else //subtract 6 from start to get new setup
            {
                start -= 6;
            }
            
        }

        unsigned long long result = 0;
        for (size_t i = 0; i < 5; i++)
        {
            result += (rValues[i] * w[i]);
        }
        return result;

    }

    //helper function to calculate value to put in w table
    unsigned long long calcW(unsigned long long sixnums[]) const
    {
        unsigned long long prod = sixnums[0];
        for (size_t i = 1; i <= 5; i++)
        {
            prod = prod * 36  + sixnums[i];
        }
        return prod;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        //convert to lowecase
        char lower = tolower(letter);

        //check if is letter
        if (lower >= 97 && lower <= 122)
        {
            return lower - 'a';
        }
        //otherwise is a number and so need to return accordingly
        return lower - '0' + 26;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }

};

#endif
