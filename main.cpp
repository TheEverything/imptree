#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <dirent.h>

using namespace std;

bool startsWith(const std::string& str, const std::string& prefix) {
    return str.compare(0, prefix.size(), prefix) == 0;
}

int main(){
    fstream dataFile;
    dataFile.open("data.txt", ios::in);

    string line;
    int skillCategoryId = 0;
    int skillId = 0;
    int skillTopicId = 0;
    int microSkillId = 0;

    ofstream skillCategories;
    skillCategories.open("export/1skillCategories.csv");
    skillCategories << "id;name" << endl;

    ofstream skills;
    skills.open("export/2skills.csv");
    skills << "id;title;progress;imageUrl;skillCategoryId" << endl;

    ofstream skilltopics;
    skilltopics.open("export/3skilltopics.csv");
    skilltopics << "id;name;skillId" << endl;

    ofstream microskills;
    microskills.open("export/4microskills.csv");
    microskills << "id;name;skillTopicId" << endl;

    string folderPath = "data";
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(folderPath.c_str())) != nullptr) {
    while ((entry = readdir(dir)) != nullptr) {
        string filename = entry->d_name;
        if (filename != "." && filename != "..") {
            ifstream dataFile(folderPath + "/" + filename);
            if (dataFile.is_open()) {
                string line;
                while(getline(dataFile, line)) {
                    if(line == "" || line == "----") {
                        continue;
                    }
                    else if(startsWith(line, "----")) { 
                        skillCategoryId++;
                        skillCategories << "1" << ";" << line.substr(5) << endl; //todo: change to dynamic skillcategoryid
                    }
                    else if(startsWith(line, "--")) { 
                        skillId++;
                        skills << skillId << ";" << line.substr(3);
                        getline(dataFile, line);
                        skills << ";" << line;
                        getline(dataFile, line);
                        skills << ";" << line;
                        skills << ";" << skillCategoryId << endl;
                    }
                    else if(startsWith(line, "-")) { 
                        skillTopicId++;
                        skilltopics << skillTopicId << ";" << line.substr(2) << ";" << skillId << endl;
                    }
                    else { 
                        if(microSkillId == 500) { break; }
                        microSkillId++;
                        microskills << microSkillId << ";" << line << ";" << skillTopicId << endl;
                    }
                }
            } else {
                cerr << "Unable to open file: " << folderPath + "/" + filename << endl;
            }
        }
    }
    closedir(dir);
    } else {
        cerr << "Unable to open directory: " << folderPath << endl;
        return 1;
    }

    dataFile.close();
    skills.close();
    skilltopics.close();
    microskills.close();

    return 0;
}


