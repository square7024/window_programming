#include <iostream>
#include <random>
#include <gl/glew.h>											//--- 필요한 헤더파일 include
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

void main(int argc, char** argv)								//--- 윈도우 출력하고 콜백함수 설정 
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);										// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);				// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);							// 윈도우의 위치 지정
	glutInitWindowSize(800, 800);								// 윈도우의 크기 지정
	glutCreateWindow("Practice_03");								// 윈도우 생성(윈도우 이름)

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
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMainLoop();												// 이벤트 처리 시작
}

GLvoid drawScene() {												//--- 콜백 함수: 출력 콜백 함수 
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);						// 바탕색을 ‘blue’로 지정
	glClear(GL_COLOR_BUFFER_BIT);								// 설정된 색으로 전체를 칠하기
	
	for (int i = 0; i < s_i; ++i) {
		glColor3f(s[i].r, s[i].g, s[i].b);
		draw_square(s[i]);
	}

	glutSwapBuffers();											// 화면에 출력하기
}

GLvoid Reshape(int w, int h) {									//--- 콜백 함수: 다시 그리기 콜백 함수 
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
			std::cout << "사각형은 10개 까지 생성 가능" << std::endl;
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