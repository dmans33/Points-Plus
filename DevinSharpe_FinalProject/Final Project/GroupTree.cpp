//
//  GroupTree.cpp
//  CSCI 2270
//
//  Created by Devin Sharpe on 4/13/19.
//  Copyright © 2019 Devin Sharpe. All rights reserved.
//

#include "GroupTree.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <cstdio>
using namespace std;

void destroyNode(Node *currNode){
    if(currNode!=NULL)
    {
        destroyNode(currNode->left);
        destroyNode(currNode->right);
        
        //delete currNode;
        currNode = NULL;
    }
}

groupBST::groupBST(){
    root=nullptr;
    found=nullptr;
    
}

groupBST::~groupBST(){
    destroyNode(root);
}


void groupBST::printLeaderboardHelper(Node* currNode){
    if (currNode!=nullptr){
        if (currNode->right!=nullptr){
            printLeaderboardHelper(currNode->right);
        }
        cout<<currNode->uName<<"-Level "<<currNode->level<<endl;
        if (currNode->left!=nullptr){
            printLeaderboardHelper(currNode->left);
        }
    }
    else{
        cout<<"No members have joined this group"<<endl;
    }
        
}

void groupBST::printLeaderboard(){
    printLeaderboardHelper(root);
    
}

Node* groupBST::createNode(std::string userName, int whatLevel, int experience, int currency){
    Node* newNode = new Node;
    newNode->uName = userName;
    newNode->level=whatLevel;
    newNode->XP=experience;
    newNode->coins=currency;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Node* groupBST::addNodeHelper(Node *currNode,std::string userName, int whatLevel, int experience,int currency){
    
    if(currNode == nullptr){
        if (root==nullptr){
            root=createNode(userName,whatLevel,experience,currency);
        }
        return createNode(userName,whatLevel,experience,currency);
    }
    else if(currNode->level <= whatLevel){
        currNode->right = addNodeHelper(currNode->right,userName,whatLevel,experience,currency);
    }
    else if(currNode->level > whatLevel){
        currNode->left = addNodeHelper(currNode->left,userName,whatLevel,experience,currency);
    }
    return currNode;
}


void groupBST::addNode(std::string userName, int whatLevel, int experience, int currency){
    Node *checkDuplicate;
    if (root!=nullptr){
        checkDuplicate=searchNode(userName);
        if (checkDuplicate!=nullptr){
            cout<<"This user already exists and can't be added twice"<<endl;
            return;
        }
    }
    addNodeHelper(root, userName, whatLevel, experience, currency);
}


Node* getMinValueNode(Node* currNode){
    while (currNode->left!=nullptr){
        currNode=currNode->left;
    }
    return currNode;
}

Node* groupBST::deleteNodeHelper(Node *currNode,int lValue){
    
    if(currNode == NULL)
    {
        return NULL;
    }
    else if(lValue < currNode->level)
    {
        currNode->left = deleteNodeHelper(currNode->left, lValue);
    }
    else if(lValue >= currNode->level)
    {
        currNode->right = deleteNodeHelper(currNode->right, lValue);
    }
    // We found the node with the value
    else
    {
        
        //TODO Case : No child
        if(currNode->left == NULL && currNode->right == NULL)
        {
            currNode=nullptr;
        }
        //TODO Case : Only right child
        else if(currNode->left == NULL)
        {
            Node *temp=currNode;
            currNode=currNode->right;
            temp=nullptr;
            //delete temp;
            
        }
        //TODO Case : Only left child
        else if(currNode->right == NULL)
        {
            Node *temp=currNode;
            currNode=currNode->left;
            temp=nullptr;
            //delete temp;
        }
        //TODO Case: Both left and right child
        else
        {
            ///Replace with Minimum from right subtree
            //***************
            bool forRoot=false;
            Node *min=getMinValueNode(currNode->right);
            if (currNode==root){
                forRoot=true;
            }
            currNode->uName=min->uName;
            currNode->XP=min->XP;
            currNode->coins=min->coins;
            currNode->level=min->level;
            if (forRoot){
                root=currNode;
            }
            currNode->right=deleteNodeHelper(currNode->right,min->level);
        }
    }
    return currNode;
}

void groupBST::deleteNode(std::string userName){
    Node* toDelete=searchNode(userName);
    if (toDelete==NULL){
        cout<<"That user is not a member of this group so they cannot be deleted"<<endl;
        return;
    }
    
    deleteNodeHelper(root, toDelete->level);
    
}


Node* groupBST::searchNodeHelper(Node *currNode,std::string userName){
    if (currNode!=NULL){
        if (currNode->left!=nullptr){
            searchNodeHelper(currNode->left,userName);
        }
        if (currNode->uName==userName){
            found=currNode;
        }
        if (currNode->right!=nullptr){
            searchNodeHelper(currNode->right,userName);
        }
    }
    else{
        cout<<"No members have joined this group so there is nothing to search"<<endl;
        return NULL;
    }
    return found;
}


Node* groupBST::searchNode(std::string userName){
    found=nullptr;
    return searchNodeHelper(root, userName);
    
}


//MIGHT HAVE TO DO FILE STREAM STUFF FOR THE BELOW

void groupBST::addXP(std::string userName, int amount){
    Node *toAdd=searchNode(userName);

    int level=toAdd->level;
    toAdd->XP+=amount;
    while(toAdd->XP>levels[level-1].neededXP){
        toAdd->XP=(toAdd->XP)-levels[level-1].neededXP;
        toAdd->level++;
        toAdd->coins=toAdd->coins+levels[level-1].coins;
        level=toAdd->level;
    }
    
    
    //file work
    
    string line,line2;
    
    ifstream inFile;
    inFile.open(treeName+".txt");
    if (inFile.fail()){
        cout<<"File failed to open"<<endl;
    }
    
    ofstream outFile;
    outFile.open("tempStorage.txt");
    if (outFile.fail()){
        cout<<"OutFile failed to open"<<endl;
    }
    
    
    while (getline(inFile,line)){
        outFile<<line<<endl;
        if(line=="USERS"){
            break;
        }
    }
    getline(inFile,line);
    outFile<<line<<endl;
    while (getline(inFile,line)){
        istringstream iss(line);
        getline(iss,line2,' ');
        if (line2==userName){
            outFile<<line2<<" "<<toAdd->level<<" "<<toAdd->XP<<" "<<toAdd->coins<<endl;
            break;
        }
        else{
            outFile<<line<<endl;
        }
    }
    while (getline(inFile,line)){
        outFile<<line<<endl;
    }
    
    //finished writing new info and now need to rename
    outFile.close();
    inFile.close();
    
    
    remove((treeName+".txt").c_str());
    char old[]="tempStorage.txt";
    rename(old,(treeName+".txt").c_str());
    
    cout<<"XP has been awarded to "<<userName<<" for completing an assignment"<<endl;
//
//    delete toAdd;
//    toAdd=nullptr;
}

void groupBST::addCoins(std::string userName, int amount){
    Node *toAddCoins=searchNode(userName);
    if (toAddCoins==NULL){
        cout<<"This user is not a member of the group"<<endl;
        cout<<"Cannot add Coins"<<endl;
        return;
    }
    toAddCoins->coins+=amount;
    cout<<amount<<" Coins Added! "<<userName<<" now has "<<toAddCoins->coins<<" Coins"<<endl;
}

void groupBST::setAdmin(std::string leader){
    admin=leader;
}
void groupBST::setName(std::string name){
    treeName=name;
}
std::string groupBST::getAdmin(){
    return admin;
}
std::string groupBST::getName(){
    return treeName;
}
void groupBST::setCode(std::string code){
    groupCode=code;
}
std::string groupBST::getCode(){
    return groupCode;
}
void groupBST::loadAssignments(string name, int points, int xp){
    Assignments A1;
    A1.name=name;
    A1.pointValue=points;
    A1.XP=xp;
    assignments.push_back(A1);
}

void groupBST::loadRewards(std::string name, int cost){
    Rewards R1;
    R1.name=name;
    R1.cost=cost;
    rewards.push_back(R1);
}



std::vector<Assignments> groupBST::getUserAssignmentsVector(){
    return assignments;
}

void groupBST::addToUserVector(std::string name, Assignments A1){
    Node* N1=searchNode(name);
    N1->userAssignments.push_back(A1);
}


void groupBST::adminViewRewards(){
    cout<<"Rewards"<<endl;
    cout<<"--------"<<endl;
    for (int i=0;i<rewards.size();i++){
        cout<<rewards[i].name<<" ("<<rewards[i].cost<<" coins)"<<endl;
    }
}


void groupBST::adminViewAssignments(){
    cout<<"Assignments"<<endl;
    cout<<"-----------"<<endl;
    for (int i=0;i<assignments.size();i++){
        cout<<assignments[i].name<<" ("<<assignments[i].pointValue<<" points) - "<<assignments[i].XP<<" XP"<<endl;
    }
}


void groupBST::setTreeName(std::string nameOfTree){
    treeName=nameOfTree;
}


void groupBST::deleteUserMembership(std::string name){
    Node *deletion=searchNode(name);
    if (deletion==nullptr&&name!=getAdmin()){
        cout<<"Not deleted because they are not a member in this group"<<endl;
        return;
    }
    string line,line2;
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
        if (line==name){
            break;
        }
    }
    getline(inFile2, line);
    outFile2<<line<<endl;
    getline(inFile2,line);
    outFile2<<line<<endl;
    getline(inFile2, line);
    //found uName
    istringstream iss(line);
    line="";
    while (getline(iss,line2,' ')){
        if (line2!=treeName){
            line=line+line2+" ";
        }
    }
    outFile2<<line<<endl;
    while (getline(inFile2,line)){
        outFile2<<line<<endl;
        
    }
    outFile2.close();
    inFile2.close();
    remove("Userinfo.txt");
    char old[]="tempStorage.txt";
    char newName[]="Userinfo.txt";
    rename(old,newName);
    //deleteNode(name);
    if (name!=getAdmin()){
        ifstream inFile;
        inFile.open(treeName+".txt");
        ofstream outFile;
        outFile.open("tempStorage.txt");
        if (inFile.fail()){
            cout<<treeName<<".txt file failed to open"<<endl;
        }
        if (outFile.fail()){
            cout<<"tempStorage.txt failed to open"<<endl;
        }
        while (getline(inFile,line)){
            outFile<<line<<endl;
            if (line=="USERS"){
                break;
            }
        }
        getline(inFile,line);
        outFile<<line<<endl;
        string tempLine;
        while (getline(inFile,line)){
            tempLine=line;
            istringstream iss(line);
            getline(iss,line2,' ');
            if (line2==name){
                break;
            }
            outFile<<tempLine<<endl;
            getline(inFile,line);
            outFile<<line<<endl;
        }
        getline(inFile,line);
        while (getline(inFile,line)){
            outFile<<line<<endl;
        }
        outFile.close();
        inFile.close();
        remove((treeName+".txt").c_str());
        char old2[]="tempStorage.txt";
        rename(old2,(treeName+".txt").c_str());
    }
    
    
}




void groupBST::deleteGroup(){
    vector <string> uNames;
    ifstream inFile;
    string line,line2;
    inFile.open(treeName+".txt");
    if (inFile.fail()){
        cout<<"Failed to open file in the deltion process"<<endl;
    }
    
    while (true){
        getline(inFile,line);
        if (line=="USERS"){
            getline(inFile,line);
            break;
        }
    }
    while (getline(inFile,line)){
        istringstream iss(line);
        getline(iss,line2,' ');
        uNames.push_back(line2);
        getline(inFile,line);
    }
    
    inFile.close();
    uNames.push_back(getAdmin());
    for (int i=0;i<uNames.size();i++){
        deleteUserMembership(uNames[i]);
    }
    
    string fileName=treeName+".txt";
    remove(fileName.c_str());
    
    
    //delete from groups file
    
    ifstream inFile2;
    inFile2.open("groupNames.txt");
    ofstream outFile2("tempStorage.txt");
    if (inFile2.fail()){
        cout<<"groupNames.txt file failed to open"<<endl;
    }
    if (outFile2.fail()){
        cout<<"tempStorage.txt failed to open"<<endl;
    }
    while (getline(inFile2,line)){
        if (line==treeName){
            break;
        }
        outFile2<<line<<endl;
    }
    while (getline(inFile2,line)){
        outFile2<<line<<endl;
        
    }
    
    inFile2.close();
    outFile2.close();
    remove("groupNames.txt");
    char old[]="tempStorage.txt";
    char newName[]="groupNames.txt";
    rename(old,newName);
    
    
    remove((treeName+"extra.txt").c_str());
    
    
    
    
    
    cout<<"The Group has been deleted. Any members will no longer have acess to this group"<<endl;
}

void groupBST::addReward(){
    string rewardName, coinCost;
    int cost;
    cout<<"**Type cancel to quit this process at any time**"<<endl;
    cout<<endl;
    while (true){
        cout<<"Please enter the name of the Reward"<<endl;
        getline(cin, rewardName);
        if (rewardName=="cancel"){
            cout<<"Reward creation cancelled"<<endl;
            return;
        }
        if (rewardName.length()!=0){
            break;
        }
        cout<<"A name is required!"<<endl;
    }
    
    while (true){
        cout<<"Please enter how many coins this reward will cost to redeem"<<endl;
        getline(cin, coinCost);

        if (coinCost=="cancel"){
            cout<<rewardName<<" will not be added since creation was canceled prior to cost submission"<<endl;
            return;
        }
        try{
            cost=stoi(coinCost);
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
    rewards.push_back(R1);
    
    
  //Add to the file
    string line,line2;
    
    ifstream inFile2;
    inFile2.open(treeName+".txt");
    ofstream outFile2("tempStorage.txt");
    if (inFile2.fail()){
        cout<<treeName<<".txt file failed to open"<<endl;
    }
    if (outFile2.fail()){
        cout<<"tempStorage.txt failed to open"<<endl;
    }
    while (getline(inFile2,line)){
        if (line=="USERS"){
            break;
        }
        outFile2<<line<<endl;
    }
    outFile2<<R1.name<<endl;
    outFile2<<R1.cost<<endl;
    outFile2<<"USERS"<<endl;
    while (getline(inFile2,line)){
        outFile2<<line<<endl;
    }

    outFile2.close();
    inFile2.close();
    
    string fileName=treeName+".txt";
    remove(fileName.c_str());
    
    char old[]="tempStorage.txt";
    rename(old,fileName.c_str());
}








void groupBST::addAssignment(){
    //**NEED TO FINISH
    Assignments A1;
    string name, points;
    int pointValue;
    bool validName;
    cout<<"**Type cancel to cancel**"<<endl;
 
    while (true){
        validName=true;
        cout<<"\nPlease enter the assignment/activity name"<<endl;
        getline (cin, name);
        if (name=="cancel"){
            cout<<"Assignment not added"<<endl;
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
        if (points=="cancel"){
            cout<<"Assignment not added"<<endl;
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
        A1.XP=195*pointValue;
        A1.completed=false;
        assignments.push_back(A1);
        cout<<"You have added "<<A1.name<<" with the point value of "<<A1.pointValue<<endl;
        
        //Add to the file
        string line,line2;
        
        ifstream inFile2;
        inFile2.open(treeName+".txt");
        ofstream outFile2("tempStorage.txt");
        if (inFile2.fail()){
            cout<<treeName<<".txt file failed to open"<<endl;
        }
        if (outFile2.fail()){
            cout<<"tempStorage.txt failed to open"<<endl;
        }
        while (getline(inFile2,line)){
            if (line=="REWARDS"){
                break;
            }
            outFile2<<line<<endl;
        }
        outFile2<<A1.name<<endl;
        outFile2<<A1.pointValue<<endl;
        outFile2<<A1.XP<<endl;
        outFile2<<"REWARDS"<<endl;
        while (getline(inFile2,line)){
            if (line=="USERS"){
                break;
            }
            outFile2<<line<<endl;
        }
        outFile2<<"USERS"<<endl;
        while (getline(inFile2,line)){
            istringstream iss(line);
            getline(iss,line2,' ');
            if (line2=="FALSE" || line2=="TRUE"){
                outFile2<<line<<" FALSE"<<endl;
            }
            else{
                outFile2<<line<<endl;
            }
            
        }
        outFile2.close();
        inFile2.close();
        
        string fileName=treeName+".txt";
        remove(fileName.c_str());
        
        char old[]="tempStorage.txt";
        rename(old,fileName.c_str());
}


void groupBST::addLevel(int numLevel, int howMuchXP, int coins){
    Level L1;
    L1.whatLevel=numLevel;
    L1.neededXP=howMuchXP;
    L1.coins=coins;
    levels.push_back(L1);
}







void groupBST::addPointsManual(std::string name){
    Node *toAdd=searchNode(name);
    if (toAdd==nullptr){
        cout<<"Cannot add points because that user is not a member"<<endl;
        return;
    }
    string input;
    int howMany;
    while (true){
        cout<<"How many points would you like to add to this user?"<<endl;
        getline(cin, input);
        try{
            howMany=stoi(input);
            if (howMany<0){
                cout<<"The points must not be a negative value"<<endl;
            }
            else{
                break;
            }
        }
        catch(exception&e){
            cout<<"Please enter an integer value"<<endl;
        }
    }
    
    
    
    
    int level=toAdd->level;
    toAdd->XP+=howMany*195;
    while(toAdd->XP>levels[level-1].neededXP){
        toAdd->XP=(toAdd->XP)-levels[level-1].neededXP;
        toAdd->level++;
        toAdd->coins=toAdd->coins+levels[level-1].coins;
        level=toAdd->level;
    }
    
    
    //file work
    
    string line,line2;
    
    ifstream inFile;
    inFile.open(treeName+".txt");
    if (inFile.fail()){
        cout<<"File failed to open"<<endl;
    }
    
    ofstream outFile;
    outFile.open("tempStorage.txt");
    if (outFile.fail()){
        cout<<"OutFile failed to open"<<endl;
    }
    
    
    while (getline(inFile,line)){
        outFile<<line<<endl;
        if(line=="USERS"){
            break;
        }
    }
    getline(inFile,line);
    outFile<<line<<endl;
    while (getline(inFile,line)){
        istringstream iss(line);
        getline(iss,line2,' ');
        if (line2==name){
            outFile<<line2<<" "<<toAdd->level<<" "<<toAdd->XP<<" "<<toAdd->coins<<endl;
            break;
        }
        else{
            outFile<<line<<endl;
        }
    }
    while (getline(inFile,line)){
        outFile<<line<<endl;
    }
    
    //finished writing new info and now need to rename
    outFile.close();
    inFile.close();
    
    
    remove((treeName+".txt").c_str());
    char old[]="tempStorage.txt";
    rename(old,(treeName+".txt").c_str());
    
    
//
//    int levelF,experience,cost;
//    levelF=toAdd->level;
//    experience=toAdd->XP;
//    cost=toAdd->coins;
    
//    delete toAdd;
//    toAdd=nullptr;
    
    //deleteNode(name);
    //addNode(name, levelF, experience, cost);
}


void groupBST::levelStatus(std::string name){
    Node *checkStatus=searchNode(name);
    cout<<"LEVEL STATUS"<<endl;
    cout<<"-------------"<<endl;
    cout<<"Level: "<<checkStatus->level<<endl;
    int total=levels[checkStatus->level-1].neededXP;
    cout<<"XP: "<<checkStatus->XP<<" out of "<<total<<endl;
    cout<<"Coins: "<<checkStatus->coins<<endl;
}

void groupBST::userViewAssignments(std::string name){
    Node *searched=searchNode(name);
    vector <Assignments> completed;
    vector <Assignments> notCompleted;
    
    for (int i=0;i<searched->userAssignments.size();i++){
        if (searched->userAssignments[i].completed==true){
            completed.push_back(searched->userAssignments[i]);
        }
        else{
            notCompleted.push_back(searched->userAssignments[i]);
        }
    }
    
    cout<<"\nUNCOMPLETED ASSIGNMENTS"<<endl;
    cout<<"-----------------------"<<endl;
    for (int i=0;i<notCompleted.size();i++){
        cout<<notCompleted[i].name<<" - "<<notCompleted[i].XP<<" XP"<<endl;
    }
    
    cout<<"\nCOMPLETED ASSIGNMENTS"<<endl;
    cout<<"---------------------"<<endl;
    for (int i=0;i<completed.size();i++){
        cout<<completed[i].name<<" - "<<completed[i].XP<<" XP"<<endl;
    }
    
}


void groupBST::userViewRewards(string user){
    string input;
    cout<<"Rewards"<<endl;
    cout<<"--------"<<endl;
    for (int i=0;i<rewards.size();i++){
        cout<<rewards[i].name<<" ("<<rewards[i].cost<<" coins)"<<endl;
    }
    
    cout<<endl;
    
    Node *tempUser=searchNode(user);
    
    
    cout<<"**You have "<<tempUser->coins<<" coins**"<<endl;
    cout<<endl;
    
    bool verify=false;
    bool verify2=false;
    int date=0;
    int index;
    int amount;
    cout<<"Would you like to purchase a reward? (Y/N)"<<endl;
    getline(cin,input);
    if (!(input=="Y"||input=="y"||input=="Yes"||input=="yes")||input.length()==0){
        cout<<"Leaving Reward Shop"<<endl;
    }
    if (input=="Y"||input=="y"||input=="Yes"||input=="yes"){
        cout<<"Please enter the name of the reward you would like to purchase"<<endl;
        getline(cin,input);
        for (int i=0;i<rewards.size();i++){
            if (rewards[i].name==input){
                verify=true;
                index=i;
                break;
            }
        }
        if (verify==true){
            amount=rewards[index].cost;
            if (tempUser->coins>=amount){
                tempUser->coins-=amount;
                verify2=true;
            }
            else{
                cout<<"You do not have enough coins for this reward"<<endl;
                return;
            }
        }
        else{
            cout<<"Please make sure you entered the reward correctly"<<endl;
            return;
        }
        
        if (verify2==true){
            
            while (true){
                cout<<"Please enter what date you plan to use this reward (Format: month/day/year)"<<endl;
                getline(cin,input);
                for (int i=0;i<input.length();i++){
                    if (input[i]=='/'){
                        date++;
                    }
                }
                if (date==2){
                    cout<<"Reward purchased and to be used on "<<input<<endl;
                    break;
                }
                else{
                    cout<<"invalid format"<<endl;
                }
            }
        }
        
        else{
            cout<<"Leaving Reward Shop!"<<endl;
            return;
        }
        
        //file work now
        
        
        
        
        ofstream outFile2;
        outFile2.open(treeName+"extra.txt",ios::app);
        if (outFile2.fail()){
            cout<<"Failed to open file"<<endl;
        }
        
        outFile2<<tempUser->uName<<endl;
        outFile2<<rewards[index].name<<endl;
        outFile2<<input<<endl;
        outFile2.close();
        
        
        string line,line2;
        
        ifstream inFile;
        inFile.open(treeName+".txt");
        if (inFile.fail()){
            cout<<"File failed to open"<<endl;
        }
        
        ofstream outFile;
        outFile.open("tempStorage.txt");
        if (outFile.fail()){
            cout<<"OutFile failed to open"<<endl;
        }
        
        
        while (getline(inFile,line)){
            outFile<<line<<endl;
            if(line=="USERS"){
                break;
            }
        }
        getline(inFile,line);
        outFile<<line<<endl;
        while (getline(inFile,line)){
            istringstream iss(line);
            getline(iss,line2,' ');
            if (line2==user){
                outFile<<line2<<" "<<tempUser->level<<" "<<tempUser->XP<<" "<<tempUser->coins<<endl;
                break;
            }
            else{
                outFile<<line<<endl;
            }
        }
        while (getline(inFile,line)){
            outFile<<line<<endl;
        }
        
        //finished writing new info and now need to rename
        
        
        remove((treeName+".txt").c_str());
        char old[]="tempStorage.txt";
        rename(old,(treeName+".txt").c_str());
        
    }

    else{
        return;
    }
    
}


void groupBST::viewUsedRewards(){
    vector <string> users;
    vector <string> rewardUsed;
    vector <string> dateUsed;
    string line;
    ifstream inFile;
    inFile.open(treeName+"extra.txt");
    if (inFile.fail()){
        cout<<"View used Rewards file failed to open"<<endl;
    }
    
    while (getline(inFile,line)){
        if (line=="HOlDER2"){
            break;
        }
    }
    
    while (getline(inFile,line)){
        users.push_back(line);
        getline(inFile,line);
        rewardUsed.push_back(line);
        getline(inFile,line);
        dateUsed.push_back(line);
    }
    inFile.close();
    
    
    for (int i=0;i<users.size();i++){
        cout<<"User: "<<users[i]<<" Reward: "<<rewardUsed[i]<<" Date: "<<dateUsed[i]<<endl;
    }
    
    if (users.size()==0){
        cout<<"No rewards have been used yet!"<<endl;
    }
}


void groupBST::completeAssignment(std::string name){
    bool found=false;
    int index;
    string input;
    Node *temp=searchNode(name);
    cout<<"Please enter which assignment you would like to mark as complete"<<endl;
    getline(cin,input);
    for (int i=0;i<temp->userAssignments.size();i++){
        if (temp->userAssignments[i].name==input){
            found=true;
            if (temp->userAssignments[i].completed==true){
                cout<<"You have already completed this assignment"<<endl;
                return;
            }
            temp->userAssignments[i].completed=true;
            index=i;
            break;
        }
    }
    
    if (!found){
        cout<<"That assignment does not exist. Pleas check your input!"<<endl;
        return;
    }
    
    cout<<"Assignment Completed! Pending verification from group admin before XP will be rewarded."<<endl;
    
    
    string line,line2;
    
    ifstream inFile;
    inFile.open(treeName+".txt");
    if (inFile.fail()){
        cout<<"File failed to open"<<endl;
    }
    
    ofstream outFile;
    outFile.open("tempStorage.txt");
    if (outFile.fail()){
        cout<<"OutFile failed to open"<<endl;
    }
    
    
    while (getline(inFile,line)){
        outFile<<line<<endl;
        if(line=="USERS"){
            break;
        }
    }
    getline(inFile,line);
    outFile<<line<<endl;
    while (getline(inFile,line)){
        istringstream iss(line);
        getline(iss,line2,' ');
        outFile<<line<<endl;
        if (line2==name){
            break;
        }
    }
    
    
    getline(inFile,line);
    istringstream iss2(line);
    for (int i=0;i<index;i++){
        getline(iss2,line2,' ');
        outFile<<line2<<" ";
    }
    outFile<<"TRUE ";
    getline(iss2,line2,' ');
    while (getline(iss2,line2, ' ')){
        outFile<<line2<<" ";
    }
    outFile<<endl;
    
    while (getline(inFile,line)){
        outFile<<line<<endl;
    }
    inFile.close();
    outFile.close();
    //finished writing new info and now need to rename
    remove((treeName+".txt").c_str());
    char old[]="tempStorage.txt";
    rename(old,(treeName+".txt").c_str());
    
    
    //add to extras file
    
    ifstream inFile2;
    inFile2.open(treeName+"extra.txt");
    if (inFile2.fail()){
        cout<<"File failed to open"<<endl;
    }
    
    ofstream outFile2;
    outFile2.open("tempStorage.txt");
    if (outFile2.fail()){
        cout<<"OutFile failed to open"<<endl;
    }
    
    
    while (getline(inFile2,line)){
        outFile2<<line<<endl;
        if(line=="HOLDER1"){
            break;
        }
    }
    outFile2<<name<<endl;
    outFile2<<temp->userAssignments[index].name<<endl;
    outFile2<<temp->userAssignments[index].XP<<endl;
    
    while (getline(inFile2,line)){
        outFile2<<line<<endl;
    }
    
    inFile2.close();
    outFile2.close();
    //finished writing new info and now need to rename
    remove((treeName+"extra.txt").c_str());
    char old2[]="tempStorage.txt";
    rename(old2,(treeName+"extra.txt").c_str());
    
}



void groupBST::changeCompletion(string name, int index){
    string line,line2;
    
    ifstream inFile;
    inFile.open(treeName+".txt");
    if (inFile.fail()){
        cout<<"File failed to open"<<endl;
    }
    
    ofstream outFile;
    outFile.open("tempStorage.txt");
    if (outFile.fail()){
        cout<<"OutFile failed to open"<<endl;
    }
    
    
    while (getline(inFile,line)){
        outFile<<line<<endl;
        if(line=="USERS"){
            break;
        }
    }
    getline(inFile,line);
    outFile<<line<<endl;
    while (getline(inFile,line)){
        istringstream iss(line);
        getline(iss,line2,' ');
        outFile<<line<<endl;
        if (line2==name){
            break;
        }
    }
    
    
    getline(inFile,line);
    istringstream iss2(line);
    for (int i=0;i<index;i++){
        getline(iss2,line2,' ');
        outFile<<line2<<" ";
    }
    outFile<<"FALSE ";
    getline(iss2,line2,' ');
    while (getline(iss2,line2, ' ')){
        outFile<<line2<<" ";
    }
    outFile<<endl;
    
    while (getline(inFile,line)){
        outFile<<line<<endl;
    }
    inFile.close();
    outFile.close();
    //finished writing new info and now need to rename
    remove((treeName+".txt").c_str());
    char old[]="tempStorage.txt";
    rename(old,(treeName+".txt").c_str());
}




void groupBST::viewCompletionList(){
    vector<addPoints> toAddPoints;
    vector<addPoints> toChangeStatus;
    
    string input;
    string line;
    ifstream inFile2;
    inFile2.open(treeName+"extra.txt");
    if (inFile2.fail()){
        cout<<"File failed to open"<<endl;
    }
    
    ofstream outFile2;
    outFile2.open("tempStorage.txt");
    if (outFile2.fail()){
        cout<<"OutFile failed to open"<<endl;
    }
    
    //FILE MANIP
    while (getline(inFile2,line)){
        outFile2<<line<<endl;
        if(line=="HOLDER1"){
            break;
        }
    }
    string user,assignmentCompleted;
    int totalXP;
    int index;
    bool empty=true;
    while(getline(inFile2,line)){
        if (line=="HOlDER2"){
            if (empty){
                cout<<"There are no completed assignments to verify at this point"<<endl;
            }
            outFile2<<line<<endl;
            break;
        }
        empty=false;
        user=line;
        getline(inFile2,line);
        assignmentCompleted=line;
        getline(inFile2,line);
        totalXP=stoi(line);
        cout<<user<< " completed "<<assignmentCompleted<<" worth "<<totalXP<<" XP"<<endl;
        cout<<"Do you verify this completion? (Y/N)"<<endl;
        getline(cin,input);
        if(input=="Y"||input=="y"||input=="Yes"||input=="yes"){
            addPoints A1;
            A1.name=user;
            A1.howMany=totalXP;
            toAddPoints.push_back(A1);
        }
        
        else{
            for (int i=0;i<assignments.size();i++){
                if (assignments[i].name==assignmentCompleted){
                    index=i;
                    cout<<"This completion will not be verified and the user will not be rewarded with XP"<<endl;
                    break;
                }
            }
            addPoints A2;
            A2.name=user;
            A2.howMany=index;
            toChangeStatus.push_back(A2);
            //changeCompletion(user, index);
            
        }
    }
    
    while (getline(inFile2,line)){
        outFile2<<line<<endl;
    }
        
    inFile2.close();
    outFile2.close();
    //finished writing new info and now need to rename
    remove((treeName+"extra.txt").c_str());
    char old[]="tempStorage.txt";
    rename(old,(treeName+"extra.txt").c_str());
    
    
    
    
    for (int i=0;i<toAddPoints.size();i++){
        addXP(toAddPoints[i].name, toAddPoints[i].howMany);
    }
    
    for (int b=0;b<toChangeStatus.size();b++){
        changeCompletion(toChangeStatus[b].name, toChangeStatus[b].howMany);
    }

}
