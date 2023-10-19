#include <windows.h>
#include <gl/glut.h>
#include <math.h>
#include <iostream>


int blackative = 0;

int activeRotate = 0;
int activeScale = 0;
int activeScaleDown = 0;

int moveRight = 0;
int moveLeft = 0;

void DesenhaOpc(int opc){
			 glClear(GL_COLOR_BUFFER_BIT);
	if(opc == 1){
		glRotatef(180, 0, 0, 1);
		glBegin(GL_TRIANGLES);
			glColor3f(1,0,0);
			glVertex3f(-0.5,-0.5,0);
			glColor3f(0,1,0);
			glVertex3f( 0.0, 0.5,0);
			glColor3f(0,0,1);
			glVertex3f( 0.5,-0.5,0);
		glEnd();
	}else if(opc == 2){
		glScalef(1.5, 1.5, 0.0);
		glBegin(GL_TRIANGLES);
			glColor3f(1,0,0);
			glVertex3f(-0.5,-0.5,0);
			glColor3f(0,1,0);
			glVertex3f( 0.0, 0.5,0);
			glColor3f(0,0,1);
			glVertex3f( 0.5,-0.5,0);
		glEnd();
	}else if(opc == 3){
			glScalef(0.0,0.5, 0.0);
		glBegin(GL_TRIANGLES);
			glColor3f(1,0,0);
			glVertex3f(-0.5,-0.5,0);
			glColor3f(0,1,0);
			glVertex3f( 0.0, 0.5,0);
			glColor3f(0,0,1);
			glVertex3f( 0.5,-0.5,0);
		glEnd();	
	}
}

void Desenha(void){
	if(activeRotate == 1){
		DesenhaOpc(1);
		activeRotate = 0;
	}	else if(activeScale == 1){
		DesenhaOpc(2);
		activeScale = 0;
	}else if(activeScaleDown == 1){
		DesenhaOpc(3);
		activeScaleDown = 0;
	}else if(moveRight == 1){
		glBegin(GL_TRIANGLES);
		glVertex3f(-0.5,-0.5,0);
		glVertex3f( 0.0, 0.5,0);
		glColor3f(0,0,9);
		glVertex3f( 0.5,-0.5,0);
		glEnd();
	}
	else{
	glBegin(GL_TRIANGLES);
		glColor3f(1,0,0);
		glVertex3f(-0.5,-0.5,0);
		glColor3f(0,1,0);
		glVertex3f( 0.0, 0.5,0);
		glColor3f(0,0,1);
		glVertex3f( 0.5,-0.5,0);
	glEnd();
	glFlush();
	}

	glFlush();
}

void Inicializa (void){ 
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


void eventTeclado(unsigned char key, int x, int y) {
	std::cout << "opa";
    switch (key) {
    	case 'r':
        	std::cout << "b";
        	
        	activeRotate = 1;
			glutPostRedisplay();
        	break;
    	case 's':
	    	std::cout << "b";
	    	
	    	activeScale = 1;
			glutPostRedisplay();
	    	break;
	    case 'o':
	    	std::cout << "J";
	    	
	    	activeScaleDown = 1;
			glutPostRedisplay();
	    	break;
	    	
	    case 'd':
	    	std::cout << "J";
	    	
	    	activeScaleDown = 1;
			glutPostRedisplay();
	    	break;

        	
    }
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000,500);
	glutInitWindowPosition(10,10);
	glutCreateWindow("Quadrado");
	glutDisplayFunc(Desenha);
	glutKeyboardFunc(eventTeclado);//Ouve teclado
	Inicializa();
	glutMainLoop();
}
//glutPostRedisplay();
