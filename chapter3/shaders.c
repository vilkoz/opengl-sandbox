#include "gl-sandbox.h"
#include "extern_globals.h"

void	cleanup(void)
{
	destroy_shaders();
	destroy_vbo();
}

void	create_vbo(void)
{
	GLfloat		Vertices[] = {
		 0.0f,  0.8f, 0.0f, 1.0f,
		-0.8f,  0.0f, 0.0f, 1.0f,
		 0.8f,  0.0f, 0.0f, 1.0f,
		 0.0f, -0.8f, 0.0f, 1.0f
	};
	GLfloat		Colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f
	};
	GLenum		ErrorCheckValue = glGetError();

	glGenVertexArrays(1, &ids.vao);
	glBindVertexArray(ids.vao);

	glGenBuffers(1, &ids.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ids.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &ids.color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, ids.color_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(stderr,"ERROR: Could not create a VBO: %s \n",
				gluErrorString(ErrorCheckValue));
		exit(-1);
	}
}

void		destroy_vbo(void)
{
	GLenum ErrorCheckValue = glGetError();

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ids.color_buffer);
	glDeleteBuffers(1, &ids.vbo);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &ids.vao);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(stderr,"ERROR: Could not destroy the VBO: %s \n",
				gluErrorString(ErrorCheckValue));
		exit(-1);
	}
}

typedef enum	e_shader_compile_error
{
	SHADER_COMPILE_ERROR,
	PROGRAM_COMPILE_ERROR
}				e_shader_error;

void	check_error(GLuint shaderId, unsigned LINE, e_shader_error type)
{
	GLint bCompiled;

	if (type == SHADER_COMPILE_ERROR)
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &bCompiled);
	else if (type == PROGRAM_COMPILE_ERROR)
		glGetProgramiv(shaderId, GL_LINK_STATUS, &bCompiled);
	if(bCompiled == 0)
	{
		GLint length;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		GLchar *pInfo = (GLchar*)malloc(sizeof(GLchar) * (length + 1));
		if (type == SHADER_COMPILE_ERROR)
			glGetShaderInfoLog(shaderId, length, &length, pInfo);
		else if (type == PROGRAM_COMPILE_ERROR)
			glGetProgramInfoLog(shaderId, length, &length, pInfo);
		fprintf(stderr, "called at line-%u: Compiler/Linker error: %s", LINE, pInfo);
		free(pInfo);
	}
}

void		create_shaders(void)
{
	GLenum ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(stderr, "ERROR: Could not create the shaders: %s \n",
				gluErrorString(ErrorCheckValue));
		exit(-1);
	}

	ids.vertex_shader = 1;
	ids.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(ids.vertex_shader, 1, &vertex_shader, NULL);
	glCompileShader(ids.vertex_shader);
	check_error(ids.vertex_shader, __LINE__, SHADER_COMPILE_ERROR);

	ids.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(ids.fragment_shader, 1, &fragment_shader, NULL);
	glCompileShader(ids.fragment_shader);
	check_error(ids.fragment_shader, __LINE__, SHADER_COMPILE_ERROR);

	ids.program = glCreateProgram();
	glAttachShader(ids.program, ids.vertex_shader);
	glAttachShader(ids.program, ids.fragment_shader);
	glLinkProgram(ids.program);
	check_error(ids.program, __LINE__, PROGRAM_COMPILE_ERROR);
	glUseProgram(ids.program);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(stderr, "ERROR: Could not create the shaders: %s \n",
				gluErrorString(ErrorCheckValue));
		exit(-1);
	}
}

void		destroy_shaders(void)
{
	GLenum ErrorCheckValue = glGetError();

	glUseProgram(0);

	glDetachShader(ids.program, ids.vertex_shader);
	glDetachShader(ids.program, ids.fragment_shader);

	glDeleteShader(ids.fragment_shader);
	glDeleteShader(ids.vertex_shader);

	glDeleteProgram(ids.program);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
				stderr,
				"ERROR: Could not destroy the shaders: %s \n",
				gluErrorString(ErrorCheckValue)
			   );

		exit(-1);
	}
}
