/*
Semestre 2021-2
Proyecto de computación gráfica e interacción humano-computadora
Alumno: Sandoval Juárez Luis Arturo 3
*/

#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h> 
#include <Windows.h>
#include <time.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//Librería para música
#include "irrKlang.h"


/////---------------------------------------------- PARA LA ILUMINACION----------------------------------------------------------------------////
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Material.h"


/////---------------------------------------------- VARIABLES PARA MUSICA----------------------------------------------------------------------////
//bool musicFondo = true;
using namespace irrklang;

/////---------------------------------------------- DIMENSIONES DE WINDOW----------------------------------------------------------------------////

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

/////---------------------------------------------- DECLARACION DE CAMERA ----------------------------------------------------------------------////

Camera camera;

/////---------------------------------------------- DECLARACION DE TEXTURAS ----------------------------------------------------------------------////

Texture pisoTexture;
Texture pastoTexture;
Texture Tagave;


/////---------------------------------------------- DECLARACION DE MODELOS ----------------------------------------------------------------------////
Model Kitt_M;
Model Llanta_M;
Model Camino_M;
Model Blackhawk_M;
Model Cabeza_M;
Model Alberca_M;
Model Alberca1_M;
Model Silla_M;
Model Maceta_M;
Model Palmera_M;
Model Casas_M;
Model Esce_M;

/////---------------------------------------------- DECLARACION DE SKYBOX ----------------------------------------------------------------------////
Skybox skybox;

/////---------------------------------------------- DECLARACION DE MATERIALES ----------------------------------------------------------------------////
Material Material_brillante;
Material Material_opaco;

/////---------------------------------------------- DECLARACION DE LUCES --------------------------------------------------------------------------////

//luz direccional
DirectionalLight mainLight;

//luz pointlight
PointLight pointLights[MAX_POINT_LIGHTS];//para declarar varias luces de tipo pointlight

//luz spotligth
SpotLight spotLights[MAX_SPOT_LIGHTS];


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

/////---------------------------------------------- DECLARACION DE VARIABLES --------------------------------------------------------------------------////

//Que se usaran para el SKYBOX
bool skyT = true;
bool skyN = false;


//Valor de toRadians
const float toRadians = 3.14159265f / 180.0f;

//Variables de movimiento de avion
GLfloat posXavion = 0.0f;
GLfloat posYavion = 0.0f;
GLfloat posZavion = 0.0f;
float offset = 0.0f;
//Variables de movimiento de coche
GLfloat posXcoche = 0.0f;
GLfloat posYcoche = 0.0f;
GLfloat posZcoche = 0.0f;
//Variables booleanas para las condiciones de estados
//Coche
bool	aniCo = false;
bool	idaCo = true;
bool	vueltaCo1 = false;
bool	vueltaCo2 = false;
bool	vueltaCo3 = false;
bool	vueltaCo4 = false;
bool	vueltaCo5 = false;
bool	vueltaCo6 = false;
bool	vueltaCo7 = false;
bool	vueltaCo8 = false;
bool	vueltaCo9 = false;
bool	vueltaCo10 = false;
bool	vueltaCo11 = false;
bool	vueltaCo12 = false;
bool	vueltaCo13 = false;
bool	vueltaCo14 = false;
bool	regresoCo = false;
bool	regreso = false;
//Helicoptero
bool	aniHe = true;
bool	ida = true;
bool	vuelta1 = false;
bool	vuelta2 = false;
bool	vuelta3 = false;
bool	vuelta4 = false;
bool	vuelta5 = false;
bool	vuelta6 = false;
bool	vuelta7 = false;
bool	vuelta8 = false;
bool	vuelta9 = false;
bool	vuelta10 = false;
//Direccion del Helicoptero
float	dire = 0.0f;
GLfloat movCir = 0.0f;
//Direccion del Coche
GLfloat movCoc = 0.0f;
GLfloat movZ = 0.0f;
GLfloat movX = 0.0f;

/////---------------------------------------------- VERTEX SHADER --------------------------------------------------------------------------////

static const char* vShader = "shaders/shader_light.vert";

/////---------------------------------------------- FRAGMENT SHADER --------------------------------------------------------------------------////

static const char* fShader = "shaders/shader_light.frag";


//cálculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

/////---------------------------------------------- CREACION DE OBJETOS CON PRIMITVAS --------------------------------------------------------------------------////


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
		0, 1, 2,
		0, 2, 3,
		4,5,6,
		4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,
	};
	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

	Mesh *obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

}

/////---------------------------------------------- CREACION DE CUBO CON PRIMITIVAS--------------------------------------------------------------------------////

void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,
	};


	GLfloat cubo_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.27f,  0.35f,		0.0f,	0.0f,	-1.0f,	//0
		0.5f, -0.5f,  0.5f,		0.48f,	0.35f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f,  0.5f,  0.5f,		0.48f,	0.64f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.27f,	0.64f,		0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.52f,  0.35f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	0.73f,	0.35f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	0.73f,	0.64f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.52f,	0.64f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.77f,	0.35f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		0.98f,	0.35f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		0.98f,	0.64f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.77f,	0.64f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.0f,	0.35f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	0.23f,  0.35f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	0.23f,	0.64f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.0f,	0.64f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.27f,	0.02f,		0.0f,	1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	0.48f,  0.02f,		0.0f,	1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	0.48f,	0.31f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.27f,	0.31f,		0.0f,	1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.27f,	0.68f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	0.48f,  0.68f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	0.48f,	0.98f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.27f,	0.98f,		0.0f,	-1.0f,	0.0f,

	};

	Mesh *cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 192, 36);
	meshList.push_back(cubo);

}

/////---------------------------------------------- CREACION DE SHADERS --------------------------------------------------------------------------////


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}


/////---------------------------------------------- AQUI EMPIEZA EL MAIN-----------------------------------------------------------------------------------------////
int main()
{
	/////---------------------------------------------- LLAMAR CANCION --------------------------------------------------------------------------////
	/*
	ISoundEngine* engine = createIrrKlangDevice();
	if (!engine)
		return 0;
	ISound* ambiental = engine->play2D("canciones/Stellar Wind - Unicorn Heads.mp3", true);
	*/
	/////---------------------------------------------- INICIAR WINDOW --------------------------------------------------------------------------////
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	/////---------------------------------------------- LLAMAR FUNCIONES --------------------------------------------------------------------------////

	//Crear Objetos
	CreateObjects();

	//Crear Cubo
	CrearCubo();

	//Crear Shaders
	CreateShaders();

	/////---------------------------------------------- VALORES DE CAMARA --------------------------------------------------------------------------////

	camera = Camera(glm::vec3(0.0f, 25.0f, -170.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 1.0f, 0.5f);
	//----------------------Posicion de la camera------Sobre que eje esta-------angulo---//----//------//



	/////---------------------------------------------- CARGA DE TEXTURAS --------------------------------------------------------------------------////

	
	//Textura Piso
	pisoTexture = Texture("Textures/pisoPiedra.png");
	pisoTexture.LoadTextureA();
	//Textura Agave
	Tagave = Texture("Textures/Agave.tga");
	Tagave.LoadTextureA();
	//Textura Pasto
	pastoTexture=Texture("Textures/arena.jpg");
	pastoTexture.LoadTextureA();

	/////---------------------------------------------- CARGA DE MODELOS --------------------------------------------------------------------------////

	//Modelo Kitt
	Kitt_M = Model();
	Kitt_M.LoadModel("Models/Coche-Jeep.obj");

	//Modelo Llanta
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta.obj");

	//Modelo Helicoptero
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");

	//Modelo Camino
	Camino_M = Model();
	Camino_M.LoadModel("Models/pista.obj");


	//Modelo Cabeza
	Cabeza_M = Model();
	Cabeza_M.LoadModel("Models/cabeza.obj");

	//Modelo Alberca
	Alberca_M = Model();
	Alberca_M.LoadModel("Models/1alb.obj");

	//Modelo Alberc1
	Alberca1_M = Model();
	Alberca1_M.LoadModel("Models/alberca1.obj");

	//Modelo SIlla
	Silla_M = Model();
	Silla_M.LoadModel("Models/silla.obj");

	//Modelo Maceta
	Maceta_M = Model();
	Maceta_M.LoadModel("Models/maceta.obj");

	//Modelo Palmera
	Palmera_M = Model();
	Palmera_M.LoadModel("Models/palmera.obj");

	//Modelo Casas
	Casas_M = Model();
	Casas_M.LoadModel("Models/casas.obj");

	//Modelo Casas
	Esce_M = Model();
	Esce_M.LoadModel("Models/escenario.obj");


	/////---------------------------------------------- CARGA DE CARAS DEL SKYBOX -----------------------------------------------------------------------////


	int sec;

	
		std::vector<std::string> skyboxFaces;
		skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
		skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
		skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
		skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
		skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
		skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");
		skybox = Skybox(skyboxFaces);
		printf("Hello Sky1");

	

	std::vector<std::string> skyboxFaces2;
	skyboxFaces2.push_back("Textures/Skybox/posx.jpg");//RIGHT
	skyboxFaces2.push_back("Textures/Skybox/negx.jpg");//LEFT
	skyboxFaces2.push_back("Textures/Skybox/negy.jpg");//DOWN
	skyboxFaces2.push_back("Textures/Skybox/posy.jpg");//TOP
	skyboxFaces2.push_back("Textures/Skybox/posz.jpg");//FRONT
	skyboxFaces2.push_back("Textures/Skybox/negz.jpg");//BACK
	skybox = Skybox(skyboxFaces2);
	printf("Hello Sky2");
	
	
	/////---------------------------------------------- VALORES MATERIALES BRILLANTE Y OPACO -------------------------------------------------------------////

	//Material Brillante
	Material_brillante = Material(4.0f, 256);

	//Material opaco
	Material_opaco = Material(0.3f, 4);


	/////------------------------------------------------------ POSICIONES INICIALES --------------------------------------------------------------------////

	//Posicion inicial helicoptero
	glm::vec3 posblackhawk = glm::vec3(20.0f, 6.0f, 40.0);

	//Posicion inicial desplazamiento
	glm::vec3 desplazamiento = glm::vec3(0.0f, 0.0f, 0.0f);

	//Posicion inicial desplazamiento2
	glm::vec3 desplazamiento2 = glm::vec3(0.0f, 0.0f, 0.0f);

	//Posicion inicial direF
	glm::vec3 direF = glm::vec3(0.0f, 0.0f, 0.0f);

	//Posición incial del coche
	glm::vec3 poscoche = glm::vec3(0.0f, -0.4f, 70.6f);

	//Posicion inicial del faro
	glm::vec3 posfaro = glm::vec3(12.0f, -1.0f, 70.6f);

	/////------------------------------------------------------ LUCES DEL MUNDO ----------------------------------------------------------------------////

	
	//---------------------DirectionalLight-----------------------------------------------------------------------------------------------------------// 
	//Madre de todas las luces, es como el sol. Solo existe una.
	



	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f, //RGB - Color blanco- se usa este para qye se vean todos los colores
		0.7f, 0.7f,	//Coeficiente de intensidad ambiental y difusa.
		0.0f, 0.0f, -1.0f);//Posicion en x, y , z
	

		
	//---------------------PointLigh-----------------------------------------------------------------------------------------------------------------// 
	//Luz punntual			


	//pointLights[0]
	unsigned int pointLightCount = 0; //Contador de luces puntuales, se tendra más de una

	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f, //RGB
		0.0f, 1.0f,//Intensidad ambiental y difusa
		2.0f, 1.5f, 1.5f,//Valor de posición
		0.3f, 0.2f, 0.1f);//Coeficientes de ecuación de segundo grado
	pointLightCount++;//Aumenta contador



	//---------------------SpotLight----------------------------------------------------------------------------------------------------------------// 

	unsigned int spotLightCount = 0;// Contador Luces SpotLight


	//Linterna-spotLights[0]

	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f, //RGB
		0.0f, 2.0f,//Coeficiente ambiental y difuso
		0.0f, 0.0f, 0.0f,//Posición x,y,z
		0.0f, -1.0f, 0.0f,//Vector de cirección, apunta hacia -y//DONDE APUNTA
		1.0f, 0.0f, 0.0f,//Valores de ecuación de segundo grado
		5.0f);//Radio de nuestro cono invicible//RADIO DEL CONO
	spotLightCount++;


	//Luz Fija-spotLights[1]

	spotLights[1] = SpotLight(0.0f, 0.0f, 1.0f,
		1.0f, 2.0f,
		-4.0f, 10.0f, -10.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;

	//Luz de Faro-spotLights[2]

	/*
	//luz de faro
	spotLights[2] = SpotLight(1.0f, 0.0f, 1.0f,//luz blanca(RGB)
		2.0f, 2.0f,//Coeficiente ambiental y difuso
		1.0f, -2.2f, -4.6f, //Posición x,y,z
		-0.1f, 0.0f, 0.0f,//Vector de dirección
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;
	*/


	//Luz de Helicoptero-spotLights[3]

	spotLights[3] = SpotLight(0.0f, 0.0f, 1.0f,//luz azul
		1.0f, 1.0f,//Coeficiente ambiental y difuso
		10.0f, -0.5f, 5.5f, //Posición x,y,z
		0.0f, -0.1f, 0.0f,//Vector de dirección
		1.0f, 0.0f, 0.0f,
		30.0f);
	spotLightCount++;


	/////---------------------------------------------- LO QUE SE PODRA VISUALIZAR CON CAMARA -------------------------------------------------------------////


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	/////------------------------------------------LOOP MIENTAS NO SE CIERRA LA VENTANA ----------------------------------------------------------------////

	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();

		//----------------información en el shader de intensidad especular y brillo----------------------------------------------------------------//
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		//----------------Esto se uso para realizar el setflash a la camara-----------------------------------------------------------------------//
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);


		//----------------Uso de SetFlash y SetPos dentro del loop------------------------------------------------------------------------------//

		//luz ligada a la cámara de tipo flash 
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//luz ligada al faro
		//spotLights[2].SetPos(poscoche + desplazamiento);


		//luz ligada al helicoptero
		spotLights[3].SetPos(posblackhawk + desplazamiento2);

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		/////------------------------------------------DIBUJAR EL PISO Y DECLARAR MODEL Y AUXILIARES ----------------------------------------------------------------////

		//MODEL
		glm::mat4 model(1.0);

		//MODELAUX
		glm::mat4 modelaux(1.0);

		//----------------DIBUJAR PISO------------------------------------------------------------------------------//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(25.0f, 0.1f, 25.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();
		//agregar material al plano de piso
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		//----------------DIBUJAR PASTO TOP------------------------------------------------------------------------------//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 80.0f));
		model = glm::scale(model, glm::vec3(4.0f, 0.1f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pastoTexture.UseTexture();
		//agregar material al plano de piso
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();
		//----------------DIBUJAR PASTO TOP LEFT------------------------------------------------------------------------------//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-80.0f, 0.2f, 80.0f));
		model = glm::scale(model, glm::vec3(4.0f, 0.1f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pastoTexture.UseTexture();
		//agregar material al plano de piso
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();
		//----------------DIBUJAR PASTO CENTER LEFT------------------------------------------------------------------------------//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-80.0f, 0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f, 0.1f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pastoTexture.UseTexture();
		//agregar material al plano de piso
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();
		//----------------DIBUJAR PASTO DOWN LEFT------------------------------------------------------------------------------//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-80.0f, 0.2f, -80.0f));
		model = glm::scale(model, glm::vec3(4.0f, 0.1f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pastoTexture.UseTexture();
		//agregar material al plano de piso
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();
		//----------------DIBUJAR PASTO TOP RIGHT------------------------------------------------------------------------------//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, 0.2f, 80.0f));
		model = glm::scale(model, glm::vec3(4.0f, 0.1f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pastoTexture.UseTexture();
		//agregar material al plano de piso
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();
		//----------------DIBUJAR PASTO CENTER RIGHT------------------------------------------------------------------------------//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, 0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f, 0.1f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pastoTexture.UseTexture();
		//agregar material al plano de piso
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();
		//----------------DIBUJAR PASTO DOWN RIGHT------------------------------------------------------------------------------//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, 0.2f, -80.0f));
		model = glm::scale(model, glm::vec3(4.0f, 0.1f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pastoTexture.UseTexture();
		//agregar material al plano de piso
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		/////----------------------------------------------------ANIMACIONES COMPLEJAS ----------------------------------------------------------------------////


		//MOVIMIENTO DE HELICOPTERO//

		offset += 0.5;

		if (aniHe)
		{

			if (ida)
			{


				posXavion -= 0.05;
				dire = 0.0f;

				if (posXavion < -40)
				{

					ida = false;
					vuelta1 = true;

				}
			}
			////

			if (vuelta1)
			{

				posXavion -= 0.01;
				posZavion -= 0.01;
				movCir -= 0.4;

				if (posZavion < -2) {//-2.1<-2.0
					vuelta1 = false;
					vuelta2 = true;
				}

			}

			//

			if (vuelta2)
			{
				posZavion -= 0.02;
				movCir -= 0.3;

				if (posZavion < -4) {//-4.1<-4.0
					vuelta2 = false;
					vuelta3 = true;
				}

			}

			//

			if (vuelta3)
			{
				posZavion -= 0.02;
				movCir -= 0.3;

				if (posZavion < -6) {//-6.1<-6.0
					vuelta3 = false;
					vuelta4 = true;
				}

			}

			//

			if (vuelta4)
			{

				//posXavion += 0.01;
				posZavion -= 0.02;
				movCir -= 0.4;

				if (posZavion < -8) {//-8.1<-8.0
					vuelta4 = false;
					vuelta5 = true;
				}

			}

			//

			if (vuelta5)
			{
				movCir = 180.0;

				if (movCir == 180.0) {
					vuelta5 = false;
					regreso = true;
				}

			}

			//
			if (regreso)
			{
				posXavion += 0.03;

				if (posXavion > 40)
				{
					vuelta6 = true;
					regreso = false;
				}

			}

			if (vuelta6)
			{

				posZavion += 0.01;
				movCir -= 0.4;

				if (posZavion > -6) {
					vuelta6 = false;
					vuelta7 = true;
				}

			}

			//

			if (vuelta7)
			{
				posZavion += 0.02;
				movCir -= 0.3;

				if (posZavion > -4) {
					vuelta7 = false;
					vuelta8 = true;
				}

			}

			//

			if (vuelta8)
			{
				posZavion += 0.02;
				movCir -= 0.3;

				if (posZavion > -2) {
					vuelta8 = false;
					vuelta9 = true;
				}

			}

			//

			if (vuelta9)
			{

				//posXavion += 0.01;
				posZavion += 0.02;
				movCir -= 0.4;

				if (posZavion >= 0) {
					vuelta9 = false;
					ida = true;
				}

			}

			//

			if (vuelta10)
			{
				movCir = 0.0;

				if (movCir == 0.0) {
					vuelta5 = false;
					regreso = true;
				}

			}
		}posYavion = sin(offset*toRadians);
		//--------------------------------------------------------------------------------------------------------------------------------------------------
		


		//MOVIMIENTO DE COCHE//

		if (mainWindow.getmuevetrue())


		{
			////////////////ADELANTE///////////
			if (idaCo) {
				posXcoche -= 0.1;
				movX = 0.0f;

				//////////////////////////////////////////////
				//luz de faro
				spotLights[2] = SpotLight(1.0f, 0.0f, 1.0f,//luz blanca(RGB)
					2.0f, 2.0f,//Coeficiente ambiental y difuso
					1.0f, -2.2f, -4.6f, //Posición x,y,z
					-0.1, 0.0f, 0.0f,//Vector de dirección
					1.0f, 0.0f, 0.0f,
					5.0f);
				spotLightCount++;
				spotLights[2].SetPos(poscoche + desplazamiento);
				///////////////////////////////////////////////

				if (posXcoche < -60)
				{
					idaCo = false;
					vueltaCo1 = true;
				}
			}
			////////////////VUELTA DERECHA///////////
			if (vueltaCo1)
			{
				posXcoche -= 0.07;
				posZcoche -= 0.05;
				movCoc -= 0.4;
				//////////////////////////////////////////////
				//luz de faro
				spotLights[2] = SpotLight(1.0f, 0.0f, 1.0f,//luz blanca(RGB)
					2.0f, 2.0f,//Coeficiente ambiental y difuso
					1.0f, -2.2f, -4.6f, //Posición x,y,z
					-0.1, 0.0f, -0.1f,//Vector de dirección
					1.0f, 0.0f, 0.0f,
					5.0f);
				spotLightCount++;
				spotLights[2].SetPos(poscoche + desplazamiento);
				///////////////////////////////////////////////

				if (posZcoche < -12) {//-2.1<-2.0


					vueltaCo1 = false;
					vueltaCo2 = true;

				}

			}
			/////////////////////ADELANTE///////////////
			if (vueltaCo2)
			{

				movCoc = -90.0;
				posZcoche -= 0.1;
				//////////////////////////////////////////////
				//luz de faro
				spotLights[2] = SpotLight(1.0f, 0.0f, 1.0f,//luz blanca(RGB)
					2.0f, 2.0f,//Coeficiente ambiental y difuso
					1.0f, -2.2f, -4.6f, //Posición x,y,z
					0.0, 0.0f, -0.1f,//Vector de dirección
					1.0f, 0.0f, 0.0f,
					5.0f);
				spotLightCount++;
				spotLights[2].SetPos(poscoche + desplazamiento);
				///////////////////////////////////////////////



				if (posZcoche < -75) {//-2.1<-2.0

					vueltaCo2 = false;
					vueltaCo3 = true;
				}


			}
			////////////////VUELTA BRUSCA///////////
			if (vueltaCo3)
			{

				posXcoche += 0.1;
				movCoc -= 0.3;
				//////////////////////////////////////////////
				//luz de faro
				spotLights[2] = SpotLight(1.0f, 0.0f, 1.0f,//luz blanca(RGB)
					2.0f, 2.0f,//Coeficiente ambiental y difuso
					1.0f, -2.2f, -4.6f, //Posición x,y,z
					0.1, 0.0f, -0.1f,//Vector de dirección
					1.0f, 0.0f, 0.0f,
					5.0f);
				spotLightCount++;
				spotLights[2].SetPos(poscoche + desplazamiento);
				///////////////////////////////////////////////



				if (posXcoche > -55) {//-2.1<-2.0
					vueltaCo3 = false;
					vueltaCo4 = true;
				}
			}
			////////////////VUELTA RECTA AVANCE///////////
			if (vueltaCo4)
			{
				movCoc = -180.0;
				posXcoche += 0.1;
				//////////////////////////////////////////////
				//luz de faro
				spotLights[2] = SpotLight(1.0f, 0.0f, 1.0f,//luz blanca(RGB)
					2.0f, 2.0f,//Coeficiente ambiental y difuso
					1.0f, -2.2f, -4.6f, //Posición x,y,z
					0.1, 0.0f, 0.0f,//Vector de dirección
					1.0f, 0.0f, 0.0f,
					5.0f);
				spotLightCount++;
				spotLights[2].SetPos(poscoche + desplazamiento);
				///////////////////////////////////////////////



				if (posXcoche > -48) {//-2.1<-2.0
					vueltaCo4 = false;
					vueltaCo5 = true;
				}
			}
			////////////////ADELANTE///////////
			if (vueltaCo5)
			{
				posXcoche += 0.1;
				//////////////////////////////////////////////
				//luz de faro
				spotLights[2] = SpotLight(1.0f, 0.0f, 1.0f,//luz blanca(RGB)
					2.0f, 2.0f,//Coeficiente ambiental y difuso
					1.0f, -2.2f, -4.6f, //Posición x,y,z
					0.1, 0.0f, 0.0f,//Vector de dirección
					1.0f, 0.0f, 0.0f,
					5.0f);
				spotLightCount++;
				spotLights[2].SetPos(poscoche + desplazamiento);
				///////////////////////////////////////////////



				if (posXcoche > -40) {//-2.1<-2.0
					vueltaCo5 = false;
					vueltaCo6 = true;
				}
			}
			////////////////RAMPA HACIA ARRIBA///////////
			if (vueltaCo6)
			{
				movZ = -15.0;
				posXcoche += 0.07;
				posYcoche += 0.022;
				//////////////////////////////////////////////
				//luz de faro
				spotLights[2] = SpotLight(1.0f, 0.0f, 1.0f,//luz blanca(RGB)
					2.0f, 2.0f,//Coeficiente ambiental y difuso
					1.0f, -2.2f, -4.6f, //Posición x,y,z
					0.1, 0.01, 0.0f,//Vector de dirección
					1.0f, 0.0f, 0.0f,
					5.0f);
				spotLightCount++;
				spotLights[2].SetPos(poscoche + desplazamiento);
				///////////////////////////////////////////////



				if (posYcoche > 8.3) {//-2.1<-2.0
					movZ = 0.0f;
					vueltaCo6 = false;
					vueltaCo7 = true;
				}
			}

			///////////////ADELANTE////////////////////////
			if (vueltaCo7)
			{
				posXcoche += 0.1;
				//////////////////////////////////////////////
				//luz de faro
				spotLights[2] = SpotLight(1.0f, 0.0f, 1.0f,//luz blanca(RGB)
					2.0f, 2.0f,//Coeficiente ambiental y difuso
					1.0f, -2.2f, -4.6f, //Posición x,y,z
					0.1, 0.0, 0.0f,//Vector de dirección
					1.0f, 0.0f, 0.0f,
					5.0f);
				spotLightCount++;
				spotLights[2].SetPos(poscoche + desplazamiento);
				///////////////////////////////////////////////

				if (posXcoche > 32.0) {//posXcoche > -1.0
					vueltaCo7 = false;
					vueltaCo8 = true;
				}
			}
			///////////////RAMPA HACIA ABAJO////////////////////////
			if (vueltaCo8)
			{
				movZ = 15.0;
				posXcoche += 0.075;
				posYcoche -= 0.025;
				//////////////////////////////////////////////
				//luz de faro
				spotLights[2] = SpotLight(1.0f, 0.0f, 1.0f,//luz blanca(RGB)
					2.0f, 2.0f,//Coeficiente ambiental y difuso
					1.0f, -2.2f, -4.6f, //Posición x,y,z
					0.1, 0.0, 0.0f,//Vector de dirección
					1.0f, 0.0f, 0.0f,
					5.0f);
				spotLightCount++;
				spotLights[2].SetPos(poscoche + desplazamiento);
				///////////////////////////////////////////////



				if (posYcoche < 0.01) {//-2.1<-2.0
					movZ = 0.0f;
					vueltaCo8 = false;
					vueltaCo9 = true;
				}
			}

			///////////////ADELANTE////////////////////////
			if (vueltaCo9)
			{
				posXcoche += 0.05;
				//////////////////////////////////////////////
				//luz de faro
				spotLights[2] = SpotLight(1.0f, 0.0f, 1.0f,//luz blanca(RGB)
					2.0f, 2.0f,//Coeficiente ambiental y difuso
					1.0f, -2.2f, -4.6f, //Posición x,y,z
					0.1, 0.0, 0.0f,//Vector de dirección
					1.0f, 0.0f, 0.0f,
					5.0f);
				spotLightCount++;
				spotLights[2].SetPos(poscoche + desplazamiento);
				///////////////////////////////////////////////

				if (posXcoche > 84.0) {//posXcoche > -1.0
					vueltaCo9 = false;
					vueltaCo10 = true;
				}
			}

			///////////////VUELTA DERECHA////////////////////////
			if (vueltaCo10)
			{

				posZcoche += 0.1;
				movCoc -= 0.36;
				//////////////////////////////////////////////
				//luz de faro
				spotLights[2] = SpotLight(1.0f, 0.0f, 1.0f,//luz blanca(RGB)
					2.0f, 2.0f,//Coeficiente ambiental y difuso
					1.0f, -2.2f, -4.6f, //Posición x,y,z
					0.1, 0.0, 0.1f,//Vector de dirección
					1.0f, 0.0f, 0.0f,
					5.0f);
				spotLightCount++;
				spotLights[2].SetPos(poscoche + desplazamiento);
				///////////////////////////////////////////////



				if (posZcoche > -50) {//-2.1<-2.0
					movCoc = 90.0;
					vueltaCo10 = false;
					vueltaCo11 = true;
				}
			}
			///////////////ADELANTE////////////////////////
			if (vueltaCo11)
			{

				posZcoche += 0.1;
				//////////////////////////////////////////////
				//luz de faro
				spotLights[2] = SpotLight(1.0f, 0.0f, 1.0f,//luz blanca(RGB)
					2.0f, 2.0f,//Coeficiente ambiental y difuso
					1.0f, -2.2f, -4.6f, //Posición x,y,z
					0.0, 0.0, 1.0f,//Vector de dirección
					1.0f, 0.0f, 0.0f,
					5.0f);
				spotLightCount++;
				spotLights[2].SetPos(poscoche + desplazamiento);
				///////////////////////////////////////////////
				if (posZcoche > -10) {//-2.1<-2.0

					vueltaCo11 = false;


				}
			}

		}

		/////----------------------------------------------------VARIABLES DE DESPLAZAMIENTO ----------------------------------------------------------------////

		//Para el coche
		desplazamiento = glm::vec3(posXcoche, posYcoche, posZcoche);//COCHE Se mueve en X y Z

		//Para el Helicoptero
		desplazamiento2 = glm::vec3(posXavion, posYavion, posZavion);//HELICOPTERO se mueve en x & y 


		////////////////////////////////////////////////////////////////////////////////////////////////////
		/*
		Reporte:
		1.- La luz de faro se mueva junto con el coche. Ya es su modelo de coche texturizado.
		2.-Crear luz del helicóptero, que la luz se mueva junto con el helicóptero e ilumine hacia el suelo
		3.-Agregar movimiento del helicóptero en Y y del Coche en Z.
		Adicional: que la llanta esté rotando constantemente.
		*/

		//¿Cómo ligas la luz al helicóptero?		
		//Ejercicio 2. - Crear la luz del coche y posicionar a que ilumine hacia adelante
		//Ejercicio 1. - Agregar al coche las 4 llantas con jerarquía y desplazamiento en X

		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////---------------------------------------------------DIBUJAR OBJETOS EN ESCENARIO ----------------------------------------------------------------////


		//MODELO DEL HELICOPTERO//

		//agregar incremento en X con teclado
		model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-20.0f+mainWindow.getmuevex(), 6.0f, -1.0));
		model = glm::translate(model, glm::vec3(posblackhawk.x + posXavion, posblackhawk.y + posYavion, posblackhawk.z + posZavion));
		//model = glm::translate(model, posblackhawk+desplazamiento);
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, dire * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));//Cambia de dirección el helicoptero

		model = glm::rotate(model, glm::radians(movCir), glm::vec3(0.0f, 0.0f, 1.0f));////MOVIMIENTO CIRCULAR

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//agregar material al helicóptero
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Blackhawk_M.RenderModel();
		//--------------------------------------------------------------------------------------------------------------------------------------------------


		//MODELO DEL COCHE//

		model = glm::mat4(1.0);
		//model = glm::translate(model, poscoche + desplazamiento);
		model = glm::translate(model, glm::vec3(poscoche.x + posXcoche, poscoche.y + posYcoche, poscoche.z + posZcoche));
		model = glm::rotate(model, glm::radians(movCoc), glm::vec3(0.0f, 1.0f, 0.0f));////MOVIMIENTO CIRCULAR Y
		model = glm::rotate(model, glm::radians(movZ), glm::vec3(0.0f, 0.0f, 1.0f));////MOVIMIENTO CIRCULAR Z
		model = glm::rotate(model, glm::radians(movX), glm::vec3(1.0f, 0.0f, 0.0f));////MOVIMIENTO CIRCULAR X
		modelaux = model;
		//model = glm::translate(model, glm::vec3(0.0f + desplazamiento.x, 0.5f, -1.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(movCoc), glm::vec3(0.0f, 1.0f, 0.0f));////MOVIMIENTO CIRCULAR Y
		//model = glm::rotate(model, glm::radians(movZ), glm::vec3(0.0f, 0.0f, 1.0f));////MOVIMIENTO CIRCULAR Z
		//model = glm::rotate(model, glm::radians(movX), glm::vec3(1.0f, 0.0f, 0.0f));////MOVIMIENTO CIRCULAR X
		//modelaux1 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Kitt_M.RenderModel();
		//--------------------------------------------------------------------------------------------------------------------------------------------------


		//LLanta 1 izquierda delantera//

		model = modelaux;
		model = glm::translate(model, glm::vec3(5.0f, -0.5f, 5.5f));
		//model = glm::translate(model, glm::vec3(posXcoche, posYcoche,posZcoche));
		model = glm::scale(model, glm::vec3(0.48f, 0.48f, 0.48f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(movCoc), glm::vec3(0.0f, 1.0f, 0.0f));////MOVIMIENTO CIRCULAR Y
		//model = glm::rotate(model, glm::radians(movZ), glm::vec3(0.0f, 0.0f, 1.0f));////MOVIMIENTO CIRCULAR Z
		//model = glm::rotate(model, glm::radians(movX), glm::vec3(1.0f, 0.0f, 0.0f));////MOVIMIENTO CIRCULAR X

		//model = glm::rotate(model, glm::radians(movCoc), glm::vec3(0.0f, 1.0f, 0.0f));////MOVIMIENTO CIRCULAR
		//model = glm::rotate(model, glm::radians(movZ), glm::vec3(0.0f, 0.0f, 1.0f));////MOVIMIENTO CIRCULAR
		//model = glm::rotate(model, glm::radians(movX), glm::vec3(1.0f, 0.0f, 0.0f));////MOVIMIENTO CIRCULAR
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();
		//--------------------------------------------------------------------------------------------------------------------------------------------------

		//LLanta 2 derecha delantera//

		model = modelaux;
		model = glm::translate(model, glm::vec3(5.0f, -0.5f, -0.5f));
		model = glm::scale(model, glm::vec3(0.48f, 0.48f, 0.48f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(movCoc), glm::vec3(0.0f, 1.0f, 0.0f));////MOVIMIENTO CIRCULAR
		//model = glm::rotate(model, glm::radians(movZ), glm::vec3(0.0f, 0.0f, 1.0f));////MOVIMIENTO CIRCULAR
		//model = glm::rotate(model, glm::radians(movX), glm::vec3(1.0f, 0.0f, 0.0f));////MOVIMIENTO CIRCULAR
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();
		//--------------------------------------------------------------------------------------------------------------------------------------------------

		//LLanta 3 izquierda trasera//

		model = modelaux;
		model = glm::translate(model, glm::vec3(13.5f, -0.5f, 5.5f));
		model = glm::scale(model, glm::vec3(0.48f, 0.48f, 0.48f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(movCoc), glm::vec3(0.0f, 1.0f, 0.0f));////MOVIMIENTO CIRCULAR
		//model = glm::rotate(model, glm::radians(movZ), glm::vec3(0.0f, 0.0f, 1.0f));////MOVIMIENTO CIRCULAR
		//model = glm::rotate(model, glm::radians(movX), glm::vec3(1.0f, 0.0f, 0.0f));////MOVIMIENTO CIRCULAR
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();
		//--------------------------------------------------------------------------------------------------------------------------------------------------

		//LLanta 4 derecha trasera//

		model = modelaux;
		model = glm::translate(model, glm::vec3(13.5f, -0.5f, -0.5f));
		model = glm::scale(model, glm::vec3(0.48f, 0.48f, 0.48f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(movCoc), glm::vec3(0.0f, 1.0f, 0.0f));////MOVIMIENTO CIRCULAR
		//model = glm::rotate(model, glm::radians(movZ), glm::vec3(0.0f, 0.0f, 1.0f));////MOVIMIENTO CIRCULAR
		//model = glm::rotate(model, glm::radians(movX), glm::vec3(1.0f, 0.0f, 0.0f));////MOVIMIENTO CIRCULAR
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();
		//--------------------------------------------------------------------------------------------------------------------------------------------------


		//Modelo de cabeza//

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cabeza_M.RenderModel();
		//--------------------------------------------------------------------------------------------------------------------------------------------------

		//Modelo de Alberca//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.11f, -25.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Alberca_M.RenderModel();
		glDisable(GL_BLEND);
		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Alberca1//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.11f, -25.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Alberca1_M.RenderModel();
		glDisable(GL_BLEND);
		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Silla--L//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(20.0f, 0.11f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_M.RenderModel();
		glDisable(GL_BLEND);
		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Silla//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(20.0f, 0.11f, 25.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_M.RenderModel();
		glDisable(GL_BLEND);
		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Silla//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(20.0f, 0.11f, -25.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_M.RenderModel();
		glDisable(GL_BLEND);
		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Silla//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(20.0f, 0.11f, -50.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_M.RenderModel();
		glDisable(GL_BLEND);
		//--------------------------------------------------------------------------------------------------------------------------------------------------
				//Modelo de Silla//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(20.0f, 0.11f, -75.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_M.RenderModel();
		glDisable(GL_BLEND);
		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Silla//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(20.0f, 0.11f, -100.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_M.RenderModel();
		glDisable(GL_BLEND);
		//--------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Silla--R//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(20.0f, 0.11f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_M.RenderModel();
		glDisable(GL_BLEND);
		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Silla//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(20.0f, 0.11f, 25.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_M.RenderModel();
		glDisable(GL_BLEND);
		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Silla//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(20.0f, 0.11f, 50.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_M.RenderModel();
		glDisable(GL_BLEND);
		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Silla//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(20.0f, 0.11f, 75.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_M.RenderModel();
		glDisable(GL_BLEND);
		//--------------------------------------------------------------------------------------------------------------------------------------------------
				//Modelo de Silla//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(20.0f, 0.11f, 100.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_M.RenderModel();
		glDisable(GL_BLEND);
		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Silla//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(20.0f, 0.11f, -25.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_M.RenderModel();
		glDisable(GL_BLEND);
		//--------------------------------------------------------------------------------------------------------------------------------------------------

		//Modelo de Maceta//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(6.0f, 0.11f, -1.8f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Maceta_M.RenderModel();
		glDisable(GL_BLEND);
		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Maceta//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-6.0f, 0.11f, -1.8f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Maceta_M.RenderModel();
		glDisable(GL_BLEND);
		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Maceta//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(6.0f, 0.11f, 46.8f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Maceta_M.RenderModel();
		glDisable(GL_BLEND);
		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Maceta//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-6.0f, 0.11f, 46.8f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Maceta_M.RenderModel();
		glDisable(GL_BLEND);

		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Palmera-L//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-35.0f, 0.11f, -30.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Palmera_M.RenderModel();
		glDisable(GL_BLEND);

		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Palmera//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-35.0f, 0.11f, 5.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Palmera_M.RenderModel();
		glDisable(GL_BLEND);


		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Palmera//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-35.0f, 0.11f, 40.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Palmera_M.RenderModel();
		glDisable(GL_BLEND);

		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Palmera//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-35.0f, 0.11f, 75.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Palmera_M.RenderModel();
		glDisable(GL_BLEND);

		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Palmera//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-35.0f, 0.11f, 110.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Palmera_M.RenderModel();
		glDisable(GL_BLEND);


		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Palmera-R//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(35.0f, 0.11f, -30.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Palmera_M.RenderModel();
		glDisable(GL_BLEND);

		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Palmera//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(35.0f, 0.11f, 5.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Palmera_M.RenderModel();
		glDisable(GL_BLEND);


		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Palmera//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(35.0f, 0.11f, 40.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Palmera_M.RenderModel();
		glDisable(GL_BLEND);

		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Palmera//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(35.0f, 0.11f, 75.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Palmera_M.RenderModel();
		glDisable(GL_BLEND);

		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Palmera//
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(35.0f, 0.11f, 110.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Palmera_M.RenderModel();
		glDisable(GL_BLEND);

		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Casas
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(75.0f, 3.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casas_M.RenderModel();
		glDisable(GL_BLEND);

		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Casas
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(75.0f, 3.5f, -50.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casas_M.RenderModel();
		glDisable(GL_BLEND);

		//Modelo de Escenario
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.2f, -190.0f));
		model = glm::rotate(model, 180* toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Esce_M.RenderModel();
		glDisable(GL_BLEND);

		/*
		//Modelo de Agave
		//Agave¿Que sycede si lo renderizan antes del coche y de la pista?
		//HARA QUE NO SE VEAN LAS DEMAS COSAS, por eso todo lo que tenga blend se debe dibujar hasta el final.
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 10.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//blending: transparencia o translucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Tagave.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();
		glDisable(GL_BLEND);
		//--------------------------------------------------------------------------------------------------------------------------------------------------
		*/
		/*
		//Modelo de Agave 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//blending: transparencia o translucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Tagave.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();
		glDisable(GL_BLEND);
		*/
		

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
