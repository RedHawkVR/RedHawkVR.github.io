/* Simple Vertex Shader */
#version 450 core
//values are copied into the shader
//this updates everytime the shader is executed
in vec4 vPosition;
in vec4 vColor;
//value copied out of the shader
out vec4 color;
//uniforms don't change per vertex/fragment, but hold same value for primitives until updated by the app
uniform mat4 ModelViewProjectionMatrix;

void main(){
	color = vColor;
	gl_Position = ModelViewProjectionMatrix * vPosition;
}
