#ifndef _SCOPE_MANAGER_H_
#define _SCOPE_MANAGER_H_

#include <queue>
#include "AbstractConfigurable.h"

using namespace std;

#define MAIN_CONFIG     "main.json"

#define LOAD_PROPERTY   "load"

namespace mf2 {

class ScopeManager: public AbstractConfigurable {
	private:
		enum {
			stTop       = 0
		};
		queue<const char*>* files;
		bool load(const char* name);
		void deepIncrement();
		void deepDecrement();
		virtual AbstractConfigurable* createContext(const char* name);
		virtual bool setValue(const char* name, const char* value);
	public:
		bool init();
		void release();

	friend class AbstractConfigurable;
};

extern ScopeManager sm;

}

#endif	// _SCOPE_MANAGER_H_
