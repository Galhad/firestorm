#include "SimpleApplication.hpp"
#include <iostream>

using namespace fs;

int main(int arg, char** argv)
{
    try
    {
        fs::SimpleApplicationPtr simpleApplication(new fs::SimpleApplication());
        simpleApplication->run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Unknown error: " << e.what() << std::endl;
    }

    return 0;
}
