#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#include "planetas/sol.h"
#include "planetas/mercurio.h"
#include "planetas/venus.h"
#include "planetas/terra.h"

const int qualidade = 30;

int pause = 0;

int mouseDown = 0;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;

float tra_x = 0.0f;
float tra_y = 0.0f;
float tra_z = -10.0f; //visao de longe

int modoLuz = 1;

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

	gluPerspective(70.0f, 1.0f * w / h, 1.0f, 100 * 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void configuraLuz(){
    if(modoLuz == 1){
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_shininess[] = { 10.0 };
        GLfloat light_position[] = { 0.1, 0.1, 0.1, 0 };
        glShadeModel (GL_SMOOTH);

        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_specular);

        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_DEPTH_TEST);
    }  else {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27 : //esc
			exit(1);
			break;
		case 'p':
			pause = !pause;
			break;
		case 'l':
		  modoLuz = !modoLuz;
		  break;
		case '1':
		  xrot = 90;
		  tra_z = 0;
		  break;
		case '2':
		  xrot = 0;
		  tra_z = -10;
		  break;
		case 'w':
			tra_z += 0.1f;
			break;
		case 's':
			tra_z -= 0.1f;
			break;
		case 'a':
			tra_x += 0.1f;
			break;
		case 'd':
		  tra_x -= 0.1f;
			break;
	}

	
	glutPostRedisplay();
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

void movimentaMouse(int x, int y)
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
	configuraLuz();
	glutPostRedisplay();
	glutTimerFunc(33, movimentaItems, 1);
	
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(1000, 600);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutCreateWindow("Sistema Solar");

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
	glutMouseFunc(mouse);
	glutMotionFunc(movimentaMouse);
	glutReshapeFunc(resize);
	
	glutTimerFunc(33, movimentaItems, 1); // 1000/33 = 30 frames por segundo

	glutMainLoop();

	return 0;
}