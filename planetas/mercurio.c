#include "mercurio.h"

GLUquadricObj *obj_mercurio = NULL;
GLuint idTexturaMercurio;

const float mercurio_tam = 0.3;
const float mercurio_raio = 2;
const float mercurio_veloc = 1000;//0 a 1000

float mercurio_ang = 0.0;
float mercurio_x = 0.0;
float mercurio_y = 0.0;

void iniciarMercurio(GLuint textura) {
    obj_mercurio = gluNewQuadric();
    gluQuadricDrawStyle(obj_mercurio, GLU_FILL);
    gluQuadricTexture(obj_mercurio, GL_TRUE);
    gluQuadricNormals(obj_mercurio, GLU_SMOOTH);
    idTexturaMercurio = textura;
}

void desenharMercurio() {
	glPushMatrix();
		glTranslatef(mercurio_x, 0, mercurio_y);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idTexturaMercurio);
		gluSphere(obj_mercurio, mercurio_tam, 10, 10);
	glPopMatrix();
}

void movimentaMercurio() {
	mercurio_ang += mercurio_veloc/10000;
	if(mercurio_ang >= 360) {
		mercurio_ang = 0;
	}
	mercurio_x = mercurio_raio * cos(mercurio_ang);
	mercurio_y = mercurio_raio * sin(mercurio_ang);
}