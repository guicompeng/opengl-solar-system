#include "netuno.h"

GLUquadricObj *obj_netuno = NULL;
GLuint idTexturaNetuno;

const float netuno_tam = 0.2;
const float netuno_raio = 15;
const float netuno_veloc = 200;//0 a 1000

float netuno_ang = 0.0;
float netuno_x = 0.0;
float netuno_y = 0.0;

void iniciarNetuno(GLuint textura) {
    obj_netuno = gluNewQuadric();
    gluQuadricDrawStyle(obj_netuno, GLU_FILL);
    gluQuadricTexture(obj_netuno, GL_TRUE);
    gluQuadricNormals(obj_netuno, GLU_SMOOTH);
    idTexturaNetuno = textura;
}

void desenharNetuno(int qualidade) {
	glPushMatrix();
		glTranslatef(netuno_x, 0, netuno_y);
		glRotatef(-90,1, 0, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idTexturaNetuno);
		gluSphere(obj_netuno, netuno_tam, qualidade, qualidade);
	glPopMatrix();
}

void movimentaNetuno() {
	netuno_ang -= netuno_veloc/10000;
	if(netuno_ang < -360) {
		netuno_ang = 0;
	}
	netuno_x = netuno_raio * cos(netuno_ang);
	netuno_y = netuno_raio * sin(netuno_ang);
}