//
//  TreeNode.h
//  Tree
//
//  Created by Joseph Pecoraro on 2/25/13.
//  Copyright (c) 2013 Joseph Pecoraro. All rights reserved.
//

#ifndef __Tree__TreeNode__
#define __Tree__TreeNode__

#include <iostream>
#include <vector>

template <class T>
struct TreeNode {
    TreeNode<T>() { };
    TreeNode<T>(T& val) { value = val; parent = NULL; children = *new std::vector<TreeNode<T>* >(); }
    TreeNode<T>(T& val, TreeNode<T> &parent) { value = val; this->parent = parent; children = new std::vector<TreeNode<T> >(); }
    TreeNode<T>(T& val, TreeNode<T> &parent, std::vector< TreeNode<T> > *children) { value = val; this->parent = parent; this->parent->addChild(this); this->children = children;  }
    void addChild(TreeNode<T> *child) { children.push_back(child); child->setParent(this); }
    TreeNode<T>* getChild(int i) { TreeNode<T> *t = children.at(i); return t; }
    unsigned long numChildren() { return children.size(); }
    void setParent(TreeNode<T>* parent) { this->parent = parent; }
    
    T value;
    std::vector< TreeNode<T>* > children;
    TreeNode<T> *parent;
};

#endif /* defined(__Tree__TreeNode__) */
