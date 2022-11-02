#include <iostream>
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

void make_vertexShader();
void make_fragmentShader();
void InitBuffer();
void InitShader();
void TimerFunction(int value);
//void SKeyboard(int key, int x, int y);
GLvoid Reshape(int w, int h);
GLvoid drawScene();
GLvoid Keyboard(unsigned char key, int x, int y);
char* filetobuf(const char* file);
int ymoving = 0;

typedef struct Figure {
	int type;
	float xrotating, yrotating;
	float xrevolution, yrevolution;
	float xmove, ymove,zmove;
}Figure;

GLchar* vertexsource, * fragmentsource; //--- 소스코드 저장 변수
GLuint vertexshader, fragmentshader; //--- 세이더 객체
GLuint s_program;
GLint result;
glm::vec3 Color, Color1;

GLuint vao, vbo[2], EBO[2], linevbo[2], linevao;
GLuint Pointvao, Pointvbo[2];
int vertexCount = 36, indexCount = 0, xradian_move = 0, yradian_move = 0,Tanimation = -1,fanimation = -1;
BOOL Draw = true, Culling = false;
GLUquadricObj* qobj = gluNewQuadric();
Figure figure[2] = { {0,10,10,0,0,0.5,0,0},{1,10,10,0,0,-0.5,0,0} };
float Scale[2][2] = { {1.0,1.0},{1.0,1.0} };
float OriginRect[2][3] = { {0.0,0.0,0.0},{0.0,0.0,0.0} };

float vPositionList[] = {
0.05f, 0.05f, 0.05f, // 앞 우측 상단
0.05f, 0.05f, -0.05f, // 뒤 우측 상단
-0.05f, 0.05f, -0.05f, // 뒤 좌측 상단
-0.05f, 0.05f, 0.05f, // 앞 좌측 상단
-0.05f,-0.05f,0.05f, // 앞 좌측 하단
-0.05f,-0.05f,-0.05f,	// 뒤 좌측 하단
0.05f,-0.05f,-0.05f,	// 뒤 우측 하단
0.05f,-0.05f,0.05f,		// 앞 우측 하단
};

unsigned int index[] = {
3, 1, 0, // 첫 번째 삼각형			// 위 사각형
2, 1, 3, // 두 번째 삼각형
4, 5, 2,									// 왼쪽 사각형
2, 3, 4,
7, 0, 6,							// 오른쪽 사각형
1, 6, 0,
4, 3, 7,							// 앞 사각형
0, 7, 3,
5, 6, 2,								// 뒤 사각형
2, 6, 1,
7, 6, 4,	// 세 번째 삼각형			// 아래 사각형
4, 6, 5,	// 네 번째 삼각형
8,9,
10,11,
12,13
};

float line[]{
1.0f,0.0f,0.0f,
-1.0f,0.0f,0.0f,
0.0f,1.0f,0.0f,
0.0f,-1.0f,0.0f,
0.0f,0.0f,1.0f,
0.0f,0.0f,-1.0f
};

GLfloat point[2001][3] = { {0.0,0.0,0.0} };

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example1");
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;

	glewInit();
	InitShader();
	InitBuffer();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백함수 지정
	//glutSpecialFunc(SKeyboard);
	glutTimerFunc(50, TimerFunction, 1);
	glutMainLoop();
}

void make_vertexShader() {
	vertexsource = filetobuf("vertex.glsl");//--- 버텍스 세이더 객체 만들기
	vertexshader = glCreateShader(GL_VERTEX_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);
	//--- 버텍스 세이더 컴파일하기
	glCompileShader(vertexshader);
	//--- 컴파일이 제대로 되지 않은 경우: 에러 체크
	GLchar errorLog[512];
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

void make_fragmentShader() {
	fragmentsource = filetobuf("fragment.glsl");
	//--- 프래그먼트 세이더 객체 만들기
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);
	//--- 프래그먼트 세이더 컴파일
	glCompileShader(fragmentshader);
	//--- 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크
	GLchar errorLog[512];
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

void InitBuffer()
{
	glGenVertexArrays(1, &vao); //--- VAO 를 지정하고 할당하기
	glBindVertexArray(vao); //--- VAO를 바인드하기
	glGenBuffers(2, vbo); //--- 2개의 VBO를 지정하고 할당하기
	//--- 1번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vPositionList), vPositionList, GL_STATIC_DRAW);
	glGenBuffers(1, &EBO[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glGenVertexArrays(1, &linevao); //--- VAO 를 지정하고 할당하기
	glBindVertexArray(linevao); //--- VAO를 바인드하기
	glGenBuffers(2, linevbo); //--- 2개의 VBO를 지정하고 할당하기
	glBindBuffer(GL_ARRAY_BUFFER, linevbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenVertexArrays(1, &Pointvao); //--- VAO 를 지정하고 할당하기
	glBindVertexArray(Pointvao); //--- VAO를 바인드하기
	glGenBuffers(2, Pointvbo); //--- 2개의 VBO를 지정하고 할당하기
	glBindBuffer(GL_ARRAY_BUFFER, Pointvbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

}

void InitShader()
{
	make_vertexShader(); //--- 버텍스 세이더 만들기
	make_fragmentShader(); //--- 프래그먼트 세이더 만들기
	//-- shader Program
	s_program = glCreateProgram();
	glAttachShader(s_program, vertexshader);
	glAttachShader(s_program, fragmentshader);
	glLinkProgram(s_program);

	GLchar errorLog[512];
	if (!result)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
	//--- 세이더 삭제하기
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
	//--- Shader Program 사용하기
	glUseProgram(s_program);
}

void drawScene()
{
	glUseProgram(s_program);
	glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);


	glm::mat4 Line = glm::mat4(1.0f);
	unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Line)); //--- modelTransform 변수에 변환 값 적용하기
	glBindVertexArray(linevao);
	glDrawArrays(GL_LINES, 2, 2);

	Line = glm::rotate(Line, glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0)); //--- z축에 대하여 회전 행렬
	Line = glm::rotate(Line, glm::radians(10.0f), glm::vec3(0.0, 1.0, 0.0)); //--- z축에 대하여 회전 행렬

	Line = glm::rotate(Line, glm::radians(figure[0].yrevolution), glm::vec3(0.0, 1.0, 0.0)); //--- z축에 대하여 회전 행렬
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Line)); //--- modelTransform 변수에 변환 값 적용하기

	glDrawArrays(GL_LINES, 0, 2);
	glDrawArrays(GL_LINES, 4, 2);

	glBindVertexArray(Pointvao);
	for (int i = 0; i < 2000; i++) {
		glm::mat4 Point = glm::mat4(1.0f);
		Point = glm::rotate(Line, glm::radians((float)i), glm::vec3(0.0, 1.0, 0.0)); //--- z축에 대하여 회전 행렬
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Point)); //--- modelTransform 변수에 변환 값 적용하기
		glDrawArrays(GL_POINTS, i, 1);
	}

	for (int j = 0; j < 2; j++) {
		glm::mat4 Tx = glm::mat4(1.0f); //--- 이동 행렬 선언
		glm::mat4 rotating = glm::mat4(1.0f); //--- 회전 행렬 선언
		glm::mat4 revolution = glm::mat4(1.0f); //--- 회전 행렬 선언
		glm::mat4 TR = glm::mat4(1.0f);
		glm::mat4 scaleMatrix1 = glm::mat4(1.0f);
		glm::mat4 scaleMatrix2 = glm::mat4(1.0f);


		//--- 적용할 모델링 변환 행렬 만들기
		scaleMatrix1 = glm::scale(scaleMatrix1, glm::vec3(Scale[j][0], Scale[j][0], Scale[j][0]));
		Tx = glm::translate(Tx, glm::vec3(figure[j].xmove, figure[j].ymove, figure[j].zmove));

		scaleMatrix2 = glm::scale(scaleMatrix2, glm::vec3(Scale[j][1], Scale[j][1], Scale[j][1]));

		revolution = glm::rotate(revolution, glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0)); //--- z축에 대하여 회전 행렬

		revolution = glm::rotate(revolution, glm::radians(figure[j].yrevolution + 10), glm::vec3(0.0, 1.0, 0.0)); //--- z축에 대하여 회전 행렬

		TR = revolution * scaleMatrix2 * Tx * scaleMatrix1;

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기

		unsigned int modelLocation1 = glGetUniformLocation(s_program, "in_Color"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
		glUniform3f(modelLocation1, Color[0], Color[1], Color[2]);


		//--- 도형 그리기

		if (figure[j].type == 0) {
			for (int i = 0; i < vertexCount; i = i + 3) {
				glBindVertexArray(vao);
				glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * i));
			}
		}
		else if (figure[j].type == 1) {
			gluQuadricDrawStyle(qobj, GLU_LINE);
			gluSphere(qobj, 0.05, 10, 10);
		}
	}

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading 
	if (!fptr) // Return NULL on failure 
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file 
	length = ftell(fptr); // Find out how many bytes into the file we are 
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator 
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file 
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer 
	fclose(fptr); // Close the file 
	buf[length] = 0; // Null terminator 
	return buf; // Return the buffer 
}

void TimerFunction(int value) {

	if (Tanimation != -1) {
		if (Tanimation < 50) {
			for (int i = 0; i < 2; i++) {
				figure[i].xmove -= OriginRect[i][0] / 50, figure[i].ymove -= OriginRect[i][1] / 50, figure[i].zmove -= OriginRect[i][2] / 50;
			}
			Tanimation++;
		}
		else if (Tanimation < 100) {
			for (int i = 0; i < 2; i++) {
				figure[i].xmove += OriginRect[i][0] / 50, figure[i].ymove += OriginRect[i][1] / 50, figure[i].zmove += OriginRect[i][2] / 50;
			}
			Tanimation++;
		}
		else if (Tanimation == 100) {
			Tanimation = -1;
		}
	}
	else if (fanimation != -1) {
		if (fanimation < 100) {
			for (int i = 0; i < 2; i++) {
				figure[i].xmove -= OriginRect[i][0] / 100, figure[i].ymove -= OriginRect[i][1] / 100, figure[i].zmove -= OriginRect[i][2] / 100;
			}
			fanimation++;
		}
		else if (fanimation == 100) {
			fanimation = -1;
		}
	}
	glutTimerFunc(50, TimerFunction, 1);
	glutPostRedisplay();
}

GLvoid Keyboard(unsigned char key, int x, int y) {
	srand(time(NULL));
	if (key == 'x') {
		figure[1].xmove += 0.01;
		figure[0].xmove -= 0.01;
	}
	else if (key == 'X') {
		figure[1].xmove -= 0.01;
		figure[0].xmove += 0.01;
	}
	else if (key == 'y') {
		figure[1].ymove += 0.01;
		figure[0].ymove -= 0.01;
	}
	else if (key == 'Y') {
		figure[1].ymove -= 0.01;
		figure[0].ymove += 0.01;
	}
	else if (key == 'z') {
		figure[1].zmove += 0.01;
		figure[0].zmove -= 0.01;
	}
	else if (key == 'Z') {
		figure[1].zmove -= 0.01;
		figure[0].zmove += 0.01;
	}
	else if (key == 'q') {
		figure[0].xmove += 0.01;
	}
	else if (key == 'Q') {
		figure[0].xmove -= 0.01;
	}
	else if (key == 'w') {
		figure[0].ymove += 0.01;
	}
	else if (key == 'W') {
		figure[0].ymove -= 0.01;
	}
	else if (key == 'e') {
		figure[0].zmove += 0.01;
	}
	else if (key == 'E') {
		figure[0].zmove -= 0.01;
	}
	else if (key == 'a') {
		figure[1].xmove += 0.01;
	}
	else if (key == 'A') {
		figure[1].xmove -= 0.01;
	}
	else if (key == 's') {
		figure[1].ymove += 0.01;
	}
	else if (key == 'S') {
		figure[1].ymove -= 0.01;
	}
	else if (key == 'd') {
		figure[1].zmove += 0.01;
	}
	else if (key == 'D') {
		figure[1].zmove -= 0.01;
	}
	else if (key == 'u') {
		Scale[0][0] += 0.1;
	}
	else if (key == 'U') {
		Scale[0][0] -= 0.1;
	}
	else if (key == 'i') {
		Scale[0][1] += 0.1;
	}
	else if (key == 'I') {
		Scale[0][1] -= 0.1;
	}
	else if (key == 'h') {
		Scale[0][0] += 0.1;
	}
	else if (key == 'H') {
		Scale[0][0] -= 0.1;
	}
	else if (key == 'j') {
		Scale[0][1] += 0.1;
	}
	else if (key == 'J') {
		Scale[0][1] -= 0.1;
	}
	else if (key == 'r') {
		float r = 0;
		for (int i = 0; i < 2000; i++) {
			point[i][0] = r;
			r += 0.0005;
		}
		InitBuffer();
	}
	else if (key == 't') {
		OriginRect[0][0] = figure[0].xmove, OriginRect[0][1] = figure[0].ymove, OriginRect[0][2] = figure[0].zmove;
		OriginRect[1][0] = figure[1].xmove, OriginRect[1][1] = figure[1].ymove, OriginRect[1][2] = figure[1].zmove;
		Tanimation = 0;
	}
	else if (key == 'f') {
		OriginRect[0][0] = figure[0].xmove - figure[1].xmove, OriginRect[0][1] = figure[0].ymove - figure[1].ymove, OriginRect[0][2] = figure[0].zmove - figure[1].zmove;
		OriginRect[1][0] = figure[1].xmove - figure[0].xmove, OriginRect[1][1] = figure[1].ymove - figure[0].ymove, OriginRect[1][2] = figure[1].zmove - figure[0].zmove;
		fanimation = 0;
	}
}