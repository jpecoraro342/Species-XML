//
//  Species.cpp
//  Tree
//
//  Created by Joseph Pecoraro on 2/25/13.
//  Copyright (c) 2013 Joseph Pecoraro. All rights reserved.
//

#include "Species.h"

Species::Species(std::string n1, std::string n2, std::string r) {
    scientificName = n1;
    commonName = n2;
    rank = r;
}

Species::Species(std::string n1, std::string n2, std::string r, int l) {
    scientificName = n1;
    commonName = n2;
    rank = r;
    level = l;
}

void Species::print() {
    if (commonName != "")
        std::cout << commonName << " (" << scientificName << ", " << rank << ")" << std::endl;
    else
        std::cout << "(" << scientificName << ", " << rank << ")" << std::endl;
}

//used in seach method to see what species matches the string input
int Species::compare(std::string s) {
    if ( s == commonName) {
        return 0;
    }
    else if ( s == scientificName) {
        return 0;
    }
    return -1;
}

int Species::compareSpecies(Species s) {
    if (s.commonName.compare(commonName) == 0) {
        return 0;
    }
    else
        return s.scientificName.compare(scientificName);
}