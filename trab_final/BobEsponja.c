#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int win_id;

#define PI M_PI

void desenhaQuadrado();

//Aqui se capturam as teclas comuns (letras, números e ESC, por exemplo)
void myKeyboard(unsigned char key, int x, int y){
  switch (key) {
    case 'R': 
    case 'r':// muda a cor corrente para vermelho
      glColor3f(1.0f, 0.0f, 0.0f);
      break;
    case 'G':
    case 'g':// muda a cor corrente para verde
      glColor3f(0.0f, 1.0f, 0.0f);
      break;
    case 'B':
    case 'b':// muda a cor corrente para azul
      glColor3f(0.0f, 0.0f, 1.0f);
      break;
    //case 27:
    //  glutDestroyWindow(win_id);
    //  exit(0);
    //  break;
  }
  glutPostRedisplay();
}

//Aqui se capturam as teclas especiais (Alt, Control, Shift, F1, F2, etc.)
void myKeyboardSpecial(int key, int x, int y ) {
  switch ( key ) {
    case GLUT_KEY_UP:                   // Quando a seta para cima é teclada...
      glutFullScreen ( );               // Vá para o modo tela cheia...
      break;
    case GLUT_KEY_DOWN:                 // Quando a seta para baixo for teclada...
      glutReshapeWindow ( 640, 480 );   // Vá para modo em janela de 640 por 480
      break;
    default:
      printf("Você apertou a tecla especial código: %d\n", key);  // ...para ajudar você a debugar...       
      break;
  }
}

// Função callback chamada para gerenciar eventos do mouse
void myMouse(int button, int state, int x, int y){
  if (button == GLUT_LEFT_BUTTON)
    if (state == GLUT_DOWN) {
      float r, g, b;
      r = (double)rand() / (double)RAND_MAX;
      g = (double)rand() / (double)RAND_MAX;
      b = (double)rand() / (double)RAND_MAX;
      glColor3f(r,g,b);
      printf("%.2f, %.2f, %.2f\n", r, g, b);
    }
  glutPostRedisplay();
}

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

void drawSpongeBob(int x, int y, int z) {
    glColor3f(1.0, 1.0, 0.0); // Yellow color

    desenhaQuadrado();
    // You'll need to draw other features of SpongeBob (eyes, mouth, etc.)
    // using similar OpenGL commands (circles, rectangles, lines, etc.)
    // using the above logic.

    // Example: Draw SpongeBob's eyes
    glColor3f(0.0, 0.0, 0.0); // Black color for eyes
    glBegin(GL_POLYGON);
    // Define vertices for a circle at position (x - 20, y + 20, z + 10) with radius 10

    glEnd();

    // Continue drawing other features of SpongeBob similarly...
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
  //glClearColor (0.24, 0.73, 0.92, 0.0);
  glClearColor(1.0, 1.0, 1.0, 0.0);
  // Define o modo de rastreio de cor utilizado para misturar a cor do material nos pontos da face (smoothing)
  glShadeModel (GL_SMOOTH);
  // Habilita a definição da cor do material a partir da cor corrente
  glEnable(GL_COLOR_MATERIAL);

  //Parâmetros para a luz ambiente, difusa e especular, definindo também a posição da luz
  GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };

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
	
	for(float t = -PI/2; t <= (PI/2)+.0001; t += tStep)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for(float s = -PI; s <= PI+.0001; s += sStep)
		{
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

    // Desenha um teapot de lado de 10 unidades  
    //glutSolidTeapot(10.0);
    
    glRotatef(-30, 0, 1, 0);
    //glTranslatef(0.0, 0.0,  0.0);

    
    //DrawEllipsoid(120, 120, 0, 50, 30);

    //BOB ESPONJA 
    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix(); 
        glScalef(20, 25, 10);
        glutSolidCube(1);
    glPopMatrix();

    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
        glTranslatef(-5, 8.0, 8.0); 
        glScalef(1.5, 1.5, 1.5);
        desenhaCirculo();   
    glPopMatrix();

    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
        glTranslatef(5, 8.0, 8.0); 
        glScalef(1.5, 1.5, 1.5);
        desenhaCirculo();   
    glPopMatrix();

    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
        glTranslatef(-5, -4.0, 0.0); 
        glRotatef(90, 1, 0, 0);
        glScalef(1.5, 1.5, 1.5);
        draw_cylinder(2, 4, 1.0, 1.0, 1.0);
    glPopMatrix(); 

    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
        glTranslatef(+5, -4.0, 0.0); 
        glRotatef(90, 1, 0, 0);
        glScalef(1.5, 1.5, 1.5);
        draw_cylinder(2, 4, 1.0, 1.0, 1.0);
    glPopMatrix(); 


    // Executa os comandos OpenGL, e depois troca os buffers de vídeo
    glFlush();
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

int main(int argc, char** argv)
{
  // Inicializa a biblioteca GLUT e negocia uma seção com o gerenciador de janelas
  glutInit(&argc, argv);
  // Inicializa o display, indicando que usará:
  // - um buffer de imagem (single buffer);
  // - buffer de profundidade;
  // - padrão de cores RGB)
  glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH | GLUT_RGB);
  // Especifica as dimensões da janela de exibição
  glutInitWindowSize (1500, 1000); 
  // Especifica a posição inicial da janela de exibição
  glutInitWindowPosition (100, 100);
  // Cria a janela de exibição
  win_id = glutCreateWindow ("Casa do Senhor");
  // Chama a função init
  init ();
  // Estabelece a função "display" como a função callback de exibição.
  glutDisplayFunc(display); 
  // Estabelece a função "reshape" como a função callback de redimensionamento da janela de exibição.
  glutReshapeFunc(reshape);
  // Estabelece a função "keyboard" como a função callback de evento de teclado.
  //glutKeyboardFunc(myKeyboard);
  // Estabelece a função "keyboardSpecial" como a função callback de evento de teclado especial.
  //glutSpecialFunc(myKeyboardSpecial);
  // Estabelece a função "mouse" como a função callback de evento de mouse.
  //glutMouseFunc(myMouse);
  // Entra no loop de eventos, não retorna
  glutMainLoop();
  return 0;
}