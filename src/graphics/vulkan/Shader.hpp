


#ifndef FIRESTORM_SHADER_HPP
#define FIRESTORM_SHADER_HPP

#include "Device.hpp"
#include "core/Types.hpp"

#include <memory>

namespace fs::graphics
{

enum class ShaderType
{
    Unknwon,
    Vertex,
    Fragment
};

class Shader
{
public:
    Shader() = default;
    virtual ~Shader() = default;

    void create(const Device& device, const std::vector<core::fs_int8>& code, ShaderType type);
    virtual void destroy();

    const VkShaderModule getShaderModule() const;

private:
    const Device* device = nullptr;

    ShaderType type = ShaderType::Unknwon;
    VkShaderModule shaderModule = VK_NULL_HANDLE;
};

typedef std::unique_ptr<Shader> ShaderPtr;
}

#endif //FIRESTORM_SHADER_HPP
