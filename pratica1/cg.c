#include <GL/glut.h>



void reshape(int w, int h){



    glViewport(0,0, w, h); 

    glMatrixModel(GL_PROJECTION);

    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1); 

    glScalef(1, -1, 1); 

    glTranslatef(0, -h, 0);

}