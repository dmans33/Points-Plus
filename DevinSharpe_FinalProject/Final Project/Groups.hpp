//
//  Groups.hpp
//  CSCI 2270
//
//  Created by Devin Sharpe on 4/15/19.
//  Copyright © 2019 Devin Sharpe. All rights reserved.
//

#ifndef Groups_hpp
#define Groups_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "GroupTree.hpp"




class Groups{
public:
    Groups();
    void createGroupName(std::string accountAdmin);
    void loadGroup(std::string gName, std::string user);
    void joinGroup(std::string userName);
    std::string getGroupName();
    bool getSuccess();
    void setPerson(std::string name);
    
    
private:
    std::string groupName;
    std::string joinCode;
    std::string personName;
    std::vector <Assignments> assignmentList;
    std::vector <Rewards> rewardList;
    void createAssignments(std::string accountAdmin);
    void levelCreation(std::string accountAdmin);
    void rewardSelection(std::string accountAdmin, int fullCoins);
    void finalizeGroup(std::string accountAdmin);
    void adminGroupJoin(std::string accountAdmin);
    void adminControl(std::string name, groupBST T1);
    void userControl(std::string name, groupBST T1, std::string user);
    bool success;
};

#endif /* Groups_hpp */
