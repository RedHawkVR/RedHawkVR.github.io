/* buffer block */

buffer BufferObject {	//create a read-writable buffer
	int mode;			// preamble members
	vec4 points[];		//last member can be an unsized array
};

/* I/O Block */

// vertex shader output
out Lighting {
	vec3 normal;
	vec2 bumpCoord;
};

// fragment shader input
#version 440
in Lighting {
	layout(location=1) vec3 normal;
	layout(location=2) vec2 bumpCoord;
};

// since each location can hold a size of vec4, we can use component to put smaller objects into the same location
#version 440
in Lighting {
	layout(location=1, component=0) vec2 offset;
	layout(location=2, component=2) vec2 bumpCoord;
};

/* static shader control flow */

#version 330 core

void func_1() {}
void func_2() {}

uniform int func;

void main(){
	if(func == 1){
		func_1();
	} else {
		func_2();
	}
}

/* Subroutine for selecting either ambient or diffuse lighting */

// declaring subroutine
subroutine vec4 LightFunc(vec3);

subroutine (LightFunc) vec4 ambient(vec3 n){
	return Materials.ambient;
}

subroutine (LightFunc) vec4 diffuse(vec3 n){
	return Materials.diffuse * max(dot(normalize(n), LightVec.xyz), 0.0);
}

subroutine uniform LightFunc materialShader;

// using subroutine
GLint materialShaderLoc;
GLuint ambientIndex;
GLuint diffuseIndex;

glUseProgram(program);

materialShaderLoc = glGetSubroutineUniformLocation(program, GL_VERTEX_SHADER, "materialShader");

if(materialShaderLoc < 0){
	// error: mat shader is not an active subroutine uniform in the shader
}

ambientIndex = glGetSubroutineIndex(program, GL_VERTEX_SHADER, "ambient");
diffuseIndex = glGetSubroutineIndex(program, GL_VERTEX_SHADER, "diffuse");

if(ambientIndex == GL_INVALID_INDEX || diffuseIndex == GL_INVALID_INDEX){
	//error
} else {
	GLsizei n;
	glGetIntegerv(GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS, &n);
	
	GLuint *indices = new GLuint[n];
	indices[materialShaderLoc] = ambientIndex;
	
	glUniformSubroutinesuiv(GL_VERTEX_SHADER, n, indices);
	
	delete[] indices;
}

