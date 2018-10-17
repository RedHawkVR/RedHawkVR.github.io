// example setup for instanced vertex attributes

int position_loc = glGetAttribLocation(prog, "position");
int normal_loc = glGetAttribLocation(prog, "normal");
int color_loc = glGetAttribLocation(prog, "color");
int matrix_loc = glGetAttribLocation(prog, "model_matrix");

glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
glVertexAttribPointer(position_loc, 4, GL_FLOAT, GL_FALSE, 0, NULL);
glEnableVertexAttribArray(position_loc);
glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, 0, NULL);
glVertexAttribArray(normal_loc);

glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
glVertexAttribPointer(color_loc, 4, GL_FLOAT, GL_FALSE, 0, NULL);
glEnableVertexAttribArray(color_loc);

glVertexAttribDivisor(color_loc, 1);

glBindBuffer(GL_ARRAY_BUFFER, model_matrix_buffer);

for(int i = 0; i < 4; i++){
	glVertexAttribPointer(matrix_loc + i, 4, GL_FLOAT, GL_FALSE, 
						sizeof(mat4), (void *)(sizeof(vec4)*i));
	glEnableVertexAttribArray(matrix_loc + i);
	glVertexAttribDivisor(matrix_loc + i, 1);
}

/* -------------------------------------------------------------- */
// instanced attributes example vertex shader

uniform mat4 view_matrix;
uniform mat4 projection_matrix;

uniform samplerBuffer color_tbo;
uniform samplerBuffer model_matrix_tbo;

out VERTEX {
	vec3 normal;
	vec4 color;
} vertex;

void main(void){
	vec4 color = texelFetch(color_tbo, gl_InstanceID);
	
	vec4 col1 = texelFetch(model_matrix_tbo, gl_InstanceID * 4);
	vec4 col2 = texelFetch(model_matrix_tbo, gl_InstanceID * 4 + 1);
	vec4 col3 = texelFetch(model_matrix_tbo, gl_InstanceID * 4 + 2);
	vec4 col4 = texelFetch(model_matrix_tbo, gl_InstanceID * 4 + 3);
	
	mat4 model_matrix = mat4(col1, col2, col3, col4);
	
	mat4 model_view_matrix = view_matrix * model_matrix;
	
	gl_Position = projection_matrix * (model_view_matrix * position);
	
	vertex.normal = mat3(model_view_matrix) * normal;
	
	vertex.color = color;
}

/* -------------------------------------------------------------- */
// instancing example drawing code

mat4 * matrices = (mat4 *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

for(int n = 0; n < INSTANCE_COUNT; n++){
	float a = 50.0f * float(n) / 4.0f;
	float b = 50.0f * float(n) / 5.0f;
	float c = 50.0f * float(n) / 6.0f;
	
	matrices[n] = rotation(a + t * 360.0f, 1.0f, 0.0f, 0.0f) * 
				rotation(b + t * 360.0f, 0.0f, 1.0f, 0.0f) * 
				rotation(c + t * 360.0f, 0.0f, 0.0f, 1.0f) * 
				translation(10.0f + a, 40.0f + b, 50.0f + c);
}

glUnmapBuffer(GL_ARRAY_BUFFER);
glUseProgram(render_prog);
mat4 view_matrix(translation(0.0f, 0.0f, -1500.0f) *
				rotation(t * 360.0f * 2.0f, 0.0f, 1.0f, 0.0f));
mat4 projection_matrix(frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 5000.0f));
glUniformMatrix4fv(view_matrix_loc, 1, GL_FALSE, view_matrix);
glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, projection_matrix);

glDrawArraysInstanced(GL_TRIANGLES, 0, object_size, INSTANCE_COUNT);


