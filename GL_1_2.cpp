#include <iostream>
#include <gl/glew.h>											//--- 필요한 헤더파일 include
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

int main(int argc, char** argv)								//--- 윈도우 출력하고 콜백함수 설정 
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);										// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);				// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);							// 윈도우의 위치 지정
	glutInitWindowSize(500, 500);								// 윈도우의 크기 지정
	glutCreateWindow("Practice_2");								// 윈도우 생성(윈도우 이름)

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {								// glew 초기화 
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	glutDisplayFunc(drawScene);									// 출력 함수의 지정
	glutReshapeFunc(Reshape);									// 다시 그리기 함수 지정
	glutMouseFunc(Mouse);
	glutMainLoop();												// 이벤트 처리 시작
}

GLvoid drawScene() {												//--- 콜백 함수: 출력 콜백 함수 
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);						// 바탕색을 ‘blue’로 지정
	glClear(GL_COLOR_BUFFER_BIT);								// 설정된 색으로 전체를 칠하기
	
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

	glutSwapBuffers();											// 화면에 출력하기
}

GLvoid Reshape(int w, int h) {									//--- 콜백 함수: 다시 그리기 콜백 함수 
	glViewport(0, 0, w, h);
}

GLvoid draw_square(const Square& s) {
	glRectf(s.x1, s.y1, s.x2, s.y2);
}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {					// 좌클릭

	}
	else if (button == GLUT_RIGHT_BUTTON) {				// 우클릭

	}
	glutPostRedisplay();
}