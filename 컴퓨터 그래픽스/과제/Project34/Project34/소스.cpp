#include <iostream>
#include <gl/glew.h> // �ʿ��� ������� include
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

GLchar* vertexsource, * fragmentsource; //--- �ҽ��ڵ� ���� ����
GLuint vertexshader, fragmentshader; //--- ���̴� ��ü
GLuint s_program;
GLint result;

GLuint vao, vbo[2], EBO[2];
float a = 0.0,yrotation = 0.0,rotation = 0,Frotation = 0;
BOOL yroatating1 = false, yroatating2 = false,Tani = false,fani = false,Fani = false;

float vPositionList[] = {
0.5f, 0.5f, 0.5f, // �� ���� ���
0.5f, 0.5f, -0.5f, // �� ���� ���
-0.5f, 0.5f, -0.5f, // �� ���� ���
-0.5f, 0.5f, 0.5f, // �� ���� ���
-0.5f,-0.5f,0.5f, // �� ���� �ϴ�
-0.5f,-0.5f,-0.5f,	// �� ���� �ϴ�
0.5f,-0.5f,-0.5f,	// �� ���� �ϴ�
0.5f,-0.5f,0.5f,		// �� ���� �ϴ�
};

unsigned int index[] = {
3, 1, 0, // ù ��° �ﰢ��			// �� �簢��
2, 1, 3, // �� ��° �ﰢ��
4, 5, 2,									// ���� �簢��
2, 3, 4,
7, 0, 6,							// ������ �簢��
1, 6, 0,
4, 3, 7,							// �� �簢��
0, 7, 3,
5, 6, 2,								// �� �簢��
2, 6, 1,
7, 6, 4,	// �� ��° �ﰢ��			// �Ʒ� �簢��
4, 6, 5,	// �� ��° �ﰢ��
8,9,
10,11,
12,13
};

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example1");
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;

	glewInit();
	InitShader();
	InitBuffer();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ��Լ� ����
	//glutSpecialFunc(SKeyboard);
	glutTimerFunc(50, TimerFunction, 1);
	glutMainLoop();
}

void make_vertexShader() {
	vertexsource = filetobuf("vertex.glsl");//--- ���ؽ� ���̴� ��ü �����
	vertexshader = glCreateShader(GL_VERTEX_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);
	//--- ���ؽ� ���̴� �������ϱ�
	glCompileShader(vertexshader);
	//--- �������� ����� ���� ���� ���: ���� üũ
	GLchar errorLog[512];
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}

void make_fragmentShader() {
	fragmentsource = filetobuf("fragment.glsl");
	//--- �����׸�Ʈ ���̴� ��ü �����
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);
	//--- �����׸�Ʈ ���̴� ������
	glCompileShader(fragmentshader);
	//--- �������� ����� ���� ���� ���: ������ ���� üũ
	GLchar errorLog[512];
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}

void InitShader()
{
	make_vertexShader(); //--- ���ؽ� ���̴� �����
	make_fragmentShader(); //--- �����׸�Ʈ ���̴� �����
	//-- shader Program
	s_program = glCreateProgram();
	glAttachShader(s_program, vertexshader);
	glAttachShader(s_program, fragmentshader);
	glLinkProgram(s_program);

	GLchar errorLog[512];
	if (!result)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader ������ ����\n" << errorLog << std::endl;
		return;
	}
	//--- ���̴� �����ϱ�
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
	//--- Shader Program ����ϱ�
	glUseProgram(s_program);
}

void InitBuffer()
{
	glGenVertexArrays(1, &vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
	glBindVertexArray(vao); //--- VAO�� ���ε��ϱ�
	glGenBuffers(2, vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
	//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vPositionList), vPositionList, GL_STATIC_DRAW);
	glGenBuffers(1, &EBO[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]); //--- GL_ELEMENT_ARRAY_BUFFER ���� �������� ���ε�
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
}

void drawScene() {
	glUseProgram(s_program);
	glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	glm::mat4 Prev_rotation = glm::mat4(1.0f);

	//glm::mat4 projection = glm::mat4(1.0f);
	//projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f); //--- ���� ������ [-100.0, 100.0] �������� ����
	//unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform"); //--- ���� ��ȯ �� ����
	//glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -2.0)); //--- ������ �ణ �ڷ� �̷���
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform"); //--- ���� ��ȯ �� ����
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	glm::vec3 cameraPos = glm::vec3(a, 0.0f, 1.0f);
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ����
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����
	glm::mat4 view = glm::mat4(1.0f);

	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- ���� ��ȯ ����
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 yro = glm::mat4(1.0f);
	glm::mat4 Tx = glm::mat4(1.0f);
	glm::mat4 mi = glm::mat4(1.0f);

	Prev_rotation = glm::rotate(Prev_rotation, glm::radians(20.0f), glm::vec3(1.0, 0.0, 0.0)); //--- z�࿡ ���Ͽ� ȸ�� ���
	Prev_rotation = glm::rotate(Prev_rotation, glm::radians(yrotation+20.0f), glm::vec3(0.0, 1.0, 0.0)); //--- z�࿡ ���Ͽ� ȸ�� ���
	TR = Prev_rotation * TR;
	unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��ȯ �� �����ϱ�


	unsigned int modelLocation1 = glGetUniformLocation(s_program, "in_Color"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glBindVertexArray(vao);
	/*glDrawArrays(GL_TRIANGLES, 0, 3);*/
	//for (int i = 6; i < 36; i = i + 3) {
	//	glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * i));
	//}

	TR = glm::mat4(1.0f);
	glm::mat4 Tx2 = glm::mat4(1.0f);
	yro = glm::rotate(yro, glm::radians(rotation), glm::vec3(1.0, 0.0, 0.0)); //--- z�࿡ ���Ͽ� ȸ�� ���

	Tx = glm::translate(Tx, glm::vec3(0.0, -0.5, 0.0));
	Tx2 = glm::translate(Tx, glm::vec3(0.0, 1.0, 0.0));
	TR = Tx2 * Prev_rotation * yro * Tx * TR;

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��ȯ �� �����ϱ�
	glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 0));
	glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 3));

	TR = glm::mat4(1.0f);
	yro = glm::mat4(1.0f);
	yro = glm::rotate(yro, glm::radians(Frotation), glm::vec3(1.0, 0.0, 0.0)); //--- z�࿡ ���Ͽ� ȸ�� ���
	Tx = glm::translate(Tx, glm::vec3(-0.5, 0.0, 0.0));

	TR = Prev_rotation * TR;

	/*Tx = glm::translate(Tx, glm::vec3(1.0, 0.0, 0.0));

	TR = Tx * TR;*/

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��ȯ �� �����ϱ�
	glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 18));
	glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 21));
	
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
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
	if (yroatating1) {
		yrotation += 1;
	}
	else if (yroatating2) {
		yrotation -= 1;
	}

	if (Tani) {
		rotation += 1;
	}
	glutTimerFunc(50, TimerFunction, 1);
	glutPostRedisplay();
}

GLvoid Keyboard(unsigned char key, int x, int y) {
	if (key == 'y') {
		yroatating2 = true;
		yroatating1 = false;
	}
	else if(key == 'Y') {
		yroatating1 = true;
		yroatating2 = false;
	}
	else if (key == 't') {
		Tani = true;
	}
	else if (key == 'T') {
		Tani = false;
	}
	glutPostRedisplay();
}