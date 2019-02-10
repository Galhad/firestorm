


#include "PhysicsApplication.hpp"

using namespace fs;

int main(int arg, char** argv)
{
    try
    {
        fs::SimpleApplicationPtr simpleApplication(new fs::PhysicsApplication());
        simpleApplication->run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Unknwon error: " << e.what() << std::endl;
    }

    return 0;
}
