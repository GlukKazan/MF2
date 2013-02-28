#ifndef _SCOPE_MANAGER_H_
#define _SCOPE_MANAGER_H_

#include <map>
#include <queue>
#include "AbstractConfigurable.h"
#include "ScopeDef.h"

using namespace std;

#define MAIN_CONFIG     "main.json"

#define DISPLAY_SCOPE   "display"
#define SCOPES_SCOPE    "scopes"

#define LOAD_PROPERTY   "load"

namespace mf2 {

class ScopeManager: public AbstractConfigurable {
	private:
		enum {
			stTop       = 0,
			stScopes    = 1
		};
		queue<const char*>* files;
		map<StringValue, ScopeDef*>* scopes;
		bool load(const char* name);
		void deepIncrement();
		void deepDecrement();
		virtual AbstractConfigurable* createContext(const char* name);
		virtual bool setValue(const char* name, const char* value);
	public:
		bool init();
		void release();

	typedef map<StringValue, ScopeDef*>::iterator SIter;
	typedef pair<StringValue, ScopeDef*> SPair;

	friend class AbstractConfigurable;
};

extern ScopeManager sm;

}

#endif	// _SCOPE_MANAGER_H_
