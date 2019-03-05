#include "glut.h"
#include <math.h>
typedef struct Esfera { 
	float radio;  
	float x;  
	float y;  
	unsigned char rojo; 
	unsigned char verde;  
	unsigned char azul; 
};
Esfera esfera = { 1,0,2,50,150,200 };
Esfera esfera2 = { 0,-3,0,255,50,255 };
typedef struct Mundo {
	float ojo_x;
	float ojo_y;
	float ojo_z;
	float mira_x;
	float mira_y;
	float mira_z;
	float eje_x;
	float eje_y;
	float eje_z;
};
Mundo mundo = { 10, 10, 20, 0, 0, 0, 0, 1, 0 };
void Camara(Mundo *);
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

	gluLookAt(mundo.ojo_x, mundo.ojo_y, mundo.ojo_z,  // posicion del ojo
		mundo.mira_x, mundo.mira_y, mundo.mira_z,      // hacia que punto mira  (0,0,0) 
		mundo.eje_x, mundo.eje_y, mundo.eje_z);      // definimos hacia arriba (eje Y)    
	   
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
		esfera.radio += 0.2f; 
	if (key == '-' && esfera.radio > 1) 
		esfera.radio -= 0.2f;  
	if (key == 'z') {
		if (esfera.rojo >= 245) {
			esfera.rojo == 254;}
		else {
			esfera.rojo += 10;}
	}
	if (key == 'x') {
		if (esfera.verde >= 245) {
			esfera.verde = 254;}
		else {
			esfera.verde += 10;}
	}
	if (key == 'c') {
		if (esfera.azul >= 245) {
			esfera.azul = 254;}
		else {
			esfera.azul += 10;}
	}
	if (key == 'v') {
		if (esfera.rojo <= 11) {
			esfera.rojo = 0;}
		else {
			esfera.rojo -= 10;}
	}
	if (key == 'b') {
		if (esfera.verde <= 11) {
			esfera.verde = 0;}
		else {
			esfera.verde -= 10;}
	}
	if (key == 'n') {
		if (esfera.azul <= 11) {
			esfera.azul = 0;}
		else {
			esfera.azul -= 10;}
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
	Camara(&mundo);
	//no borrar estas lineas  
	glutTimerFunc(25,OnTimer,0);  
	glutPostRedisplay();
}
void Mueve(Esfera* e) { 
	e->radio += 0.02f; 
	e->rojo += 10;
	if (e->radio > 3)  
		e->radio = 0.5f; 
}
void Camara(Mundo *a) {

	//Calculamos la distancia
	float d, theta;
	d = sqrt(600.0f); //sqrt(10*10+10*10+20*20)
	//Calculamos angulo plano xz
	theta = atan2(a->ojo_x, a->ojo_z);
	theta += 0.02f;
	//Volvemos a las coordenadas tras el aumento
	a->ojo_z = d * cos(theta);
	a->ojo_x = d * sin(theta);
}
