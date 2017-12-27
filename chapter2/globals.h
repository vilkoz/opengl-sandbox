#ifndef GLOBALS_H
# define GLOBALS_H

# include "gl-sandbox.h"

t_window		win = {W, H, 0, WINDOW_TITLE, 0};

t_ids			ids;

const GLchar			* const vertex_shader = 
{
	"#version400\n"\
	"\n"\
	"layout(location=0) in vec4	in_Position;\n"\
	"layout(location=1) in vec4	in_Color;\n"\
	"out vec4					ex_Color:\n"\
	"\n"\
	"void		main(void)\n"\
	"{\n"\
		"gl_Position = in_Position;\n"\
		"ex_Color = in_Color;\n"\
	"}\n"
};

const GLchar			* const fragment_shader = 
{
	"#version400\n"\
	"\n"\
	"in vec4		ex_Color;\n"\
	"out vec4	out_Color;\n"\
	"\n"\
	"void		main(void)\n"\
	"{\n"\
		"out_Color = ex_Color;\n"\
	"}\n"
};

#endif
