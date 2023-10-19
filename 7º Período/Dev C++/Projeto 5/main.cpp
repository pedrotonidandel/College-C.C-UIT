#include <windows.h>
#include <gl/glut.h>
#include <math.h>

// Tamanho e posição inicial do triangulo (x,y) (x+d,y+d) (x+d+d,y)
GLfloat x = 100.0f; //coordenada X
GLfloat y = 150.0f; //coordenada Y
GLsizei d = 50; //deslocamento
// Tamanho do incremento nas direções x e y
// (número de pixels para se mover a cada intervalo de tempo)
GLfloat passox = 1.0f;
GLfloat passoy = 1.0f;
// Largura e altura da janela
GLfloat largura;
GLfloat altura;

void Desenha(void)
{
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glClearColor(1,1,1,0);
glClear(GL_COLOR_BUFFER_BIT);
glBegin(GL_TRIANGLES);
glColor3f(1.0f, 0.0f, 0.0f);
glVertex2i(x,y);
glColor3f(0.0f, 1.0f, 0.0f);
glVertex2i(x+d,y+d);
glColor3f(0.0f, 0.0f, 1.0f);
glVertex2i(x+d+d,y);
glEnd();
glutSwapBuffers();
}

void Timer(int value)
{
    // Verifica se o triângulo atingiu os limites da janela
    if (x + d + d >= largura || x <= 0) {
        passox = -passox; // Inverte a direção do movimento na direção X
    }
    if (y + d >= altura || y <= 0) {
        passoy = -passoy; // Inverte a direção do movimento na direção Y
    }
   
    // Muda (x,y) movendo o desenho
    x += passox;
    y += passoy;
   
    glutPostRedisplay(); //Redesenha
    glutTimerFunc(33,Timer, 1); //Aguarda 33 ms e volta
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
if(h == 0) h = 1;
glViewport(0, 0, w, h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
if (w <= h) {
altura = 250.0f*h/w;
largura = 250.0f;
}
else {
largura = 250.0f*w/h;
altura = 250.0f;
}
gluOrtho2D(0.0f, largura, 0.0f, altura);
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{
// Define a cor de fundo da janela de visualização como preta
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
// Função callback chamada quando o tamanho da janela é alterado
// Programa Principal
int main(int argc, char** argv) {
glutInit(&argc, argv); // Initialize GLUT
glutCreateWindow("Primeiro Programa");
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
glutDisplayFunc(Desenha);
glutTimerFunc(33, Timer, 1);
glutReshapeFunc(AlteraTamanhoJanela);
glutIdleFunc(Desenha);

glutInitWindowPosition(350, 100);
// tamanho em pixels da janela
glutInitWindowSize(600,600); 
Inicializa();
glutMainLoop();
}
