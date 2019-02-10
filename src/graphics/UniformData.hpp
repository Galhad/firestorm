


#ifndef FIRESTORM_UNIFORMDATA_HPP
#define FIRESTORM_UNIFORMDATA_HPP

#include <glm/glm.hpp>

namespace fs::graphics
{
struct UniformData
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
};
}

#endif //FIRESTORM_UNIFORMDATA_HPP
