#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "planetas/sol.h"
#include "planetas/mercurio.h"
#include "planetas/venus.h"
#include "planetas/terra.h"

const int qualidade = 30;

int pause = 0;

int fullscreen = 0;
int mouseDown = 0;

float xrot = 0.0f;
float yrot = -0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;

float tra_x = 0.0f;
float tra_y = 0.0f;
float tra_z = 0.0f;

float grow_shrink = 70.0f;
float resize_f = 1.0f;

GLuint idTexturaSol;
GLuint idTexturaMercurio;
GLuint idTexturaVenus;
GLuint idTexturaTerra;

GLuint carregaTextura(const char* arquivo) {
    GLuint idTextura = SOIL_load_OGL_texture(
                           arquivo,
                           SOIL_LOAD_AUTO,
                           SOIL_CREATE_NEW_ID,
                           SOIL_FLAG_INVERT_Y
                       );

    if (idTextura == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

    return idTextura;
}

void desenhaPlanetas() {
	
	glTranslatef(tra_x, tra_y, tra_z);
	glColor3f(1.0f, 1.0f, 1.0f);

	desenharSol(qualidade);
	desenharMercurio(qualidade);
	desenharVenus(qualidade);
	desenharTerra(qualidade);
}

int init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(
	0.0f, 0.0f, 10.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f);

	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);

	desenhaPlanetas();

	glutSwapBuffers();
}

void resize(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective(grow_shrink, resize_f * w / h, resize_f, 100 * resize_f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle(void)
{
	if (!mouseDown)
	{
		xrot += 0.3f;
		yrot += 0.4f;
	}

	glutPostRedisplay();
}


void mySpecialFunction(int key, int x, int y)
{
    //if (key == GLUT_KEY_F1)
    //{
        printf("U -----------> rotate clockwise\n");
        printf("Y -----------> rotate counter clockwise\n");
        printf("W or w ------> Up\n");
        printf("S or s -----> Down\n");
        printf("D or d ------> Right\n");
        printf("A or a ------> Left\n");
        printf("Z or z ------> Shrink\n");
        printf("X or x ------> Grow\n");
        printf("Escape Key ---> exit the program\n\n");
    //}
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27 : 
			exit(1); 
			break;
		case 'p':
			pause = !pause;
			break;
		case 'w':
		case 'W':
			tra_x += 0.1f;
			break;
		case 's':
		case 'S':
			tra_x -= 0.1f;
			break;
		case 'a':
		case 'A':
			tra_z -= 0.1f;
			break;
		case 'd':
		case 'D':
			tra_z += 0.1f;
			break;
		case 'u':
		case 'U':
			xrot += 1.0f;
			yrot += 1.0f;
			xdiff += 1.0f;
			ydiff += 1.0f;
			break;

		case 'y':
		case 'Y':
			xrot -= 1.0f;
			yrot -= 1.0f;
			xdiff += 1.0f;
			ydiff += 1.0f;
			break;

		case 'h':
		case 'H':
			mySpecialFunction(key, x, y);
			break;
		case 'Z':
		case 'z':
			grow_shrink--;
			resize(500, 500);
			
			break;
		case 'X':
		case 'x':
			grow_shrink++;
			resize(500, 500);
			
			break;

	}

	
	glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_F1)
	{
		fullscreen = !fullscreen;

		if (fullscreen)
			glutFullScreen();
		else
		{
			glutReshapeWindow(500, 500);
			glutPositionWindow(50, 50);
		}
	}
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseDown = 1;

		xdiff = x - yrot;
		ydiff = -y + xrot;
	}
	else
		mouseDown = 0;
}

void mouseMotion(int x, int y)
{
	if (mouseDown)
	{
		yrot = x - xdiff;
		xrot = y + ydiff;

		glutPostRedisplay();
	}
}


void movimentaItems() {
	if(!pause) {
		movimentaSol();
		movimentaMercurio();
		movimentaVenus();
		movimentaTerra();
	}
	glutPostRedisplay();
	glutTimerFunc(33, movimentaItems, 1);
	
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutCreateWindow("Solar System");

	idTexturaSol = carregaTextura("img/sol.png");
	idTexturaMercurio = carregaTextura("img/mercurio.png");
	idTexturaVenus = carregaTextura("img/venus.png");
	idTexturaTerra = carregaTextura("img/terra.png");

	iniciarSol(idTexturaSol);
	iniciarMercurio(idTexturaMercurio);
	iniciarVenus(idTexturaVenus);
	iniciarTerra(idTexturaTerra);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutReshapeFunc(resize);

	glutTimerFunc(33, movimentaItems, 1); // 1000/33 = 30 frames por segundo

	init();

	glutMainLoop();

	return 0;
}