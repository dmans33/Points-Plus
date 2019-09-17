//
//  Groups.cpp
//  CSCI 2270
//
//  Created by Devin Sharpe on 4/15/19.
//  Copyright © 2019 Devin Sharpe. All rights reserved.
//

#include "Groups.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

Groups::Groups(){
    groupName="";
    joinCode="";
    success=false;
}


//Deals with creating a group
void Groups::createGroupName(string accountAdmin){
    success=false;
    
    string gName,line;
    bool verify=false;
    bool exit=false;
    cout<<"If at any time you would like to cancel this proccess please type exit"<<endl;
    cout<<endl;
    cout<<"*******************"<<endl;
    cout<<"GROUP CREATION!"<<endl;
    cout<<"*******************\n"<<endl;
    ifstream inFile;
    inFile.open("groupNames.txt");
    if (inFile.fail()){
        cout<<"The groupNames.txt file failed to open"<<endl;
    }
    cout<<"GROUP NAME"<<endl;
    cout<<"-----------"<<endl;
    while (verify==false){
        verify=true;
        cout<<"Please Name the Group (no spaces)"<<endl;
        getline (cin,gName);
        if (gName=="exit"){
            exit=true;
            break;
        }
        for (int i=0;i<gName.length();i++){
            if (gName[i]==' '){
                cout<<"There must be no spaces in the group name. Try again!"<<endl;
                verify=false;
                break;
            }
        }
        if (gName.length()==0){
            cout<<"Looks like you didn't enter anything! Try again!"<<endl;
            verify=false;
        }        
        if (verify==true){
            while (getline(inFile,line)){
                if (line==gName){
                    cout<<"There is already a group named that. Please chose a different name!"<<endl;
                    verify=false;
                    break;
                    
                }
            }
        }
    }
    inFile.close();
    if (exit==true){
        cout<<"Group creation has been cancelled"<<endl;
        return;
    }
    
    cout<<"\nJOIN CODE"<<endl;
    cout<<"----------"<<endl;
    groupName=gName;
    bool verifyPass=false;
    string password,confirmation;
    cout<<"Next you will need to enter a code which will be used to join this group."<<endl;
    cout<<"Anyone who wishes to join this group must know the code."<<endl;
    cout<<endl;
    while (verifyPass==false){
        cout<<"Please Enter a Code"<<endl;
        getline(cin, password);
        if (password=="exit"){
            cout<<"Group creation has been cancelled"<<endl;
            return;
        }
        cout<<"Please Enter Your Code Again:"<<endl;
        getline(cin, confirmation);
        if (confirmation=="exit"){
            cout<<"Group creation has been cancelled"<<endl;
            return;
        }
        if (password==confirmation){
            verifyPass=true;
        }
        else{
            cout<<"Your Codes do not match. Try again!"<<endl;
        }
        if (confirmation.length()==0){
            cout<<"A code is required!"<<endl;
            verifyPass=false;
        }
    }
    cout<<"Please write down your code ("<<password<<")\nProvide it to the people you wish to join your group along with the group name!"<<endl;
    joinCode=password;
    createAssignments(accountAdmin);
}



void Groups::createAssignments(string accountAdmin){
    cout<<"\nASSIGNMENTS/ACTIVITIES"<<endl;
    cout<<"-----------------------"<<endl;
    string skip;
    cout<<"Now you must enter the assignments/activities availiable for group members to complete"<<endl;
    cout<<"Activities can be added and deleted later but it is suggested you have some to begin with"<<endl;
    cout<<"Recomended that point values:"<<endl;
    cout<<"5-20 (for smaller assignments)"<<endl;
    cout<<"30-50 (for medium sized assignments)"<<endl;
    cout<<"50-100 (for larger assignments)"<<endl;
    cout<<"100-200 (for large projects and such)"<<endl;
    cout<<endl;

    cout<<"Would you like to skip this step and add assignments individually later? (Y/N)"<<endl;
    getline (cin, skip);
    if (skip=="exit"){
        cout<<"Group creation has been cancelled"<<endl;
        return;
    }
    if (skip=="Y" || skip=="y" || skip=="yes" ||skip=="Yes"){
        cout<<"You have chosen to skip this step, make sure to add assignments/activities later"<<endl;
        levelCreation(accountAdmin);
        return;
    }
    if (skip.length()==0){
        cout<<"Since nothing was entered this step is being skipped by default. Assignments can be added later!"<<endl;
        levelCreation(accountAdmin);
        return;
    }
    cout<<endl;
    cout<<"Type done when you have finished entering all assignments/activities"<<endl;
    Assignments A1;
    string name, points;
    int pointValue;
    bool validName;
    bool done=false;
    while (!done){
        while (true){
            validName=true;
            cout<<"\nPlease enter the assignment/activity name"<<endl;
            getline (cin, name);
            if (name=="done"){
                cout<<"You have finished with this stage of the setup!"<<endl;
                //CALL NEXT STEP
                levelCreation(accountAdmin);
                done=true;
                return;
            }
            if (name=="exit"){
                cout<<"Group creation has been cancelled"<<endl;
                return;
            }
            if (name.length()==0){
                cout<<"A name is required"<<endl;
                validName=false;
            }
            if (validName==true){
                break;
            }
        }
        while (true){
            cout<<"Please enter the point value you would like members to recieve upon completion of this assignment/activity"<<endl;
            getline(cin, points);
            if (points=="done"){
                cout<<"You have finished with this stage of the setup!"<<endl;
                //CALL NEXT STEP
                levelCreation(accountAdmin);
                done=true;
                return;
            }
            if (points=="exit"){
                cout<<"Group creation has been cancelled"<<endl;
                return;
            }
            
            try{
                pointValue=stoi(points);
                break;
            }
            catch(exception&e){
                cout<<"Please enter an integer value"<<endl;
            }
        }
        A1.name=name;
        A1.pointValue=pointValue;
        A1.completed=false;
        assignmentList.push_back(A1);
        cout<<"You have added "<<A1.name<<" with the point value of "<<A1.pointValue<<endl;
    }
    
}

void Groups::levelCreation(string accountAdmin){
    int totalPoints=0;
    string points;
    cout<<"\nLEVEL OPTIMIZATION"<<endl;
    cout<<"------------------"<<endl;
    //**************************
    //LEVEL BALANCING ALGORITHM
    //**************************
    for (int i=0;i<assignmentList.size();i++){
        
        assignmentList[i].XP=195*(assignmentList[i].pointValue);
        totalPoints+=assignmentList[i].XP;
    }
    
    ofstream outFile;
    outFile.open(groupName+"extra.txt");
    int temp=1500;
    int level=1;
    int sum=1;
    for (int i=0;i<50;i++){
        outFile<<temp<<endl;
        if ((i+1)%10==0){
            outFile<<10<<endl;
        }
        else if ((i+1)%5==0){
            outFile<<5<<endl;
        }
        else{
            outFile<<2<<endl;
        }
        sum+=temp;
        if (totalPoints>sum){
            level++;
        }
        temp=double(temp)*1.08;
    }
    outFile<<"HOLDER1"<<endl;
    outFile<<"HOlDER2"<<endl;
    outFile.close();
    
    
    int maxCoins=0;
    for (int b=2;b<=level;b++){
        
        if (b%10==0){
            maxCoins+=10;
        }
        else if (b%5==0){
            maxCoins+=5;
        }
        else{
            maxCoins+=2;
        }
    }
        
    
    
    
    cout<<"With the assignments you have entered already the max level is currently level "<<level<<endl;
    //1500, 1875, 2344, 2930
    //1.25
    
    
    
    
    
    //Call next step
    rewardSelection(accountAdmin,maxCoins);
}

void Groups::rewardSelection(std::string accountAdmin, int fullCoins){
    string rewardName, coinAmmount;
    int cost;
    cout<<"\nREWARDS"<<endl;
    cout<<"--------"<<endl;
    cout<<"Currency System:"<<endl;
    cout<<"Group members will earn 10 coins upon reaching levels that are a multiple of 10"<<endl;
    cout<<"Group members will earn 5 coins upon reaching levels that are a multiple of 5"<<endl;
    cout<<"Group members will earn 2 coins for ever other level"<<endl;
    
    
    
    cout<<"Right now with the current assignments entered members will be able to earn a maximum of "<<fullCoins<<" coins"<<endl;
    cout<<"Please price rewards accordingly"<<endl;
    
    
    
    
    
    
    cout<<"**Please type done when finished**"<<endl;
    bool moveOn;
    while (true){
        moveOn=true;
        cout<<"\nPlease enter a reward"<<endl;
        getline (cin, rewardName);
        if (rewardName=="exit"){
            cout<<"Group creation has been cancelled"<<endl;
            return;
        }
        if(rewardName=="done"){
            cout<<"Ok! Finalizing group"<<endl;
            finalizeGroup(accountAdmin);
            return;
        }
        if (rewardName.length()==0){
            cout<<"A Name is required!"<<endl;
            moveOn=false;
        }
        if (moveOn==true){
            while (true){
                cout<<"Please enter how many coins this reward will cost to redeem"<<endl;
                getline(cin, coinAmmount);
                if (coinAmmount=="exit"){
                    cout<<"Group creation has been cancelled"<<endl;
                    return;
                }
                if (coinAmmount=="done"){
                    cout<<rewardName<<" will not be added since creation was canceled prior to cost submission"<<endl;
                    cout<<"Finalizing group"<<endl;
                    finalizeGroup(accountAdmin);
                    return;
                }
                try{
                    cost=stoi(coinAmmount);
                    if (cost<0){
                        cout<<"The cost must not be a negative value"<<endl;
                    }
                    else{
                        break;
                    }
                }
                catch(exception&e){
                    cout<<"Please enter an integer value"<<endl;
                }
            }
            Rewards R1;
            R1.name=rewardName;
            R1.cost=cost;
            rewardList.push_back(R1);
        }
    }
    
}


void Groups::finalizeGroup(string accountAdmin){
    ofstream outFile;
    outFile.open(groupName+".txt");
    if (outFile.fail()){
        cout<<"New group couldn't be created"<<endl;
        return;
    }
    outFile<<accountAdmin<<endl;
    outFile<<groupName<<endl;
    outFile<<joinCode<<endl;
    outFile<<"ASSIGNMENTS"<<endl;
    outFile<<endl;
    for (int i=0;i<assignmentList.size();i++){
        outFile<<assignmentList[i].name<<endl;
        outFile<<assignmentList[i].pointValue<<endl;
        outFile<<assignmentList[i].XP<<endl;
    }
    outFile<<"REWARDS"<<endl;
    outFile<<endl;
    for (int i=0;i<rewardList.size();i++){
        outFile<<rewardList[i].name<<endl;
        outFile<<rewardList[i].cost<<endl;
    }
    outFile<<"USERS"<<endl;
    outFile<<endl;
    outFile.close();
    
    //*************************************
    //MIGHT MAKE IT ITS OWN FUNCTION MAYBE
    //************************************
    cout<<"\nGROUP OVERVEIW"<<endl;
    cout<<"--------------"<<endl;
    cout<<"Name: "<<groupName<<endl;
    cout<<"\nJoin Code: "<<joinCode<<endl;
    cout<<"\nAssignments/Activites:"<<endl;
    for (int i=0;i<assignmentList.size();i++){
        cout<<assignmentList[i].name<<" ("<<assignmentList[i].pointValue<<" points)"<<endl;
    }
    cout<<"\nRewards: "<<endl;
    for (int b=0;b<rewardList.size();b++){
        cout<<rewardList[b].name<<" ("<<rewardList[b].cost<<" coins)"<<endl;
    }
    cout<<endl;
    
    adminGroupJoin(accountAdmin);
    cout<<"************************"<<endl;
    cout<<"GROUP CREATION FINALIZED"<<endl;
    cout<<"************************"<<endl;
    cout<<"-To view you group please do so from the main menu"<<endl;
    cout<<endl;
    success=true;
    
    ofstream outFile2;
    outFile2.open("groupNames.txt",ios::app);
    if (outFile2.fail()){
        cout<<"File failed to open"<<endl;
    }
    outFile2<<groupName<<endl;
}

void Groups::adminGroupJoin(std::string accountAdmin){
    string line;
    ifstream inFile;
    inFile.open("Userinfo.txt");
    ofstream outFile("tempStorage.txt");
    if (inFile.fail()){
        cout<<"Userinfo.txt file failed to open"<<endl;
    }
    if (outFile.fail()){
        cout<<"tempStorage.txt failed to open"<<endl;
    }
    while (getline(inFile,line)){
        outFile<<line<<endl;
        if (line==accountAdmin){

            break;
        }
    }
    getline(inFile, line);
    outFile<<line<<endl;
    getline(inFile, line);
    outFile<<line<<endl;
    getline(inFile, line);
    if (line.length()==0){
        line=groupName;
    }
    else{
        line=line+" "+groupName;
    }
    outFile<<line<<endl;
    while (getline(inFile,line)){
        outFile<<line<<endl;

    }
    remove("Userinfo.txt");
    char old[]="tempStorage.txt";
    char newName[]="Userinfo.txt";
    rename(old,newName);
}





void Groups::loadGroup(std::string gName, std::string user){
    string checkAdmin=user;
    groupName=gName;
    ifstream inFile;
    inFile.open(groupName+".txt");
    if (inFile.fail()){
        cout<<"This group is currently under maitenence. Please check back in a little!"<<endl;
        return;
    }
    groupBST T1;
    T1.setTreeName(gName);
    string line;
    getline(inFile,line);
    T1.setAdmin(line);
    getline(inFile,line);
    T1.setName(line);
    getline(inFile,line);
    T1.setCode(line);
    getline(inFile,line);
    getline(inFile,line);
    Assignments A1;
    string name;
    int points,XP;
    while (true){
        getline(inFile,line);
        if (line=="REWARDS"){
            break;
        }
        name=line;
        getline(inFile,line);
        points=stoi(line);
        getline(inFile,line);
        XP=stoi(line);
        T1.loadAssignments(name, points, XP);
    }
    getline(inFile,line);
    while (true){
        getline(inFile,line);
        if (line=="USERS"){
            break;
        }
        name=line;
        getline(inFile,line);
        points=stoi(line);
        T1.loadRewards(name, points);
    }
    getline(inFile,line);
    
    string FileuName, FileLevel, FileXP, FileCoins, complete;
    
    //ON USERS LINE NOW
    while (getline(inFile,line)){
        istringstream iss(line);
        getline (iss,FileuName,' ');
        getline(iss,FileLevel,' ');
        getline (iss,FileXP,' ');
        getline(iss,FileCoins,' ');
        T1.addNode(FileuName, stoi(FileLevel), stoi(FileXP), stoi(FileCoins));
        //DEAL WITH ASSIGNMENT VECTOR COMPLETION ALGORITHM
        
        getline(inFile,line);
        istringstream iss2(line);
        
        Assignments A1;
        vector<Assignments> finishCompletion;
        finishCompletion=T1.getUserAssignmentsVector();
        for (int i=0;i<finishCompletion.size();i++){
            getline(iss2, complete, ' ');
            A1=finishCompletion[i];
            if (complete=="FALSE"){
                A1.completed=false;
            }
            else{
                A1.completed=true;
            }
            T1.addToUserVector(FileuName, A1);
        }
    }
    
    
    ifstream inFile3;
    int numLevel=1;
    int howMuch, coins;
    inFile3.open(groupName+"extra.txt");
    if (inFile3.fail()){
        cout<<"Something messed up"<<endl;
    }
    while (getline(inFile3,line)){
        if (line=="HOLDER1"){
            break;
        }
        howMuch=stoi(line);
        getline(inFile3,line);
        coins=stoi(line);
        T1.addLevel(numLevel, howMuch, coins);
    }
    inFile3.close();
    
    
    //loaded info successful
    if (checkAdmin==T1.getAdmin()){
        //user is admin of the group
        adminControl(gName,T1);
        //return;
    }
    else{
        //user is not an admin
        userControl(gName,T1, user);
        //return;
    }
    
    
    
    
}



void Groups::joinGroup(std::string userName){
    success=false;
    string toJoin,line, code;
    bool exists=false;
    ifstream inFile;
    inFile.open("groupNames.txt");
    if (inFile.fail()){
        cout<<"Failed to opern groupNames.txt"<<endl;
        return;
    }
    cout<<"Please enter the group name"<<endl;
    getline (cin, toJoin);
    if (toJoin.length()==0){
        cout<<"You must enter a name! You must restart the process to try again"<<endl;
        return;
    }
    while (getline(inFile,line)){
        if (line==toJoin){
            exists=true;
            break;
        }
    }
    inFile.close();
    if (exists==false){
        cout<<"This group does not exist please make sure you have the right name"<<endl;
        return;
    }
    
    inFile.open("Userinfo.txt");
    if (inFile.fail()){
        cout<<"Failed to open file"<<endl;
        return;
    }
    while (getline(inFile, line)){
        if (line==userName){
            break;
        }
    }
    string line2;
    getline(inFile,line);
    getline(inFile,line);
    getline(inFile,line);
    istringstream iss(line);
    while (getline(iss,line2,' ')){
        if (line2==toJoin){
            cout<<"You already are a member of this group!"<<endl;
            return;
        }
    }
    inFile.close();
    
    inFile.open(toJoin+".txt");
    if (inFile.fail()){
        cout<<"Couldn't open group file"<<endl;
        return;
    }
    cout<<"Please enter the join code for this group:"<<endl;
    getline (cin, code);
    getline(inFile,line);
    getline(inFile,line);
    getline(inFile,line);
    inFile.close();
    
    
    if (line==code){
        //add to group list
        
        ifstream in_file;
        in_file.open(toJoin+".txt");
        if (in_file.fail()){
            cout<<"failed to open file"<<endl;
            return;
        }
        getline (in_file,line);
        getline (in_file,line);
        getline (in_file,line);
        getline (in_file,line);
        getline (in_file,line);
        int count=0;
        while (true){
            getline (in_file,line);
            if (line=="REWARDS"){
                break;
            }
            getline (in_file,line);
            getline (in_file,line);
            count++;
            
        }
        in_file.close();
        
        ofstream outFile;
        outFile.open(toJoin+".txt",ios::app);
        if (outFile.fail()){
            cout<<"couldn't open file"<<endl;
            return;
        }
        outFile<<userName<<" 1 0 0"<<endl;
        //ADD ALL FALSES HERE
        for (int i=0;i<count;i++){
            outFile<<"FALSE ";
        }
        outFile<<endl;
        outFile.close();
        
        //add to userInfo list
        ifstream inFile2;
        inFile2.open("Userinfo.txt");
        ofstream outFile2("tempStorage.txt");
        if (inFile2.fail()){
            cout<<"Userinfo.txt file failed to open"<<endl;
        }
        if (outFile2.fail()){
            cout<<"tempStorage.txt failed to open"<<endl;
        }
        while (getline(inFile2,line)){
            outFile2<<line<<endl;
            if (line==userName){
                break;
            }
        }
        getline(inFile2, line);
        outFile2<<line<<endl;
        getline(inFile2, line);
        outFile2<<line<<endl;
        getline(inFile2, line);
        if (line.length()==0){
            line=toJoin;
        }
        else{
            line=line+" "+toJoin;
        }
        outFile2<<line<<endl;
        while (getline(inFile2,line)){
            outFile2<<line<<endl;
            
        }
        remove("Userinfo.txt");
        char old[]="tempStorage.txt";
        char newName[]="Userinfo.txt";
        rename(old,newName);
        
        cout<<"\nYou have successfully joined "<<toJoin<<"!"<<endl;
        success=true;
        cout<<endl;
        groupName=toJoin;
        return;
    
    }
    
    else{
        cout<<"Code incorrect. Group not joined"<<endl;
        return;
    }
}
std::string Groups::getGroupName(){
    return groupName;
}

bool Groups::getSuccess(){
    return success;
}




void adminGroupMenu(){
    cout<<"\nSelect An Option Below"<<endl;
    cout<<"----------------------"<<endl;
    cout<<"1) View Group Leaderboard"<<endl;
    cout<<"2) Add Points"<<endl;
    cout<<"3) Add Reward to the Shop"<<endl;
    cout<<"4) View Rewards"<<endl;
    cout<<"5) See Used Rewards"<<endl;
    cout<<"6) Add New Assignments"<<endl;
    cout<<"7) View Assignments"<<endl;
    cout<<"8) See Group Assignment Completions"<<endl;
    cout<<"9) Delete User From Group"<<endl;
    cout<<"10) Delete Group"<<endl;
    cout<<"11) GO BACK"<<endl;
    
    
    
    
}

void groupMenu(){
    cout<<"\nSelect An Option Below"<<endl;
    cout<<"----------------------"<<endl;
    cout<<"1) View Leaderboard"<<endl;
    cout<<"2) View Level Status"<<endl;
    cout<<"3) View Assignments"<<endl;
    cout<<"4) Visit Rewards Shop"<<endl;
    cout<<"5) Mark Assignment Completed"<<endl;
    cout<<"6) Leave Group"<<endl;
    cout<<"7) GO BACK"<<endl;
    
    

    
}



void Groups::adminControl(string name, groupBST T1){
    //T1 is already loaded so it can now be used for manipulation
    Node *check;
    string choice="3";
    int testing;
    bool valid;
    while (choice!="11"){
        valid=true;
        adminGroupMenu();
        getline (cin, choice);
        try{
            testing=stoi(choice);
        }
        catch(exception&e){
            cout<<"Please enter an integer value corresponding to your desired choice"<<endl;
            valid=false;
        }
        string input;
        if (valid){
            switch (stoi(choice)){
                case 1:
                    T1.printLeaderboard();
                    break;
                case 2:
                    //add points
                    //******************
                    cout<<"Which User would you like to add points to"<<endl;
                    getline(cin,input);
                    check=T1.searchNode(input);
                    if (check==nullptr){
                        cout<<"Can't add points to a user who is not a member"<<endl;
                        break;
                    }
                    T1.addPointsManual(input);
                    cout<<"Please reload the group to see updates"<<endl;
                    return;
                case 3:
                    //add reward
                    T1.addReward();
                    break;
                case 4:
                    //view rewards/shop
                    T1.adminViewRewards();
                    break;
                case 5:
                    //see used rewards
                    //****************
                    T1.viewUsedRewards();
                    
                    break;
                case 6:
                    //add assignment
                    T1.addAssignment();
                    break;
                case 7:
                    //view assignments
                    T1.adminViewAssignments();
                    break;
                case 8:
                    //see assignment completions
                    //***************************
                    T1.viewCompletionList();
                    cout<<"Please reload group to view updates"<<endl;
                    return;
                    break;
                case 9:
                    //delete user
                    cout<<"Please enter the username of the person you would like to delete or cancel to go back"<<endl;
                    getline(cin, input);
                    if (input=="cancel"){
                        cout<<"Deletion Canceled"<<endl;
                    }
                    else{
                        T1.deleteUserMembership(input);
                        cout<<"Please reload the group to see updates"<<endl;
                        return;
                    }
                    break;
                    
                case 10:
                //delete groupc
                    cout<<"Are you sure you would like to delete the group? (Y/N)"<<endl;
                    getline (cin, input);
                    if (input=="Y"||input=="y"){
                        T1.deleteGroup();
                        return;
                    }
                    cout<<"Group not deleted"<<endl;
                    break;
                case 11:
                    //go back
                    return;
                default:
                    cout<<"This is an invalid option!"<<endl;
                    break;
            }
        }
        
    }
    
    
    
    
}



void Groups::userControl(string name,groupBST T1,string user){
    string choice="4";
    int testing;
    bool valid;
    while (choice!="8"){
        valid=true;
        groupMenu();
        getline (cin, choice);
        try{
            testing=stoi(choice);
        }
        catch(exception&e){
            cout<<"Please enter an integer value corresponding to your desired choice"<<endl;
            valid=false;
        }
        string input;
        if (valid){
            switch (stoi(choice)){
                case 1:
                    //leaderboard
                    T1.printLeaderboard();
                    break;
                case 2:
                    //level status
                    T1.levelStatus(user);
                    break;
                case 3:
                    //View Activities
                    T1.userViewAssignments(user);
                    break;
                case 4:
                    //reward shop
                    T1.userViewRewards(user);
                    break;
                case 5:
                    //mark assignment completed
                    T1.completeAssignment(user);
                    break;
                case 6:
                    //leave group
                    T1.deleteUserMembership(personName);
                    cout<<"You have left the group!"<<endl;
                    choice="8";
                    break;
                case 7:
                    //go back
                    return;
                default:
                    cout<<"This is an invalid option!"<<endl;
                    break;
            }
        }
    }
}


void Groups::setPerson(std::string name){
    personName=name;
}
