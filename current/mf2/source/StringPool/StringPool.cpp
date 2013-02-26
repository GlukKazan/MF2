#include "StringPool.h"

namespace mf2 {

StringPool pool;

void StringPool::init(){
	usage = new map<Value, int>();
}

void StringPool::release() {
	for (VIter p = usage->begin(); p != usage->end(); ++p) {
		delete [] p->first.strValue;
	}
	delete usage;
}

size_t StringPool::calculateSize(const char* s) {
	size_t r = strlen(s) + 1;
	size_t i = 2;
	for (; i < r; i <<= 1);
	return i;
}

bool StringPool::freeString(const char* s) {
	VIter p = usage->find(Value(s));
	if (p != usage->end()) {
		if (--p->second <= 0) {
			delete [] p->first.strValue;
			usage->erase(p);
		}
		return true;
	}
	return false;
}

const char* StringPool::getString(const char* s) {
	if (s == NULL) return s;
	VIter p = usage->find(Value(s));
	if (p != usage->end()) {
		p->second++;
		return p->first.strValue;
	}
	size_t sz = calculateSize(s);
	char* r = new char[sz];
	memset(r, 0, sz);
	strcpy(r, s);
	usage->insert(VPair(Value(r), 1));
	return r;
}

const char* StringPool::getString(char c) {
	char s[2];
	s[0] = c; s[1] = 0;
	return getString(s);
}

const char* StringPool::getString(int v) {
	char s[MAX_NUM_STR_SZ];
	memset(s, 0, sizeof(s));
	sprintf(s, "%d", v);
	return getString(s);
}

}