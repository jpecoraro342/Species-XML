//
//  Species.h
//  Tree
//
//  Created by Joseph Pecoraro on 2/25/13.
//  Copyright (c) 2013 Joseph Pecoraro. All rights reserved.
//

#ifndef __Tree__Species__
#define __Tree__Species__

#include <iostream>

class Species {
public:
    Species() { }
    Species(std::string n1, std::string n2, std::string r);
    Species(std::string n1, std::string n2, std::string r, int l);
    std::string getScientificName() { return scientificName; }
    std::string getCommonName() { return commonName; }
    std::string getRank() { return rank; }
    void print();
    int compare(std::string c);
    int compareSpecies(Species s);
    int getLevel() { return level; }
    
private:
    std::string scientificName;
    std::string commonName;
    std::string rank;
    int level;
};

#endif /* defined(__Tree__Species__) */
