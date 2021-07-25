#version 330
in vec3 TexCoords;
uniform vec4 colorskybox;
out vec4 color;
uniform samplerCube skybox;
void main()
{
color=texture(skybox,TexCoords)*colorskybox;
}