//
//  GroupTree.hpp
//  CSCI 2270
//
//  Created by Devin Sharpe on 4/13/19.
//  Copyright © 2019 Devin Sharpe. All rights reserved.
//

#ifndef GroupTree_hpp
#define GroupTree_hpp
#include <iostream>
#include <stdio.h>
#include <vector>
#include "StructDef.h"



struct Node{
    std::string uName;
    int level;
    int XP;
    int coins;
    std::vector <Assignments> userAssignments;
    Node *left=nullptr;
    Node *right=nullptr;
};




class groupBST{
public:
    groupBST();
    ~groupBST();
    void printLeaderboard();
    void addNode(std::string userName, int whatLevel, int experience, int currency);
    void deleteNode(std::string userName);
    Node* searchNode(std::string userName);
    void addXP(std::string userName, int amount);
    void addCoins(std::string userName, int amount);
    void setAdmin(std::string leader);
    void setName(std::string name);
    std::string getAdmin();
    std::string getName();
    void setCode(std::string code);
    std::string getCode();
    void loadAssignments(std::string name, int points, int xp);
    void loadRewards(std::string name, int cost);
    std::vector<Assignments> getUserAssignmentsVector();
    void addToUserVector(std::string name, Assignments A1);
    void adminViewRewards();
    void userViewRewards(std::string user);
    void adminViewAssignments();
    void userViewAssignments(std::string name);
    void deleteGroup();
    void setTreeName(std::string nameOfTree);
    void addReward();
    void addAssignment();
    void deleteUserMembership(std::string name);
    void addLevel(int numLevel, int howMuchXP, int coins);
    void addPointsManual(std::string name);
    void levelStatus(std::string name);
    void viewUsedRewards();
    void completeAssignment(std::string name);
    void viewCompletionList();
private:
    Node* createNode(std::string userName, int whatLevel, int experience, int currency);
    void printLeaderboardHelper(Node* currNode);
    Node* addNodeHelper(Node *currNode,std::string userName, int whatLevel, int experience, int currency);
    Node* deleteNodeHelper(Node *currNode,int lValue);
    Node* searchNodeHelper(Node *currNode,std::string userName);
    void changeCompletion(std::string name, int index);
    Node *root;
    Node *found;
    std::string admin;
    std::string treeName;
    std::string groupCode;
    std::vector <Rewards> rewards;
    std::vector <Assignments> assignments;
    std::vector <Level> levels;
    
};

#endif /* GroupTree_hpp */
