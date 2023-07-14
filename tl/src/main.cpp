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
    prjct::lbrSome::printSomething();
    prjct::lbrAnother::printSomething();
    std::cout << std::endl;

    std::cout << "Transitive dependency:" << std::endl;
#ifndef THINGY_INTERFACE
    std::cout << "Via AnotherLibrary: ";
    prjct::lbrAnother::doTheThing();
#endif
#if defined(THINGY_PUBLIC) || defined(THINGY_INTERFACE)
    std::cout << "Directly: ";
    dpndnc::doThingy();
#endif
}
