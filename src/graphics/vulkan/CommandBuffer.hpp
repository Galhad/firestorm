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

#ifndef FIRESTORM_COMMANDBUFFER_HPP
#define FIRESTORM_COMMANDBUFFER_HPP

#include "Device.hpp"

#include <memory>

namespace fs::graphics
{
class CommandBuffer
{
public:
    CommandBuffer() = default;
    virtual ~CommandBuffer() = default;

    void create(const Device& device);
    virtual void destroy();

    void beginSingleTimeCommand();
    void endSingleTimeCommand();

    void reset();

    const VkCommandBuffer getCommandBuffer() const;

private:
    const Device* device = nullptr;

    VkCommandBuffer commandBuffer = VK_NULL_HANDLE;
};

typedef std::unique_ptr<CommandBuffer> CommandBufferPtr;

}
#endif //FIRESTORM_COMMANDBUFFER_HPP
