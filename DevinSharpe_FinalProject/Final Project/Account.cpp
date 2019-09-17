//
//  Account.cpp
//  CSCI 2270
//
//  Created by Devin Sharpe on 4/15/19.
//  Copyright © 2019 Devin Sharpe. All rights reserved.
//

#include "Account.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

//*************************************************************
//THE FOLLOWING DEALS WITH ACCOUNT CREATION AND LOGIN PROCESSES
//*************************************************************

bool Account::newAccount(){
    string name, userName, password, confirmation, fileLine;
    string groupMembership="";
    bool verifyPass=false;
    bool duplicateUsername=true;
    bool validUsername=false;
    
    ifstream inFile;
    inFile.open("UserInfo.txt");
    
    if (inFile.fail()){
        cout<<"OOPS...Something went wrong. Please contact your system administrator"<<endl;
        return false;
    }
    cout<<endl;
    while(true){
        cout<<"Please Enter Your Full Name:"<<endl;
        getline (cin, name);
        if (name.length()==0){
            cout<<"You must enter a name!"<<endl;
        }
        else{
            break;
        }
    }
    
    while (duplicateUsername==true||validUsername==false){
        cout<<"Please Enter a Username:"<<endl;
        getline(cin, userName);
        
        validUsername=true;
        if (userName.length()==0){
            cout<<"You must enter a Username!"<<endl;
            validUsername=false;
        }
        for (int i=0;i<userName.length();i++){
            if(userName[i]==' '){
                cout<<"Usernames must not contain any spaces"<<endl;
                validUsername=false;
                break;
            }
        }
        
        
        duplicateUsername=false;
        while (getline(inFile, fileLine)&&validUsername==true){
            if (fileLine==userName){
                cout<<"That username is already taken. Please choose another!"<<endl;
                duplicateUsername=true;
                break;
            }
            
        }
        
    }
    
    inFile.close();
    
    while (verifyPass==false){
        cout<<"Please Enter a Password:"<<endl;
        getline(cin, password);
        cout<<"Please Enter Your Password Again:"<<endl;
        getline(cin, confirmation);
        
        if (password==confirmation){
            verifyPass=true;
        }
        else{
            cout<<"Your passwords do not match. Try again!"<<endl;
        }
        
        if (password.length()==0){
            cout<<"You must enter a password!"<<endl;
            verifyPass=false;
        }
    }
    
    ofstream outFile;
    outFile.open("UserInfo.txt",ios::app);
    if (outFile.fail()){
        cout<<"OOPS...Something went wrong. Please contact your system administrator"<<endl;
        return false;
    }    
    outFile<<userName<<endl;
    outFile<<password<<endl;
    outFile<<name<<endl;
    outFile<<groupMembership<<endl;
    
    outFile.close();
    
    cout<<"You have sucessfully created a new account!"<<endl;
    cout<<endl;
    return true;
    
    
}


User Account::login(User toLogin){
    bool foundUName=false;
    bool foundPass=false;
    ifstream inFile;
    
    string line, userName, passWord, createAccount;
    while (foundUName==false||foundPass==false){
        inFile.open("UserInfo.txt");
        if (inFile.fail()){
            cout<<"Something went wrong"<<endl;
            exit(0);
        }
        foundUName=false;
        foundPass=false;
        cout<<"Please Enter Your Username:"<<endl;
        getline(cin, userName);
        cout<<"Please Enter Your Password:"<<endl;
        getline(cin, passWord);
        
        while (getline(inFile,line)){
            if (line==userName){
                foundUName=true;
                break;
            }
        }
        
        if (foundUName==true){
            getline(inFile,line);
            if (line==passWord){
                foundPass=true;
            }
            else{
                cout<<"Incorrect Password"<<endl;
            }
            
        }
        else{
            cout<<"That username is not in our database"<<endl;
            cout<<"Would You like to create an account? (Y/N)"<<endl;
            getline(cin,createAccount);
            if (createAccount=="Y"||createAccount=="y"){
                newAccount();
                cout<<"Please Login Now!"<<endl;
                
            }
            
        }
        
        //sucessfull login info
        if (foundPass==true&&foundUName==true){
            cout<<endl;
            cout<<"Login Successful!"<<endl;
            toLogin.uName=userName;
            getline(inFile, line);
            toLogin.name=line;
            getline(inFile, line);
            
            string membership;
            //DO SOME STRING STREAM STUFF FOR GROUP MEMBERSHIP INFO
            //Currently the info is stored in line
            istringstream iss(line);
            while (getline(iss, membership,' ')){
                toLogin.groupMembership.push_back(membership);
            }
            inFile.close();
            break;
        }
        inFile.close();
    }
    
    
    return toLogin;
}


//********************************************
//END OF ACCOUNT CREATION AND LOGIN PROCESSES
//*******************************************
