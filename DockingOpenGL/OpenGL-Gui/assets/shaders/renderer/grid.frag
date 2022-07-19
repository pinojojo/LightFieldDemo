#version 430
// in
layout(location = 1) in vec3 nearPoint; // nearPoint calculated in vertex shader
layout(location = 2) in vec3 farPoint; // farPoint calculated in vertex shader

// out
layout(location = 0) out vec4 outColor;

// uniform 
uniform mat4 fragProj;
uniform mat4 fragView;
uniform float far;
uniform float near;



vec4 grid(vec3 fragPos3D, float scale) {
    vec2 coord = fragPos3D.xy * scale;
    vec2 derivative = fwidth(coord);
    vec2 grid = abs(fract(coord - 0.5) - 0.5) / derivative;
    float line = min(grid.x, grid.y);
    float minimumz = min(derivative.y, 1);
    float minimumx = min(derivative.x, 1);
    float lineFlag= 1.0 - min(line, 1.0);
    //vec4 color = vec4(0.2*lineFlag, 0.2*lineFlag, 0.2*lineFlag, 1);
    vec4 color = vec4(0.4, 0.42, 0.4, lineFlag);



    // y axis green
    if(fragPos3D.x > -0.1 * minimumx && fragPos3D.x < 0.1 * minimumx)
        color.y = 1.0;
    // x axis red
    if(fragPos3D.y > -0.1 * minimumz && fragPos3D.y < 0.1 * minimumz)
        color.x = 1.0;


    
    return color;
}

float computeDepth(vec3 pos) {
    vec4 clip_space_pos = fragProj * fragView * vec4(pos.xyz, 1.0);
    float ndc_depth = clip_space_pos.z / clip_space_pos.w;  // ndc depth range: (-1,1)
    float depth = (ndc_depth + 1) / 2 ; // gl_FragDepth

    return depth;
}

float computeLinearDepth(vec3 pos) {
    // Ref:https://stackoverflow.com/questions/7777913/how-to-render-depth-linearly-in-modern-opengl-with-gl-fragcoord-z-in-fragment-sh
    vec4 clip_space_pos = fragProj * fragView * vec4(pos.xyz, 1.0);
    float ndc_depth = clip_space_pos.z / clip_space_pos.w; // ndc
    float linearDepth = (2.0 * near * far) / (far + near - ndc_depth * (far - near)); // get linear value between 0.01 and 100
    return linearDepth / far; // normalize
}

float fadingFunc(float initialFading)
{
    float ret;

    ret=3.0*initialFading;

    ret=clamp(ret,0,1);
    
    return ret;
}


void main() {
    // Grid Position
    float t = -nearPoint.z / (farPoint.z - nearPoint.z);
    vec3 fragPos3D = nearPoint + t * (farPoint - nearPoint);

    // Fading
    float linearDepth = computeLinearDepth(fragPos3D);
    float fading=1.0;
    fading=1.0-fadingFunc(linearDepth);

   
    // Color 
    outColor = (grid(fragPos3D, 5))* float(t > 0);
    outColor.a *= fading;

    // Calculating Depth
    gl_FragDepth=computeDepth(fragPos3D);
   
}