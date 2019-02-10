


#ifndef FIRESTORM_RESOURCE_HPP
#define FIRESTORM_RESOURCE_HPP

#include "core/Types.hpp"

#include <memory>
#include <vector>

namespace fs::io
{
class Resource
{
public:
    Resource() = default;
    virtual ~Resource() = default;

    void create(const std::string& filename, const std::vector<core::fs_uint8>& data);
    void create(const std::string& filename, std::vector<core::fs_uint8>&& data);
    virtual void destroy();

    const std::vector<core::fs_uint8>& getData() const;
    std::vector<core::fs_uint8>& getData();

    const std::string& getFilename() const;

protected:
    std::vector<core::fs_uint8> data;
    std::string filename;

};

typedef std::unique_ptr<Resource> ResourcePtr;
}

#endif //FIRESTORM_RESOURCE_HPP
