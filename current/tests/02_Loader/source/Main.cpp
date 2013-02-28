#include "ScopeManager.h"

using namespace mf2;

void init() {
     sm.init();
}

void release() {
     sm.release();
}

int main() {
    init();


    release();
    return 0;
}