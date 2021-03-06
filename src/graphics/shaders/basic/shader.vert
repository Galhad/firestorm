#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 projection;
} ubo;

layout(push_constant) uniform Transform
{
	mat4 model;
} transform;

layout(location = 0) in vec3 inPostion;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

void main() {
    gl_Position = ubo.projection * ubo.view * transform.model * vec4(inPostion, 1.0);
    fragColor = inColor;
    fragTexCoord = inTexCoord;
}
