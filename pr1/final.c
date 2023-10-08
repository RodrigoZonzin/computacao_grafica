
/* Copyright (c) Mark J. Kilgard, 1996. */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */

/* This program is a response to a question posed by Gil Colgate
   <gcolgate@sirius.com> about how lengthy a program is required using
   OpenGL compared to using  Direct3D immediate mode to "draw a
   triangle at screen coordinates 0,0, to 200,200 to 20,200, and I
   want it to be blue at the top vertex, red at the left vertex, and
   green at the right vertex".  I'm not sure how long the Direct3D
   program is; Gil has used Direct3D and his guess is "about 3000
   lines of code". */

/* X compile line: cc -o simple simple.c -lglut -lGLU -lGL -lXmu -lXext -lX11 -lm */

#include <GL/glut.h>
#include <time.h>
#include <math.h>


float CORZONA = 0;

void display(void); 
void reshape(int w, int h); 

void reshape(int w, int h){
  /* Because Gil specified "screen coordinates" (presumably with an
     upper-left origin), this short bit of code sets up the coordinate
     system to correspond to actual window coodrinates.  This code
     wouldn't be required if you chose a (more typical in 3D) abstract
     coordinate system. */

  glViewport(0, 0, w, h);       /* Establish viewing area to cover entire window. */
  glMatrixMode(GL_PROJECTION);  /* Start modifying the projection matrix. */
  glLoadIdentity();             /* Reset project matrix. */
  glOrtho(0, w, 0, h, -1, 1);   /* Map abstract coords directly to window coords. */
  glScalef(1, -1, 1);           /* Invert Y axis so increasing Y goes down. */
  glTranslatef(0, -h, 0);       /* Shift origin up to upper-left corner. */
}

void meuTeclado(unsigned char key, int x, int y){
  switch(key){
    case 27:
      exit(0); 
      break;

    case 'a':
    case 'A':
      srand((time_t)time(NULL));
      CORZONA = (float)rand();
      glutPostRedisplay();
      break;
  }
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  
  glBegin(GL_QUADS);
  /*PORTA AZUL*/
    glColor3f(1.0, 1.0, 0.8);  
    glVertex2i(500, 500);

    glColor3f(1.0, 1.0, 0.8);  
    glVertex2i(500, 300);

    glColor3f(1.0, 1.0, 0.8);  
    glVertex2i(300, 300);

    glColor3f(1.0, 1.0, 0.8);  
    glVertex2i(300, 500);
  glEnd();

  /*PARTE RETANGULAR*/
  glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 0.8);  
    glVertex2i(1000, 500);

    glColor3f(1.0, 1.0, 0.8);  
    glVertex2i(1000, 300);

    glColor3f(1.0, 1.0, 0.8);  
    glVertex2i(500, 300);

    glColor3f(1.0, 1.0, 0.8);  
    glVertex2i(500, 500);
  glEnd();

  /*TETO RETANGULAR*/
  glBegin(GL_QUADS);
    glColor3f(0.525, 0.349, 0.176);  
    glVertex2i(1000, 300);

    glColor3f(0.525, 0.349, 0.176);  
    glVertex2i(900, 100);

    glColor3f(0.525, 0.349, 0.176);  
    glVertex2i(400, 100);

    glColor3f(0.525, 0.349, 0.176);  
    glVertex2i(500, 300);
  glEnd();

  /*PARTE TRIANGULAR*/
  glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 0.8);  
    glVertex2i(500, 300);

    glColor3f(1.0, 1.0, 0.8);  
    glVertex2i(400, 100);

    glColor3f(1.0, 1.0, 0.8);  
    glVertex2i(300, 300);
  glEnd();

  /*PORTA*/
  glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.0);  
    glVertex2i(440, 500);

    glColor3f(0.2, 0.2, 0.0);  
    glVertex2i(440, 380);

    glColor3f(0.2, 0.2, 0.0);  
    glVertex2i(360, 380);

    glColor3f(0.2, 0.2, 0.0);  
    glVertex2i(360, 500);
  glEnd();

  /*JANELA1*/
  glBegin(GL_QUADS);
    glColor3f(0.901, 0.952, 1.0);  
    glVertex2i(680, 400);

    glColor3f(0.901, 0.952, 1.0);  
    glVertex2i(680, 320);

    glColor3f(0.901, 0.952, 1.0);  
    glVertex2i(600, 320);

    glColor3f(0.901, 0.952, 1.0);  
    glVertex2i(600, 400);
  glEnd();

  /*JANELA2*/
  glBegin(GL_QUADS);
    glColor3f(0.901, 0.952, 1.0);  
    glVertex2i(830, 400);

    glColor3f(0.901, 0.952, 1.0);  
    glVertex2i(830, 320);

    glColor3f(0.901, 0.952, 1.0);  
    glVertex2i(750, 320);

    glColor3f(0.901, 0.952, 1.0);  
    glVertex2i(750, 400);
  glEnd();

  /*chamineh*/
  glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);  
    glVertex2i(520, 40);

    glColor3f(1.0, 0.4, 0.0);  
    glVertex2i(520, 20);

    glColor3f(1.0, 0.4, 0.0);  
    glVertex2i(470, 20);

    glColor3f(1.0, 0.4, 0.0);  
    glVertex2i(470, 40);
  glEnd();

  /*chamineh*/
  glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);  
    glVertex2i(510, 100);

    glColor3f(1.0, 0.4, 0.0);  
    glVertex2i(510, 40);

    glColor3f(1.0, 0.4, 0.0);  
    glVertex2i(480, 40);

    glColor3f(1.0, 0.4, 0.0);  
    glVertex2i(480, 100);
  glEnd();

  float  x = 400, y = 250, radius = 50, num_segments = 1000; 
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.8, 1.0);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * i / (float)num_segments;
        float cx = radius * cosf(theta);
        float cy = radius * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();

  glFlush();  /* Single buffered, so needs a flush. */
}

int main(int argc, char **argv){
  glutInitWindowSize(800,600);
  glutInit(&argc, argv);
  glutCreateWindow("single triangle");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(meuTeclado);
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}
