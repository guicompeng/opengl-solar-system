#include "urano.h"

GLUquadricObj *obj_urano = NULL;
GLuint idTexturaUrano;

const float urano_tam = 0.5;
const float urano_raio = 13;
const float urano_veloc = 300;//0 a 1000

float urano_ang = 0.0;
float urano_x = 0.0;
float urano_y = 0.0;

void iniciarUrano(GLuint textura) {
    obj_urano = gluNewQuadric();
    gluQuadricDrawStyle(obj_urano, GLU_FILL);
    gluQuadricTexture(obj_urano, GL_TRUE);
    gluQuadricNormals(obj_urano, GLU_SMOOTH);
    idTexturaUrano = textura;
}

void desenharUrano(int qualidade) {
	glPushMatrix();
		glTranslatef(urano_x, 0, urano_y);
		glRotatef(-90,1, 0, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idTexturaUrano);
		gluSphere(obj_urano, urano_tam, qualidade, qualidade);
	glPopMatrix();
}

void movimentaUrano() {
	urano_ang -= urano_veloc/10000;
	if(urano_ang < -360) {
		urano_ang = 0;
	}
	urano_x = urano_raio * cos(urano_ang);
	urano_y = urano_raio * sin(urano_ang);
}