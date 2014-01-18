//
//  Tree.cpp
//  Tree
//
//  Created by Joseph Pecoraro on 2/24/13.
//  Copyright (c) 2013 Joseph Pecoraro. All rights reserved.
//

#include "Tree.h"
#include <queue>
#include <stack>

//searches for proper node of given species, then follows its parents, pringing at each step.
template <class T>
void Tree<T>::getLineage(std::string s) {
    TreeNode<T>* species = search(rootNode, s);
    if ( species == NULL) {
        std::cout << "Sorry, we could not find that species" << std::endl;
    }
    else {
        int level = 0;
        while (species->value.compareSpecies(rootNode->value) != 0) {
            for(int i = 0; i < level; i ++) {
                std::cout << ">";
            }
            std::cout << " ";
            species->value.print();
            species = species->parent;
            level++;
        }
    }
}

//gets and prints out the common lineage. searches for the node that matches the given species. Once found, stacks are used to keep track of the lineage. They are then compared together, starting at the top, to find where the lineage breaks off
template <class T>
void Tree<T>::getCommonLineage(std::string s1, std::string s2) {
    TreeNode<T> *species1 = search(rootNode, s1);
    TreeNode<T> *species2 = search(rootNode, s2);
    
    if ( species1 == NULL) {
        std::cout << "Sorry, we could not find " << s1 << std::endl;
    }
    else if ( species2 == NULL ) {
        std::cout << "Sorry, we could not find " << s2 << std::endl;
    }
    else {
        std::stack<TreeNode<T>* > species1Lineage = *new std::stack<TreeNode<T>* >();
        std::stack<TreeNode<T>* > species2Lineage = *new std::stack<TreeNode<T>* >();
    
        while (species1->value.compareSpecies(rootNode->value) != 0) {
            species1Lineage.push(species1);
            species1 = species1->parent;
        }
        while (species2->value.compareSpecies(rootNode->value) !=0) {
            species2Lineage.push(species2);
            species2 = species2->parent;
        }
    
        while (species1->value.compareSpecies(species2->value) == 0) {
            std::cout << "Level[" << species1->value.getLevel() << "] Common Ancestor: ";
            species1->value.print();
            species1 = species1Lineage.top();
            species1Lineage.pop();
            species2 = species2Lineage.top();
            species2Lineage.pop();
            if (species1Lineage.empty() || species2Lineage.empty())
                break;
        }
    
        std::cout << std::endl << std::endl << "Ancestry unique to " << s1 << std::endl;
        while (!species1Lineage.empty()) {
            std::cout << "Level[" << species1Lineage.top()->value.getLevel() << "] ";
            species1Lineage.top()->value.print();
            species1Lineage.pop();
        }
    
        std::cout << std::endl << std::endl << "Ancestry unique to " << s2 << std::endl;
        while (!species2Lineage.empty()) {
            std::cout << "Level[" << species2Lineage.top()->value.getLevel() << "] ";
            species2Lineage.top()->value.print();
            species2Lineage.pop();
        }
    }
}

//search that returns the node in the tree that corresponds to the correct species
template <class T>
TreeNode<T>* Tree<T>::search(TreeNode<T> *n, std::string s) {
    int l = n->value.compare(s);
    if (l == 0) {
        return n;
    }
    else {
        for (int i = 0; i < n->numChildren(); i ++) {
            TreeNode<T> *k = search(n->getChild(i), s);
            if ( k != NULL) {
                return k;
            }
        }
    }
    return NULL;
}