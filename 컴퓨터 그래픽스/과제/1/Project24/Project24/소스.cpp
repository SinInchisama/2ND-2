#include <iostream>
#include <gl/glew.h> // 필요한 헤더파일 include
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

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("Example1"); // 윈도우 생성(윈도우 이름) //--- GLEW 초기화하기
	init_sub();

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK
		) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	glutDisplayFunc(drawScene); // 출력 콜백함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 콜백함수 지정
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백함수 지정
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop(); // 이벤트 처리 시작
}

GLvoid drawScene() {
	//--- 콜백 함수: 그리기 콜백 함수 
	glClearColor(Brgb.R, Brgb.G, Brgb.B, 1.0f); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다
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

	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Keyboard(unsigned char key, int x, int y) {
	if(key == 'r' ||key == 'R')
		init_sub();
	glutPostRedisplay();
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수 
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