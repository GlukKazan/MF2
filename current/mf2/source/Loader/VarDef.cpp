#include "VarDef.h"
#include <string.h>

namespace mf2 {

VarDef::VarDef(int t): defType(t), valType(vtString), values(), events(), locks() {}

bool VarDef::setValue(const char* name, const char* value) {
	if (strcmp(name, TYPE_PROPERTY) == 0) {
		if (strcmp(value, NUMBER_TYPE) == 0) {
			valType = vtNumber;
			return true;
		}
		if (strcmp(value, STRING_TYPE) == 0) {
			valType = vtString;
			return true;
		}
	}
	if (strcmp(name, EVENT_PROPERTY) == 0) {
		if (defType != dtSet) return false;
		events.insert(StringValue(value));
		return true;
	}
	if (strcmp(name, LOCK_PROPERTY) == 0) {
		if (defType != dtSet) return false;
		locks.push_back(StringValue(value));
		return true;
	}
	values.push_back(Val(name, value));
	return true;
}

}