#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int xCursor, yCursor, zCursor;
int xMouse = 0, yMouse = 0; 
float phi = 90, teta = 0;
int modoLuz = 1;

GLUquadricObj *IDquadric;

struct {
  float x, y, z;
  float targetX, targetY, targetZ;
} camera;


void movimentaItems() {
  //chamar funcoes que se movem aqui


  glutPostRedisplay();
  glutTimerFunc(33, movimentaItems, 1);
}


void desenhaTorreObservacao(){
    glColor3f(1, 1, 1);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glPushMatrix();
        glTranslatef(35,0,0);
        
        //base giratória - sobe|desce
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glColor3f(1, 1, 1);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glPolygonMode(GL_FRONT, GL_FILL);
            gluQuadricTexture(IDquadric, GL_TRUE);
            
            glTranslatef(0,0.0,0);
            glRotatef(0,0.,1.,0.);
            glPushMatrix();
                glRotatef(90,1.,0.,0.);
                
                gluCylinder(IDquadric,10.0f,5.0f,5.0f,32,32);
            glPopMatrix();

        glPopMatrix();

        //eixo central (barra)
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glColor3f(1, 1, 1);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glPolygonMode(GL_FRONT, GL_FILL);
            glTranslatef(0,30,0);
            glRotatef(90,1.,0.,0.);
            gluQuadricTexture(IDquadric, GL_TRUE);
            gluCylinder(IDquadric,1.0f,1.0f,60.0f,32,32);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();        

    glPopMatrix();
}

void configuraLuz(){
    if(modoLuz == 1){
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_shininess[] = { 150.0 };
        GLfloat light_position[] = { -5, 10.0, 0, 0.50 };
        glShadeModel (GL_SMOOTH);

        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_specular);

        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_DEPTH_TEST);
    }  else {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }
}

void redimensiona(int w, int h){
    glEnable(GL_DEPTH_TEST);                // Ativa o Z buffer
    glViewport (0, 0, w, h);                //define a proporção da janela de visualização
    glMatrixMode (GL_PROJECTION);           //define o tipo de matriz de transformação que será utilizada
    glLoadIdentity();                       //carrega a matriz identidade do tipo GL_PROJECTION configurado anteriormente
    gluPerspective(60.0, (float)w/(float)h, 0.2, 400.0);    //funciona como se fosse o glOrtho, mas para o espaço 3D
    glMatrixMode(GL_MODELVIEW);                             //ativa o modo de matriz de visualização para utilizar o LookAt
}

// callback de desenho
void desenhaMinhaCena() {
    configuraLuz();
    //esfera de raio 100
    camera.x = 100 * sin(phi) * cos(teta);  //coordenada x denotada em coordenadas esféricas
    camera.z = 100 * sin(phi) * sin(teta); //coordenada z denotada em coordenadas esféricas
    camera.y = 100 * cos(phi);          //coordenada y denotada em coordenadas esféricas

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // carrega a matriz identidade do modelo de visualização,
    // sempre utilize antes de usar LookAt
    glLoadIdentity();


    gluLookAt( xCursor+0, 0, zCursor+0,                    //já aqui, a câmera está posicionada no centro da esfera
        xCursor+camera.x, camera.y, zCursor+camera.z,     //e a câmera estará olhando para a casca da esfera (primeira pessoa)
        0, 1, 0);                                        //vetor UP, apontando para o eixo Y (para cima)

    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                

    desenhaTorreObservacao();

    glutSwapBuffers();
}

void inicializa(){
    IDquadric=gluNewQuadric();      // Create A Pointer To The Quadric Object ( NEW )
    gluQuadricNormals(IDquadric, GLU_SMOOTH);  // Create Smooth Normals ( NEW )
    gluQuadricTexture(IDquadric, GL_TRUE);    // Create Texture Coords ( NEW )
 
    glClearColor(0, 0.5, 1, 1);                          //cor de fundo branca
    glEnable(GL_BLEND);                                //ativa a mesclagem de cores
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //ativando o blend, podemos criar objetos transparentes
    xCursor = 0;                                       //a câmera começa olhando para o ponto 0
    yCursor = 0;
    zCursor = 100;
    
}

//capturar posicionamento do mouse
void posicionaCamera(int x, int y){
    // variáveis que guardam o vetor 2D de movimento do mouse na tela
    // xMouse e yMouse são os valores de x e y no frame anterior
    float xChange = x - xMouse;
    float yChange = y - yMouse;

    // este exemplo usa coordenadas esféricas para controlar a câmera...
    // teta e phi guardam a conversão do vetor 2D para um espaço 3D
    // com coordenada esférica
    teta = (teta + xChange/150);
    phi = (phi - yChange/150);

    if(phi >= 180){
      //limite de 180 para o phi
      phi = 180;
    }

    // guarda o x e y do mouse para usar na comparação do próximo frame
    xMouse = x;
    yMouse = y;
}

void tecla(unsigned char key, int x, int y) {
    // verifica qual tecla foi pressionada
    switch(key) {
    case 27:      // "ESC"
        exit(0);  // encerra a aplicacao
        break;
        
    case 32:      // barra de espaco
        
        break;

    case 's':   //andar pelo plano X-Z utilizando W A S D
        zCursor++;
        break;
    case 'w':
        zCursor--;
        break;
    case 'a':
        xCursor--;
        break;
    case 'd':
        xCursor++;
        break;
    case 'l':
        modoLuz *= -1;
        break;
    default:
        break;
    }
}

void teclaEspecial(GLint key, int x, int y) {
    int i;
    // verifica qual tecla foi pressionada
    switch(key) {
      case GLUT_KEY_LEFT: //seta para esquerda
        
        break;
        
      case GLUT_KEY_RIGHT: //seta para direita

        break;
          
      default:
        break;
    }

    desenhaMinhaCena();
}

// função principal
int main(int argc, char** argv) {
   glutInit(&argc, argv);
   
   glutInitContextVersion(1, 1);
   glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(1280, 720);
    glutInitWindowPosition (0, 0);

   glutCreateWindow("Sistema Solar");
   
   // registra callbacks para alguns eventos
   glutDisplayFunc(desenhaMinhaCena);
   glutReshapeFunc(redimensiona);
   glutKeyboardFunc(tecla);
   glutSpecialFunc(teclaEspecial);

   // usada para capturar o posicionamento do mouse
   glutPassiveMotionFunc(posicionaCamera);

   glutTimerFunc(33, movimentaItems, 1); // 1000/33 = 30 frames por segundo

   inicializa();
   
   glutMainLoop();

   return 0;
}