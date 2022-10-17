#include <iostream>
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <stdlib.h>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void TimerFunction(int value);
void Move_diagonal();
void Move_zigzag();
void Change_size();

typedef struct RGB {
	GLfloat R, G, B;
}RGB;

typedef struct rectangle {
	GLfloat x1, x2, y1, y2;
	GLfloat originx1, originx2, originy1, originy2;
	RGB rgb;
	BOOL view,xmove,ymove;
	int Zigzag,change;
}Rectanglea;

RGB Brgb = { 0.8,0.8,0.8 };
Rectanglea ra[5] = { 0 };
int top = 0;
int select = -1;
int movestyle = 0;

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("Example1"); // 윈도우 생성(윈도우 이름) //--- GLEW 초기화하기

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
	for (int i = 0; i < top; i++) {
		glColor3f(ra[i].rgb.R, ra[i].rgb.G, ra[i].rgb.B);
		glRectf(ra[i].x1, ra[i].y1, ra[i].x2, ra[i].y2);
	}

	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	glutPostRedisplay();
	switch (key) {
	case 'a':
		glutTimerFunc(10, TimerFunction, 1);
		movestyle = 1;
		break;
	case 'i':
		for (int i = 0; i <= top - 1; i++) {
			ra[i].Zigzag = rand() % 2;
		}
		glutTimerFunc(10, TimerFunction, 1);
		movestyle = 2;
		break;
	case 'c':
		for (int i = 0; i <= top - 1; i++) {
			ra[i].change = 0;
		}
		glutTimerFunc(10, TimerFunction, 1);
		movestyle = 3;
		break;
	case's':
		movestyle = 0;
		break;
	case 'm':
		for (int i = 0; i <= top - 1; i++) {
			ra[i].x1 = ra[i].originx1,ra[i].x2 = ra[i].originx2;
			ra[i].y1 = ra[i].originy1, ra[i].y2 = ra[i].originy2;
		}
		break;
	case 'r':
		top = 0;
		break;
	case 'q':
		exit(0);
		break;
	}
	

}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수 
{
	glViewport(0, 0, w, h);
}

void Mouse(int button, int state, int x, int y) {
	srand(time(NULL));
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (top < 5) {
			ra[top].x1 = ra[top].originx1 = (float)(x - 400) / 40 / 10 - 0.05;
			ra[top].x2 = ra[top].originx2 = (float)(x - 400) / 40 / 10 + 0.05;
			ra[top].y1 = ra[top].originy1 = (float)(300 - y) / 30 / 10 - 0.05;
			ra[top].y2 = ra[top].originy2 = (float)(300 - y) / 30 / 10 + 0.05;
			ra[top].rgb.R = (float)(rand() % 11) / 10;
			ra[top].rgb.G = (float)(rand() % 11) / 10;
			ra[top].rgb.B = (float)(rand() % 11) / 10;
			top++;
		}
	}
	//else if (select != -1 && state == GLUT_UP)
	//	select = -1;
}

void Motion(int x, int y) {
	/*if (select != -1) {
		ra[select].x1 += ((float)(x - prevxy[0]) / 400);
		ra[select].x2 += ((float)(x - prevxy[0]) / 400);
		ra[select].y1 -= ((float)(y - prevxy[1]) / 300);
		ra[select].y2 -= ((float)(y - prevxy[1]) / 300);
		prevxy[0] = x;
		prevxy[1] = y;
	}
	glutPostRedisplay();*/
}

 {
	glutPostRedisplay(); // 화면 재 출력
	switch (movestyle) {
	case 1:
		Move_diagonal();
		break;
	case 2:
		Move_zigzag();
		break;
	case 3:
		Change_size();
		break;
	}
	if (movestyle)
		glutTimerFunc(10, TimerFunction, 1);
}

void Move_diagonal(){
	for (int i = 0; i <= top - 1; i++) {
		if (ra[i].xmove) {
			ra[i].x1 += 0.01, ra[i].x2 += 0.01;

			if (ra[i].x2 * 400 + 400 >= 800)
				ra[i].xmove = FALSE;
		}
		else {
			ra[i].x1 -= 0.01, ra[i].x2 -= 0.01;
			if (ra[i].x1 * 400 + 400 <= 0)
				ra[i].xmove = TRUE;
		}

		if(ra[i].ymove) {
			ra[i].y1 += 0.01, ra[i].y2 += 0.01;
			if(300 - ra[i].y2 * 300 <=0)
				ra[i].ymove = FALSE;
		}
		else {
		ra[i].y1 -= 0.01, ra[i].y2 -= 0.01;
		if (300 - ra[i].y1 * 300 >= 600)
			ra[i].ymove = TRUE;
		}
	}
}

void Move_zigzag() {
	for (int i = 0; i <= top - 1; i++) {
		switch (ra[i].Zigzag) {
		case 0:
			if (ra[i].xmove) {
				ra[i].x1 += 0.01, ra[i].x2 += 0.01;

				if (ra[i].x2 * 400 + 400 >= 800)
					ra[i].xmove = FALSE;
			}
			else {
				ra[i].x1 -= 0.01, ra[i].x2 -= 0.01;
				if (ra[i].x1 * 400 + 400 <= 0)
					ra[i].xmove = TRUE;
			}
			break;
		case 1:
			if (ra[i].ymove) {
				ra[i].y1 += 0.01, ra[i].y2 += 0.01;
				if (300 - ra[i].y2 * 300 <= 0)
					ra[i].ymove = FALSE;
			}
			else {
				ra[i].y1 -= 0.01, ra[i].y2 -= 0.01;
				if (300 - ra[i].y1 * 300 >= 600)
					ra[i].ymove = TRUE;
			}
			break;
		}
	}
}

void Change_size() {
	for (int i = 0; i <= top - 1; i++) {
		switch (ra[i].change) {
		case 0:case 1:case 2:case 3:case 4:case 5:
			if (ra[i].xmove) {
				ra[i].x1 += 0.01, ra[i].x2 -= 0.01;
			}
			else {
				ra[i].x1 -= 0.01, ra[i].x2 += 0.01;
			}

			if (ra[i].ymove) {
				ra[i].y1 -= 0.01, ra[i].y2 += 0.01;
			}
			else {
				ra[i].y1 += 0.01, ra[i].y2 -= 0.01;
			}
			break;
		case 6: case 7: case 8: case 9: case 10:case 11:
			if (ra[i].xmove) {
				ra[i].x1 -= 0.01, ra[i].x2 += 0.01;
			}
			else {
				ra[i].x1 += 0.01, ra[i].x2 -= 0.01;
			}

			if (ra[i].ymove) {
				ra[i].y1 += 0.01, ra[i].y2 -= 0.01;
			}
			else {
				ra[i].y1 -= 0.01, ra[i].y2 += 0.01;
			}
		}
		ra[i].change = (ra[i].change + 1) % 12;
	}
}