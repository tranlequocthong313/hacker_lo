#include <string>

using namespace std;

class EncDec {
	private:
		string getExt(string fname);
	public:
		bool encode(string fname);
		bool decode(string fname);
};
