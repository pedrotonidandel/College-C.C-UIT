#include <GL/glut.h>

// Vari�veis globais para controlar o tamanho e a posi��o dos tri�ngulos
float posicaoTriangulo1X = -0.4f;
float posicaoTriangulo2X = 0.4f;
float posicaoTrianguloY = 0.0f;
float escalaTriangulos = 0.1f;
float tamanhoTriangulo1 = 0.2f; // tamanho original
float tamanhoTriangulo2 = 0.2f; // tamanho original
float posicaoTriangulo2Y = 0.0f; // posi��o original do tri�ngulo 2

// Fun��o para desenhar um tri�ngulo na tela
void desenharTriangulo(float tamanho, float posX, float posY, float r, float g, float b) {
    glPushMatrix(); // Salva a matriz de transforma��o atual
    glTranslatef(posX, posY, 0.0f); // Aplica uma transla��o ao tri�ngulo
    glScalef(tamanho, tamanho, 1.0f); // Aplica uma escala ao tri�ngulo
    glBegin(GL_TRIANGLES);
    glColor3f(r, g, b);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glEnd();
    glPopMatrix(); // Restaura a matriz de transforma��o anterior
}

// Fun��o para desenhar os dois tri�ngulos na tela
void Desenha() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenhar tri�ngulo esquerdo em vermelho
    desenharTriangulo(tamanhoTriangulo1, posicaoTriangulo1X, posicaoTrianguloY, 1.0f, 0.0f, 0.0f);

    // Desenhar tri�ngulo direito em azul
    desenharTriangulo(tamanhoTriangulo2, posicaoTriangulo2X, posicaoTriangulo2Y, 0.0f, 0.0f, 1.0f);

    glFlush();
}


// Fun��o para tratar os comandos do teclado
void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
        case 'a':
        case 'A':
            tamanhoTriangulo1 *= 1.5f; // Aumenta o tamanho do tri�ngulo 1 em 50%
            break;
        case 'd':
        case 'D':
            tamanhoTriangulo1 /= 1.5f; // Diminui o tamanho do tri�ngulo 1 em 50%
            break;
        case 'b':
        case 'B':
            posicaoTriangulo2Y -= 0.1f; // Move o tri�ngulo 2 para baixo
            break;
        case 'c':
        case 'C':
            posicaoTriangulo2Y += 0.1f; // Move o tri�ngulo 2 para cima
            break;
        case 'o':
        case 'O':
            tamanhoTriangulo1 = tamanhoTriangulo2 = 0.2f; // Restaura o tamanho original dos tri�ngulos
            posicaoTriangulo1X = -0.4f; // Restaura a posi��o original do tri�ngulo 1
            posicaoTriangulo2Y = 0.0f; // Restaura a posi��o original do tri�ngulo 2
            break;
    }
    glutPostRedisplay(); // Solicita uma nova chamada � fun��o "desenhar"
}

// Fun��o callback chamada quando o tamanho da janela � alterado
// Fun��o principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Dois Tri�ngulos");

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Cor de fundo branca

    glutDisplayFunc(Desenha);
    glutKeyboardFunc(teclado);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutMainLoop();
    return 0;
}

