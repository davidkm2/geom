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
#include <sstream>
#include <fstream>

using namespace std;

static int WIN_WIDTH = 600;
static int WIN_HEIGHT = 600;

/*float vertices[] = {
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





};*/

vector<float> vertices2;
vector<float> colors;
vector<float> faces;

int nvertices;
int nfaces;

void feltolt() {
	int nLines = 0;
	ifstream source;
	source.open("bunny.txt", ios_base::in);
	for (string line; getline(source, line); )   //read stream line by line
	{
		istringstream in(line);      //make a stream for the line itself

		string type;
		// cout << line.length() << endl;
		/*teszt*/
		if (nLines == 0) {
			in >> nvertices;
		}
		else if (nLines == 1) {
			in >> nfaces;
		} else if (vertices2.size() < 3 * nvertices) {
			float x, y, z, c, i;
			in >> x >> y >> z >> c >> i;

			vertices2.push_back(x);
			vertices2.push_back(y);
			vertices2.push_back(z);
			// vertices3.push_back(c);
			colors.push_back(i);
		}
		else {
			float n, f, s, t;
			in >> n >> f >> s >> t;

			//glm::vec3 u = { vertices2[3 * s] - vertices2[3*f], vertices2[3 * s + 1] - vertices2[3 * f + 1], vertices2[3 * s + 1] - vertices2[3 * f + 1] };
			//glm::vec3 v = { vertices2[3 * t] - vertices2[3 * f], vertices2[3 * t + 1] - vertices2[3 * f + 1], vertices2[3 * t + 1] - vertices2[3 * f + 1] };
			/*glm::vec3 normal = {
			u.y * v.z - u.z * v.y,
			u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x };*/

			faces.push_back(vertices2[3*f]);
			faces.push_back(vertices2[3 * f + 1]);
			faces.push_back(vertices2[3 * f + 2]);
			faces.push_back(colors[f]);
			faces.push_back(colors[f]);
			faces.push_back(colors[f]);

			faces.push_back(vertices2[3 * s]);
			faces.push_back(vertices2[3 * s + 1]);
			faces.push_back(vertices2[3 * s + 2]);
			faces.push_back(colors[s]);
			faces.push_back(colors[s]);
			faces.push_back(colors[s]);

			faces.push_back(vertices2[3 * t]);
			faces.push_back(vertices2[3 * t + 1]);
			faces.push_back(vertices2[3 * t + 2]);
			faces.push_back(colors[t]);
			faces.push_back(colors[t]);
			faces.push_back(colors[t]);

		}

		nLines++;

		 //now read the whitespace-separated floats
		//cout << x << " " << y << " " << z  << endl;
		/*glm::vec3 coords = { x,y,z };
		glm::vec3 color = { u,v,w };
		vertices.push_back(coords);
		vertices.push_back(color);*/
		
	}

	cout << vertices2.size() << "  " << faces.size();
}
/* Vertex buffer objektum és vertex array objektum az adattároláshoz.*/
GLuint VBO;
GLuint VAO;

GLuint renderingProgram;

/** Vetítési és kamera mátrixok felvétele. */
glm::mat4 view, projection;

float deltaTime = 0.0f, lastTime = 0.0f;

/* Vegyük fel a kamera pozicót tároló változót, illetve a tengelyekhezz szükséges vektorokat. */
glm::vec3 cameraPos = glm::vec3(0.0f, 0.15f, 0.5f), cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f), up = glm::vec3(0.0f, 1.0f, 0.0f),
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

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	float cameraSpeed = 2.5f * deltaTime;

	if (key == GLFW_KEY_F && action == GLFW_REPEAT)
	{
		/* A kamera számára számítsuk ki az előre mutató irányt .*/
		cameraPos += cameraSpeed * cameraMoving;
	}

	if (key == GLFW_KEY_G && action == GLFW_REPEAT)
	{
		cameraPos -= cameraSpeed * cameraMoving;
	}

	if (key == GLFW_KEY_A && action == GLFW_REPEAT)
	{
		/* A kamera számára számítsuk ki a balra mutató irányt .*/
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

/** Kiszámoljuk a kamera mátrixokat. */
void computeCameraMatrices()
{
	/* A paraméterek rendre: az új koordinátarendszerünk középpontja (hol a kamera), merre néz a kamera, mit tekintünk ,,fölfele" iránynak */
	view = glm::lookAt(cameraPos, cameraPos + cameraMoving, up);
	projection = glm::perspective(glm::radians(45.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);
}

void init(GLFWwindow* window) {
	feltolt();
	renderingProgram = createShaderProgram();

	/* Létrehozzuk a szükséges Vertex buffer és vertex array objektumot. */
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	/* Típus meghatározása: a GL_ARRAY_BUFFER nevesített csatolóponthoz kapcsoljuk a buffert (ide kerülnek a vertex adatok). */
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* Másoljuk az adatokat a pufferbe! Megadjuk az aktuálisan csatolt puffert,  azt hogy hány bájt adatot másolunk,
	a másolandó adatot, majd a feldolgozás módját is meghatározzuk: most az adat nem változik a feltöltés után */
	glBufferData(GL_ARRAY_BUFFER, faces.size() * sizeof(float), faces.data(), GL_STATIC_DRAW);

	/* A puffer kész, lecsatoljuk, már nem szeretnénk módosítani. */
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Csatoljuk a vertex array objektumunkat a konfiguráláshoz. */
	glBindVertexArray(VAO);

	/* Vertex buffer objektum újracsatolása. */
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* Ezen adatok szolgálják a 0 indexű vertex attribútumot (itt: pozíció).
	Elsőként megadjuk ezt az azonosítószámot.
	Utána az attribútum méretét (vec3, láttuk a shaderben).
	Harmadik az adat típusa.
	Negyedik az adat normalizálása, ez maradhat FALSE jelen példában.
	Az attribútum értékek hogyan következnek egymás után? Milyen lépésköz után találom a következő vertex adatait?
	Végül megadom azt, hogy honnan kezdődnek az értékek a pufferben. Most rögtön, a legelejétől veszem őket.*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	/* Engedélyezzük az imént definiált 0 indexű attribútumot. */
	glEnableVertexAttribArray(0);

	/* Szín attribútum */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* Leválasztjuk a vertex array objektumot és a puffert is.*/
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

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glClear(GL_COLOR_BUFFER_BIT);

	/** Z-bufferezés engedélyezése. */
	//glEnable(GL_DEPTH_TEST);

	// aktiváljuk a shader-program objektumunkat.
	glUseProgram(renderingProgram);

	glm::mat4 model[2];
	model[0] = glm::mat4(1.0f);
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
	glEnable(GL_POLYGON_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, faces.size());
	/* Leválasztjuk, nehogy bármilyen érték felülíródjon.*/
	glBindVertexArray(0);
	glBindVertexArray(1);


	//glUseProgram(renderingProgram);

	/*model[1] = glm::mat4(1.0f);
	model[1] = model[1] * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	//model[1] = glm::translate(model[1], glm::vec3(1.2f, 0.0f, 0.0f));
	model[1] = glm::rotate(model[1], (float)glfwGetTime() * glm::radians(-50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model[1] = glm::translate(model[1], glm::vec3(1.2f, 0.0f, 0.0f));
	model[1] = glm::rotate(model[1], (float)glfwGetTime() * glm::radians(-50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model[1] = model[1] * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));

	//model[1] = model[1] * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	modelLoc = glGetUniformLocation(renderingProgram, "model");

	computeCameraMatrices();
	viewLoc = glGetUniformLocation(renderingProgram, "view");
	projectionLoc = glGetUniformLocation(renderingProgram, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model[1]));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


	glBindVertexArray(VAO);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));

	glBindVertexArray(0);*/
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(void) {

	/* Próbáljuk meg inicializálni a GLFW-t! */
	if (!glfwInit()) { exit(EXIT_FAILURE); }

	/* A kívánt OpenGL verzió (4.3) */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	/* Próbáljuk meg létrehozni az ablakunkat. */
	GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Kamera", NULL, NULL);

	/* Válasszuk ki az ablakunk OpenGL kontextusát, hogy használhassuk. */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetKeyCallback(window, keyCallback);
	//glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	/* Incializáljuk a GLEW-t, hogy elérhetővé váljanak az OpenGL függvények. */
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	/* Az alkalmazáshoz kapcsolódó előkészítő lépések, pl. hozd létre a shader objektumokat. */
	init(window);

	while (!glfwWindowShouldClose(window)) {

		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

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