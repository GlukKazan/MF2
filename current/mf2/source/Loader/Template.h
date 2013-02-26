#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include <vector>
#include "AbstractConfigurable.h"
#include "VarHolder.h"

using namespace std;

namespace mf2 {

class Template: public AbstractConfigurable
              , public VarHolder {
	private:
		enum {
			itOpen  = 0,
			itClose = 1,
			itSet   = 2
		};
		struct Item {
			Item(const char* nm = NULL, const char* vl = NULL): name(nm), value(vl) {}
			Item(const Item& p): name(p.name), value(p.value) {}
			StringValue name;
			StringValue value;
			int getType() const;
		};
		Template*       next;
		int             level;
		vector<Item>    items;
	public:
		Template(const char* name, Template* t, int l);

		virtual AbstractConfigurable* createContext(const char* name);
		virtual bool setValue(const char* name, const char* value);
		virtual bool closeContext();

		int       getLevel() const {return level;}
		Template* getNext() {return next;}
		bool      apply(AbstractConfigurable* ctx);

	typedef vector<Item>::iterator IIter;
};

}

#endif	// _TEMPLATE_H_
