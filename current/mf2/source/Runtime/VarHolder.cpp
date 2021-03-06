#include "VarHolder.h"
#include <string.h>

namespace mf2 {

VarHolder::VarHolder(VarHolder* p, const char* nm): name(nm), parent(p), values() {
	addMagic();
}

template<class T>
void VarHolder::defVar(const char* name, T value) {
	VIter p = values.find(StringValue(name));
	if (p != values.end()) {
		p->second = Value(value);
	} else {
		values.insert(VPair(StringValue(name), Value(value)));
	}
}

template<class T>
void VarHolder::setVar(const char* name, T value) {
	VIter p = values.find(StringValue(name));
	if (p != values.end()) {
		p->second = Value(value);
		return;
	}
	if (parent != NULL) {
		parent->setVar(name, value);
	}
}

bool VarHolder::isExists(const char* name) {
	VIter p = values.find(StringValue(name));
	if (p != values.end()) {
		return true;
	}
	if (parent != NULL) {
		return parent->isExists(name);
	}
	return false;
}

const char* VarHolder::getString(const char* name) {
	VIter p = values.find(StringValue(name));
	if (p != values.end()) {
		return p->second.getString();
	}
	if (parent != NULL) {
		return parent->getString(name);
	}
	return "";
}

int VarHolder::getInt(const char* name) {
	VIter p = values.find(StringValue(name));
	if (p != values.end()) {
		return p->second.getInt();
	}
	if (parent != NULL) {
		return parent->getInt(name);
	}
	return 0;
}

void VarHolder::addMagic() {
	const char* s = name.getString();
	for (int i = 0; i < (int)strlen(s); i++) {
		if ((s[i] >= 'A')&&(s[i] <= 'Z')) {
			defVar(StringValue(s[i]).getString(), 0);
		}
	}
}

int VarHolder::getMagicValue(char c) {
	if ((c >= '0') && (c <= '9')) {
		return (int)(c - '0');
	}
	if ((c >= 'a') && (c <= 'z')) {
		return (int)(c - 'a' + 10);
	}
	return -1;
}

void VarHolder::setMagic(const char* actualName) {
	const char* s = name.getString();
	for (int i = 0; i < (int)strlen(s); i++) {
		if (i >= (int)strlen(actualName)) break;
		if ((s[i] >= 'A')&&(s[i] <= 'Z')) {
			int v = getMagicValue(actualName[i]);
			if (v >= 0) {
				setVar(StringValue(s[i]).getString(), v);
			}
		}
	}
}

bool VarHolder::isEqual(const char* actualName) {
	const char* s = name.getString();
	for (int i = 0; i < (int)strlen(s); i++) {
		if (i >= (int)strlen(actualName)) return false;
		if ((s[i] >= 'A')&&(s[i] <= 'Z')) continue;
		if (s[i] != actualName[i]) return false;
	}
	return true;
}

bool VarHolder::isEmpty(const char* v) {
	if (v == NULL) return true;
	if (v[0] == 0) return true;
	return false;
}

void VarHolder::magicValue(Value& v) {
	const char* value = v.getString();
	for (int i = 0; i < (int)strlen(value); i++) {
		if ((value[i] >= 'A')&&(value[i] <= 'Z')) {
			StringValue name(value[i]);
			if (isExists(name.getString())) {
				const char* vl = getString(name.getString());
				if (!isEmpty(vl)) {
					v.replace(i, vl[0]);
					value = v.getString();
				}
			}
		}
	}
}

}