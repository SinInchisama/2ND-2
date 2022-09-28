#include <iostream>
#include <gl/glew.h> // �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <stdlib.h>
#include <time.h>
#include <random>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void init_sub();

typedef struct RGB {
	GLfloat R, G, B;
}RGB;

typedef struct rectangle {
	GLfloat x1, x2, y1, y2;
	RGB rgb;
	BOOL view;
}Rectanglae;

int prevxy[2] = { 0 };
RGB Brgb = { 1.0,1.0,1.0 }; 
Rectanglae sub[100] = { 0 };
Rectanglae Eraser = { 0 };

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(0, 0); // �������� ��ġ ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("Example1"); // ������ ����(������ �̸�) //--- GLEW �ʱ�ȭ�ϱ�
	init_sub();

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK
		) // glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	glutDisplayFunc(drawScene); // ��� �ݹ��Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �ݹ��Լ� ����
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ��Լ� ����
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop(); // �̺�Ʈ ó�� ����
}

GLvoid drawScene() {
	//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
	glClearColor(Brgb.R, Brgb.G, Brgb.B, 1.0f); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�
	for (int i = 0; i < 100; i++) {
		if (sub[i].view) {
			glColor3f(sub[i].rgb.R, sub[i].rgb.G, sub[i].rgb.B);
			glRectf(sub[i].x1, sub[i].y1, sub[i].x2, sub[i].y2);
		}
	}
	if (Eraser.view) {
		glColor3f(0, 0, 0);
		glRectf(Eraser.x1, Eraser.y1, Eraser.x2, Eraser.y2);
	}

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

GLvoid Keyboard(unsigned char key, int x, int y) {
	if(key == 'r' ||key == 'R')
		init_sub();
	glutPostRedisplay();
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
{
	glViewport(0, 0, w, h);
}

void Mouse(int button, int state, int x, int y) {
	srand(time(NULL));
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		Eraser.x1 = (float)(x - 400) / 40 / 10 - 0.1;
		Eraser.x2 = (float)(x - 400) / 40 / 10 + 0.1;
		Eraser.y1 = (float)(300 - y) / 30 / 10 - 0.1;
		Eraser.y2 = (float)(300 - y) / 30 / 10 + 0.1;
		Eraser.view = TRUE;
		prevxy[0] = x, prevxy[1] = y;
	}
	else if (Eraser.view && state == GLUT_UP) {
		Eraser.view = FALSE;
	}
	glutPostRedisplay();
}

void Motion(int x, int y) {
	if (Eraser.view) {
		Eraser.x1 += ((float)(x - prevxy[0]) / 400);
		Eraser.x2 += ((float)(x - prevxy[0]) / 400);
		Eraser.y1 -= ((float)(y - prevxy[1]) / 300);
		Eraser.y2 -= ((float)(y - prevxy[1]) / 300);
		prevxy[0] = x;
		prevxy[1] = y;

		for (int i = 0; i < 100; i++) {
			if (sub[i].x1 >= Eraser.x1 && sub[i].x1 <= Eraser.x2 && sub[i].y1 <= Eraser.y2 && sub[i].y1 >= Eraser.y1)
				sub[i].view = FALSE;
			else if(sub[i].x1 >= Eraser.x1 && sub[i].x1 <= Eraser.x2 && sub[i].y2 >= Eraser.y1 && sub[i].y1 <= Eraser.y2)
				sub[i].view = FALSE;
			else if (sub[i].x2 >= Eraser.x1 && sub[i].x2 <= Eraser.x2 && sub[i].y1 <= Eraser.y2 && sub[i].y1 >= Eraser.y1)
				sub[i].view = FALSE;
			else if (sub[i].x2 >= Eraser.x1 && sub[i].x2 <= Eraser.x2 && sub[i].y2 >= Eraser.y1 && sub[i].y1 <= Eraser.y2)
				sub[i].view = FALSE;
		}
	}
	glutPostRedisplay();
}

void init_sub() {
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<float> dis(-1, 0.95);
	std::uniform_real_distribution<float> disrt(0, 1);

	for (int i = 0; i < 100; ++i) {
		sub[i].x1 = dis(eng);
		sub[i].x2 = sub[i].x1 + 0.05;
		sub[i].y1 = dis(eng);
		sub[i].y2 = sub[i].y1 + 0.05;
		sub[i].view = TRUE;
		sub[i].rgb.R = disrt(eng), sub[i].rgb.G = disrt(eng), sub[i].rgb.B = disrt(eng);
	}
}