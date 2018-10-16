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
}