


#include "Resource.hpp"

namespace fs::io
{

void Resource::create(const std::string& filename, const std::vector<core::fs_uint8>& data)
{
    this->filename = filename;
    this->data = data;
}

void Resource::create(const std::string& filename, std::vector<core::fs_uint8>&& data)
{
    this->filename = filename;
    this->data = data;
}

void Resource::destroy()
{
    data.clear();
    filename.clear();
}

const std::vector<core::fs_uint8>& Resource::getData() const
{
    return data;
}

std::vector<core::fs_uint8>& Resource::getData()
{
    return data;
}

const std::string& Resource::getFilename() const
{
    return filename;
}

}
