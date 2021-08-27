#include "terra.h"

GLUquadricObj *obj_terra = NULL;
GLuint idTexturaTerra;

const float terra_tam = 0.5;
const float terra_raio = 5;
const float terra_veloc = 200;//0 a 1000

float terra_ang = 0.0;
float terra_rotate = 0.0;
float terra_x = 0.0;
float terra_y = 0.0;

void iniciarTerra(GLuint textura) {
    obj_terra = gluNewQuadric();
    gluQuadricDrawStyle(obj_terra, GLU_FILL);
    gluQuadricTexture(obj_terra, GL_TRUE);
    gluQuadricNormals(obj_terra, GLU_SMOOTH);
    idTexturaTerra = textura;
}

void desenharTerra(int qualidade) {
	glPushMatrix();
		glTranslatef(terra_x, 0, terra_y);
		glRotatef(terra_rotate,0, 1, 0); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idTexturaTerra);
		gluSphere(obj_terra, terra_tam, qualidade, qualidade);
	glPopMatrix();
}

void movimentaTerra() {
	terra_ang -= terra_veloc/10000;
	if(terra_ang < -360) {
		terra_ang = 0;
	}
	terra_x = terra_raio * cos(terra_ang);
	terra_y = terra_raio * sin(terra_ang);

	//rotation
	terra_rotate += 20.0f; 
	if(terra_rotate > 360.0f) { 
		terra_rotate = 0.0f; 
	} 
}