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


/////---------------------------------------------- VARIABLES PARA KEYFRAME----------------------------------------------------------------------////

float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;

/////---------------------------------------------- VARIABLES PARA MUSICA----------------------------------------------------------------------////
//bool musicFondo = true;
using namespace irrklang;

/////---------------------------------------------- void my_input(GLFWwindow *window);----------------------------------------------------------------------////
void inputKeyframes(bool* keys);

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
Model Luz_M;
Model Race_M;
Model Tronco_M;
Model BrazoDer_M;
Model BrazoIzq_M;
Model PiernaDer_M;
Model PiernaIzq_M;
Model Rayo_M;
/////---------------------------------------------- Declaración Variables Personaje ----------------------------------------------------------------------////
float muevePiernaDer = 0.0f;
float muevePiernaIzq = 0.0f;
bool iniPierna = true;
bool iniPierna2 = false;
float angulo = 0.0f;
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
//GLfloat posXavion = 0.0f;
//GLfloat posYavion = 0.0f;
//GLfloat posZavion = 0.0f;
float offset = 0.0f;
//Variables de movimiento de coche
float posXcoche = 0.0f;
float posYcoche = 0.0f;
float posZcoche = 0.0f;

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
bool	vueltaCo15 = false;
bool	vueltaCo16 = false;
bool	vueltaCo17 = false;
bool	vueltaCo18 = false;
bool	vueltaCo19 = false;
bool	vueltaCo20 = false;
bool	vueltaCo21 = false;
bool	vueltaCo22 = false;
bool	vueltaCo23 = false;
bool	vueltaCo24 = false;
bool	vueltaCo25 = false;
bool	vueltaCo26 = false;
bool	vueltaCo27 = false;
bool	vueltaCo28 = false;
bool	vueltaCo29 = false;
bool	vueltaCo30 = false;
bool	vueltaCo31 = false;
bool	vueltaCo32 = false;
bool	regresoCo = false;
bool	regreso = false;
//Show de luces
bool	aniShow = true;
bool	star1 = true;
bool	star2 = false;
bool	star3 = false;
bool	star4 = false;
bool	star5 = false;
bool	star6 = false;
bool	star7 = false;
bool	star8 = false;

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

///////////////////////////////-------------------------------KEYFRAMES----------------------------------------------------------------/////////////////////


bool animacion = false;



//NEW// Keyframes
float posXavion = 2.0, posYavion = 2.0, posZavion = 0;
float	movAvion_x = 0.0f, movAvion_y = 0.0f;
float giroAvion = 0;

#define MAX_FRAMES 100
int i_max_steps = 90;
int i_curr_steps = 6;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float movAvion_x;		//Variable para PosicionX
	float movAvion_y;		//Variable para PosicionY
	float movAvion_xInc;		//Variable para IncrementoX
	float movAvion_yInc;		//Variable para IncrementoY
	float giroAvion;
	float giroAvionInc;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 6;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void) //tecla L
{

	printf("frameindex %d\n", FrameIndex);


	KeyFrame[FrameIndex].movAvion_x = movAvion_x;
	KeyFrame[FrameIndex].movAvion_y = movAvion_y;
	KeyFrame[FrameIndex].giroAvion;
	//no volatil, agregar una forma de escribir a un archivo para guardar los frames
	FrameIndex++;
}

void resetElements(void) //Tecla 0
{

	movAvion_x = KeyFrame[0].movAvion_x;
	movAvion_y = KeyFrame[0].movAvion_y;
	giroAvion = KeyFrame[0].giroAvion;
}

void interpolation(void)
{
	KeyFrame[playIndex].movAvion_xInc = (KeyFrame[playIndex + 1].movAvion_x - KeyFrame[playIndex].movAvion_x) / i_max_steps;
	KeyFrame[playIndex].movAvion_yInc = (KeyFrame[playIndex + 1].movAvion_y - KeyFrame[playIndex].movAvion_y) / i_max_steps;
	KeyFrame[playIndex].giroAvionInc = (KeyFrame[playIndex + 1].giroAvion - KeyFrame[playIndex].giroAvion) / i_max_steps;

}


void animate(void)
{
	//Movimiento del objeto // barra espaciadora
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			printf("playindex : %d\n", playIndex);
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("Frame index= %d\n", FrameIndex);
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				//printf("entro aquí\n");
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//printf("se quedó aqui\n");
			//printf("max steps: %f", i_max_steps);
			//Draw animation
			movAvion_x += KeyFrame[playIndex].movAvion_xInc;
			movAvion_y += KeyFrame[playIndex].movAvion_yInc;
			giroAvion += KeyFrame[playIndex].giroAvionInc;
			i_curr_steps++;
		}

	}
}

///////////////* ---------------------------------------FIN KEYFRAMES*--------------------------------------------------------------------////////////////////////////

/////---------------------------------------------- AQUI EMPIEZA EL MAIN-----------------------------------------------------------------------------------------////
int main()
{
	float brightness = 1.0, brightnesslights = 0.2;
	float brillodir = 1.0;
	float brillo = 1.0;
	float poSpotX = 0.0;
	float poSpotY = 0.0;
	float poSpotZ = 0.0;
	float poSpotZA = 0.0;
	float difusa = 0.0;

	int dia = 0.0;
	int day_state=0.0;
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
	//-----------------------------------------------Personaje----------------------------------------------------------------//
	//Modelo Tronco--1
	Tronco_M = Model();
	Tronco_M.LoadModel("Models/tronco.obj");

	//Modelo Cabeza--2
	Cabeza_M = Model();
	Cabeza_M.LoadModel("Models/cabeza.obj");

	//Modelo Mano Derecha--3
	BrazoDer_M = Model();
	BrazoDer_M.LoadModel("Models/manoder.obj");

	//Modelo Mano Izquierda--4
	BrazoIzq_M = Model();
	BrazoIzq_M.LoadModel("Models/manoizq.obj");

	//Modelo Pierna Izquierda--5
	PiernaIzq_M = Model();
	PiernaIzq_M.LoadModel("Models/piernaizq.obj");

	//Modelo Pierna Derecha--6
	PiernaDer_M = Model();
	PiernaDer_M.LoadModel("Models/pata.fbx");
	//-----------------------------------------------------------------------------------------------------------------------------------------//

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

	//Modelo Luz
	Luz_M = Model();
	Luz_M.LoadModel("Models/luz.obj");

	//Modelo Race
	Race_M = Model();
	Race_M.LoadModel("Models/race.obj");

	//Modelo Rayo
	Rayo_M = Model();
	Rayo_M.LoadModel("Models/LightingMcqueen.obj");


	/////---------------------------------------------- CARGA DE CARAS DEL SKYBOX -----------------------------------------------------------------------////


	int sec;

		/*
		std::vector<std::string> skyboxFaces;
		skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
		skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
		skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
		skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
		skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
		skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");
		skybox = Skybox(skyboxFaces);
		printf("Hello Sky1");
		*/
	
		std::vector<std::string> skyboxFaces2;
		skyboxFaces2.push_back("Textures/Skybox/posx1.jpg");//RIGHT
		skyboxFaces2.push_back("Textures/Skybox/negx1.jpg");//LEFT
		skyboxFaces2.push_back("Textures/Skybox/negy1.jpg");//DOWN
		skyboxFaces2.push_back("Textures/Skybox/posy1.jpg");//TOP
		skyboxFaces2.push_back("Textures/Skybox/posz1.jpg");//FRONT
		skyboxFaces2.push_back("Textures/Skybox/negz1.jpg");//BACK
		skybox = Skybox(skyboxFaces2);
		//printf("Hello Sky2");
	
	
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

	





	/////---------------------------------------------- LO QUE SE PODRA VISUALIZAR CON CAMARA -------------------------------------------------------------////


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	
	//Utilizadas para cambiar la luz de escenario
	GLint activa = 1;
	GLint desactiva = 1;

	//--------------------------------------------------KEYFRAMES DECLARADOS INICIALES--------------------------------------------------------------------//

	KeyFrame[0].movAvion_x = 0.0f;
	KeyFrame[0].movAvion_y = 0.0f;
	KeyFrame[0].giroAvion = 0;


	KeyFrame[1].movAvion_x = 1.0f;
	KeyFrame[1].movAvion_y = 2.0f;
	KeyFrame[1].giroAvion = 0;


	KeyFrame[2].movAvion_x = 2.0f;
	KeyFrame[2].movAvion_y = 0.0f;
	KeyFrame[2].giroAvion = 0;


	KeyFrame[3].movAvion_x = 3.0f;
	KeyFrame[3].movAvion_y = -2.0f;
	KeyFrame[3].giroAvion = 0;

	/*	KeyFrame[4].movAvion_x = 3.0f;
		KeyFrame[4].movAvion_y = -2.0f;
		KeyFrame[4].giroAvion = 45.0f*/;

		KeyFrame[4].movAvion_x = 3.0f;
		KeyFrame[4].movAvion_y = -2.0f;
		KeyFrame[4].giroAvion = 180.0f;

		KeyFrame[5].movAvion_x = 0.0f;
		KeyFrame[5].movAvion_y = 0.0f;
		KeyFrame[5].giroAvion = 0;

	/////------------------------------------------FIN DECLARACION DE KEYFRAMES ----------------------------------------------------------------////

	/////------------------------------------------------------WHILE ----------------------------------------------------------------////
	while (!mainWindow.getShouldClose())
	{
		//---------------------DirectionalLight-----------------------------------------------------------------------------------------------------------// 
		//Madre de todas las luces, es como el sol. Solo existe una.
		mainLight = DirectionalLight(1.0f, 1.0f, 1.0f, //RGB - Color blanco- se usa este para qye se vean todos los colores
			brillodir, brightnesslights,	//Coeficiente de intensidad ambiental y difusa.
			0.0f, 0.0f, -1.0f);//Posicion en x, y , z

		//--------------------PointlLight-----------------------------------------------------------------------------------------------------------//
		unsigned int pointLightCount = 0; //Contador de luces puntuales, se tendra más de una
		//pointLights[0]
		pointLights[0] = PointLight(1.0f, 1.0f, 0.0f, //RGB
			brillo, brillo,//Intensidad ambiental y difusa
			30.0f, 25.0f, -93.0f,//Valor de posición 
			0.3f, 0.2f, 0.1f);//Coeficientes de ecuación de segundo grado
		pointLightCount++;//Aumenta contador


		//pointLights[1]

		pointLights[1] = PointLight(1.0f, 1.0f, 0.0f, //RGB
			brillo, brillo,//Intensidad ambiental y difusa
			30.0f, 25.0f, 13.0f,//Valor de posición 
			0.3f, 0.2f, 0.1f);//Coeficientes de ecuación de segundo grado
		pointLightCount++;//Aumenta contador

		//pointLights[2]

		pointLights[2] = PointLight(1.0f, 1.0f, 0.0f, //RGB
			brillo, brillo,//Intensidad ambiental y difusa
			-30.0f, 25.0f, -93.0f,//Valor de posición 
			0.3f, 0.2f, 0.1f);//Coeficientes de ecuación de segundo grado
		pointLightCount++;//Aumenta contador


		//pointLights[3]

		pointLights[3] = PointLight(1.0f, 1.0f, 0.0f, //RGB
			brillo, brillo,//Intensidad ambiental y difusa
			-30.0f, 25.0f, 13.0f,//Valor de posición 
			0.3f, 0.2f, 0.1f);//Coeficientes de ecuación de segundo grado
		pointLightCount++;//Aumenta contador


		//---------------------SpotLight----------------------------------------------------------------------------------------------------------------// 

		unsigned int spotLightCount = 0;// Contador Luces SpotLight


		//Luz de Camara-spotLights[0]

		spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f, //RGB
			0.0f, 2.0f,//Coeficiente ambiental y difuso
			0.0f + poSpotX, 40.0f + poSpotY, 75.0f + poSpotZ,//Posición x,y,z
			0.0f, -1.0f, 0.0f,//Vector de cirección, apunta hacia -y//DONDE APUNTA
			1.0f, 0.0f, 0.0f,//Valores de ecuación de segundo grado
			5.0f);//Radio de nuestro cono invicible//RADIO DEL CONO
		spotLightCount++;
		//---------------------Luces Fiesta----------------------------------------------------------------------------------------------------------------// 

		//Luz Fiesta-spotLights[1]
		spotLights[1] = SpotLight(1.0f, 0.0f, 0.0f,//RGB-Roja
			1.0f, 1.0f,//Coefciente ambient y difuso
			10.4f + poSpotX, 40.5f + poSpotY, 94.5f + poSpotZ,//Posición x,y,x
			0.0f, -1.0f, -0.5f,//Vector de dirección
			1.0f, 0.0f, 0.0f,//Valores de ecuación
			10.0f);
		spotLightCount++;

		//Luz Fiesta-spotLights[2]
		spotLights[2] = SpotLight(0.0f, 0.0f, 1.0f,//RGB-Azul
			1.0f, 1.0f,//Coeficiente ambiental y difuso
			-4.4f + poSpotX, 40.5f + poSpotY, 94.5f + poSpotZA, //Posición x,y,z
			0.0f, -1.0f, -0.5f,//Vector de dirección
			1.0f, 0.0f, 0.0f,
			10.0f);
		spotLightCount++;



		//Luz Fiesta- spotLights[3]
		spotLights[3] = SpotLight(0.0f, 1.0f, 0.0f,//luz verde
			1.0f, 1.0f,//Coeficiente ambiental y difuso
			-19.4f + poSpotX, 40.5f + poSpotY, 94.5f + poSpotZ, //Posición x,y,z
			0.0f, -1.0f, -0.5f,//Vector de dirección
			1.0f, 0.0f, 0.0f,
			10.0f);
		spotLightCount++;


		switch (dia) {
		case 0:
			brillodir -= 0.0009;
			brillo = 0.0;
			skybox.r -= 0.0009;
			skybox.g -= 0.0009;
			skybox.b -= 0.0009;
			if (brillodir <= 0.2) {
				dia = 1;
			}
			break;
		case 1:
			brillodir += 0.0009;
			brightnesslights -= 0.0009;
			brillo = 10.0;
			skybox.r += 0.0009;
			skybox.g += 0.0009;
			skybox.b += 0.0009;
			if (brillodir >= 1.0) {
				dia = 0;
			}
			break;
		}
		//

		
		if (mainWindow.getshow() == 1)
		{
			//if (activa == 1) {
				activa = 0;
				desactiva = 0;
				printf("Aprieto M y activo");

				if (star1)
				{	
					poSpotX += 0.7;
					if (poSpotX > 20)
					{
						star1 = false;
						star2 = true;
					}
				}
				if (star2)
				{
					poSpotX -= 0.7;
					if (poSpotX < -18)
					{
						star2 = false;
						star3 = true;
					}
				}
				if (star3)
				{
					poSpotX += 0.7;
					if (poSpotX > 1)
					{
						star3 = false;
						star4 = true;
					}
				}
				if (star4)
				{
					poSpotZ += 0.7;
					poSpotZA -= 0.7;
					if (poSpotZ > 20)
					{
						star4 = false;
						star5 = true;
					}
				}
				if (star5)
				{
					poSpotZ -= 0.7;
					poSpotZA += 0.7;
					if (poSpotZ < -20)
					{
						star5 = false;
						star6 = true;
					}
				}
				if (star6)
				{
					poSpotZ += 0.7;
					poSpotZA -= 0.7;
					if (poSpotZ > 20)
					{
						star6 = false;
						star7 = true;
					}
				}
				if (star7)
				{
					poSpotZ -= 0.7;
					poSpotZA += 0.7;
					if (poSpotZ < 0.5)
					{
						star7 = false;
						//star1 = true;


					}
				}
			//}
		}
		else if (mainWindow.getshow() == 0) {
			if (desactiva == 0) {
				printf("Aprieto N y desactivo");
				star1 = true;
				star2 = false;
				star3 = false;
				star4 = false;
				star5 = false;
				star6 = false;
				star7 = false;
				star8 = false;
	
				activa = 1;
				desactiva = 1;

			}


		}
	
	
		GLfloat now = glfwGetTime();
		
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		//------------------------------------------------------------para keyframes------------------------------------------------------------------------------
		inputKeyframes(mainWindow.getsKeys());
		animate();

		//-------------------------------------------------------------- Clear the window-------------------------------------------------------------------------
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
		//spotLights[3].SetPos(posblackhawk + desplazamiento2);

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);

		if (mainWindow.getshow()) {
			shaderList[0].SetSpotLights(spotLights, spotLightCount);
		}
		else {
			shaderList[0].SetSpotLights(spotLights, spotLightCount-3);
		}
		/////------------------------------------------DIBUJAR EL PISO Y DECLARAR MODEL Y AUXILIARES ----------------------------------------------------------------////

		//MODEL
		glm::mat4 model(1.0);

		//MODELAUX
		glm::mat4 modelaux(1.0);

		//----------------DIBUJAR PISO------------------------------------------------------------------------------//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -70.0f));
		model = glm::scale(model, glm::vec3(20.0f, 0.1f, 20.0f));
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
		/*
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

		*/
		//--------------------------------------------------------------------------------------------------------------------------------------------------

		//MOVIMIENTO DE COCHE//
		if(true)
		{
			if (idaCo) //AVANZA
			{
				posXcoche += 0.5;
				movX = 0.0f;
				if (posXcoche > 100)
				{
					idaCo = false;
					vueltaCo1 = true;
					
				}
			}
			if (vueltaCo1)// VUELTA IZQ
			{
				posXcoche += 0.1;
				posZcoche -= 0.1;
				movCoc += 0.8f;
				if (posZcoche<  -10)
				{
					vueltaCo1 = false;
					vueltaCo2 = true;
				}
			}
			if (vueltaCo2)//AVANZA
			{

				posZcoche -= 0.5;
				movCoc =90;
				if (posZcoche < -90)
				{
					vueltaCo2 = false;
					vueltaCo3 = true;
				}
			}
			if (vueltaCo3)//VUELTA IZQ
			{

				posZcoche -= 0.1;
				movCoc += 0.8f;
				if (posZcoche < -95)
				{
					vueltaCo3 = false;
					vueltaCo4 = true;
				}
			}
			if (vueltaCo4)// AVANZA INCLINADO -X -Z
			{

				posZcoche -= 0.2;
				posXcoche -= 0.2;
				
				if (posZcoche < -110)
				{
					vueltaCo4 = false;
					vueltaCo5 = true;
				}
			}
			if (vueltaCo5) //VUELTA IZQ
			{
				movCoc += 1.0;
				posZcoche -= 0.1;
				posXcoche -= 0.1;

				if (posZcoche < -120)
				{
					vueltaCo5 = false;
					vueltaCo6 = true;
				}
			}
			if (vueltaCo6) //VUELTA IZQ -X +Z
			{
				movCoc += 1.0;
				posXcoche -= 0.2;
				posZcoche += 0.2;

				if (posXcoche < 69)
				{
					vueltaCo6 = false;
					vueltaCo7 = true;
				}
			}
			if (vueltaCo7) //VUELTA IZQ +X +Z
			{
				posXcoche += 0.2;
				posZcoche += 0.2;

				if (posXcoche > 90)
				{
					vueltaCo7 = false;
					vueltaCo8 = true;
				}
			}
			if (vueltaCo8) //VUELTA DER-AVANZA SOBRE +Z
			{
				movCoc -= 0.4;
				posZcoche += 0.2;

				if (posZcoche >-40)
				{
					vueltaCo8 = false;
					vueltaCo9 = true;
				}
			}
			if (vueltaCo9) //AVANZA -X +Z
			{
				//movCoc -= 0.4;
				posZcoche += 0.2;
				posXcoche -= 0.2;

				if (posXcoche < 70)
				{
					vueltaCo9 = false;
					vueltaCo10 = true;
				}
			}
			if (vueltaCo10) //VUELTA DER
			{
				movCoc -= 0.35;
				posXcoche -= 0.2;

				if (posXcoche < 45)
				{
					vueltaCo10 = false;
					vueltaCo11 = true;
				}
			}
			if (vueltaCo11) //AVANZA -X
			{
				posXcoche -= 0.5;
				posZcoche += 0.01;

				if (posXcoche < -80)
				{
					vueltaCo11 = false;
					vueltaCo12 = true;
				}
			}

			if (vueltaCo12) //VUELTA DER
			{
				movCoc -= 1.2;
				posXcoche -= 0.2;
				posZcoche -= 0.2;

				if (posXcoche < -95)
				{
					vueltaCo12 = false;
					vueltaCo13 = true;
				}
			}
			if (vueltaCo13) //AVANZA -Z
			{
				//movCoc -= 1.2;
				//posXcoche -= 0.2;
				posZcoche -= 0.5;

				if (posZcoche < -80)
				{
					vueltaCo13 = false;
					vueltaCo14 = true;
				}
			}
			if (vueltaCo14) //AVANZA  +X -Z
			{
				movCoc -= 1.0;
				posXcoche += 0.2;
				posZcoche -= 0.2;


				if (posZcoche < -98)
				{
					vueltaCo14 = false;
					vueltaCo15 = true;
				}
			}
			if (vueltaCo15) // +X +Z
			{
				movCoc -= 1.0;
				posXcoche += 0.2;
				posZcoche += 0.2;


				if (posZcoche > -80)
				{
					vueltaCo15 = false;
					vueltaCo16 = true;
				}
			}
			if (vueltaCo16) // +X -Z
			{
				movCoc += 0.5;
				posXcoche += 0.1;
				posZcoche += 0.3;


				if (posZcoche > -50)
				{
					vueltaCo16 = false;
					vueltaCo17 = true;
				}
			}
			if (vueltaCo17) // +X -Z
			{
				movCoc += 0.5;
				posXcoche += 0.2;
				posZcoche += 0.1;


				if (posZcoche > -35)//d
				{
					vueltaCo17 = false;
					vueltaCo18 = true;
				}
			}
			if (vueltaCo18) // +X -Z
			{
				movCoc += 0.7;
				posXcoche += 0.1;
				posZcoche -= 0.1;


				if (posZcoche < -50)//d
				{
					vueltaCo18 = false;
					vueltaCo19 = true;
				}
			}
			if (vueltaCo19) // +X -Z
			{
				//movCoc += 0.7;
				posXcoche -= 0.2;
				posZcoche -= 0.2;


				if (posZcoche < -85)//d
				{
					vueltaCo19 = false;
					vueltaCo20 = true;
				}
			}
			if (vueltaCo20) // +X -Z
			{
				movCoc -= 0.9;
				posXcoche += 0.1;
				posZcoche -= 0.1;


				if (posZcoche < -105)//d
				{
					vueltaCo20 = false;
					vueltaCo21 = true;
				}
			}
			if (vueltaCo21) // +X -Z
			{
				posXcoche += 0.2;
				posZcoche += 0.2;


				if (posZcoche > -35)//d
				{
					vueltaCo21 = false;
					vueltaCo22 = true;
				}
			}
			if (vueltaCo22) // +X -Z
			{
				movCoc += 0.8;
				posXcoche += 0.1;
				posZcoche -= 0.1;


				if (posZcoche < -45)//d
				{
					vueltaCo22 = false;
					vueltaCo23 = true;
				}
			}
			if (vueltaCo23) // +X -Z
			{
				movCoc += 0.8;
				posXcoche += 0.09;
				posZcoche -= 0.2;


				if (posZcoche < -68)//d
				{
					vueltaCo23 = false;
					vueltaCo24 = true;
				}
			}
			if (vueltaCo24) // +X -Z
			{
				//movCoc += 0.8;
				posXcoche -= 0.2;
				posZcoche -= 0.2;


				if (posZcoche < -115)//d
				{
					vueltaCo24 = false;
					vueltaCo25 = true;
				}
			}
			if (vueltaCo25) // +X -Z
			{
				movCoc += 1.8;
				posXcoche -= 0.2;
				posZcoche -= 0.2;


				if (posZcoche < -120)//d
				{
					vueltaCo25 = false;
					vueltaCo26 = true;
				}
			}
			if (vueltaCo26) // +X -Z
			{
				//movCoc += 1.8;
				posXcoche -= 0.5;
				//posZcoche -= 0.2;


				if (posXcoche < -100)//d
				{
					vueltaCo26 = false;
					vueltaCo27 = true;
				}
			}
			if (vueltaCo27) // +X -Z
			{
				movCoc += 0.88;
				posZcoche += 0.2;
				posXcoche -= 0.1;


				if (posZcoche > -99)//d
				{
					vueltaCo27 = false;
					vueltaCo28 = true;
				}
			}
			if (vueltaCo28) // +X -Z
			{
				//movCoc += 0.88;
				posZcoche += 0.5;
				//posXcoche -= 0.1;


				if (posZcoche > -26)//d
				{
					vueltaCo28 = false;
					vueltaCo29 = true;
				}
			}
			if (vueltaCo29) // +X -Z
			{
				movCoc += 0.6;
				posZcoche += 0.18;
				posXcoche += 0.1;


				if (posZcoche > 2)//d
				{
					vueltaCo29 = false;
					vueltaCo30 = true;
				}
			}
			if (vueltaCo30) // +X -Z
			{
				//movCoc += 0.6;
				posZcoche -= 0.008;
				posXcoche += 0.5;


				if (posXcoche > 30)//d
				{
					vueltaCo30 = false;
					idaCo = true;
				}
			}



	
		}
		/*
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

		}*/

		/////----------------------------------------------------VARIABLES DE DESPLAZAMIENTO ----------------------------------------------------------------////

		//Para el coche
		desplazamiento = glm::vec3(posXcoche, posYcoche, posZcoche);//COCHE Se mueve en X y Z

		//Para el Helicoptero
		desplazamiento2 = glm::vec3(posXavion, posYavion, posZavion);//HELICOPTERO se mueve en x & y 

		/////---------------------------------------------------DIBUJAR OBJETOS EN ESCENARIO ----------------------------------------------------------------////

		/*
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

		model = glm::mat4(1.0);
		posblackhawk = glm::vec3(posXavion + movAvion_x, posYavion + movAvion_y, posZavion);
		model = glm::translate(model, posblackhawk);
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, (-90 + giroAvion) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Blackhawk_M.RenderModel();
		spotLights[3].SetPos(posblackhawk);
		//--------------------------------------------------------------------------------------------------------------------------------------------------
		*/

		/*
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
		*/
		//----------------------------------------------------------------------------------------------------------------------------------------------------//
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////// HASTA AQUI LLEGA ///////////////////////////////////////////////////////////7
		/*
		///////////////// QUITAALOOOOOOOOOOOO////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////
		 
		
		//Modelo Tronco//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f,0.0f,-100.0f));
		//model = glm::rotate(model, glm::radians(movCoc), glm::vec3(0.0f, 1.0f, 0.0f));////MOVIMIENTO CIRCULAR Y
		//model = glm::rotate(model, glm::radians(movZ), glm::vec3(0.0f, 0.0f, 1.0f));////MOVIMIENTO CIRCULAR Z
		//model = glm::rotate(model, glm::radians(movX), glm::vec3(1.0f, 0.0f, 0.0f));////MOVIMIENTO CIRCULAR X
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_M.RenderModel();
		
		//Modelo de cabeza//
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cabeza_M.RenderModel();

		//Modelo Brazo Der//
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BrazoDer_M.RenderModel();

		//Modelo Brazo Izq//
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//model = glm::rotate(model, (-30 + angulo) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BrazoIzq_M.RenderModel();

		angulo -= 5.0f;
		//Modelo Pierna Der//
		model = modelaux; 
		model = glm::translate(model, glm::vec3(-5.0f, 13.0f, 0.0f));
		model = glm::rotate(model, (-30+angulo) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Movimiento de PIERNA DERECHA 
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PiernaDer_M.RenderModel();

		//Modelo Pierna Izq//
		model = modelaux;
		//model = glm::rotate(model, (-30 + angulo) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Movimiento de PIERNA DERECHA 
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PiernaIzq_M.RenderModel();



		//--------------------------------------------------------------------------------------------------------------------------------------------------//

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


		/////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////// HASTA AQUI LLEGA ///////////////////////////////////////////////////////////7
		*/ 
		///////////////// QUITAALOOOOOOOOOOOO////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////
		 

		/////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////// HASTA AQUI LLEGA ///////////////////////////////////////////////////////////7
		/*
		///////////////// QUITAALOOOOOOOOOOOO////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////

		//Modelo de Escenario
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.2f, 75.0f));
		model = glm::rotate(model, 0* toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Esce_M.RenderModel();
		glDisable(GL_BLEND);

		//Modelo de Luz
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, 0.1f, -93.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Luz_M.RenderModel();
		glDisable(GL_BLEND);

		//Modelo de Luz
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, 0.1f, 13.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Luz_M.RenderModel();
		glDisable(GL_BLEND);

		//Modelo de Luz
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-40.0f, 0.1f, -93.0f));
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Luz_M.RenderModel();
		glDisable(GL_BLEND);

		//Modelo de Luz
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-40.0f, 0.1f, 13.0f));
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Luz_M.RenderModel();
		glDisable(GL_BLEND);



		/////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////// HASTA AQUI LLEGA ///////////////////////////////////////////////////////////7
		*/
		///////////////// QUITAALOOOOOOOOOOOO////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////

		//Modelo de Pista
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, -180.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Race_M.RenderModel();
		glDisable(GL_BLEND);

		//Modelo de Rayo MC
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f+posXcoche, 0.1f+posYcoche, -128.0f+posZcoche));
		model = glm::rotate(model, glm::radians(movCoc), glm::vec3(0.0f, 1.0f, 0.0f));////MOVIMIENTO CIRCULAR Y
		model = glm::rotate(model, glm::radians(movZ), glm::vec3(0.0f, 0.0f, 1.0f));////MOVIMIENTO CIRCULAR Z
		model = glm::rotate(model, glm::radians(movX), glm::vec3(1.0f, 0.0f, 0.0f));////MOVIMIENTO CIRCULAR X
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		
		Rayo_M.RenderModel();

		



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

void movimientoPiernas() {
	if (true) {
		if (iniPierna) {
			muevePiernaDer += 5.0;
			muevePiernaIzq -= 5.0;
			if (muevePiernaDer>90) {
				iniPierna = false;
				iniPierna2 = true;
			}
		}
		if (iniPierna2) {
			muevePiernaDer -= 5.0;
			muevePiernaIzq += 5.0;
			if (muevePiernaDer < -90) {
				iniPierna2 = false;
				iniPierna = true;
			}
		}
	}
	
}
void inputKeyframes(bool* keys)
{
	if (keys[GLFW_KEY_1])//
	{
		if (reproduciranimacion < 1)
		{
			if (play == false && (FrameIndex > 1))
			{
				resetElements();
				//First Interpolation				
				interpolation();
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
				reproduciranimacion++;
				printf("presiona 0 para habilitar reproducir de nuevo la animación'\n");
				habilitaranimacion = 0;

			}
			else
			{
				play = false;

			}
		}
	}
	if (keys[GLFW_KEY_2])//
	{
		if (habilitaranimacion < 1)
		{
			reproduciranimacion = 0;
			printf("Ya puedes reproducir de nuevo la animación con la tecla de barra espaciadora'\n");
		}
	}

	if (keys[GLFW_KEY_3])//
	{
		if (guardoFrame < 1)
		{
			saveFrame();
			//printf("movAvion_x es: %f\n", movAvion_x);
			//printf("movAvion_y es: %f\n", movAvion_y);
			printf("presiona P para habilitar guardar otro frame'\n");
			guardoFrame++;
			reinicioFrame = 0;
		}
	}
	if (keys[GLFW_KEY_4])//
	{
		if (reinicioFrame < 1)
		{
			guardoFrame = 0;
			printf("Ya puedes guardar otro frame presionando la tecla L'\n");
		}
	}


	if (keys[GLFW_KEY_5])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			movAvion_x += 1.0f;
			printf("movAvion_x es: %f\n", movAvion_x);
			ciclo++;
			ciclo2 = 0;
			printf("Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_6])
	{
		if (ciclo2 < 1)
		{
			ciclo = 0;
			printf("Ya puedes modificar tu variable presionando la tecla 1\n");
		}
	}

}