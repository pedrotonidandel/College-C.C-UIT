// Quadrado.c
// Um programa OpenGL simples que desenha um
// quadrado em uma janela GLUT.
#include <windows.h>
#include <gl/glut.h>
#include <math.h>
int porta = 0;
int telhado = 0;
int tronco = 0;
int chao = 0 ;
int casa = 0;
int copa = 0;
int sol = 0;

void Arvore(float cx, float cy, float r, int num_segmentos)
{
if(copa == 1){
	glColor3f(0.5f, 1.0f, 0.5f);
}else{
	glColor3f(0, 1.0f, 0);
}

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
void Teclado (unsigned char key, int x, int y) {
if(key=='t' || key == 'T'){
	if(telhado == 0){
		telhado = 1;
	}else{
		telhado = 0;
	} 
	
	glutPostRedisplay();
}else if(key=='c' || key == 'C'){
		if(chao == 0){
		chao = 1;
	}else{
		chao= 0;
	} 
	
	glutPostRedisplay();
}else if(key=='s' || key == 'S'){
	if(sol == 0){
		sol = 1;
	}else{
		sol= 0;
	} 
	
	glutPostRedisplay();
}else if(key=='r' || key == 'R'){
		if(tronco == 0){
		tronco = 1;
	}else{
		tronco= 0;
	} 
	
	glutPostRedisplay();
}else if(key=='p' || key == 'P'){
		if(porta == 0){
		porta = 1;
	}else{
		porta= 0;
	} 
	
	glutPostRedisplay();
}else if(key=='b' || key == 'B'){
		if(casa == 0){
		casa = 1;
	}else{
		casa= 0;
	} 
	
	glutPostRedisplay();
}else if(key=='o' || key == 'O'){
		if(copa == 0){
		copa = 1;
	}else{
		copa= 0;
	} 
	
	glutPostRedisplay();
}

}


void Circulo(float cx, float cy, float r, int num_segmentos)
{ 

if(sol == 1){
		glColor3f(3.0f, 1.0f, 0);
}else{
	glColor3f(1.8f, 0.8f, 0);
} 
	

glBegin(GL_LINE_LOOP); 
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
if(chao == 1){
	glColor3f(0.7f, 1.0f, 0.7f);
}else{
	glColor3f(0.5f, 1.0f, 0.5f);
}

glBegin(GL_QUADS); // chao
glVertex2i(0,120);
glVertex2i(0,0);
glVertex2i(400,0);
glVertex2i(400,120);
glEnd();


if(tronco == 1){
	glColor3f(0.7f, 0.5f, 0.7f);
}else{
	glColor3f(0.7, 0.5f, 0.2f);
} 
glBegin(GL_QUADS);//tronco
glVertex2i(40,120);
glVertex2i(60,120);
glVertex2i(60,170);
glVertex2i(40,170);
glEnd();


if(casa == 1){
	glColor3f(0.2f, 0.6f, 2.0f);
}else{
	glColor3f(0.5f, 0.7f, 2.2f);
} 
glBegin(GL_QUADS); //casa
glVertex2i(150,120);
glVertex2i(200,120);
glVertex2i(200,170);
glVertex2i(150,170);
glEnd();


if(telhado == 1){
	glColor3f(0.9f, 0.6f, 0);
}else{
	glColor3f(1.2f, 0.8f, 0);
} 
glBegin(GL_QUADS); //telhado
glVertex2i(150,170);
glVertex2i(200,170);
glVertex2i(175,210);
glVertex2i(175,210);
glEnd();


if(porta == 1){
	glColor3f(1.6f, 0.6f, 0);
}else{
	glColor3f(1.8f, 0.8f, 0);
} 
glBegin(GL_QUADS); //porta
glVertex2i(170,120);
glVertex2i(180,120);
glVertex2i(180,145);
glVertex2i(170,145);
glEnd();

Circulo(110,220,10,500);



glColor3f(1.2f, 1.3f, 0);
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

Arvore(50,175,10,500);

Arvore(35,165,10,500);

Arvore(65,165,10,500);


// Executa os comandos OpenGL
glFlush();
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
glutKeyboardFunc(Teclado); 
glutReshapeFunc(AlteraTamanhoJanela);

glutInitWindowPosition(350, 100);
// tamanho em pixels da janela
glutInitWindowSize(640,480); 
Inicializa();
glutMainLoop();
}
