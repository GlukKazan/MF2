#ifndef _VAR_DEF_H_
#define _VAR_DEF_H_

#include <vector>
#include "AbstractConfigurable.h"
#include "StringValue.h"
#include "Value.h"

using namespace std;

#define TYPE_PROPERTY   "type"

#define NUMBER_TYPE     "number"
#define STRING_TYPE     "string"

namespace mf2 {

class VarDef: public AbstractConfigurable {
	private:
		enum EValueType {
			vtString    = 0,
			vtNumber    = 1
		};
		struct Val {
			Val(const char* n, const char* v): name(n), value(v) {}
			Val(const char* n, int v): name(n), value(v) {}
			Val(const Val& p): name(p.name), value(p.value) {}
			StringValue name;
			Value value;
		};
		int   defType;
		int   valType;
		vector<Val> values;
	public:
		enum EDefType {
			dtVar       = 0,
			dtSet       = 1
		};
		VarDef(int t);
		virtual bool setValue(const char* name, const char* value);

	typedef vector<Val>::iterator VIter;
};

}

#endif	// _VAR_DEF_H_
