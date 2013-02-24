#ifndef _STRING_VALUE_H_
#define _STRING_VALUE_H_

class StringValue {
		enum {
			MAX_STR_SZ = 32
		};
		const char* strValue;
	public:
		StringValue(const char* s);
		StringValue(const StringValue& p);
		~StringValue();

		bool  isString() const {return true;}
		const char* getString() const {return strValue;}
		bool  replace(size_t pos, char c);

		bool  operator<(const StringValue& p)  const;
		bool  operator>(const StringValue& p)  const;
		bool  operator<=(const StringValue& p) const {return !(*this > p);}
		bool  operator>=(const StringValue& p) const {return !(*this < p);}
		bool  operator==(const StringValue& p) const {return  (*this < p) || (*this > p);}
		bool  operator!=(const StringValue& p) const {return !(*this == p);}

		StringValue& operator=(const StringValue& p);
};

#endif	// _STRING_VALUE_H_
