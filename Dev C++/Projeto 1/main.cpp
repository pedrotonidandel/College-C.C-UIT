// Quadrado.c
// Um programa OpenGL simples que desenha um
// quadrado em uma janela GLUT.
#include <windows.h>
#include <gl/glut.h>
#include <math.h>
// Função callback chamada para fazer o desenho

void DesenhaCirculo(float cx, float cy, float r, int num_segmentos)
{
glColor3f(1.0f, 1.0f, 0);
glBegin(GL_LINE_LOOP); // desenha o círculo
for(int ii = 0; ii < num_segmentos; ii++)
{
float theta = 2.0f * 3.1415926f * float(ii) / float(num_segmentos);
float x = r * cosf(theta); //calcular o componente x
float y = r * sinf(theta); //calculate o componente y
glVertex2f(x + cx, y + cy); //vertices de saída
}
glEnd();
glBegin(GL_POLYGON); // preenche o círculo
for (int i = 0; i < 360; i++) {
float angle_theta = i * 3.142 / 180;
glVertex2f(cx + r * cos(angle_theta), cy + r * sin(angle_theta));
}
glEnd();
}

void DesenhaCirculoArvore(float cx, float cy, float r, int num_segmentos)
{
glColor3f(0, 1.0f, 0);
glBegin(GL_LINE_LOOP); // desenha o círculo
for(int ii = 0; ii < num_segmentos; ii++)
{
float theta = 2.0f * 3.1415926f * float(ii) / float(num_segmentos);
float x = r * cosf(theta); //calcular o componente x
float y = r * sinf(theta); //calculate o componente y
glVertex2f(x + cx, y + cy); //vertices de saída
}
glEnd();
glBegin(GL_POLYGON); // preenche o círculo
for (int i = 0; i < 360; i++) {
float angle_theta = i * 3.142 / 180;
glVertex2f(cx + r * cos(angle_theta), cy + r * sin(angle_theta));
}
glEnd();
}

void Desenha(void)
{
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
// Limpa a janela de visualização
glClear(GL_COLOR_BUFFER_BIT);
// Especifica que a cor corrente é vermelha
// R G B
// Desenha um quadrado na cor corrente
glColor3f(0.0f, 1.0f, 0.0f);
glBegin(GL_QUADS);
glVertex2i(0,120);
glVertex2i(0,0);
glVertex2i(400,0);
glVertex2i(400,120);
glEnd();

glColor3f(0.5, 0, 0);
glBegin(GL_QUADS);
glVertex2i(40,120);
glVertex2i(60,120);
glVertex2i(60,170);
glVertex2i(40,170);
glEnd();

glColor3f(0, 0, 1.0f);
glBegin(GL_QUADS);
glVertex2i(150,120);
glVertex2i(200,120);
glVertex2i(200,170);
glVertex2i(150,170);
glEnd();

glColor3f(0.5f, 0, 0);
glBegin(GL_QUADS);
glVertex2i(150,170);
glVertex2i(200,170);
glVertex2i(175,210);
glVertex2i(175,210);
glEnd();

glColor3f(0.5f, 0, 0);
glBegin(GL_QUADS);
glVertex2i(170,120);
glVertex2i(180,120);
glVertex2i(180,145);
glVertex2i(170,145);
glEnd();

DesenhaCirculo(110,220,10,500);

glColor3f(1.0f, 1.0f, 0);
glLineWidth(5);
glBegin(GL_LINES);

glVertex2i(100,210);
glVertex2i(90,200);

glVertex2i(110,208);
glVertex2i(110,195);

glVertex2i(120,210);
glVertex2i(130,200);

glVertex2i(125,220);
glVertex2i(142,220);

glVertex2i(80,220);
glVertex2i(95,220);

glVertex2i(90,240);
glVertex2i(100,230);

glVertex2i(120,230);
glVertex2i(130,240);

glVertex2i(110,233);
glVertex2i(110,245);

glEnd();

DesenhaCirculoArvore(50,175,10,500);

DesenhaCirculoArvore(35,165,10,500);

DesenhaCirculoArvore(65,165,10,500);


// Executa os comandos OpenGL
glFlush();
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{
// Define a cor de fundo da janela de visualização como preta
glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
if (w <= h)
gluOrtho2D (0.0f, 250.0f, 0.0f, 250.0f*h/w);
else
gluOrtho2D (0.0f, 250.0f*w/h, 0.0f, 250.0f);
}
// Programa Principal
int main(int argc, char** argv) {
glutInit(&argc, argv); // Initialize GLUT
glutCreateWindow("Primeiro Programa");
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutDisplayFunc(Desenha);
glutReshapeFunc(AlteraTamanhoJanela);

glutInitWindowPosition(350, 100);
// tamanho em pixels da janela
glutInitWindowSize(640,480); 
Inicializa();
glutMainLoop();
}
