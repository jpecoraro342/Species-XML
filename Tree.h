//
//  Tree.h
//  Tree
//
//  Created by Joseph Pecoraro on 2/24/13.
//  Copyright (c) 2013 Joseph Pecoraro. All rights reserved.
//

#ifndef __Tree__Tree__
#define __Tree__Tree__

#include <iostream>
#include "TreeNode.h"

template <class T>
class Tree {
    
public:
    Tree<T>() { rootNode = NULL; }
    Tree<T>(TreeNode<T> &n) { rootNode = &n; }
    TreeNode<T>* getRoot() { return rootNode; }
    void replaceFirstNode(TreeNode<T> n) { rootNode = n; }
    void getLineage(std::string s);
    void getCommonLineage(std::string s1, std::string s2);
    TreeNode<T>* search(TreeNode<T> *n, std::string s);
    
private:
    TreeNode<T> *rootNode;
    
};

#endif /* defined(__Tree__Tree__) */
