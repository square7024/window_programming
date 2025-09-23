#include <iostream>
#include <random>
#include <gl/glew.h>											//--- �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

struct Square {
	float x1, y1, x2, y2;
	float r, g, b;
	float scale{ 0.1f };
};

struct Square s[30];
int s_i{ 0 };

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> urd(0.0f, 1.0f);
std::uniform_real_distribution<float> urd_xy(-1.0f, 1.0f);

GLvoid randomize_color(Square& s) {
	s.r = urd(gen);
	s.g = urd(gen);
	s.b = urd(gen);
}

GLvoid randomize_xy(Square& s) {
	s.x1 = urd_xy(gen);
	s.y1 = urd_xy(gen);
	s.x2 = s.x1 + s.scale;
	s.y2 = s.y1 + s.scale;
}

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid draw_square(Square& s);

void main(int argc, char** argv)								//--- ������ ����ϰ� �ݹ��Լ� ���� 
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);										// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);				// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);							// �������� ��ġ ����
	glutInitWindowSize(800, 800);								// �������� ũ�� ����
	glutCreateWindow("Practice_03");								// ������ ����(������ �̸�)

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
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMainLoop();												// �̺�Ʈ ó�� ����
}

GLvoid drawScene() {												//--- �ݹ� �Լ�: ��� �ݹ� �Լ� 
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);						// �������� ��blue���� ����
	glClear(GL_COLOR_BUFFER_BIT);								// ������ ������ ��ü�� ĥ�ϱ�
	
	for (int i = 0; i < s_i; ++i) {
		glColor3f(s[i].r, s[i].g, s[i].b);
		draw_square(s[i]);
	}

	glutSwapBuffers();											// ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) {									//--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a' :
		if (s_i < 10) {
			randomize_color(s[s_i]);
			randomize_xy(s[s_i]);
			++s_i;
		}
		else {
			std::cout << "�簢���� 10�� ���� ���� ����" << std::endl;
		}
		break;
	case 'q' :
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

GLvoid Mouse(int button, int state, int x, int y) {

}

GLvoid draw_square(Square &s) {
	glRectf(s.x1, s.y1, s.x2, s.y2);
}