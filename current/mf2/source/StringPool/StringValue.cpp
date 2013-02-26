#include "StringValue.h"
#include "StringPool.h"

namespace mf2 {

StringValue::StringValue(const char* s): strValue(pool.getString(s)) {}
StringValue::StringValue(const StringValue& p): strValue(pool.getString(p.strValue)) {}
StringValue::StringValue(char c): strValue(pool.getString(c)) {}

StringValue::~StringValue() {
	pool.freeString(strValue);
}

const char* StringValue::getString() const {
	if (isNull()) {
		return "";
	} else {
		return strValue;
	}
}

bool StringValue::replace(size_t pos, char c) {
	if (pos >= MAX_STR_SZ - 1) return false;
	const char* s = getString();
	if (strlen(s) >= MAX_STR_SZ) return false;
	pool.freeString(s);
	char r[MAX_STR_SZ];
	memset(r, 0, sizeof(r));
	strcpy(r, s);
	for (size_t i = strlen(r); i < pos; i++) {
		r[i] = '0';
	}
	r[pos] = c;
	strValue = pool.getString(r);
	return true;
}

bool StringValue::operator<(const StringValue& p) const {
	return strcmp(getString(), p.getString()) < 0;
}

bool StringValue::operator>(const StringValue& p) const {
	return strcmp(getString(), p.getString()) > 0;
}

StringValue& StringValue::operator=(const StringValue& p) {
	if (this != &p) {
		strValue = pool.getString(p.strValue);
	}
	return *this;
}

}