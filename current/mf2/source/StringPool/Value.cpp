#include "Value.h"
#include "StringPool.h"

namespace mf2 {

Value::Value(int v): numValue(v), strValue(NULL) {}
Value::Value(const char* s): numValue(0), strValue(pool.getString(s)) {}
Value::Value(const Value& p): numValue(p.numValue), strValue(pool.getString(p.strValue)) {}

Value::~Value() {
	if (isString()) {
		pool.freeString(strValue);
	}
}

bool Value::isString() const {
	return strValue != NULL;
}

int Value::strToNum(const char* strValue) {
	bool sign = false;
	int numValue = 0;
	int base = 10;
	size_t i = 0;
	for (; i < strlen(strValue); i++) {
		if (strValue[i] != ' ') break;
	}
	if (strValue[i] == '-') {
		sign = true;
		i++;
	}
	for (; i < strlen(strValue); i++) {
		if (strValue[i] == '0') continue;
		if (strValue[i] == 'x') {
			base = 16;
			continue;
		}
		break;
	}
	for (; i < strlen(strValue); i++) {
		if ((strValue[i] >= '0')&&(strValue[i] <= '9')) {
			numValue *= base;
			numValue += strValue[i] - '0';
			continue;
		}
		if (base == 10) break;
		if ((strValue[i] >= 'a')&&(strValue[i] <= 'f')) {
			numValue *= base;
			numValue += strValue[i] - 'a' + 10;
			continue;
		}
		if ((strValue[i] >= 'A')&&(strValue[i] <= 'F')) {
			numValue *= base;
			numValue += strValue[i] - 'A' + 10;
			continue;
		}
		break;
	}
	if (sign) {
		numValue = -numValue;
	}
	return numValue;
}

int Value::getInt() const {
	if (isString()) {
		numValue = strToNum(strValue);
		pool.freeString(strValue);
		strValue = NULL;
	}
	return numValue;
}

const char* Value::getString() const {
	if (!isString()) {
		strValue = pool.getString(numValue);
	}
	return strValue;
}

bool Value::replace(size_t pos, char c) {
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

bool Value::operator<(const Value& p) const {
	if (isString() || p.isString()) {
		return strcmp(getString(), p.getString()) < 0;
	}
	return numValue < p.numValue;
}

bool Value::operator>(const Value& p) const {
	if (isString() || p.isString()) {
		return strcmp(getString(), p.getString()) > 0;
	}
	return numValue > p.numValue;
}

Value& Value::operator=(const Value& p) {
	if (this != &p) {
		numValue = p.numValue;
		strValue = pool.getString(p.strValue);
	}
	return *this;
}

}