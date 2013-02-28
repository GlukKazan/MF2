#include "ScopeManager.h"
#include "ConfigLoader.h"
#include "StringPool.h"
#include "Desktop.h"

namespace mf2 {

ScopeManager sm;

bool ScopeManager::init() {
	setState(stTop);
	desktop.init();
	pool.init();
	files = new queue<const char*>();
	scopes = new map<StringValue, ScopeDef*>();
	return load(MAIN_CONFIG);
}

void ScopeManager::release() {
	for (SIter p = scopes->begin(); p != scopes->end(); ++p) {
		delete p->second;
	}
	delete scopes;
	delete files;
	pool.release();
	desktop.release();
}

bool ScopeManager::load(const char* name) {
	Loader loader;
	setState(stTop);
	files->push(pool.getString(name));
	while (!files->empty()) {
		const char* fn = files->front();
		files->pop();
		if (!loader.load(fn, (AbstractConfigurable*)this)) return false;
		pool.freeString(fn);
	}
	return true;
}

AbstractConfigurable* ScopeManager::createContext(const char* name) {
	if (getState() == stTop) {
		if (strcmp(name, DISPLAY_SCOPE) == 0) {
			return &desktop;
		}
		if (strcmp(name, SCOPES_SCOPE) == 0) {
			setState(stScopes);
			return this;
		}
	}
	if (getState() == stScopes) {
		ScopeDef* r = new ScopeDef;
		scopes->insert(SPair(StringValue(name), r));
		return r;
	}
	return (AbstractConfigurable*)this;
}

bool ScopeManager::setValue(const char* name, const char* value) {
	if (getState() == stTop) {
		if (strcmp(name, LOAD_PROPERTY) == 0) {
			files->push(pool.getString(value));
			return true;
		}
	}
	return false;
}

}