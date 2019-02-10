


#include "Shader.hpp"

namespace fs::graphics
{
void Shader::create(const fs::graphics::Device& device, const std::vector<fs::core::fs_int8>& code,
                    fs::graphics::ShaderType type)
{
    this->device = &device;

    VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
    shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shaderModuleCreateInfo.codeSize = code.size();
    shaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    if (vkCreateShaderModule(device.getDevice(), &shaderModuleCreateInfo, nullptr, &shaderModule) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create shader module.");
    }
}

void Shader::destroy()
{
    vkDestroyShaderModule(device->getDevice(), shaderModule, nullptr);

    type = ShaderType::Unknwon;
    device = nullptr;
}

const VkShaderModule Shader::getShaderModule() const
{
    return shaderModule;
}
}
