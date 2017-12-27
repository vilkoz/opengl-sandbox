#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define W 800
#define H 600
#define WINDOW_TITLE "JUST FOR FUN WITH GLSL"

typedef struct	s_window
{
	int			w;
	int			h;
	int			handle;
	char		*title;
	unsigned	frames;
}				t_window;

t_window	win = {W, H, 0, WINDOW_TITLE, 0};

void	idle_function(void)
{
	glutPostRedisplay();
}

void	timer_function(int count)
{
	char	*title_string;

	if (count == 0)
	{
		win.frames = 0;
		return ;
	}
	title_string = (char*)malloc(sizeof(char) * (32 + strlen(win.title)));
	sprintf(title_string, "%s: %d fps @ %d x %d", win.title, win.frames * 4, win.w, win.h);
	glutSetWindowTitle(title_string);
	free(title_string);
	win.frames = 0;
	glutTimerFunc(250, timer_function, 1);
}

void	resize_function(int w, int h)
{
	win.w = w;
	win.h = h;
	glViewport(0, 0, win.w, win.h);
}

void	render_function(void)
{
	win.frames += 1;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
	glutPostRedisplay();
}

void	init_window(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(W, H);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	if ((win.handle = glutCreateWindow(WINDOW_TITLE)) < 1)
	{
		fprintf(stderr, "ERROR! Could not create window!");
		exit(1);
	}
	glutReshapeFunc(resize_function);
	glutDisplayFunc(render_function);
	glutTimerFunc(0, timer_function, 0);
	glutIdleFunc(idle_function);
}

void	init_glut(int argc, char **argv)
{
	init_window(argc, argv);
	printf("INFO: OpenGL version: %s\n", glGetString(GL_VERSION));
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

int		main(int argc, char **argv)
{
	init_glut(argc, argv);
	glutMainLoop();
	return 0;
}
