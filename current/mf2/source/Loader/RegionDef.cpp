#include "RegionDef.h"
#include "Desktop.h"
#include <string.h>

namespace mf2 {

RegionDef::RegionDef(): vars(), regions(), images(), zorder(0) {
	setState(stTop);
}

RegionDef::~RegionDef() {
	for (RIter p = regions.begin(); p != regions.end(); ++p) {
		delete *p;
	}
	for (VIter p = vars.begin(); p != vars.end(); ++p) {
		delete *p;
	}
}

AbstractConfigurable* RegionDef::createContext(const char* name) {
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
		if (strcmp(name, IMAGE_SCOPE) == 0) {
			state = 0;
			image.clear();
			setState(stImage);
			return this;
		}
	}
	if (getState() == stRegions) {
		RegionDef* r = new RegionDef;
		regions.push_back(r);
		return r;
	}
	return NULL;
}

bool RegionDef::closeContext() {
	if (getState() == stImage) {
		images.insert(IPair(state, image));
		image.clear();
	}
	return true;
}

bool RegionDef::setValue(const char* name, const char* value) {
	if (strcmp(name, LOCK_PROPERTY) == 0) {
		locks.push_back(StringValue(value));
		return true;
	}
	if (strcmp(name, ACTION_PROPERTY) == 0) {
		action = StringValue(value);
		return true;
	}
	if (strcmp(name, NAME_PROPERTY) == 0) {
		regionName = StringValue(value);
		return true;
	}
	if (strcmp(name, IMAGE_PROPERTY) == 0) {
		if (getState() == stImage) {
			image = StringValue(value);
		} else {
			images.insert(IPair(0, StringValue(value)));
		}
		return true;
	}
	if (strcmp(name, STATE_PROPERTY) == 0) {
		state = Value::strToNum(value);
		return true;
	}
	if (strcmp(name, ZORDER_PROPERTY) == 0) {
		zorder = Value::strToNum(value);
		return true;
	}
	if (strcmp(name, X_PROPERTY) == 0) {
		x = desktop.getXSize(Value::strToNum(value));
		return true;
	}
	if (strcmp(name, Y_PROPERTY) == 0) {
		y = desktop.getYSize(Value::strToNum(value));
		return true;
	}
	if (strcmp(name, WIDTH_PROPERTY) == 0) {
		width = desktop.getXSize(Value::strToNum(value));
		return true;
	}
	if (strcmp(name, HEIGHT_PROPERTY) == 0) {
		height = desktop.getYSize(Value::strToNum(value));
		return true;
	}
	return false;
}

}