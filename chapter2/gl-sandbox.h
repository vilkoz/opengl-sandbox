#ifndef GL_SANDBOX_H
# define GL_SANDBOX_H

# include <GL/glew.h>
# include <GL/freeglut.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define W 800
# define H 600
# define WINDOW_TITLE "JUST FOR FUN WITH GLSL"

typedef struct	s_window
{
	int			w;
	int			h;
	int			handle;
	char		*title;
	unsigned	frames;
}				t_window;


typedef struct	s_ids
{
	GLuint		vertex_shader;
	GLuint		fragment_shader;
	GLuint		program;
	GLuint		vao;
	GLuint		vbo;
	GLuint		color_buffer;
}				t_ids;

void			cleanup(void);
void			create_vbo(void);
void			destroy_vbo(void);
void			create_shaders(void);
void			destroy_shaders(void);

#endif
