// MIT License
//
// Copyright (c) 2018 Wojciech Wilk
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
