#include "ScopeDef.h"

namespace mf2 {

ScopeDef::ScopeDef(): vars(), regions(), IsDefault(false) {
	setState(stTop);
}

ScopeDef::~ScopeDef() {
	for (RIter p = regions.begin(); p != regions.end(); ++p) {
		delete *p;
	}
	for (VIter p = vars.begin(); p != vars.end(); ++p) {
		delete *p;
	}
}

AbstractConfigurable* ScopeDef::createContext(const char* name) {
	if (getState() == stTop) {
		if (strcmp(name, REGIONS_SCOPE) == 0) {
			setState(stRegions);
			return this;
		}
		if (strcmp(name, VARS_SCOPE) == 0) {
			VarDef* r = new VarDef(VarDef::dtVar);
			vars.push_back(r);
			return r;
		}
		if (strcmp(name, SET_SCOPE) == 0) {
			VarDef* r = new VarDef(VarDef::dtSet);
			vars.push_back(r);
			return r;
		}
	}
	if (getState() == stRegions) {
		RegionDef* r = new RegionDef;
		regions.push_back(r);
		return r;
	}
	return NULL;
}

bool ScopeDef::setValue(const char* name, const char* value) {
	if (strcmp(name, DEFAULT_PROPERTY) == 0) {
		IsDefault = Value::strToBool(value);
		return true;
	}
	if (strcmp(name, LOAD_PROPERTY) == 0) {
		load = StringValue(value);
		return true;
	}
	if (strcmp(name, GAME_PROPERTY) == 0) {
		game = StringValue(value);
		return true;
	}
	return false;
}

}