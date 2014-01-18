//
//  main.cpp
//  Tree
//
//  Created by Joseph Pecoraro on 2/24/13.
//  Copyright (c) 2013 Joseph Pecoraro. All rights reserved.
//

#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml.hpp"
#include "Species.h"
#include "Tree.cpp"
#include "TreeNode.h"
#include <stack>

using namespace std;
using namespace rapidxml;

//used for running through command line
int numarg;
const char ** arg;
int currentarg;

//user input variables
int option;
string species1;
string species2;


//nodes, trees, and other variable for parsing the file, and writing it to a tree
int level = 0;
Species root = *new Species("Root", "Root", "Root", 1);
TreeNode<Species> *rootNode = new TreeNode<Species>(root);
Tree<Species> dataStructure = *new Tree<Species>(*rootNode);

stack< TreeNode<Species>* > nodes = *new stack< TreeNode<Species>* >();

//parses the taxonomies. returns Tree Node that is created
TreeNode<Species>* parseTax(xml_node<> *tax) {
    xml_node<> *value = tax->first_node();
    string sciname = "", commname = "", rank = "";
    while(value!=NULL) {
        string name = value->name();
        if (name == "scientific_name") {
            sciname = value->value();
        }
        else if (name == "common_name") {
            commname = value->value();
        }
        else if (name == "rank") {
            rank = value->value();
        }
        value = value->next_sibling();
    }
    if (sciname != "" || commname!= "" || rank!="") {
        Species s = *new Species(sciname, commname, rank, level);
        return new TreeNode<Species>(s);
    }
    return NULL;
}

//parses through the clades, parsing taxonomies at each level, and adding the nodes created from the taxonomies to one stack used for adding to tree structure note: goes through in level order
void parseClade(xml_node<> *clade) {
    xml_node<> *tax;
    clade = clade->first_node("clade");
    level++;
    while (clade != NULL) {
        parseClade(clade);
        tax = clade->first_node("taxonomy");
        level++;
        if (tax != NULL) {
            nodes.push(parseTax(tax));
        }
        clade = clade->next_sibling("clade");
        level--;
    }
    level--;
}

//begin parsing the file (retrieve the first node)
void parseFile() {
	xml_document<> doc;
	xml_node<> * root_node;

	ifstream theFile ("/Users/Joseph/Dropbox/College/COP3530/Tree/Tree/species.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');

	doc.parse<0>(&buffer[0]);

	root_node = doc.first_node()->first_node();
    
    parseClade(root_node->first_node());
}

//adds the data to the tree structure. uses 1 stack. Because the level is kept track of, and because it is gone through in level order, the parents and siblings are known
TreeNode<Species> *parent;
TreeNode<Species> *current;
void addToTree(TreeNode<Species> *n) {
    parent = n;
    int pl = parent->value.getLevel();
    int cl;
    while (!nodes.empty()) {
        current = nodes.top();
        nodes.pop();
        pl = parent->value.getLevel();
        cl = current->value.getLevel();
        while (true) {
            if (cl <= pl) {
                parent = parent->parent;
                pl = parent->value.getLevel();
            }
            else if (cl > pl) {
                parent->addChild(current);
                parent = current;
                break;
            }
        }
    }
}

//prints out lineage for a species
void getLineage() {
    dataStructure.getLineage(species1);
}

//finds common lineage for two species and prints it out
void getCommonLineage() {
    dataStructure.getCommonLineage(species1, species2);
}

//gets user input for 1 species for lineage to be found
void get1Species() {
    cout << "Please enter the name of the species of interest:" << endl;
    cin.ignore();
    getline(cin, species1);
    
    cout <<endl;
    
    getLineage();
}

//gets user input for two species to be compared
void get2Species() {
    cout << "Please enter the name of the first species" << endl;
    cin.ignore();
    getline(cin, species1);
    cout << endl << "Please enter the name of the second species:" << endl;
    getline(cin, species2);
    
    cout << endl;
    getCommonLineage();
}

//get species from command line (for finding lineage)
void get1Species1() {
    species1 = arg[currentarg];
    currentarg++;
    
    getLineage();
}

//get species from command line (for finding common lineage)
void get2Species2() {
    species1 = arg[currentarg];
    currentarg++;
    species2 = arg[currentarg];
    currentarg++;
    
    getCommonLineage();
}

//uses option, calls functions for getting species
void useOption() {
    switch (option) {
        case 1:
            get1Species();
            break;
        case 2:
            get2Species();
            break;
        case 3:
            exit(0);
    }
}

//use option from command line (calls command line versions of get1species and get2species)
void useOption1() {
    switch (option) {
        case 1:
            get1Species1();
            break;
        case 2:
            get2Species2();
            break;
        case 3:
            exit(0);
    }
}

//asks user input for option
void getOption() {
    cout << endl << "Please choose from the following options: " << endl << "\t1.Get the lineage of a species" << endl << "\t2.Get the common lineage of two species" << endl << "\t3.Exit program" <<endl << endl;
    cin >> option;
    useOption();
}

//runs UI verion of program
void run1() {
    cout << "Welcome to the Tree of Life" << endl;
    while (option!=3)
        getOption();
}

//runs command line version of program
void run2() {
    for (currentarg = 1; currentarg < numarg; currentarg ++) {
        option = atoi(arg[currentarg]);
        currentarg++;
        useOption1();
    }
}

//main, calls UI version or command version based on number of arguments
int main(int argc, const char * argv[])
{
    parseFile();
    addToTree(rootNode);
    
    if (argc == 1) {
        run1();
    }
    else {
        numarg = argc;
        arg = argv;
        run2();
    }
    return 0;
}

