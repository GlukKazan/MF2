#include "ScopeManager.h"
#include "Loader.h"
#include "StringPool.h"

namespace mf2 {

ScopeManager sm;

bool ScopeManager::init() {
	files = new queue<const char*>();
	return load(MAIN_CONFIG);
}

void ScopeManager::release() {
	delete files;
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
	// TODO:

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