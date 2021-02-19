#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstring>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores,vector<char> &grades){
    ifstream source;
    source.open(filename.c_str());
    string textline;
    char listname[100];
    char grade1;
    int score1,score2,score3,sumScore,i;
    while(getline(source,textline)){
        char format[]=  "%[^:]: %d %d %d";
        sscanf(textline.c_str(),format,listname,&score1,&score2,&score3);
        sumScore= score1+score2+score3;
        grade1=score2grade(sumScore);
        names.push_back(listname);
        scores.push_back(sumScore);
        grades.push_back(grade1);
        i++;
    }
}



void getCommand(string &command,string &key){
    cout<<"Please input your command: ";
    cin>>command;
    cin>>key;
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    cout<<"--------------------------------- "<<endl;
    bool c=false;
    for(int i=0;i<26;i++){
        if(names[i]==key){
            cout<<names[i]<<"'s score = "<<scores[i]<<endl;
            cout<<names[i]<<"'s grade = "<<grades[i]<<endl;
            c=true;
        }
    }
    if(c==false) cout<<"Cannot found."<<endl;
    cout<<"--------------------------------- "<<endl;
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    char ikey[100];
    strcpy(ikey,key.c_str());
    cout<<"--------------------------------- "<<endl;
    bool c=false;
    for(int i=0;i<26;i++){
        if(grades[i]== *ikey){
            cout<<names[i]<<" ("<<scores[i]<<")"<<endl;
            c=true;
        }
    }
    if(c==false) cout<<"Cannot found."<<endl;
    cout<<"--------------------------------- "<<endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}