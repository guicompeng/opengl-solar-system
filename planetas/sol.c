#include "sol.h"

GLUquadricObj *obj_sol = NULL;
GLuint idTexturaSol;

const float sol_tam = 1;
const float sol_raio = 0;

float sol_ang = 0.0f;
float sol_x = 0.0;
float sol_y = 0.0;

void iniciarSol(GLuint textura) {
    obj_sol = gluNewQuadric();
    gluQuadricDrawStyle(obj_sol, GLU_FILL);
    gluQuadricTexture(obj_sol, GL_TRUE);
    gluQuadricNormals(obj_sol, GLU_SMOOTH);
    idTexturaSol = textura;
}

void desenharSol() {
	glPushMatrix();
		glTranslatef(sol_x, 0, sol_y);
		glRotatef(sol_ang,0, 1, 0); 
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idTexturaSol);
		gluSphere(obj_sol, sol_tam, 10, 10);
	glPopMatrix();
}

void movimentaSol() {
	sol_ang -= 1.3f; 
	if(sol_ang < -360.0f) { 
		sol_ang = 0.0f; 
	} 
}