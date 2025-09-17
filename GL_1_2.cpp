#include <iostream>
#include <gl/glew.h>											//--- �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>

struct Square {
	float x1, y1, x2, y2;
	float r, g, b;
	float scale = 1.0f;
};

struct Square s[4] = {
	{ 0.25, 0.25, 0.75, 0.75,      1.0f,0.0f,0.0f },
	{ -0.25, -0.25, 0.75, 0.75,    0.0f,1.0f,0.0f },
	{ -0.25, -0.25, -0.75, -0.75,  0.0f,0.0f,1.0f },
	{ 0.25, 0.25, -0.75, -0.75,    1.0f,1.0f,0.0f }
};

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> urd(0.0f, 1.0f);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid draw_square(const Square& s);

int main(int argc, char** argv)								//--- ������ ����ϰ� �ݹ��Լ� ���� 
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);										// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);				// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);							// �������� ��ġ ����
	glutInitWindowSize(500, 500);								// �������� ũ�� ����
	glutCreateWindow("Practice_2");								// ������ ����(������ �̸�)

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {								// glew �ʱ�ȭ 
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	glutDisplayFunc(drawScene);									// ��� �Լ��� ����
	glutReshapeFunc(Reshape);									// �ٽ� �׸��� �Լ� ����
	glutMouseFunc(Mouse);
	glutMainLoop();												// �̺�Ʈ ó�� ����
}

GLvoid drawScene() {												//--- �ݹ� �Լ�: ��� �ݹ� �Լ� 
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);						// �������� ��blue���� ����
	glClear(GL_COLOR_BUFFER_BIT);								// ������ ������ ��ü�� ĥ�ϱ�
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(0, 0, 1, 1);
	glColor3f(0.0f, 1.0f, 0.0f);
	glRectf(0, 0, -1, 1);
	glColor3f(0.0f, 0.0f, 1.0f);
	glRectf(0, 0, -1, -1);
	glColor3f(1.0f, 1.0f, 0.0f);
	glRectf(0, 0, 1, -1);

	glColor3f(0.5f, 0.0f, 0.0f);
	draw_square(s[0]);

	glutSwapBuffers();											// ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) {									//--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
	glViewport(0, 0, w, h);
}

GLvoid draw_square(const Square& s) {
	glRectf(s.x1, s.y1, s.x2, s.y2);
}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {					// ��Ŭ��

	}
	else if (button == GLUT_RIGHT_BUTTON) {				// ��Ŭ��

	}
	glutPostRedisplay();
}