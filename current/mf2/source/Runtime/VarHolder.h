#ifndef _VAR_HOLDER_H_
#define _VAR_HOLDER_H_

#include <map>
#include "StringValue.h"
#include "Value.h"

using namespace std;

namespace mf2 {

class VarHolder {
	private:
		VarHolder* parent;
		StringValue name;
		map<StringValue, Value> values;
		void addMagic();
		int  getMagicValue(char c);
	protected:
		const char* magicValue(const char* value);
	public:
		VarHolder(VarHolder* p, const char* nm = "");
		void setMagic(const char* actualName);
		bool isEqual(const char* actualName);

		template<class T>
		void defVar(const char* name, T value);
		template<class T>
		void setVar(const char* name, T value);
		bool isExists(const char* name);
		const char* getString(const char* name);
		int getInt(const char* name);

	typedef map<StringValue, Value>::iterator VIter;
	typedef pair<StringValue, Value> VPair;
};

}

#endif	// _VAR_HOLDER_H_
