#include "IwGx.h"
#include "StringPool.h"
#include "Value.h"

using namespace mf2;

void init() {
     IwGxInit();
     pool.init();
}

void release() {
     pool.release();
     IwGxTerminate();
}

int main() {
    init();

	Value s("");
	s.replace(3, '1');
	int v = s.getInt();
	printf("%d\n", v);

    release();
    return 0;
}