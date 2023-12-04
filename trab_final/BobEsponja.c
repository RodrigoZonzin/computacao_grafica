#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int win_id;

#define PI M_PI

void desenhaQuadrado();

void draw_cylinder(GLfloat radius, GLfloat height, GLubyte R, GLubyte G, GLubyte B){
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */
    glColor3ub(R-40, G-40, B-40);
    glBegin(GL_TRIANGLE_FAN);
    angle = 0.0;
    while (angle < 2 * M_PI) { // Use M_PI for π
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        glVertex3f(x, y, 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of the cylinder */
    glColor3ub(R, G, B);
    glBegin(GL_TRIANGLE_FAN);
    angle = 0.0;
    while (angle < 2 * M_PI) { // Use M_PI for π
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();
}

void desenhaCirculo() {
    glBegin(GL_POLYGON);
        for (int i = 0; i < 30; i++) {
            glVertex2f(cos(i), sin(i));
        }
    glEnd();
}

void desenhaQuadrado() {
    glBegin(GL_QUADS);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(-0.5, 0.5);
    glEnd();
}

void init(void){
  // Define a cor de fundo da janela de visualização como preto
  //glClearColor (1.0, 1.0, 1.0, 0.5);
  glClearColor(0.53, 0.81, 0.92, 0.0);
  // Define o modo de rastreio de cor utilizado para misturar a cor do material nos pontos da face (smoothing)
  glShadeModel (GL_SMOOTH);
  // Habilita a definição da cor do material a partir da cor corrente
  glEnable(GL_COLOR_MATERIAL);

  //Parâmetros para a luz ambiente, difusa e especular, definindo também a posição da luz
  GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_position[] = { 400.0, 400.0, 400.0, 0.0 };

  // Passa os parâmetros definidos acima para a OpenGL
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  // Habilita a luz ambiente, a luz zero e o depth buffer
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  //Primeira cor, para depois mudarmos com os eventos
  //glColor3f(0.5, 1.0, 0.5);
}

void DrawEllipsoid(unsigned int uiStacks, unsigned int uiSlices, float fA, float fB, float fC){
	float tStep = (PI) / (float)uiSlices;
	float sStep = (PI) / (float)uiStacks;
	
	//Essa linha desenha em modo wireframe, caso queiram ver os polígonos criados pela função
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	for(float t = -PI/2; t <= (PI/2)+.0001; t += tStep){
		glBegin(GL_TRIANGLE_STRIP);
		for(float s = -PI; s <= PI+.0001; s += sStep){
			glVertex3f(fA * cos(t) * cos(s), fB * cos(t) * sin(s), fC * sin(t));
			glVertex3f(fA * cos(t+tStep) * cos(s), fB * cos(t+tStep) * sin(s), fC * sin(t+tStep));
		}
		glEnd();
	}
} 

void display(void){
    // Limpa a janela de visualização com a cor de fundo especificada, e limpa também o depth buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Entra no modo de definição de matriz de visualização
    glMatrixMode(GL_MODELVIEW);
    // Carrega a matriz identidade
    glLoadIdentity();
    // Define a posição da câmera, para onde ela aponta e qual o vetor UP
    gluLookAt(0.0f, 30.0f, 50.0f, 0.0f, 20.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    
    glRotatef(30, 0, 1, 0);
    glPushMatrix();
        glRotatef(-90, 1, 0, 0);
        glTranslatef(0, -400, 0);
        glScalef(2000,2000,200);
        glColor3ub(233, 227, 206); 
           
        desenhaQuadrado(); 
    glPopMatrix();
    //glTranslatef(0.0, 0.0,  0.0);

    

    /*BOB ESPONJA */
    //Corpo
    glTranslatef(0, 25, 0);

    glPushMatrix(); 
        glColor3f(1.0, 1.0, 0.0);
        glScalef(1.0, 1.3, 0.5);
        glutSolidCube(20);
    glPopMatrix();
    //Calca
    glPushMatrix();
        glColor3f(0.36, 0.25, 0.20);
        glTranslatef(0, -15, 0); 
        glScalef(1.0, 0.25, 0.5);
        glutSolidCube(20);
    glPopMatrix();

    //Olho
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(-5, 8.0, 8.0); 
        glScalef(1.5, 1.5, 1.5);
        desenhaCirculo();   
    glPopMatrix();
    
    //Olho 1
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(5, 8.0, 8.0); 
        glScalef(1.5, 1.5, 1.5);
        desenhaCirculo();   
    glPopMatrix();


    //Perna
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslatef(-5, -25.0, 0.0); 
        glRotatef(-90, 1, 0, 0);
        //glScalef(2, 2, 2);
        draw_cylinder(2, 10, 1.0, 1.0, 1.0);
    glPopMatrix(); 

    //Perna
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslatef(+5, -25.0, 0.0); 
        glRotatef(-90, 1, 0, 0);
        //glScalef(1.5, 1.5, 1.5);
        draw_cylinder(2, 10, 1.0, 1.0, 1.0);
    glPopMatrix(); 

    //Braco
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslatef(-10, 0.0, 0.0); 
        glRotatef(-90, 0, 1, 0);
        //glScalef(1.5, 1.5, 1.5);
        draw_cylinder(2, 10, 1.0, 1.0, 1.0);
    glPopMatrix(); 

    //Braco
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslatef(+20, 0.0, 0.0); 
        glRotatef(-90, 0, 1, 0);
        //glScalef(1.5, 1.5, 1.5);
        draw_cylinder(2, 10, 1.0, 1.0, 1.0);
    glPopMatrix(); 

    //Casa
    glTranslatef(-30, -5, -20); 
    glPushMatrix();
        glColor3ub(254, 255, 0);
        glScalef(3, 3, 3);
        glRotatef(-90, 0, 2, 0);
        DrawEllipsoid(100, 100, 5, 10, 5);
    glPopMatrix();

    //folhas do abacaxi
        glTranslatef(0, 30, 0);
        glPushMatrix();
            glTranslatef(0, 0, 0);
            glColor3f(0.0, 1.0, 0.0);
            glScalef(0.5, 1, 0.5);
            DrawEllipsoid(100, 100, 5, 10, 5);
        glPopMatrix();

        
        glPushMatrix();
            glTranslatef(-4, 0, 0); 
            glColor3f(0.0, 1.0, 0.0);
            glRotatef(15, 0, -2 ,0 );
            glScalef(0.5, 1, 0.5);

            DrawEllipsoid(100, 100, 5, 10, 5);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(+4, 0, 0); 
            glColor3f(0.0, 1.0, 0.0);
            glRotatef(15, 0, -2 ,0 );
            glScalef(0.5, 1, 0.5);

            DrawEllipsoid(100, 100, 5, 10, 5);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 0, +4); 
            glColor3f(0.0, 1.0, 0.0);
            glRotatef(15, 0, -2 ,0 );
            glScalef(0.5, 1, 0.5);

            DrawEllipsoid(100, 100, 5, 10, 5);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-4, 0, +4); 
            glColor3f(0.0, 1.0, 0.0);
            glRotatef(15, 0, -2 ,0 );
            glScalef(0.5, 1, 0.5);

            DrawEllipsoid(100, 100, 5, 10, 5);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(+4, 0, -4); 
            glColor3f(0.0, 1.0, 0.0);
            glRotatef(15, 0, -2 ,0 );
            glScalef(0.5, 1, 0.5);

            DrawEllipsoid(100, 100, 5, 10, 5);
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0, 0, 0); 
            glColor3f(0.0, 1.0, 0.0);
            glRotatef(0, 0, 0 ,0 );
            glScalef(0.5, 1.5, 0.5);

            DrawEllipsoid(100, 100, 5, 10, 5);
        glPopMatrix();


    //JANELA DE CIMA
    glPopMatrix();
        glTranslatef(-1, -30, 0);
        glTranslatef(-5, 15, +15); 
        //glColor3f(1.0, 0.650, 0.0);
        glColor3f(0.0, 0.5, 1.0);
        glScalef(5, 5, 5);
        desenhaCirculo();

        glTranslatef(1.5, -2.25, 0); 
        desenhaCirculo();
    glPushMatrix();

    glTranslatef(10, 0, +15);
    glPushMatrix();
        glColor3ub(255, 203, 219);
        glutSolidSphere(2.5, 50, 50);
        glTranslatef(0, 1.5, 0);
        glutSolidSphere(2.0, 50, 50);
        glTranslatef(0, 2, 0);
        glRotatef(-90, 0, 1, 0);
        glScalef(0.1, 0.2, 0.1);
        glColor3ub(255, 203, 219);
        DrawEllipsoid(100, 100, 5, 10, 5);
    glPopMatrix();
    
    glPushMatrix();
        glRotatef(-90, 0, 1, 0);
        //glScalef(0.5, 0.5, 0.5);
        glColor3ub(255, 203, 219);
        //DrawEllipsoid(200, 200, 255, 203, 219);
        draw_cylinder(0.5, 5, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        //glScalef(0.5, 0.5, 0.5);
        glColor3ub(255, 203, 219);
        draw_cylinder(0.5, 5, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
        glColor3ub(255, 203, 219);
        glTranslatef(-2, -1, 1);
        glRotatef(90, 1, -1, -1);
        //glScalef(0.5, 0.5, 0.5);
        draw_cylinder(0.5, 4, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(2, -1, 1);
        glRotatef(90, 1, 1, 1);
        //glScalef(0.5, 0.5, 0.5);
        glColor3ub(255, 203, 219);
        draw_cylinder(0.5, 4, 0, 0, 0);
    glPopMatrix();

    //TRONCO DA ARVORE
    glTranslatef(-25, -1, -5);      
    glPushMatrix();
        glRotatef(-90, 1, 0, 0);
        glScalef(0.2, 0.1, 0.1);
        draw_cylinder(2, 45, 140,120,83);
    glPopMatrix();

  //COPA DA ARVORE
    glTranslatef(0, 5, 0);
    glScalef(0.15, 0.15, 0.15);
    glColor3f(0, 1, 0);
    glutSolidSphere(10, 30, 50);
    glTranslatef(0, 10, 0);
    glutSolidSphere(7, 30, 50);


    // Executa os comandos OpenGL, e depois troca os buffers de vídeo
    //glutSwapBuffers();
    glFlush();
    //glutSwapBuffers();
}

void reshape (int w, int h){
  // Define o viewport como o tamanho da janela
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  // Entra no modo de definição de matriz de projeção
  glMatrixMode (GL_PROJECTION);
  // Carrega a matriz identidade
  glLoadIdentity();
  // Define a projeção ortogonal
  if (w <= h)
    // Se a largura for menor que a altura, a projeção é feita para manter a proporção da janela
    glOrtho (-50, 50, -50*(GLfloat)h/(GLfloat)w, 50*(GLfloat)h/(GLfloat)w, -100.0, 100.0);
  else
    // Se a altura for menor que a largura, a projeção é feita para manter a proporção da janela
    glOrtho (-50*(GLfloat)w/(GLfloat)h, 50*(GLfloat)w/(GLfloat)h, -50, 50, -100.0, 100.0);
   
}

int main(int argc, char** argv){
  // Inicializa a biblioteca GLUT e negocia uma seção com o gerenciador de janelas
  glutInit(&argc, argv);
  // Inicializa o display, indicando que usará:
  // - um buffer de imagem (single buffer);
  // - buffer de profundidade;
  // - padrão de cores RGB)
  glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH | GLUT_RGB);
  // Especifica as dimensões da janela de exibição
  glutInitWindowSize (1280, 1000); 
  // Especifica a posição inicial da janela de exibição
  glutInitWindowPosition (100, 100);
  // Cria a janela de exibição
  win_id = glutCreateWindow ("O maximo q meu TDAH permitiu");
  // Chama a função init
  init();
  // Estabelece a função "display" como a função callback de exibição.
  glutDisplayFunc(display); 
  // Estabelece a função "reshape" como a função callback de redimensionamento da janela de exibição.
  glutReshapeFunc(reshape);
  // Entra no loop de eventos, não retorna
  glutMainLoop();
  return 0;
}