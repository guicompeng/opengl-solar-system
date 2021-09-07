#include "saturno.h"

GLUquadricObj *obj_saturno = NULL;
GLuint idTexturaSaturno;

const float saturno_tam = 0.2;
const float saturno_raio = 11;
const float saturno_veloc = 100;//0 a 1000

float saturno_ang = 0.0;
float saturno_rotate = 0.0;
float saturno_x = 0.0;
float saturno_y = 0.0;

void iniciarSaturno(GLuint textura) {
    obj_saturno = gluNewQuadric();
    gluQuadricDrawStyle(obj_saturno, GLU_FILL);
    gluQuadricTexture(obj_saturno, GL_TRUE);
    gluQuadricNormals(obj_saturno, GLU_SMOOTH);
    idTexturaSaturno = textura;
}

void desenharSaturno(int qualidade) {
	glPushMatrix();
		glTranslatef(saturno_x, 0, saturno_y);
		glRotatef(saturno_rotate,0, 1, 0);
		glRotatef(-90,1, 0, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idTexturaSaturno);
		gluSphere(obj_saturno, saturno_tam, qualidade, qualidade);
	glPopMatrix();
}

void movimentaSaturno() {
	saturno_ang -= saturno_veloc/10000;
	if(saturno_ang < -360) {
		saturno_ang = 0;
	}
	saturno_x = saturno_raio * cos(saturno_ang);
	saturno_y = saturno_raio * sin(saturno_ang);
	
	//rotation
	saturno_rotate += 6.0f;
	if(saturno_rotate > 360.0f) {
		saturno_rotate = 0.0f;
	}
}