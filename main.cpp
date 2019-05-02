//
// Created by wsl on 19-4-18.
//

#include <iostream>
#include "src/dstring.h"
#include"src/dlist.h"
#include "src/dmap.h"
#include "vm/compile.h"
#include "vm/vm.h"

using namespace std;

int main() {

    VirtualMachine vm = VirtualMachine();

    vm.run();

    return 0;
}