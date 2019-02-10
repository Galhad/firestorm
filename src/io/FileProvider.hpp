


#ifndef FIRESTORM_FILEPROVIDER_HPP
#define FIRESTORM_FILEPROVIDER_HPP

#include "Resource.hpp"

#include <future>
#include <memory>

namespace fs::io
{
class FileProvider
{
public:
    FileProvider() = default;
    virtual ~FileProvider() = default;

    void create();
    virtual void destroy();

    Resource loadFile(const std::string& filename) const;
    std::future<Resource> loadFileAsync(const std::string& filename) const;

};

typedef std::unique_ptr<FileProvider> FileProviderPtr;
}

#endif //FIRESTORM_FILEPROVIDER_HPP
