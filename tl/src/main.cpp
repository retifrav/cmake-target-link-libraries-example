#include <iostream>

#include <SomeLibrary/some.h>
#include <AnotherLibrary/another.h>

#if defined(THINGY_PUBLIC) || defined(THINGY_INTERFACE)
    #include <Thingy/thingy.h>
#endif

int main(int argc, char *argv[])
{
    std::cout << "Base application message" << std::endl;
    std::cout << std::endl;

    std::cout << "Direct dependencies:" << std::endl;
    prjct::lbrSome::doSome();
    prjct::lbrAnother::doAnother();
    std::cout << std::endl;

    std::cout << "Transitive dependency:" << std::endl;
#ifndef THINGY_INTERFACE
    std::cout << "via AnotherLibrary | ";
    prjct::lbrAnother::doTheThing();
#endif
#if defined(THINGY_PUBLIC) || defined(THINGY_INTERFACE)
    std::cout << "directly | ";
    dpndnc::doThingy();
#endif
}
