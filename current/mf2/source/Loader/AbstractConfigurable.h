#ifndef _ABSTRACT_CONFIGURABLE_H_
#define _ABSTRACT_CONFIGURABLE_H_

#include "s3eTypes.h"

namespace mf2 {

class AbstractConfigurable {
	private:
		int state;
	protected:
		virtual AbstractConfigurable* createContext(const char* name) {return NULL;}
		virtual bool setValue(const char* name, const char* value) = 0;
		virtual bool closeContext() {return true;}
	public:
		int getState() const {return state;}
		void setState(int s) {state = s;}

	friend class Loader;
	friend class Template;
};

}

#endif	// _ABSTRACT_CONFIGURABLE_H_
