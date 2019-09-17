//
//  StructDef.h
//  CSCI 2270
//
//  Created by Devin Sharpe on 4/20/19.
//  Copyright © 2019 Devin Sharpe. All rights reserved.
//

#ifndef StructDef_h
#define StructDef_h

struct Assignments{
    std::string name;
    bool completed;
    int pointValue;
    int XP;
};

struct Rewards{
    std::string name;
    int cost;
};


struct Level{
    int whatLevel;
    int neededXP;
    int coins;
};


struct addPoints{
    std::string name;
    int howMany;
};

#endif /* StructDef_h */
