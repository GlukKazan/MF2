#ifndef _SCOPE_DEF_H_
#define _SCOPE_DEF_H_

#include <vector>
#include "AbstractConfigurable.h"
#include "RegionDef.h"
#include "VarDef.h"

using namespace std;

#define REGIONS_SCOPE       "regions"
#define VARS_SCOPE          "vars"
#define SET_SCOPE           "set"

#define DEFAULT_PROPERTY    "default"
#define LOAD_PROPERTY       "load"
#define GAME_PROPERTY       "game"

namespace mf2 {

class ScopeDef: public AbstractConfigurable {
	private:
		enum {
			stTop           = 0,
			stRegions       = 1
		};
		bool                  IsDefault;
		StringValue           load;
		StringValue           game;
		vector<RegionDef*>    regions;
		vector<VarDef*>       vars;
	public:
		ScopeDef();
		~ScopeDef();
		virtual AbstractConfigurable* createContext(const char* name);
		virtual bool setValue(const char* name, const char* value);

		bool isDefault() const {return IsDefault;}

	typedef vector<VarDef*>::iterator VIter;
	typedef vector<RegionDef*>::iterator RIter;
};

}

#endif	// _SCOPE_DEF_H_
