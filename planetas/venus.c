#include "venus.h"

GLUquadricObj *obj_venus = NULL;
GLuint idTexturaVenus;

const float venus_tam = 0.5;
const float venus_raio = 3;
const float venus_veloc = 300;//0 a 1000

float venus_ang = 0.0;
float venus_x = 0.0;
float venus_y = 0.0;

void iniciarVenus(GLuint textura) {
    obj_venus = gluNewQuadric();
    gluQuadricDrawStyle(obj_venus, GLU_FILL);
    gluQuadricTexture(obj_venus, GL_TRUE);
    gluQuadricNormals(obj_venus, GLU_SMOOTH);
    idTexturaVenus = textura;
}

void desenharVenus(int qualidade) {
	glPushMatrix();
		glTranslatef(venus_x, 0, venus_y);
		glRotatef(-90,1, 0, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idTexturaVenus);
		gluSphere(obj_venus, venus_tam, qualidade, qualidade);
	glPopMatrix();
}

void movimentaVenus() {
	venus_ang -= venus_veloc/10000;
	if(venus_ang < -360) {
		venus_ang = 0;
	}
	venus_x = venus_raio * cos(venus_ang);
	venus_y = venus_raio * sin(venus_ang);
}