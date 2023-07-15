#include <iostream>

#ifndef THINGY_INTERFACE
    #include <Thingy/thingy.h>
#endif

#include "stuff.h"

namespace prjct
{
    namespace lbrAnother
    {
        void doAnother()
        {
            std::cout << "ololo, " << anotherString << std::endl;
        }

#ifndef THINGY_INTERFACE
        void doTheThing()
        {
            dpndnc::doThingy();
        }
#endif
    }
}
