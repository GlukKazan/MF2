#ifndef _VAR_DEF_H_
#define _VAR_DEF_H_

#include <set>
#include <vector>
#include "AbstractConfigurable.h"
#include "StringValue.h"
#include "Value.h"

using namespace std;

#define TYPE_PROPERTY   "type"
#define EVENT_PROPERTY  "event"
#define LOCK_PROPERTY   "lock"

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
		int                 defType;
		int                 valType;
		vector<Val>         values;
		vector<StringValue> locks;
		set<StringValue>    events;
	public:
		enum EDefType {
			dtVar       = 0,
			dtSet       = 1
		};
		VarDef(int t);
		virtual bool setValue(const char* name, const char* value);

	typedef vector<Val>::iterator VIter;
	typedef vector<StringValue>::iterator LIter;
	typedef set<StringValue>::iterator EIter;
};

}

#endif	// _VAR_DEF_H_
