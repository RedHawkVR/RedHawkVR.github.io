/////////////////////////////////////////////////////////
/* Initialising a Buffer Object with glNamedBufferStorage() */
/////////////////////////////////////////////////////////

// Vertex positions
static const GLfloat positions[] = {
	-1.0f, -1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, 0.0f, 1.0f
	1.0f, 1.0f, 0.0f, 1.0f
	-1.0f, 1.0f, 0.0f, 1.0f
};

// Vertex colors
static const GLfloat colors[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f
};

// The buffer object
GLuint buffer;

// Create a new buffer object
glCreateBuffers(1, &buffer);
// Allocate space for it
glNamedBufferStorage(buffer, sizeof(positions), nullptr, GL_DYNAMIC_STORAGE_BIT); //(target, total size, no data, flags)
// Put positions at offset zero in the buffer
glNamedBufferSubData(buffer, 0, sizeof(positions), positions); //(target, offset, size, data)
// Put colors at an offset equal to the filled size of the buffer so far
glNamedBufferSubData(buffer, sizeof(positions), sizeof(colors), colors);
// Now positions is at an offset of 0 and colors is directly after it within the same buffer

/////////////////////////////////////////////////////////
/* Initialising a Buffer Object with glMapBuffer() */
/////////////////////////////////////////////////////////

GLuint buffer;
FILE *f;
size_t filesize;

// Open a file and find its size
f = fOpen("data.dat", "rb");
fseek(f, 0, SEEK_END);
filesize = ftell(f);
fseek(f, 0, SEEK_SET);

// Create a buffer by generating a name and binding it to a buffer binding point
glGenBuffers(1, &buffer);
glBindBuffer(GL_COPY_WRITE_BUFFER, buffer);

// Allocate the data store for the buffer
glBufferData(GL_COPY_WRITE_BUFFER, (GLsizei)filesize, NULL, GL_STATIC_DRAW);

// Map the buffer
void *data = glMapBuffer(GL_COPY_WRITE_BUFFER, GL_WRITE_ONLY);

// Read the file into the buffer
fread(data, 1, filesize, f);

// Done, now unmap the buffer and close the file
glUnmapBuffer(GL_COPY_WRITE_BUFFER);
fclose(f);


