//======================================================================
// Mafia Tournament Table Generator
//
//  Copyright (c) Eugene Birukov, 2018
//
// The randomized selector
//
#pragma once

template<typename T>
class Selector : public std::vector<T>
{
public:

    // Sefault constructor
    //
    Selector() :
        std::vector<T>()
    {
    }

    // Constructor
    //
    Selector(size_t n) :
        std::vector<T>(n)
    {
    }

    // Randomly pick one element and remove it from collection
    //
    T PickOne()
    {
        // Pick random index
        //
        unsigned index = rand() % this->size();

        // Get the value at index
        //
        T result = this->at(index);

        // Remove it from the selector
        //
        this->erase(this->begin() + index);

        return result;
    }
};

