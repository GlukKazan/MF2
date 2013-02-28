#ifndef _VALUE_H_
#define _VALUE_H_

namespace mf2 {

class Value {
	private:
		enum {
			MAX_STR_SZ = 32
		};
		mutable int numValue;
		mutable const char* strValue;
	public:
		Value(int v);
		Value(const char* s);
		Value(const Value& p);
		~Value();

		static int  strToNum(const char* strValue);
		static bool strToBool(const char* strValue);

		bool  isString() const;
		int   getInt() const;
		const char* getString() const;
		bool  replace(int pos, char c);

		bool  operator<(const Value& p)  const;
		bool  operator>(const Value& p)  const;
		bool  operator<=(const Value& p) const {return !(*this > p);}
		bool  operator>=(const Value& p) const {return !(*this < p);}
		bool  operator==(const Value& p) const {return  (*this < p) || (*this > p);}
		bool  operator!=(const Value& p) const {return !(*this == p);}

		Value& operator=(const Value& p);
};

}

#endif	// _VALUE_H_
