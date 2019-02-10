


#ifndef FIRESTORM_MAPPEDMEMORYBUFFER_HPP
#define FIRESTORM_MAPPEDMEMORYBUFFER_HPP

#include "Buffer.hpp"

#include <memory>

namespace fs::graphics
{
class MappedMemoryBuffer : public Buffer
{
public:
    MappedMemoryBuffer() = default;
    ~MappedMemoryBuffer() override = default;

    void create(const Device& device, VkDeviceSize size);
    void destroy() override;

    void* getMappedData() const;

protected:
    void* mappedData = nullptr;

};

typedef std::unique_ptr<MappedMemoryBuffer> MappedMemoryBufferPtr;
}

#endif //FIRESTORM_MAPPEDMEMORYBUFFER_HPP
