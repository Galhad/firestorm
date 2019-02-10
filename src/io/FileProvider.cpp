


#include "FileProvider.hpp"

#include <fstream>

namespace fs::io
{
void FileProvider::create()
{

}

void FileProvider::destroy()
{

}

Resource FileProvider::loadFile(const std::string& filename) const
{
    std::ifstream file{filename.c_str(), std::ifstream::binary | std::ifstream::in};
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file " + filename);
    }

    file.seekg(0, std::ifstream::end);
    core::fs_int64 size = file.tellg();
    file.seekg(0, std::ifstream::beg);

    std::vector<core::fs_uint8> data(static_cast<unsigned long>(size));
    file.read(reinterpret_cast<char*>(data.data()), size);
    file.close();

    Resource resource;
    resource.create(filename, std::move(data));
    return resource;
}

std::future<Resource> FileProvider::loadFileAsync(const std::string& filename) const
{
    return std::async(std::launch::async, [this, filename]
    {
        return loadFile(filename);
    });
}
}