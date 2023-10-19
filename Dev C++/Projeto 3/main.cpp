#include <windows.h>
#include <gl/glut.h>
#include <iostream>
int rotate;
int scale;
int translate;

void Teclado (unsigned char key, int x, int y) {
switch (key){
	case 'r':
		rotate = 1;
		printf("\nEntrei no r");
		glutPostRedisplay();
	 	break;
 	case 's':
		scale = 2;
		printf("\nEntrei no s");
		glutPostRedisplay();
	 	break;
 	case 't':
		translate = 3;
		printf("\nEntrei no t");
		glutPostRedisplay();
 	break;
	}
}
void Desenha(void) {
  
  glClear(GL_COLOR_BUFFER_BIT);
  
 // glLoadIdentity();
  
    if (rotate == 1){
    printf("\ndesenha 1")	;
  	glRotatef(180, 0, 0, 1);
  	rotate = 0;
  }
  
  else if (scale == 2){
	printf("\ndesenha 2")	;
	glScalef(1.5, 1.5, 0.0);
	scale = 0;
  }
  
  else if (translate == 3){
  	printf("\ndesenha 3")	;
  	glTranslatef(-0.4,0.4,0.0);
  	translate = 0;
  }
  
    glBegin(GL_TRIANGLES);
  		glColor3f(1,0,0);
  		glVertex3f(0,0,0);
  		glColor3f(0,1,0);
  		glVertex3f(10,40,0);
 		glColor3f(0,0,1);
  		glVertex3f(20,0,0);
 	glEnd();
  
    // Executa os comandos OpenGL
  glFlush();
  
}

// Inicializa parâmetros de rendering
void Inicializa(void) {
  // Define a cor de fundo da janela de visualização como preta
  scale = 0;
  translate = 0;
  rotate = 0;
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  gluOrtho2D(-320,320,-240,240);
  glMatrixMode(GL_MODELVIEW);
  printf("\nInicializa!");
}
// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
if(h == 0) h = 1; // Evita a divisao por zero
//glViewport(0, 0, 400, 400); // largura e altura da janela mudam viewport NÃO
glViewport(0, 0, w, h); // largura e altura da imagem mudam proporcionalmente a janela
glMatrixMode(GL_PROJECTION); // Inicializa o sistema de coordenadas
glLoadIdentity(); // Substitui a matriz atual pela matriz alterada
if (w <= h) // Estabelece a janela de seleção (left, right, bottom, top)
gluOrtho2D(-1,1,-1,1*h/w);
else
gluOrtho2D(-1,1*w/h,-1,1);
}
// Programa Principal
int main(int argc, char ** argv) {
  glutInit( & argc, argv); // Initialize GLUT
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(10, 10);
  glutCreateWindow("Quadrado");
  glutKeyboardFunc(Teclado);
  glutReshapeFunc(AlteraTamanhoJanela);
  glutDisplayFunc(Desenha);
  Inicializa();
  glutMainLoop();
}
