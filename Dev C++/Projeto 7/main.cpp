#include <GL/glut.h>
#include <stdio.h>

// largura e altura da janela
int width = 640;
int height = 480;

// coordenadas do quadrado
int squareX = width/2;
int squareY = height/2;
int squareSize = 50;

// estado do mouse
int mouseState = 0;
int mouseX = 0;
int mouseY = 0;

// função de desenho
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(squareX, squareY);
    glVertex2i(squareX+squareSize, squareY);
    glVertex2i(squareX+squareSize, squareY+squareSize);
    glVertex2i(squareX, squareY+squareSize);
    glEnd();
    glutSwapBuffers();
}

// função de callback para eventos de mouse
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        mouseX = x;
        mouseY = height - y;
        if (state == GLUT_DOWN) {
            printf("\nBotao esquerdo pressionado.");
            if (x >= squareX && x <= squareX+squareSize &&
                mouseY >= squareY && mouseY <= squareY+squareSize) {
                mouseState = 1;
                printf("\nPressionado na posicao: %d , %d",x,y);
            }
        } else {
            if (mouseState == 1) {
                printf("\nSolto na posicao: %d , %d",x,y);
            }
            mouseState = 0;
        }
    } else if (button == GLUT_RIGHT_BUTTON) {
        printf("\nBotão direito pressionado.");
    }
}

// função de callback para eventos de movimento do mouse
void motion(int x, int y) {
    if (mouseState == 1) {
        squareX += x - mouseX;
        squareY += (height - y) - mouseY;
        mouseX = x;
        mouseY = height - y;
        printf("Movendo - PRESSIONADO. Posicao: (%d, %d)\n", x,y);
        glutPostRedisplay();
    } else {
        printf("Solto. Posicao: (%d, %d)\n", x,y);
    }
}

// função principal
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutCreateWindow("Quadrado arrastavel");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glutMainLoop();
    return 0;
}

