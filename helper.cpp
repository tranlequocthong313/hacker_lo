#include <dirent.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Helper {
	public:
		vector<string> getAbsPaths(string dirPath) {
			vector<string> paths;
			DIR* dir=opendir(dirPath.c_str());
			if(dir==nullptr) {
				return paths;
			}
			struct dirent* entry;
			while((entry=readdir(dir))!=nullptr) {
				string fname=entry->d_name;
				if(fname=="."||fname=="..") continue;
				string absPath=dirPath+"/"+fname;
				paths.push_back(absPath);
			}
			closedir(dir);
			return paths;
		}
};

