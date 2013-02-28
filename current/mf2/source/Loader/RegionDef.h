#ifndef _REGION_DEF_H_
#define _REGION_DEF_H_

#include <map>
#include <vector>
#include "AbstractConfigurable.h"
#include "StringValue.h"
#include "VarDef.h"

using namespace std;

#define REGIONS_SCOPE       "regions"
#define VARS_SCOPE          "vars"
#define SET_SCOPE           "set"
#define IMAGE_SCOPE         "image"

#define ACTION_PROPERTY     "action"
#define ZORDER_PROPERTY     "zorder"
#define NAME_PROPERTY       "name"
#define LOCK_PROPERTY       "lock"
#define X_PROPERTY          "x"
#define Y_PROPERTY          "y"
#define WIDTH_PROPERTY      "width"
#define HEIGHT_PROPERTY     "height"
#define IMAGE_PROPERTY      "image"
#define STATE_PROPERTY      "state"

namespace mf2 {

class RegionDef: public AbstractConfigurable {
	private:
		enum {
			stTop           = 0,
			stRegions       = 1,
			stImage         = 2
		};
		StringValue           action;
		StringValue           regionName;
		StringValue           image;
		int                   state;
		int                   zorder;
		int                   x, y, width, height;
		vector<RegionDef*>    regions;
		vector<VarDef*>       vars;
		vector<StringValue>   locks;
		map<int, StringValue> images;
	public:
		RegionDef();
		~RegionDef();
		virtual AbstractConfigurable* createContext(const char* name);
		virtual bool setValue(const char* name, const char* value);
		virtual bool closeContext();

	typedef vector<VarDef*>::iterator VIter;
	typedef vector<RegionDef*>::iterator RIter;
	typedef vector<StringValue>::iterator LIter;
	typedef map<int, StringValue>::iterator IIter;
	typedef pair<int, StringValue> IPair;
};

}

#endif	// _REGION_DEF_H_
