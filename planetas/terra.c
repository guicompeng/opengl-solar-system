#include "terra.h"

GLUquadricObj *obj_terra = NULL;
GLuint idTexturaTerra;

const float terra_tam = 0.5;
const float terra_raio = 3.0;

float terra_ang = 0.0;
float terra_x = 0.0;
float terra_y = 0.0;

void iniciarTerra(GLuint textura) {
    obj_terra = gluNewQuadric();
    gluQuadricDrawStyle(obj_terra, GLU_FILL);
    gluQuadricTexture(obj_terra, GL_TRUE);
    gluQuadricNormals(obj_terra, GLU_SMOOTH);
    idTexturaTerra = textura;
}

void desenharTerra() {
	glPushMatrix();
		glTranslatef(terra_x, 0, terra_y);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idTexturaTerra);
		gluSphere(obj_terra, terra_tam, 10, 10);
	glPopMatrix();
}

void movimentaTerra() {
	terra_ang += 0.05;
	if(terra_ang >= 360) {
		terra_ang = 0;
	}
	terra_x = terra_raio * cos(terra_ang);
	terra_y = terra_raio * sin(terra_ang);
}