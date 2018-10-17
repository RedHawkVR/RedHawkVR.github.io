typedef struct DrawArraysIndirectCommand_t {
	GLuint count, primCount, first, baseInstance;
} DrawArraysIndirectCommand;

/* ------------ */

typedef struct DrawElementsIndirectCommand_t {
	GLuint count, primCount, firstIndex, baseVertex, baseInstance;
} DrawElementsIndirectCommand;

/* ------------ */

// 4 vertices
static const GLfloat vertex_positions[] {
	-1.0f, -1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, 0.0f, 1.0f, 
	1.0f, 0.0f, 1.0f, 1.0f, 
	0.0f, 1.0f, 1.0f, 1.0f
};

// colors for each vertex
static const GLfloat vertex_colors[] = {
	1.0f, 1.0f, 1.0f, 1.0f, 
	1.0f, 1.0f, 0.0f, 1.0f, 
	1.0f, 0.0f, 1.0f, 1.0f, 
	0.0f, 1.0f, 1.0f, 1.0f
};

// 3 indices to draw 1 triangle at a time
static const GLushort vertex_indices[] = { 0,1,2 };

// setup up element array buffer
glGenBuffers(1, ebo);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				sizeof(vertex_positions) + sizeof(vertex_colors),
				NULL, GL_STATIC_DRAW);
glBufferSubData(GL_ARRAY_BUFFER, 0,
				sizeof(vertex_positions), vertex_positions);
glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_positions),
				sizeof(vertex_colors), vertex_colors);

/* ------------ */

// draw arrays
model_matrix = vmath::translation(-3.0f, 0.0f, -5.0f);
glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, model_matrix);
glDrawArrays(GL_TRIANGLES, 0, 3);

// draw elements
model_matrix = vmath::translation();
glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, model_matrix);
glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);

// draw elements base vertex
model_matrix = vmath::translation();
glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, model_matrix);
glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL, 1);

// draw arrays instanced
model_matrix = vmath::translation();
glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, model_matrix);
glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);

/* ------------ */

// Initialising data for a cube made of 2 triangle strips

// 8 corners of a cube, side length 2, centered on the origin
static const GLfloat cube_positions[] = {
	-1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f
};

// color for each vertex
static const GLfloat cube_colors[] = {
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f
};

// indices for the triangle strips
static const GLushort cube_indices[] = {
	0,1,2,3,6,7,4,5,	// first strip
	0xFFFF,				// restart index
	2,6,0,4,1,5,3,7	// second strip
};

// set up element array buffer
glGenBuffers(1, ebo);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), 
				cube_indices, GL_STATIC_DRAW);

// set up vertex atrributes
glGenVertexArrays(1, vao);
glBindVertexArray(vao[0]);

glGenBuffers(1, vbo);
glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
glBufferData(GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(cube_colors),
				NULL, GL_STATIC_DRAW);
glBufferSubData(GL_ARRAY_BUFFER, 0,
					sizeof(cube_positions), cube_positions);
glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions),
					sizeof(cube_colors), cube_colors);

glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(cube_positions));

glEnableVertexAttribArray(0);
glEnableVertexAttribArray(1);
