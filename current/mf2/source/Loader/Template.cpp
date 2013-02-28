#include "Template.h"

#include "s3eTypes.h"

namespace mf2 {

Template::Template(const char* name, Template* t, int l): AbstractConfigurable(), VarHolder(NULL, name), next(t), level(l), items(), deep(0) {}

int Template::Item::getType() const {
	if (name.isNull()) {
		return itClose;
	}
	if (value.isNull()) {
		return itOpen;
	}
	return itSet;
}

AbstractConfigurable* Template::createContext(const char* name) {
	items.push_back(Item(name));
	deep++;
	return this;
}

bool Template::setValue(const char* name, const char* value) {
	items.push_back(Item(name, value));
	return true;
}

bool Template::closeContext() {
	if (deep == 0) return true;
	deep--;
	items.push_back(Item());
	return true;
}

bool Template::apply(AbstractConfigurable* ctx) {
	const char* v;
	for (IIter p = items.begin(); p != items.end(); ++p) {
		switch (p->getType()) {
			case itOpen:
				if (ctx->createContext(p->name.getString()) == NULL) return false;
				break;
			case itClose:
				if (!ctx->closeContext()) return false;
				break;
			case itSet:
				v = magicValue(p->value.getString());
				if (!ctx->setValue(p->name.getString(), v)) return false;
				break;
		}
	}
	return true;
}

}