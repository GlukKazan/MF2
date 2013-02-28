#include "VarDef.h"
#include <string.h>

namespace mf2 {

VarDef::VarDef(int t): defType(t), valType(vtString), values() {}

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
	values.push_back(Val(name, value));
	return true;
}

}