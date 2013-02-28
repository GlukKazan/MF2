#ifndef _LOADER_H_
#define _LOADER_H_

#include <stack>
#include <map>
#include <yaml.h>
#include "AbstractConfigurable.h"
#include "Template.h"
#include "StringValue.h"

#define MAX_NAME_SZ           80

#define TEMPLATES_SCOPE       "templates"
#define TEMPLATE_PROPERTY     "template"

using namespace std;

namespace mf2 {

	class Loader: public AbstractConfigurable {
	private:
		enum {
			stTop       = 0,
			stTemplates = 1,
			stTemplate  = 2
		};
		struct Scope {
			Scope(AbstractConfigurable* c, int s = 0): ctx(c), state(s) {}
			Scope(const Scope& p): ctx(p.ctx), state(p.state) {}
			AbstractConfigurable* ctx;
			int state;
		};
        yaml_parser_t                 parser;
        yaml_event_t                  evnt;
		stack<Scope>                  scopes;
		map<StringValue, Template*>   templates;
		char                          currentName[MAX_NAME_SZ];
		void                          clearCurrentName();
        bool                          notify(AbstractConfigurable* ctx);
		virtual AbstractConfigurable* createContext(const char* name);
		virtual bool                  setValue(const char* name, const char* value);
		virtual bool                  closeContext();
		void                          dropTemplates(int level = 0);
		bool                          applyTemplate(const char* name);
	public:
		Loader();
		~Loader();
		bool                          load(const char* name, AbstractConfigurable* ctx);

	typedef map<StringValue, Template*>::iterator TIter;
	typedef pair<StringValue, Template*> TPair;
};

}

#endif	// _LOADER_H_
