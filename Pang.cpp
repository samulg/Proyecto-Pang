#include "glut.h"
typedef struct _Esfera { 
	float radio;  
	float x;  
	float y;  
	unsigned char rojo; 
	unsigned char verde;  
	unsigned char azul; 
} Esfera;
Esfera esfera = { 1,0,0,255,255,255 };
Esfera esfera2 = { 0,0,3,0,255,255 };
//los callback, funciones que seran llamadas automaticamente por la glut
//cuando sucedan eventos
//NO HACE FALTA LLAMARLAS EXPLICITAMENTE
void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
void Dibuja(Esfera e);
void Mueve(Esfera* e);
int main(int argc, char* argv[])
{
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("MiJuego");

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);

	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();

	return 0;
}
void Dibuja(Esfera e) {
	glColor3ub(e.rojo, e.verde, e.azul);
	glTranslatef(e.x, e.y, 0);
	glutSolidSphere(e.radio, 20, 20);
	glTranslatef(-e.x, -e.y, 0);
}
void OnDraw(void)
{
	//Borrado de la pantalla	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 20, 30,  // posicion del ojo
		0.0, 0, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	Dibuja(esfera); 
	Dibuja(esfera2);
	glColor3ub(0, 255, 0);
	glutSolidTorus(1, 5, 50, 50);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 0); 
	glVertex3f(-5.0f, 0.0f, -5.0f);
	glColor3ub(255, 255, 0); 
	glVertex3f(-5.0f, 0.0f, 5.0f); 
	glColor3ub(255, 0, 0); 
	glVertex3f(5.0f, 0.0f, 5.0f); 
	glColor3ub(255, 0, 0); 
	glVertex3f(5.0f, 0.0f, -5.0f);
	glEnd();
	glEnable(GL_LIGHTING);
	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	if (key == '+' && esfera.radio < 3)  
		esfera.radio += 0.5f; 
	if (key == '-' && esfera.radio > 1) 
		esfera.radio -= 0.5f;  
	if (key == 'r') {
		esfera.rojo = 255;   
		esfera.verde = 0;   
		esfera.azul = 0;
	}  
	if (key == 'a')  
		esfera.x -= 0.1f;
	if (key == 'd')  
		esfera.x += 0.1f; 
	if (key == 's')   
		esfera.y -= 0.1f;  
	if (key == 'w')   
		esfera.y += 0.1f;
		glutPostRedisplay();
}

void OnTimer(int value)
{
	//poner aqui el código de animacion  
	//Mueve(&esfera);  
	Mueve(&esfera2);
	//no borrar estas lineas  
	glutTimerFunc(25,OnTimer,0);  
	glutPostRedisplay();
}
void Mueve(Esfera* e) { 
	e->radio += 0.1f; 
	e->azul += 10;
	if (e->radio > 3)  
		e->radio = 0.5f; 
}