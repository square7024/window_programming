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
	{  0.0f,  0.0f, 1.0f, 1.0f,    1.0f,0.0f,0.0f },
	{ -1.0f,  0.0f, 0.0f, 1.0f,    0.0f,1.0f,0.0f },
	{ -1.0f, -1.0f, 0.0f, 0.0f,    0.0f,0.0f,1.0f },
	{  0.0f, -1.0f, 1.0f, 0.0f,    1.0f,1.0f,0.0f }
};

float bgR = 1.0f, bgG = 1.0f, bgB = 1.0f;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> urd(0.0f, 1.0f);

GLvoid randomizeColor(Square& s) {
	s.r = urd(gen);
	s.g = urd(gen);
	s.b = urd(gen);
}

GLvoid randomizeBGColor() {
	bgR = urd(gen);
	bgG = urd(gen);
	bgB = urd(gen);
}

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid draw_square(const Square& s);
bool pointInSquare(float nx, float ny, const Square& s);
int quadrantOf(float nx, float ny);

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
	glClearColor(bgR, bgG, bgB, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);								// 설정된 색으로 전체를 칠하기
	
	for (int i = 0; i < 4; i++) draw_square(s[i]);												
	
	glutSwapBuffers();											// 화면에 출력하기
}

GLvoid Reshape(int w, int h) {									//--- 콜백 함수: 다시 그리기 콜백 함수 
	glViewport(0, 0, w, h);
}

GLvoid draw_square(const Square& s) {
	float cx = 0.5f * (s.x1 + s.x2);
	float cy = 0.5f * (s.y1 + s.y2);
	float x1 = cx + (s.x1 - cx) * s.scale;
	float y1 = cy + (s.y1 - cy) * s.scale;
	float x2 = cx + (s.x2 - cx) * s.scale;
	float y2 = cy + (s.y2 - cy) * s.scale;

	glColor3f(s.r, s.g, s.b);
	glRectf(x1, y1, x2, y2);
}

bool pointInSquare(float nx, float ny, const Square& s) {
	float cx = 0.5f * (s.x1 + s.x2);
	float cy = 0.5f * (s.y1 + s.y2);
	float x1 = cx + (s.x1 - cx) * s.scale;
	float x2 = cx + (s.x2 - cx) * s.scale;
	float y1 = cy + (s.y1 - cy) * s.scale;
	float y2 = cy + (s.y2 - cy) * s.scale;

	if (x1 > x2) std::swap(x1, x2);
	if (y1 > y2) std::swap(y1, y2);

	return (nx >= x1 && nx <= x2 && ny >= y1 && ny <= y2);
}

int quadrantOf(float nx, float ny) {
	// Q1: 0 0, Q2: 1 0, Q3: 2 2, Q4: 3
	if (nx >= 0.0f && ny >= 0.0f) return 0; // Q1 (오른쪽 위)
	if (nx < 0.0f && ny >= 0.0f) return 1; // Q2 (왼쪽 위)
	if (nx < 0.0f && ny < 0.0f) return 2; // Q3 (왼쪽 아래)
	return 3;                                // Q4 (오른쪽 아래)
}

GLvoid Mouse(int button, int state, int x, int y) {
	if (state != GLUT_DOWN) return;

	float nx = (x / 500.0f) * 2.0f - 1.0f;
	float ny = 1.0f - (y / 500.0f) * 2.0f;

	int hit = -1;
	for (int i = 0; i < 4; i++) {
		if (pointInSquare(nx, ny, s[i])) {
			hit = i;
			break;
		}
	}

	const float shrinkStep = 0.08f;
	const float growStep = 0.08f;
	const float minScale = 0.4f;
	
	if (button == GLUT_LEFT_BUTTON) {
		if (hit >= 0) {
			// 사각형 내부: 해당 사각형 색 랜덤
			randomizeColor(s[hit]);
		}
		else {
			// 외부: 배경색 랜덤
			randomizeBGColor();
		}
	}
	else if (button == GLUT_RIGHT_BUTTON) {
		if (hit >= 0) {
			// 내부: 해당 사각형 축소
			s[hit].scale = std::max(minScale, s[hit].scale - shrinkStep);
		}
		else {
			// 외부: 모든 사각형 확대 (최대 1.0)
			int q = quadrantOf(nx, ny);
			s[q].scale = std::min(1.0f, s[q].scale + growStep);
		}
		
	}

	glutPostRedisplay();
}
