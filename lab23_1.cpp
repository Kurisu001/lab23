#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

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


void importDataFromFile(string filename,vector<string>& names,vector<int>& scores,vector<char>& grades){
    ifstream source;
    source.open("name_score.txt");
    string textline;
    while(getline(source,textline)){
        char format[] = "%[^:]: %d %d %d";
        char name[100];
        int a,b,c;
        sscanf(textline.c_str(),format,name,&a,&b,&c);
        names.push_back(name);
        scores.push_back(a+b+c);
        grades.push_back(score2grade(a+b+c));
    }
}

void getCommand(string &command,string &key){
    cout << "Please input your command:" << endl;
    string input;
    char c[100];
    char k[100];
    getline(cin,input);
    sscanf(input.c_str()," %s %[^\n]",c,k);
    key = k;
    command =c;
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades ,string key){
    cout << "---------------------------------" << endl;
    for(int i = 0 ; i < (int)names.size() ; i++){
        if(key == toUpperStr(names[i])){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------" << endl;
            return;
        }
    }
    cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades ,string key){
    cout << "---------------------------------" << endl;
    bool found = false;
    for(int i = 0 ; i  < (int)grades.size() ; i++){
        if(key == toUpperStr(string(1,grades[i]))){
            cout << names[i] << " (" << scores[i]<< ")" << endl;
            found = true;
        }
    }
    if(!found) cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;

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
