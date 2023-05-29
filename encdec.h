#include <fstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class EncDec {
	private:
		string getExt(string fname);
		pair<bool, vector<char>> read(string fname);
		int getFileSize();
	public:
		bool encode(string path, int key);
		bool decode(string path, int key);
		void encode(vector<string>& paths, int key);
		void decode(vector<string>& paths, int key);
};
