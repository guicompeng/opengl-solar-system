#include "marte.h"

GLUquadricObj *obj_marte = NULL;
GLuint idTexturaMarte;

const float marte_tam = 0.3;
const float marte_raio = 7;
const float marte_veloc = 100;//0 a 1000

float marte_ang = 0.0;
float marte_x = 0.0;
float marte_y = 0.0;

void iniciarMarte(GLuint textura) {
    obj_marte = gluNewQuadric();
    gluQuadricDrawStyle(obj_marte, GLU_FILL);
    gluQuadricTexture(obj_marte, GL_TRUE);
    gluQuadricNormals(obj_marte, GLU_SMOOTH);
    idTexturaMarte = textura;
}

void desenharMarte(int qualidade) {
	glPushMatrix();
		glTranslatef(marte_x, 0, marte_y);
		glRotatef(-90,1, 0, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idTexturaMarte);
		gluSphere(obj_marte, marte_tam, qualidade, qualidade);
	glPopMatrix();
}

void movimentaMarte() {
	marte_ang -= marte_veloc/10000;
	if(marte_ang < -360) {
		marte_ang = 0;
	}
	marte_x = marte_raio * cos(marte_ang);
	marte_y = marte_raio * sin(marte_ang);
}