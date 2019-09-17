//
//  Driver.cpp
//  CSCI 2270
//
//  Created by Devin Sharpe on 4/8/19.
//  Copyright © 2019 Devin Sharpe. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Groups.hpp"
#include "Account.hpp"


using namespace std;

int loginScreen(){
    string option="4";
    while (option!="1" && option!="2"){
        cout<<"Please Login or Create a New Account"<<endl;
        cout<<"------------------------------------"<<endl;
        cout<<"1) Login"<<endl;
        cout<<"2) Create a New Account"<<endl;
        cout<<"3) Exit"<<endl;
        getline(cin,option);
        if (option=="1"||option=="2"||option=="3"){
            break;
        }
        else{
            cout<<"Invalid choice. Please select 1 to login, 2 to create a new account, or 3 to exit"<<endl;
        }
    }
    return stoi(option);
    
}









void starterMenu(){
    cout<<"\nSelect An Option Below"<<endl;
    cout<<"----------------------"<<endl;
    cout<<"1) See All Groups Joined"<<endl;
    cout<<"2) Select a Group to view"<<endl;
    cout<<"3) Join a New Group"<<endl;
    cout<<"4) Create a New Group"<<endl;
    cout<<"5) Logout"<<endl;
}




int derivedMain(){
    User loggedIn;
    Account A1;
    
    //Log in the User and make sure their information is loaded;
    
    int toLogin=2;
    while (toLogin==2){
        toLogin=loginScreen();
        if (toLogin==1){
            loggedIn=A1.login(loggedIn);
        }
        else if (toLogin==2){
            A1.newAccount();
        }
        else{
            cout<<"GoodBye"<<endl;
            exit(0);
        }
    }
    
    cout<<endl;
    cout<<"**********************"<<endl;
    cout<<"Welcome "<<loggedIn.uName<<endl;
    cout<<"**********************"<<endl;
    cout<<endl;
    
    Groups G1;
    G1.setPerson(loggedIn.uName);
    string userChoice="4";
    string groupName;
    bool found=false;
    bool check;
    
    while(userChoice!="5"){
        bool valid=false;
        //load group membership

        while (true){
            if (loggedIn.groupMembership.size()==0){
                break;
            }
            loggedIn.groupMembership.pop_back();
        }
        string line,line2;
        ifstream inFile;
        inFile.open("Userinfo.txt");
        if (inFile.fail()){
            cout<<"File failed to open"<<endl;
        }
        while (getline(inFile,line)){
            if (line==loggedIn.name){
                break;
            }
        }
        getline(inFile,line);
        istringstream iss(line);
        while (getline(iss,line2,' ')){
            loggedIn.groupMembership.push_back(line2);
        }
        inFile.close();
        //****
        starterMenu();
        int input;
        getline(cin, userChoice);
        try{
            input=stoi(userChoice);
            valid=true;

        }
        catch(exception&e){
            cout<<"Please enter an integer value"<<endl;
        }
        
        
        if (valid){
            switch (stoi(userChoice)){
                case 1:
                    if (loggedIn.groupMembership.size()==0){
                        cout<<"\nYou currently are not a member of any groups\n"<<endl;
                    }
                    else{
                        cout<<"\nYou are a member of the following groups:"<<endl;
                        for (int i=0; i<loggedIn.groupMembership.size();i++){
                            cout<<loggedIn.groupMembership[i]<<endl;
                        }
                        cout<<endl;
                    }
                    break;
                case 2:
                    cout<<"\nPlease enter the name of the group you would like to view:"<<endl;
                    getline(cin, groupName);
                    for (int i=0;i<loggedIn.groupMembership.size();i++){
                        if (loggedIn.groupMembership[i]==groupName){
                            found=true;
                            break;
                        }
                    }
                    if (groupName.length()==0){
                        cout<<"You must enter a name"<<endl;
                        break;
                    }
                    if (found==false){
                        cout<<"You do not belong to a group named "<<groupName<<endl;
                        cout<<"Choose Option 1 to see what groups you belong too"<<endl;
                    }
                    else{
                        //LOAD GROUP HERE
                        G1.loadGroup(groupName, loggedIn.uName);
                    }
                    break;
                case 3:
                    //join group
                    G1.joinGroup(loggedIn.uName);
                    check=G1.getSuccess();
                    if (check){
                        loggedIn.groupMembership.push_back(G1.getGroupName());
                    }
                    break;
                case 4:
                    //create group
                    G1.createGroupName(loggedIn.uName);
                    check=G1.getSuccess();
                    if (check){
                        loggedIn.groupMembership.push_back(G1.getGroupName());
                    }
                    
                    break;
                case 5:
                    cout<<"You have been logged out!\n"<<endl;
                    return 0;
                    break;
                default:
                    cout<<"Invalid Input! Please use the numerical option next to your desired action"<<endl;
                    break;
            }
        }
    }
    
    return 0;
    
}


int main (){
    while (true){
        derivedMain();
    }
    
    return 0;
}
