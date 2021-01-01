#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

#include <array>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

static int WIN_WIDTH = 800;
static int WIN_HEIGHT = 600;

GLint dragged = -1;
GLdouble updateFrequency = 0.01, lastUpdate;

bool enterpressed = 0;
static std::vector<glm::vec3> myPoints = {
			glm::vec3(-0.9f, 0.8f, 0.0f),
			glm::vec3(-0.8f, 0.1f, 0.0f),
			glm::vec3(-0.3f, -0.1f, 0.0f),

			glm::vec3(0.0f, 0.1f, 0.0f),
			//glm::vec3(myPoints[3].x + (myPoints[3].x - myPoints[2].x), myPoints[3].y + (myPoints[3].y - myPoints[2].y), 0.0f),
			//myPoints[3] + (myPoints[5] - myPoints[3])/4,
			//glm::vec3(myPoints[3].x + (myPoints[5].x - myPoints[3].x) / 5, myPoints[3].y + (myPoints[5].y - myPoints[3].y) / 5, 0.0f),
			glm::vec3(0.5f, 0.7f, 0.0f),
			glm::vec3(0.8f, 0.0f, 0.0f),
			glm::vec3(0.9f, -0.6f, 0.0f) 
};



/* Vertex buffer objektum és vertex array objektum az adattároláshoz.*/
GLuint VBO;
GLuint VAO;

GLuint renderingProgram;

void updateVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, myPoints.size() * sizeof(glm::vec3), myPoints.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bool checkOpenGLError() {
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR) {
		cout << "glError: " << glErr << endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

void printShaderLog(GLuint shader) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		cout << "Shader Info Log: " << log << endl;
		free(log);
	}
}

void printProgramLog(int prog) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		cout << "Program Info Log: " << log << endl;
		free(log);
	}
}

string readShaderSource(const char* filePath) {
	string content;
	ifstream fileStream(filePath, ios::in);
	string line = "";

	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

GLuint createShaderProgram() {

	GLint vertCompiled;
	GLint fragCompiled;
	GLint linked;

	string vertShaderStr = readShaderSource("vertexShader.glsl");
	string fragShaderStr = readShaderSource("fragmentShader.glsl");

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vertShaderSrc = vertShaderStr.c_str();
	const char* fragShaderSrc = fragShaderStr.c_str();

	glShaderSource(vShader, 1, &vertShaderSrc, NULL);
	glShaderSource(fShader, 1, &fragShaderSrc, NULL);

	glCompileShader(vShader);
	checkOpenGLError();
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1) {
		cout << "vertex compilation failed" << endl;
		printShaderLog(vShader);
	}


	glCompileShader(fShader);
	checkOpenGLError();
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled != 1) {
		cout << "fragment compilation failed" << endl;
		printShaderLog(fShader);
	}

	// Shader program objektum létrehozása. Eltároljuk az ID értéket.
	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);

	glLinkProgram(vfProgram);
	checkOpenGLError();
	glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
	if (linked != 1) {
		cout << "linking failed" << endl;
		printProgramLog(vfProgram);
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	return vfProgram;
}

int fact(int n) {
	if (n == 0)
		return 1;
	if (n == 0)
		return 1;
	return n * fact(n - 1);
}

GLfloat poly(int n, int i, GLfloat t)
{
	GLfloat B = (fact(n) / (fact(i) * fact(n - i)) * pow(t, i) * pow(1 - t, n - i));
	return B;
}

GLfloat dist2(glm::vec3 P1, glm::vec3 P2)
{
	GLfloat t1 = P1.x - P2.x;
	GLfloat t2 = P1.y - P2.y;

	return t1 * t1 + t2 * t2;
}

void addPoint(GLfloat x, GLfloat y) {
	GLfloat xNorm = x / (WIN_WIDTH / 2) - 1.0f;
	GLfloat yNorm = y / (WIN_HEIGHT / 2) - 1.0f;
	myPoints.push_back(glm::vec3(xNorm, yNorm, 0.0f));
	cout <<x <<" " <<y <<" " << " size: " << myPoints.size() << endl;
	updateVBO();
}

GLint getActivePoint(vector<glm::vec3> p, GLint size, GLfloat sens, GLfloat x, GLfloat y)
{

	GLint i;
	GLfloat s = sens * sens;

	GLfloat xNorm = x / (WIN_WIDTH / 2) - 1.0f;
	GLfloat yNorm = y / (WIN_HEIGHT / 2) - 1.0f;
	glm::vec3 P = glm::vec3(xNorm, yNorm, 0.0f);

	for (i = 0; i < size; i++) {
		if (dist2(p[i], P) < s) {
			return i;
		}
	}
	return -1;

}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		case GLFW_KEY_ENTER:
			cout << "Enter pressed, drawing bezier curve" << endl;
			enterpressed = true;
			break;
		}
	}
}

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{
	GLint i;

	GLfloat xNorm = xPos / (WIN_WIDTH / 2) - 1.0f;
	GLfloat yNorm = (WIN_HEIGHT - yPos) / (WIN_HEIGHT / 2) - 1.0f;

	if (dragged >= 0)
	{
		myPoints.at(dragged).x = xNorm;
		myPoints.at(dragged).y = yNorm;

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, myPoints.size() * sizeof(glm::vec3), myPoints.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if (dragged == 3 || dragged == 4) {
		myPoints[7].x = myPoints[3].x + (myPoints[4].x - myPoints[3].x) / 4;
		myPoints[7].y = myPoints[3].y + (myPoints[4].y - myPoints[3].y) / 4;
		updateVBO();
	}

}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	GLint i;
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		if ((i = getActivePoint(myPoints, myPoints.size(), 0.1f, x, WIN_HEIGHT-y)) != -1)
		{
			dragged = i;
		}
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		dragged = -1;
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		addPoint(x, WIN_HEIGHT - y);
	}
}

double blending(GLint i, GLfloat t)
{
	switch (i)
	{
	case 0: return ((1 - t) * (1 - t) * (1 - t));
	case 1: return (3 * t * (1 - t) * (1 - t));
	case 2: return (3 * t * t * (1 - t));
	case 3: return (t * t * t);
	}
}


void firstBezierCurve(std::vector<glm::vec3> controlPoints)
{
	while (controlPoints.size() > 8) {
		controlPoints.pop_back();
	}
	glm::vec3 nextPoint;
	GLfloat t = 0.0f;
	GLfloat increment = 1.0f / 100.0f; /* hány darab szakaszból rakjuk össze a görbénket? */

	while (t <= 1.0f)
	{
		nextPoint = glm::vec3(0.0f, 0.0f, 0.0f);
		for (int i = 0; i <= 3; i++)
		{
			nextPoint.x = nextPoint.x + (blending(i, t) * controlPoints.at(i).x);
			nextPoint.y = nextPoint.y + (blending(i, t) * controlPoints.at(i).y);
			nextPoint.z = nextPoint.z + (blending(i, t) * controlPoints.at(i).z);
		}

		myPoints.push_back(glm::vec3(nextPoint.x, nextPoint.y, nextPoint.z));
	//3*(P[3]-P[2])=4*(p[4]-p[3])
		myPoints[7] = myPoints[3] + glm::vec3(0.75, 0.75, 0.75) * (myPoints[3] - myPoints[2]);
		t += 0.001;
	}
	updateVBO();
}



void secondBezierCurve(std::vector<glm::vec3> controlPoints)
{
	while (controlPoints.size() > 8) {
		controlPoints.pop_back();
	}
	glm::vec3 nextPoint;
	GLfloat t = 0.0f;
	GLfloat increment = 1.0f / 100.0f; /* hány darab szakaszból rakjuk össze a görbénket? */

	while (t <= 1.0f)
	{
		nextPoint = glm::vec3(0.0f, 0.0f, 0.0f);
		for (int i = 0; i < 5; i++)
		{
			nextPoint.x = nextPoint.x + (poly(4, i, t) * controlPoints.at(i).x);
			nextPoint.y = nextPoint.y + (poly(4, i, t) * controlPoints.at(i).y);
			nextPoint.z = nextPoint.z + (poly(4, i, t) * controlPoints.at(i).z);
		}

		myPoints.push_back(glm::vec3(nextPoint.x, nextPoint.y, nextPoint.z));
		t += 0.001;
	}
	updateVBO();
}

void init(GLFWwindow* window) {
	renderingProgram = createShaderProgram();
	myPoints.push_back(glm::vec3(myPoints[3].x + (myPoints[3].x - myPoints[2].x), myPoints[3].y + (myPoints[3].y - myPoints[2].y), 0.0f));
	/* Létrehozzuk a szükséges Vertex buffer és vertex array objektumot. */
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	/* Típus meghatározása: a GL_ARRAY_BUFFER nevesített csatolóponthoz kapcsoljuk a buffert (ide kerülnek a vertex adatok). */
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* Másoljuk az adatokat a pufferbe! Megadjuk az aktuálisan csatolt puffert,  azt hogy hány bájt adatot másolunk,
	a másolandó adatot, majd a feldolgozás módját is meghatározzuk: most az adat nem változik a feltöltés után */
	glBufferData(GL_ARRAY_BUFFER, myPoints.size() * sizeof(glm::vec3), myPoints.data(), GL_STATIC_DRAW);

	/* A puffer kész, lecsatoljuk, már nem szeretnénk módosítani. */
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Csatoljuk a vertex array objektumunkat a konfiguráláshoz. */
	glBindVertexArray(VAO);

	/* Vertex buffer objektum újracsatolása. */
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* Ezen adatok szolgálják a 0 indexû vertex attribútumot (itt: pozíció).
	Elsõként megadjuk ezt az azonosítószámot.
	Utána az attribútum méretét (vec3, láttuk a shaderben).
	Harmadik az adat típusa.
	Negyedik az adat normalizálása, ez maradhat FALSE jelen példában.
	Az attribútum értékek hogyan következnek egymás után? Milyen lépésköz után találom a következõ vertex adatait?
	Végül megadom azt, hogy honnan kezdõdnek az értékek a pufferben. Most rögtön, a legelejétõl veszem õket.*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	/* Engedélyezzük az imént definiált 0 indexû attribútumot. */
	glEnableVertexAttribArray(0);

	/* Leválasztjuk a vertex array objektumot és a puufert is.*/
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/** A jelenetünk utáni takarítás. */
void cleanUpScene()
{
	/** Töröljük a vertex puffer és vertex array objektumokat. */
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	/** Töröljük a shader programot. */
	glDeleteProgram(renderingProgram);
}



void display(GLFWwindow* window, double currentTime) {

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // fontos lehet minden egyes alkalommal törölni!

	// aktiváljuk a shader-program objektumunkat.
	glUseProgram(renderingProgram);

	/*Csatoljuk a vertex array objektumunkat. */
	//glm::vec4 color = (0.0f, 0.0f, 1.0f, 1.0f);
	float myFloats[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	//GLint myLoc = glGetUniformLocation(renderingProgram, "color");
	//glProgramUniform4fv(renderingProgram, myLoc, 0.0f, 0.0f, 1.0f, 1.0f);
	
	firstBezierCurve(myPoints);
	vector<glm::vec3> secondbeziercontrolpts = { myPoints[3], myPoints[7], myPoints[4], myPoints[5], myPoints[6] };
	secondBezierCurve(secondbeziercontrolpts);
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_STRIP, 0, 7);
	glPointSize(1.0f);
	glDrawArrays(GL_POINTS, 0, myPoints.size());
	
	//glDrawArrays(GL_LINE_STRIP, , 2);


	if (currentTime - lastUpdate >= updateFrequency) {
		//firstBezierCurve(myPoints);
		lastUpdate = currentTime;
		while (myPoints.size() > 8) {
			myPoints.pop_back();
		}
		updateVBO();
	}

	/* Leválasztjuk, nehogy bármilyen érték felülíródjon.*/
	glBindVertexArray(0);
}

int main(void) {
	/* Próbáljuk meg inicializálni a GLFW-t! */
	if (!glfwInit()) { exit(EXIT_FAILURE); }

	/* A kívánt OpenGL verzió (4.3) */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	/* Próbáljuk meg létrehozni az ablakunkat. */
	GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Drag and drop", NULL, NULL);

	/* Válasszuk ki az ablakunk OpenGL kontextusát, hogy használhassuk. */
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	/* Incializáljuk a GLEW-t, hogy elérhetõvé váljanak az OpenGL függvények. */
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	/* Az alkalmazáshoz kapcsolódó elõkészítõ lépések, pl. hozd létre a shader objektumokat. */
	init(window);
	lastUpdate = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		/* a kód, amellyel rajzolni tudunk a GLFWwindow ojektumunkba. */
		display(window, glfwGetTime());
		/* double buffered */
		glfwSwapBuffers(window);
		/* események kezelése az ablakunkkal kapcsolatban, pl. gombnyomás */
		glfwPollEvents();
	}

	/* töröljük a GLFW ablakot. */
	glfwDestroyWindow(window);
	/* Leállítjuk a GLFW-t */

	cleanUpScene();

	glfwTerminate();
	exit(EXIT_SUCCESS);
}