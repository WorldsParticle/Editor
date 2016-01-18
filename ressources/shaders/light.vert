#version 440

layout(location = 0) in vec3 positions;
layout(location = 1) in vec3 normals;

uniform mat4    model;
uniform mat4    view;
uniform mat4    projection;

out vec3    fragNormal;
out vec3    fragVert;

void main()
{
    fragVert = positions;
    fragNormal = normals;
    gl_Position = projection * view * model * vec4(positions, 1.0);
}
