/*
Prototipo de programa principal
ULPGC, EII, Creando Interfaces de Usuario
*/

#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

float gl_ancho = 2.0, gl_alto = 2.0, gl_cerca = -1, gl_lejos = 5.0;
int w_ancho = 500, w_alto = 500;

void InitGlew() {
    GLenum glew_init = glewInit();
    if (glew_init != GLEW_OK) {
        fprintf(stderr, "Error %s\n", glewGetErrorString(glew_init));
    } else {
        printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    }
}

void writeBitmapString(float x, float y, void *font, char *string) {
    char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void writeStrokeString(float x, float y, void *font, char *string) {
    char *c;
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(x, y, 0);
    glScalef(1.0f / 300, 1.0f / 300, 1.0f / 300);
    for (c = string; *c != '\0'; c++) {
        glutStrokeCharacter(font, *c);
    }
    glPopMatrix();
}


void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    writeBitmapString(0.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, (char *) "Hola OpenGL!");
    glFlush();
}


void Display2() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    writeStrokeString(-1, 0, GLUT_STROKE_ROMAN, (char *) "Hola OpenGL!");
    glFlush();
}


void InitGL() {

    if (gl_ancho / w_ancho != gl_alto / w_alto) {
        fprintf(stderr, "La relación de aspecto no es correcta\n");
    }

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-gl_ancho / 2.0, gl_ancho / 2.0, -gl_alto / 2.0, gl_alto / 2.0, gl_cerca, gl_lejos); // espacio de trabajo
}

void ReshapeSize(int ancho, int alto) {

    float dx = gl_ancho;
    float dy = gl_alto;

    dx *= (float) ancho / (float) w_ancho;
    dy *= (float) alto / (float) w_alto;

    glViewport(0, 0, ancho, alto); // utiliza la totalidad de la ventana
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-dx / 2.0, dx / 2.0, -dy / 2.0, dy / 2.0, gl_cerca, gl_lejos); // espacio de trabajo
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(w_ancho, w_alto);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

    glutCreateWindow("OpenGL Práctica 3_1. BITMAP.");
    InitGlew();
    InitGL();
    glutDisplayFunc(Display);
    glutReshapeFunc(ReshapeSize);

    glutCreateWindow("OpenGL Práctica 3_1. STROKE");
    InitGL();
    glutDisplayFunc(Display2);
    glutReshapeFunc(ReshapeSize);

    glutMainLoop();
    return 0;
}