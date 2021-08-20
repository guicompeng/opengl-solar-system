#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int fullscreen = 0;
int mouseDown = 0;

float xrot = 100.0f;
float yrot = -100.0f;

float xdiff = 100.0f;
float ydiff = 100.0f;

float tra_x = 0.0f;
float tra_y = 0.0f;
float tra_z = 0.0f;

float posTerra = 0.0f;

float grow_shrink = 70.0f;
float resize_f = 1.0f;


GLUquadricObj *sphere = NULL;
GLUquadricObj *terra = NULL;

GLuint idTexturaSol;
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

void drawSphere(double r, int lats, int longs) {

	glPushMatrix();
		glTranslated(0, 0, 4-posTerra);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idTexturaSol);
		gluSphere(sphere, 1.0, 10, 10);
	glPopMatrix();
}

void desenharTerra(double r, int lats, int longs) {
   glColor3f(0.0f, 0.0f, 1.0f);
	glPushMatrix();
		glTranslated(0, 0, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idTexturaTerra);
		gluSphere(sphere, 1.0, 100, 100);
	glPopMatrix();


}

void drawBox()
{
	
	glTranslatef(tra_x, tra_y, tra_z);

	//esfera
	glColor3f(1.0f, 1.0f, 1.0f);
	drawSphere(1, 10, 10);
	desenharTerra(1, 10, 10);

	//lado aleatorio
	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-4.0f, -4.0f, 4.0f);
		glVertex3f( 4.0f, -4.0f, 4.0f);
		glVertex3f( 4.0f, 4.0f, 4.0f);
		glVertex3f(-4.0f, 4.0f, 4.0f);
	glEnd();

	glBegin(GL_QUADS);
	
		glColor3f(1.0f, 0.0f, 0.0f);

		// FRONT
		glVertex3f(0.5f, 0.5f, -5.0f+posTerra);
		glVertex3f( 1.5f, 0.5f, -5.0f+posTerra);
		glVertex3f( 1.5f, 1.5f, -5.0f+posTerra);
		glVertex3f(0.5f, 1.5f, -5.0f+posTerra);
		
		// BACK
		glVertex3f(0.5f, 0.5f, -6.0f+posTerra);
		glVertex3f(0.5f, 1.5f, -6.0f+posTerra);
		glVertex3f( 1.5f, 1.5f,-6.0f+posTerra);
		glVertex3f( 1.5f, 0.5f,-6.0f+posTerra);

		// LEFT
		glVertex3f(0.5f, 0.5f, -5.0f+posTerra);
		glVertex3f(0.5f, 1.5f, -5.0f+posTerra);
		glVertex3f(0.5f, 1.5f, -6.0f+posTerra);
		glVertex3f(0.5f, 0.5f, -6.0f+posTerra);
		
		// RIGHT
		glVertex3f( 1.5f, 0.5f, -6.0f+posTerra);
		glVertex3f( 1.5f, 1.5f, -6.0f+posTerra);
		glVertex3f( 1.5f, 1.5f, -5.0f+posTerra);
		glVertex3f( 1.5f, 0.5f, -5.0f+posTerra);


		
		// TOP
		glVertex3f(0.5f, 1.5f, -5.0f+posTerra);
		glVertex3f( 1.5f, 1.5f, -5.0f+posTerra);
		glVertex3f( 1.5f, 1.5f, -6.0f+posTerra);
		glVertex3f(0.5f, 1.5f, -6.0f+posTerra);
		

		// BOTTOM
		glVertex3f(0.5f, 0.5f, -5.0f+posTerra);
		glVertex3f(0.5f, 0.5f, -6.0f+posTerra);
		glVertex3f( 1.5f, 0.5f, -6.0f+posTerra);
		glVertex3f( 1.5f, 0.5f, -5.0f+posTerra);
	glEnd();
}

int init(void)
{
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);

	return 1;
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

	drawBox();

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
void movimentaTerra() {
	posTerra += 0.1;
}

void movimentaItems() {
	movimentaTerra();
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


	terra = gluNewQuadric();
	sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);

	idTexturaSol = carregaTextura("img/sol.png");
	idTexturaTerra = carregaTextura("img/terra.png");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutReshapeFunc(resize);
	// glutIdleFunc(idle);

	glutTimerFunc(33, movimentaItems, 1); // 1000/33 = 30 frames por segundo

	if (!init())
		return 1;

 	
	glutMainLoop();

	return 0;
}