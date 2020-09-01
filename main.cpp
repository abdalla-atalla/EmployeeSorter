//
//  main.cpp
//  Copyright © 2019 Abdalla Atalla. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

struct Person { 
    int id;
    std::string name;
    double salary;
    double bonus;
};

using namespace std;

void displayInfo(std::vector<Person> persons) {
    cout << setfill(' ');
    for (Person &p : persons) {
        cout.width(10); cout << left << p.id;
        cout.width(20); cout << left << p.name;
        cout.width(15); cout << left << fixed << setprecision(2) << p.salary;
        cout.width(15); cout << left << fixed << setprecision(2) << p.bonus << endl;
    }
    cout << endl;
}

void saveData(std::vector<Person> persons) {
    char outFilename[100];
    cout << "give an output filename: ";
    cin.getline(outFilename, sizeof(outFilename));
    ofstream f(outFilename);
    f << setfill(' ');
    if (persons.size() < 1000)
        for (Person &p : persons) {
            f.width(10); f << left << p.id;
            f.width(20); f << left << p.name;
            f.width(15); f << left << fixed << setprecision(2) << p.salary;
            f.width(15); f << left << fixed << setprecision(2) << p.bonus << endl;
        }
    f << endl;
    f.close();
}


int main()
{
    char inFilename[100];
    cout << "give an input filename: ";
    
    cin.getline(inFilename, sizeof(inFilename));
    cout << inFilename << endl;
    //ifstream myfile("/Users/AbdallaAtalla/Documents/projects/EC2" + std::string(inFilename));
    ifstream myfile(inFilename);
    
    if (!myfile)
    {
        cout << "Error opening output file" << endl;
        system("pause");
        return -1;
    }
    
    string line;
    std::vector<std::string> lines;
    std::vector<Person> persons;
    
    while (!myfile.eof())
    {
        getline(myfile, line, '\n');
        lines.push_back(line);
    }
    
    // sort lines
    sort(lines.begin(), lines.end());
    
    for (string &line : lines) {
        // token each line
        std::vector<std::string> words;
        std::istringstream iss(line);
        for(std::string s; iss >> s; ) {
            words.push_back(s);
        }
        
        Person p;
        p.id = std::stoi(words[0]);
        p.name = words[1] + " " + words[2];
        p.salary = std::stod(words[3]);
        p.bonus = (p.salary / 100) * 15;
        persons.push_back(p);
    }
    
    displayInfo(persons);
    saveData(persons);
}
