#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <filesystem>
using namespace std;

//Data declration
string url = "git@github.com:";
string gitName;
char* cfgPath = "/.config/devScripts/";
char* homeDir = getenv("HOME");
char* sysCmd; 
string cfgDir;
string nameDir;
filesystem::path workingDir;
string workingCmd;

string getGitName() {
  cfgDir += homeDir;
  cfgDir += cfgPath;
  nameDir = cfgDir + "name";
  ifstream readFile;
  readFile.open(nameDir);
  if(!readFile.is_open()){
    cout << "name file not found, create one in ~/.config/devScripts/name";
    return 0;
  }
  readFile >> gitName;
  return gitName;
}

int main(int argc, char* argv[]){
  if(argc <=2) {
    cout << "not enough arguments, <command> <language> <project name>";
    return 0;
  }
  getGitName();
  workingDir = filesystem::current_path();
  workingCmd = "mkdir ";
  workingCmd += workingDir;
  workingCmd += "/";
  workingCmd += argv[2];
  workingCmd += "/";
  const char* createProject = workingCmd.c_str();
  int sys = system(createProject);
  workingCmd = "cp -r " + cfgDir + argv[1] + "/* ";
  workingCmd += workingDir;
  workingCmd += "/";
  workingCmd += argv[2];
  const char* copyProject = workingCmd.c_str();
  sys = system(copyProject);
  workingCmd = "git init ";
  workingCmd += workingDir;
  workingCmd += "/";
  workingCmd += argv[2];
  const char* gitInit = workingCmd.c_str();
  sys = system(gitInit);
  workingCmd = "git remote add ";
  workingCmd += argv[2];
  workingCmd += " git@github:" + gitName + "/";
  workingCmd += argv[2];
  const char* gitRemote = workingCmd.c_str();
  sys = system(gitRemote);
}
