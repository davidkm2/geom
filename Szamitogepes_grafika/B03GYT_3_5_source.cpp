#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <array>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

static int WIN_WIDTH = 600;
static int WIN_HEIGHT = 600;

float vertices[] = {
	// positions           // color
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.1f, -0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.1f, -0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.1f, -0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.1f,  0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.1f,  0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f,  0.1f,  0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

		-0.5f,  0.1f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.1f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.1f,  0.5f,  0.0f, 0.0f, 1.0f,

		 0.5f,  0.1f,  0.5f,  0.0f, 1.0f, 1.0f,
		 0.5f,  0.1f, -0.5f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
		 0.5f,  0.1f,  0.5f,  0.0f, 1.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,

		-0.5f,  0.1f, -0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f,  0.1f, -0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f,  0.1f,  0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f,  0.1f,  0.5f,  1.0f, 0.0f, 1.0f,
		-0.5f,  0.1f,  0.5f,  1.0f, 0.0f, 1.0f,
		-0.5f,  0.1f, -0.5f,  1.0f, 0.0f, 1.0f,

		
		0.5f, 0.1f, -0.5f, 0.0f, 0.5f, 0.5f,
		-0.5f, 0.1f, -0.5f, 0.0f, 0.5f, 0.5f, 
		0.0f, 0.5f, 0.0f, 0.0f, 0.5f, 0.5f,


		0.5, 0.1f, 0.5f, 0.5f, 0.5f, 0.0f,
		-0.5f, 0.1f, 0.5f, 0.5f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f,

		0.5f, 0.1f, 0.5f, 0.5f, 0.0f, 0.5f,
		0.5f, 0.1f, -0.5f, 0.5f, 0.0f, 0.5f,
		0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 0.5f,

		-0.5f, 0.1f, 0.5f, 0.0f, 0.5f, 0.0f,
		-0.5f, 0.1f, -0.5f, 0.0f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.5f, 0.0f
		
		
		
		
		
};

/* Vertex buffer objektum �s vertex array objektum az adatt�rol�shoz.*/
GLuint VBO;
GLuint VAO;

GLuint renderingProgram;

/** Vet�t�si �s kamera m�trixok felv�tele. */
glm::mat4 view, projection;

float deltaTime = 0.0f, lastTime = 0.0f;

/* Vegy�k fel a kamera pozic�t t�rol� v�ltoz�t, illetve a tengelyekhezz sz�ks�ges vektorokat. */
glm::vec3 cameraPos = glm::vec3(0.0f, 0.5f, 3.0f), cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f), up = glm::vec3(0.0f, 1.0f, 0.0f),
cameraMoving = glm::vec3(0.0, 0.0, -1.0);

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

	// Shader program objektum l�trehoz�sa. Elt�roljuk az ID �rt�ket.
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

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	float cameraSpeed = 2.5f * deltaTime;

	if (key == GLFW_KEY_F && action == GLFW_REPEAT)
	{
		/* A kamera sz�m�ra sz�m�tsuk ki az el�re mutat� ir�nyt .*/
		cameraPos += cameraSpeed * cameraMoving;
	}

	if (key == GLFW_KEY_G && action == GLFW_REPEAT)
	{
		cameraPos -= cameraSpeed * cameraMoving;
	}

	if (key == GLFW_KEY_A && action == GLFW_REPEAT)
	{
		/* A kamera sz�m�ra sz�m�tsuk ki a balra mutat� ir�nyt .*/
		cameraPos = cameraPos + cameraSpeed * -1 * glm::normalize(glm::cross(cameraMoving, up));
	}

	if (key == GLFW_KEY_D && action == GLFW_REPEAT)
	{
		cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraMoving, up));
	}

	if (key == GLFW_KEY_W && action == GLFW_REPEAT) {
		cameraPos.y += 0.1;
	}

	if (key == GLFW_KEY_S && action == GLFW_REPEAT) {
		cameraPos.y -= 0.1;
	}
}

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{

}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{

}

/** Kisz�moljuk a kamera m�trixokat. */
void computeCameraMatrices()
{
	/* A param�terek rendre: az �j koordin�tarendszer�nk k�z�ppontja (hol a kamera), merre n�z a kamera, mit tekint�nk ,,f�lfele" ir�nynak */
	view = glm::lookAt(cameraPos, cameraPos + cameraMoving, up);
	projection = glm::perspective(glm::radians(45.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);
}

void init(GLFWwindow* window) {

	renderingProgram = createShaderProgram();

	/* L�trehozzuk a sz�ks�ges Vertex buffer �s vertex array objektumot. */
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	/* T�pus meghat�roz�sa: a GL_ARRAY_BUFFER neves�tett csatol�ponthoz kapcsoljuk a buffert (ide ker�lnek a vertex adatok). */
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* M�soljuk az adatokat a pufferbe! Megadjuk az aktu�lisan csatolt puffert,  azt hogy h�ny b�jt adatot m�solunk,
	a m�soland� adatot, majd a feldolgoz�s m�dj�t is meghat�rozzuk: most az adat nem v�ltozik a felt�lt�s ut�n */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* A puffer k�sz, lecsatoljuk, m�r nem szeretn�nk m�dos�tani. */
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Csatoljuk a vertex array objektumunkat a konfigur�l�shoz. */
	glBindVertexArray(VAO);

	/* Vertex buffer objektum �jracsatol�sa. */
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* Ezen adatok szolg�lj�k a 0 index� vertex attrib�tumot (itt: poz�ci�).
	Els�k�nt megadjuk ezt az azonos�t�sz�mot.
	Ut�na az attrib�tum m�ret�t (vec3, l�ttuk a shaderben).
	Harmadik az adat t�pusa.
	Negyedik az adat normaliz�l�sa, ez maradhat FALSE jelen p�ld�ban.
	Az attrib�tum �rt�kek hogyan k�vetkeznek egym�s ut�n? Milyen l�p�sk�z ut�n tal�lom a k�vetkez� vertex adatait?
	V�g�l megadom azt, hogy honnan kezd�dnek az �rt�kek a pufferben. Most r�gt�n, a legelej�t�l veszem �ket.*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	/* Enged�lyezz�k az im�nt defini�lt 0 index� attrib�tumot. */
	glEnableVertexAttribArray(0);

	/* Sz�n attrib�tum */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* Lev�lasztjuk a vertex array objektumot �s a puufert is.*/
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

/** A jelenet�nk ut�ni takar�t�s. */
void cleanUpScene()
{
	/** T�r�lj�k a vertex puffer �s vertex array objektumokat. */
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	/** T�r�lj�k a shader programot. */
	glDeleteProgram(renderingProgram);
}

void display(GLFWwindow* window, double currentTime) {

	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/** Z-bufferez�s enged�lyez�se. */
	glEnable(GL_DEPTH_TEST);

	// aktiv�ljuk a shader-program objektumunkat.
	glUseProgram(renderingProgram);

	glm::mat4 model[2];
		model[0]=glm::mat4(1.0f); 
	model[0] = glm::translate(model[0], glm::vec3(0.0f, 0.0f, 0.0f));
	model[0] = glm::rotate(model[0], (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int modelLoc = glGetUniformLocation(renderingProgram, "model");

	computeCameraMatrices();
	unsigned int viewLoc = glGetUniformLocation(renderingProgram, "view");
	unsigned int projectionLoc = glGetUniformLocation(renderingProgram, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model[0]));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	/*Csatoljuk a vertex array objektumunkat. */
	glBindVertexArray(VAO);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));
	/* Lev�lasztjuk, nehogy b�rmilyen �rt�k fel�l�r�djon.*/
	glBindVertexArray(0);

	glUseProgram(renderingProgram);

	model[1] = glm::mat4(1.0f);
	model[1] = glm::translate(model[1], glm::vec3(1.2f, 0.0f, 0.0f));
	model[1] = glm::rotate(model[1], (float)glfwGetTime() * glm::radians(-50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model[1] = model[1] * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	modelLoc = glGetUniformLocation(renderingProgram, "model");

	computeCameraMatrices();
	viewLoc = glGetUniformLocation(renderingProgram, "view");
	projectionLoc = glGetUniformLocation(renderingProgram, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model[1]));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	/*Csatoljuk a vertex array objektumunkat. */
	glBindVertexArray(VAO);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));
	/* Lev�lasztjuk, nehogy b�rmilyen �rt�k fel�l�r�djon.*/
	glBindVertexArray(0);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(void) {

	/* Pr�b�ljuk meg inicializ�lni a GLFW-t! */
	if (!glfwInit()) { exit(EXIT_FAILURE); }

	/* A k�v�nt OpenGL verzi� (4.3) */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	/* Pr�b�ljuk meg l�trehozni az ablakunkat. */
	GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Kamera", NULL, NULL);

	/* V�lasszuk ki az ablakunk OpenGL kontextus�t, hogy haszn�lhassuk. */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetKeyCallback(window, keyCallback);
	//glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	/* Incializ�ljuk a GLEW-t, hogy el�rhet�v� v�ljanak az OpenGL f�ggv�nyek. */
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	/* Az alkalmaz�shoz kapcsol�d� el�k�sz�t� l�p�sek, pl. hozd l�tre a shader objektumokat. */
	init(window);

	while (!glfwWindowShouldClose(window)) {

		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		/* a k�d, amellyel rajzolni tudunk a GLFWwindow ojektumunkba. */
		display(window, glfwGetTime());
		/* double buffered */
		glfwSwapBuffers(window);
		/* esem�nyek kezel�se az ablakunkkal kapcsolatban, pl. gombnyom�s */
		glfwPollEvents();
	}

	/* t�r�lj�k a GLFW ablakot. */
	glfwDestroyWindow(window);
	/* Le�ll�tjuk a GLFW-t */

	cleanUpScene();

	glfwTerminate();
	exit(EXIT_SUCCESS);
}