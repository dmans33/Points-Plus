//
//  Account.hpp
//  CSCI 2270
//
//  Created by Devin Sharpe on 4/15/19.
//  Copyright © 2019 Devin Sharpe. All rights reserved.
//

#ifndef Account_hpp
#define Account_hpp
#include <string>
#include <vector>

#include <stdio.h>

struct User{
    std::string name;
    std::string uName;
    std::vector <std::string> groupMembership;
};

class Account{
public:
    bool newAccount();
    User login(User toLogin);
};

#endif /* Account_hpp */
