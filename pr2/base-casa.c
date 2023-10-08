#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

// Largura e altura da janela
GLfloat windowWidth;
GLfloat windowHeight;

//Desenha um quadrado de lado 1 centrado na origem
void desenhaQuadrado() {
    glBegin(GL_QUADS);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(-0.5, 0.5);
    glEnd();
}

//Desenha um triângulo equilátero de lado 1 centrado na origem
void desenhaTriangulo() {
    glBegin(GL_TRIANGLES);
        glVertex2d(0.0, 0.5);
        glVertex2d(-0.5, -0.5);
        glVertex2d(0.5, -0.5);
    glEnd();
}

//Desenha um círculo de raio 1 centrado na origem
void desenhaCirculo() {
    glBegin(GL_POLYGON);
        for (int i = 0; i < 30; i++) {
            glVertex2f(cos(i), sin(i));
        }
    glEnd();
}

//Faz o cisalhamento de um objeto em relação ao eixo X
//Basta utilizar como uma das funções do OpenGL como glTranslatef, glRotatef, glScalef
void skewX(GLfloat angle) {
    GLfloat m[16] = {
        1, 0, 0, 0,
        tan(angle), 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0 ,1
    };
    glMultMatrixf(m);
}

//Faz o cisalhamento de um objeto em relação ao eixo Y
//Basta utilizar como uma das funções do OpenGL como glTranslatef, glRotatef, glScalef
void skewY(GLfloat angle) {
    GLfloat m[16] = {
        1, tan(angle), 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    glMultMatrixf(m);
}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Limpa a janela de visualização com a cor de fundo especificada
    glClear(GL_COLOR_BUFFER_BIT);

    // Aqui entra todo o seu código da casa 2D.
    //Vocês só pode usar as funções de desenho:
        // desenhaQuadrado, desenhaTriangulo, desenhaCirculo
    // as transformações geométricas:
        // glTranslatef, glRotatef, glScalef, skewX, skewY
    // e as funções de cor:
        // glColor3f
    // Não desenhe nenhuma primitiva utilizando glBegin/glEnd diretamente aqui.


        /*quadrado amarelo*/
        glColor3f(1.0, 1.0, 0.0);
        glTranslatef(50, 50, 0);
        glPushMatrix();
        glScalef(90, 90, 1);
        desenhaQuadrado();
        glPopMatrix();

        /*porta*/
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(0, -25, 0);
        glPushMatrix();
        glScalef(25, 55, 1);
        desenhaQuadrado();
        glPopMatrix();


        /*parede vermelha*/
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(150, 0, 0);
        glPushMatrix();
        glScalef(200, 100, 1);
        desenhaQuadrado();
        glPopMatrix();



        /*triangulo*/
        glColor3f(0.0, 0.0, 1.0);
        glTranslatef(-150, 100, 0);
        glPushMatrix();
        glScalef(100, 100, 1);
        desenhaTriangulo();
        glPopMatrix();

        /*circulo*/
        glColor3f(1.0, 0.0, 1.0);
        glTranslatef(0, 0, 0);
        glPushMatrix();
        glScalef(20, 20, 1);
        desenhaCirculo();
        glPopMatrix();


        /*teiado*/
        glColor3f(0.0, 0.0, 1.0);
        glTranslatef(124, -1, 0);
        glPushMatrix();
        skewX(-27.895*M_PI/180.0f);
        glScalef(200, 100, 1);
        desenhaQuadrado();
        glPopMatrix();

        /*chamine*/
        glColor3f(1.0, 1.0, 0.0);
        glTranslatef(0, 55, 0);
        glPushMatrix();
        glScalef(15, 55, 1);
        desenhaQuadrado();
        glPopMatrix();




    // Executa os comandos OpenGL
    glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Evita a divisao por zero
    if(h == 0) h = 1;

    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Estabelece a janela de seleção (left, right, bottom, top)
    // Se a largura da janela, em pixels, for menor que a altura, a largura da viewport é fixada em 250 e a altura é escalada para o necessário
    if (w <= h)  {
        windowHeight = 250.0f*h/w;
                windowWidth = 250.0f;
    }
    else  {
    // Se a altura da janela, em pixels, for menor que a largura, a altura da viewport é fixada em 250 e a largura é escalada para o necessário
                windowWidth = 250.0f*w/h;
                windowHeight = 250.0f;
    }

    // As dimensões da janela vão de (0.0, 0.0) até (windowWidth, windowHeight), essas são as coordenadas da tela
    gluOrtho2D(0.0f, windowWidth, 0.0f, windowHeight);
}

// Programa Principal
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400,350);
    glutInitWindowPosition(10,10);
    glutCreateWindow("eu odeio programar");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    Inicializa();
    glutMainLoop();
    return 0;
}