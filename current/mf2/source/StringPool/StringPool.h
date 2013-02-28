#ifndef _STRING_POOL_H_
#define _STRING_POOL_H_

#include <stdio.h>
#include <string.h>
#include <map>

using namespace std;

namespace mf2 {

class StringPool {
	private:
		struct Value {
			Value(const char* s): strValue(s) {}
			Value(const Value& p): strValue(p.strValue) {}
			bool operator<(const Value& p) const  {return strcmp(strValue, p.strValue) < 0;}
			const char* strValue;
		};
		enum {
			MAX_NUM_STR_SZ = 32
		};
		map<Value, int>* usage;
		int calculateSize(const char* s);
	public:
		void init();
		void release();

		bool freeString(const char* s);
		const char* getString(const char* s);
		const char* getString(char c);
		const char* getString(int v);

	typedef map<Value, int>::iterator VIter;
	typedef pair<Value, int> VPair;
};

extern StringPool pool;

}

#endif	// _STRING_POOL_H_
