#include "Loader.h"
#include <string.h>

namespace mf2 {

Loader::Loader(): scopes(), templates() {}

Loader::~Loader() {
	dropTemplates();
}

void Loader::clearCurrentName() {
	memset(currentName, 0, sizeof(currentName));
}

bool Loader::load(const char* name, AbstractConfigurable* ctx) {
	bool r = true;
	setState(stTop);
	scopes.push(Scope(ctx, ctx->getState()));
	clearCurrentName();
    yaml_parser_initialize(&parser);
    FILE* input = fopen(name, "rb");
	if (input != NULL) {
		yaml_parser_set_input_file(&parser, input);
		int done = 0;
		while (!done) {
	        if (!yaml_parser_parse(&parser, &evnt)) {
		        r = false;
			}
			if (!notify(ctx)) {
				r = false;
			}
			if (!r) break;
			done = (evnt.type == YAML_STREAM_END_EVENT);
			yaml_event_delete(&evnt);
		}
	    fclose(input);
	} else {
		r = true;
	}
    yaml_parser_delete(&parser);
	return r;
}

bool Loader::notify(AbstractConfigurable* ctx) {
	bool r = true;
    switch (evnt.type) {
        case YAML_MAPPING_START_EVENT:
        case YAML_SEQUENCE_START_EVENT:
			r = (createContext(currentName) != NULL);
			clearCurrentName();
			break;
        case YAML_MAPPING_END_EVENT:
        case YAML_SEQUENCE_END_EVENT:
			if (!closeContext()) return false;
            break;
        case YAML_SCALAR_EVENT:
			if (currentName[0] == 0) {
				strncpy(currentName, (const char*)evnt.data.scalar.value, sizeof(currentName) - 1);
				break;
			}
			r = setValue(currentName, (const char*)evnt.data.scalar.value);
			clearCurrentName();
            break; 
        default:
            break;
    }
	return r;
}

void Loader::dropTemplates(int level) {
	for (bool f = true; f;) {
		f = false;
		for (TIter p = templates.begin(); p != templates.end(); ++p) {
			if (p->second->getLevel() > level) {
				f = true;
				Template* next = p->second->getNext();
				delete p->second;
				if (next == NULL) {
					templates.erase(p);
				} else {
					p->second = next;
				}
				break;
			}
		}
	}
}

AbstractConfigurable* Loader::createContext(const char* name) {
	AbstractConfigurable* r = (AbstractConfigurable*)this;
	if (strcmp(name, TEMPLATES_SCOPE) == 0) {
		scopes.push(Scope(r, stTemplates));
		return r;
	}
	if (scopes.empty()) return NULL;
	if ((scopes.top().ctx == r) && (scopes.top().state == stTemplates)) {
		StringValue nm(name);
		TIter p = templates.find(nm);
		if (p != templates.end()) {
			r = p->second = new Template(name, p->second, scopes.size());
		} else {
			Template* t = new Template(name, NULL, scopes.size());
			templates.insert(TPair(nm, t));
			r = (AbstractConfigurable*)t;
		}
		scopes.push(Scope(r));
		return r;
	}
	r = scopes.top().ctx->createContext(name);
	scopes.push(Scope(r, r->getState()));
	return r;
}

bool Loader::closeContext() {
	if (scopes.empty()) return false;
	scopes.top().ctx->closeContext();
	scopes.pop();
	dropTemplates(scopes.size());
	if (!scopes.empty()) {
		scopes.top().ctx->setState(scopes.top().state);
	}
	return true;
}

bool Loader::setValue(const char* name, const char* value) {
	if (strcmp(name, TEMPLATE_PROPERTY) == 0) {
		return applyTemplate(value);
	}
	if (scopes.empty()) return false;
	return scopes.top().ctx->setValue(name, value);
}

bool Loader::applyTemplate(const char* name) {
	for (TIter p = templates.begin(); p != templates.end(); ++p) {
		if (p->second->isEqual(name)) {
			p->second->setMagic(name);
			return p->second->apply((AbstractConfigurable*)this);
		}
	}
	return false;
}

}