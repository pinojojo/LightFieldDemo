#version 430

// in
layout (location = 0) in vec3 iPos;

// out
layout(location = 1) out vec3 nearPoint;
layout(location = 2) out vec3 farPoint;

// uniform
uniform mat4 view;
uniform mat4 projection;

vec3 UnprojectPoint(float x, float y, float z, mat4 vm, mat4 pm) {
    mat4 viewInv = inverse(vm);
    mat4 projInv = inverse(pm);
    vec4 unprojectedPoint =  viewInv * projInv * vec4(x, y, z, 1.0);
    return unprojectedPoint.xyz / unprojectedPoint.w;
}

// normal vertice projection
void main() {
    vec3 p = iPos;
    nearPoint = UnprojectPoint(p.x, p.y, 0.0, view, projection).xyz; // unprojecting on the near plane
    farPoint = UnprojectPoint(p.x, p.y, 1.0, view, projection).xyz; // unprojecting on the far plane

   // gl_Position = projection * view * vec4(iPos.xyz, 1.0);

    gl_Position =vec4(p,1.0);
}