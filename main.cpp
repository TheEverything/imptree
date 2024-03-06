#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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

  while(getline(dataFile, line)) {
    if(line == "" || line == "----") {
      continue;
    }
    else if(startsWith(line, "----")) { 
      skillCategoryId++;
      skillCategories << skillCategoryId << ";" << line.substr(5) << endl;
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
      microSkillId++;
      microskills << microSkillId << ";" << line << ";" << skillTopicId << endl;
    }
  }

  skills.close();
  skilltopics.close();
  microskills.close();

  return 0;
}