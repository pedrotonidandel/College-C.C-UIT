#include <GL/glut.h>

// Variáveis globais para controlar o tamanho e a posição dos triângulos
float posicaoTriangulo1X = -0.4f;
float posicaoTriangulo2X = 0.4f;
float posicaoTrianguloY = 0.0f;
float escalaTriangulos = 0.1f;
float tamanhoTriangulo1 = 0.2f; // tamanho original
float tamanhoTriangulo2 = 0.2f; // tamanho original
float posicaoTriangulo2Y = 0.0f; // posição original do triângulo 2

// Função para desenhar um triângulo na tela
void desenharTriangulo(float tamanho, float posX, float posY, float r, float g, float b) {
    glPushMatrix(); // Salva a matriz de transformação atual
    glTranslatef(posX, posY, 0.0f); // Aplica uma translação ao triângulo
    glScalef(tamanho, tamanho, 1.0f); // Aplica uma escala ao triângulo
    glBegin(GL_TRIANGLES);
    glColor3f(r, g, b);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glEnd();
    glPopMatrix(); // Restaura a matriz de transformação anterior
}

// Função para desenhar os dois triângulos na tela
void Desenha() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenhar triângulo esquerdo em vermelho
    desenharTriangulo(tamanhoTriangulo1, posicaoTriangulo1X, posicaoTrianguloY, 1.0f, 0.0f, 0.0f);

    // Desenhar triângulo direito em azul
    desenharTriangulo(tamanhoTriangulo2, posicaoTriangulo2X, posicaoTriangulo2Y, 0.0f, 0.0f, 1.0f);

    glFlush();
}


// Função para tratar os comandos do teclado
void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
        case 'a':
        case 'A':
            tamanhoTriangulo1 *= 1.5f; // Aumenta o tamanho do triângulo 1 em 50%
            break;
        case 'd':
        case 'D':
            tamanhoTriangulo1 /= 1.5f; // Diminui o tamanho do triângulo 1 em 50%
            break;
        case 'b':
        case 'B':
            posicaoTriangulo2Y -= 0.1f; // Move o triângulo 2 para baixo
            break;
        case 'c':
        case 'C':
            posicaoTriangulo2Y += 0.1f; // Move o triângulo 2 para cima
            break;
        case 'o':
        case 'O':
            tamanhoTriangulo1 = tamanhoTriangulo2 = 0.2f; // Restaura o tamanho original dos triângulos
            posicaoTriangulo1X = -0.4f; // Restaura a posição original do triângulo 1
            posicaoTriangulo2Y = 0.0f; // Restaura a posição original do triângulo 2
            break;
    }
    glutPostRedisplay(); // Solicita uma nova chamada à função "desenhar"
}

// Função callback chamada quando o tamanho da janela é alterado
// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Dois Triângulos");

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Cor de fundo branca

    glutDisplayFunc(Desenha);
    glutKeyboardFunc(teclado);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutMainLoop();
    return 0;
}

