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
		bool encode(string fname, int key);
		bool decode(string fname, int key);
};
