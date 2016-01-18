#version 440

uniform mat4    model;

in vec3     fragNormal;
in vec3     fragVert;

out vec4    finalColor;

void main() {

    vec3    lightPosition = vec3(0.0, -15.0, 7.0);
    vec3    lightColor = vec3(1.0, 1.0, 1.0);

    //calculate normal in world coordinates
    mat3    normalMatrix = transpose(inverse(mat3(model)));
    vec3    normal = normalize(normalMatrix * fragNormal);

    //calculate the location of this fragment (pixel) in world coordinates
    vec3    fragPosition = vec3(model * vec4(fragVert, 1));

    //calculate the vector from this pixels surface to the light source
    vec3    surfaceToLight = lightPosition - fragPosition;

    //calculate the cosine of the angle of incidence
    float   AoI = dot(normal, surfaceToLight);
    float   brightness = AoI / (length(surfaceToLight) * length(normal));
    brightness = clamp(brightness, 0, 1);

    //calculate final color of the pixel, based on:
    // 1. The angle of incidence: brightness
    // 2. The color/intensities of the light: light.intensities
    // 3. The texture and texture coord: texture(tex, fragTexCoord)
    vec4    surfaceColor = vec4(1.0, 1.0, 1.0, 1.0);
    finalColor = vec4(brightness * lightColor * surfaceColor.rgb, surfaceColor.a);
}

