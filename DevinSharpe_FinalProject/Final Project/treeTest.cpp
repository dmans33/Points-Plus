//
//  treeTest.cpp
//  CSCI 2270
//
//  Created by Devin Sharpe on 4/16/19.
//  Copyright © 2019 Devin Sharpe. All rights reserved.
//

#include <stdio.h>
#include "GroupTree.hpp"
#include <iostream>
#include <string>
using namespace std;
int main (){
    groupBST B1;
    B1.addNode("dmans33", 13, 30, 70);
    B1.addNode("panda", 6, 30, 70);
    B1.addNode("cat", 3, 30, 70);
    B1.addNode("squash", 14, 30, 70);
    B1.addNode("paula", 24, 30, 70);
    B1.addNode("koala", 2, 30, 70);
    B1.addNode("bear", 17, 30, 70);
    B1.addNode("tiger", 11, 30, 70);
    B1.addNode("lion", 29, 30, 70);
    B1.addNode("bird", 2, 30, 70);
    B1.addNode("penguin", 20, 30, 70);
    
    B1.printLeaderboard();
    
    
    B1.deleteNode("dmans33");
    B1.deleteNode("panda");
    B1.deleteNode("bear");
    

    cout<<"AFTER DELETION"<<endl;
    B1.printLeaderboard();
    
    
    B1.addXP("squash", 100);
    B1.addCoins("squash",100);

    
    
}
