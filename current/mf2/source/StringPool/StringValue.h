#ifndef _STRING_VALUE_H_
#define _STRING_VALUE_H_

#include "s3eTypes.h"

namespace mf2 {

class StringValue {
		enum {
			MAX_STR_SZ = 32
		};
		const char* strValue;
	public:
		StringValue(): strValue(NULL) {}
		StringValue(char c);
		StringValue(const char* s);
		StringValue(const StringValue& p);
		~StringValue();

		bool  isString() const {return true;}
		bool  isNull() const {return (strValue == NULL);}
		void  clear();
		const char* getString() const;
		bool  replace(int pos, char c);

		bool  operator<(const StringValue& p)  const;
		bool  operator>(const StringValue& p)  const;
		bool  operator<=(const StringValue& p) const {return !(*this > p);}
		bool  operator>=(const StringValue& p) const {return !(*this < p);}
		bool  operator==(const StringValue& p) const {return  (*this < p) || (*this > p);}
		bool  operator!=(const StringValue& p) const {return !(*this == p);}

		StringValue& operator=(const StringValue& p);
};

}

#endif	// _STRING_VALUE_H_
