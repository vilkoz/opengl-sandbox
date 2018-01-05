#include "gl-sandbox.h"
#include "globals.h"

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
	title_string = (char*)malloc(sizeof(char) * (512 + strlen(win.title)));
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
	/* glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); */
	glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_BYTE, (GLvoid*)0);
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
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(1);
	}
	glutReshapeFunc(resize_function);
	glutDisplayFunc(render_function);
	glutTimerFunc(0, timer_function, 0);
	glutCloseFunc(cleanup);
	glutIdleFunc(idle_function);
}

void	init_glut(int argc, char **argv)
{
	init_window(argc, argv);
	printf("INFO: OpenGL version: %s\n", glGetString(GL_VERSION));
	create_shaders();
	create_vbo();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

int		main(int argc, char **argv)
{
	init_glut(argc, argv);
	glutMainLoop();
	return 0;
}
