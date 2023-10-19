#include <windows.h>
#include <gl/glut.h>
#include <math.h>
#include <iostream>

int activeRotate = 0;
int aumentaTamanho = 0;
int diminuiTamanho = 0;

int moveRight = 0;
int moveLeft = 0;
int moveUp = 0;
int moveDown = 0;

int zoomIn = 0;
int zoomOut = 0;

int giraManual = 0;

int gira = 0;
int para = 0;

int reseta = 0;

float angulo = 0;
//Tamanhos vertex Triangulo
float v1p1 = -0.5;
float v1p2 = -0.5;
float v2p1 = 0.0;
float v2p2 = 0.5;
float v3p1 = 0.5;
float v3p2 = -0.5;


//Move Direta
void funcMoveRight(){
	v1p1 = v1p1 + 0.2;
	v2p1 = v2p1 + 0.2;
	v3p1 = v3p1 + 0.2;
	moveRight = 0;
}
//Move esquerda
void funcMoveLeft(){
	v1p1 = v1p1 - 0.2;
	v2p1 = v2p1 - 0.2;
	v3p1 = v3p1 - 0.2;
	moveLeft = 0;
}
//Move cima
void funcMoveUp(){
	v1p2 = v1p2 + 0.2;
	v2p2 = v2p2 + 0.2;
	v3p2 = v3p2 + 0.2;
	moveUp = 0;
}
//Move Down
void funcMoveDown(){
	v1p2 = v1p2 - 0.2;
	v2p2 = v2p2 - 0.2;
	v3p2 = v3p2 - 0.2;
	moveDown = 0;
}





void Desenha(void){
	 glClear(GL_COLOR_BUFFER_BIT);
	 glLoadIdentity();
	if(aumentaTamanho == 1){
		//glScalef(1.1, 1.1, 0.0);
		std::cout << "auemntaTamanho";
		v1p1 = v1p1 - 0.1;
		v2p2 = v2p2 + 0.2;
		v3p1 = v3p1 + 0.1;
		aumentaTamanho = 0;
	}if(diminuiTamanho == 1){
		//glScalef(0.5,0.5, 0.0);
				std::cout << "";
		v1p1 = v1p1 + 0.1;
		v2p2 = v2p2 - 0.2;
		v3p1 = v3p1 - 0.1;
		diminuiTamanho = 0;
	}if(zoomIn == 1){
				std::cout << "";
		zoomOut = 0;
		glScalef(1.5, 1.5, 0.0);
	}if(zoomOut == 1){
				std::cout << "";
		zoomIn = 0;
		glScalef(0.8, 0.8, 0.0);

	}
	if(moveLeft == 1){
		std::cout << "moveLeft";
		funcMoveLeft();
	}if(moveRight == 1){
		std::cout << "moveRight";
		funcMoveRight();
		moveRight = 0;
	}if(moveUp == 1){
		std::cout << "";
		funcMoveUp();
	}if(moveDown == 1){
				std::cout << "";
		funcMoveDown();
	}if(gira == 1){
		std::cout << "";
		if(para == 1){
			angulo += 0;
		}else{
			angulo += 0.1;	
		}
		glRotatef(angulo,0,0,1);
	}if(giraManual == 1){
		std::cout << "";
		glRotatef(angulo,0,0,1);
	
	}
	if(reseta == 1){
		gira = 0;
		para = 0;
		angulo = 0;
		 v1p1 = -0.5;
		 v1p2 = -0.5;
		 v2p1 = 0.0;
		 v2p2 = 0.5;
		 v3p1 = 0.5;
		 v3p2 = -0.5;
		 reseta = 0;
	}

	glBegin(GL_TRIANGLES);
		glColor3f(1,0,0);
		glVertex3f(v1p1,v1p2,0);
		glColor3f(0,1,0);
		glVertex3f( v2p1, v2p2,0);
		glColor3f(0,0,1);
		glVertex3f( v3p1,v3p2,0);
	glEnd();
	glutSwapBuffers();
}

void Inicializa (void){ 
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void TeclasEspeciais(int key, int x, int y)
{
	switch (key) // setas do teclado
	{
	case GLUT_KEY_UP:
		std::cout << "";
		moveUp = 1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN: 
		std::cout << "";
		moveDown = 1;
		glutPostRedisplay();
		break; 
	case GLUT_KEY_LEFT:
		std::cout << "";
    	
    	moveLeft = 1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT: 
		std::cout << "";	
	    moveRight = 1;
		glutPostRedisplay();
		break; 
	}
}
void GerenciaMouse(int button, int state, int x, int y)
{
	switch(button)
	{
		case GLUT_LEFT_BUTTON: 
			if (state == GLUT_DOWN){
				std::cout << "";
				zoomOut = 1;
				zoomIn = 0;
				glutPostRedisplay();
			}; 
		break;
		case GLUT_MIDDLE_BUTTON: break;
		case GLUT_RIGHT_BUTTON: 
			if (state == GLUT_DOWN){
				std::cout << "";
				zoomIn = 1;
				zoomOut = 0;
				glutPostRedisplay();
			}; 
		break;
	}
	glutPostRedisplay();
}

void eventTeclado(unsigned char key, int x, int y) {
    switch (key) {
    	case 'g':
    		gira = 1;
    		para = 0;
    		glutPostRedisplay();
    		break;
    	case 'p':
    		para = 1;
    		glutPostRedisplay();
    		break;
    	case 'r':
	    	giraManual = 1;
	    	angulo = angulo + 30;
	    	glutPostRedisplay();
	    	break;
	    case 'o':
	    	gira = 0;
	    	para = 0;
	    	reseta = 1;
	    	break;
    	case 'a':
	    	std::cout << "a";
	    	aumentaTamanho = 1;
			glutPostRedisplay();
	    	break;
	    case 'd':
	    	std::cout << "d";
	    	
	    	diminuiTamanho = 1;
			glutPostRedisplay();
	    	break;
		case 27 : // Escape key
		std::cout << "ESC";
			exit (0);
			break;
        	
    }
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000,500);
	glutInitWindowPosition(10,10);
	glutCreateWindow("Quadrado");
	glutMouseFunc(GerenciaMouse);
	glutDisplayFunc(Desenha);
	glutSpecialFunc(TeclasEspeciais);
	glutKeyboardFunc(eventTeclado);//Ouve teclado
	Inicializa();
	glutIdleFunc(Desenha);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutMainLoop();
}
