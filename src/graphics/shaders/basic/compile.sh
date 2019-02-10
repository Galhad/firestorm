#!/bin/bash

VULKAN_SDK_GLSLANG_VALIDATOR=/home/galhad/sources/VulkanSDK/1.0.65.0/x86_64/bin/glslangValidator

$VULKAN_SDK_GLSLANG_VALIDATOR -V shader.vert
$VULKAN_SDK_GLSLANG_VALIDATOR -V shader.frag

HEADER_FILE=BasicShaders.hpp
echo '// MIT License





















#ifndef FIRESTORM_BASICSHADERS_HPP
#define FIRESTORM_BASICSHADERS_HPP
' > ${HEADER_FILE}

echo 'namespace fs::graphics
{
' >> ${HEADER_FILE}

xxd -i vert.spv >> ${HEADER_FILE}
xxd -i frag.spv >> ${HEADER_FILE}

echo '}' >> ${HEADER_FILE}

echo '#endif //FIRESTORM_BASICSHADERS_HPP' >> ${HEADER_FILE}

