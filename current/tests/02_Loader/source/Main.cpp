#include "IwGx.h"
#include "ScopeManager.h"

using namespace mf2;

void init() {
     IwGxInit();
     sm.init();
}

void release() {
     sm.release();
     IwGxTerminate();
}

int main() {
    init();


    release();
    return 0;
}