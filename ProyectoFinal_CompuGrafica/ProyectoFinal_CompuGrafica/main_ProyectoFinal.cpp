/*
Semestre 2021-2
Proyecto de computaci?n gr?fica e interacci?n humano-computadora
Alumno: Sandoval Ju?rez Luis Arturo 3
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

//Librer?a para m?sica
#include "irrKlang.h"


/////---------------------------------------------- PARA LA ILUMINACION----------------------------------------------------------------------////
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Material.h"

//float ang;
//-------------------------------------------------VARIABLES PARA ACTIVAR ANIMACION DE BASKET--------------------------------------------------------// 
int basketball = 0;
//-------------------------------------------------VARIABLES PARA ACTIVAR ANIMACION DE FLOTADOR------------------------------------------------------//

int flota = 0;
//-------------------------------------------------VARIABLES PARA ACTIVAR ANIMACION DE SPIDERMAN-----------------------------------------------------//

int spiderman = 0;
//-------------------------------------------------VARIABLES PARA LAS CAMARAS------------------------------------------------------------------------//
int cambioTer=1;
int cambioArea = 0;
float mueveXlibre;
float mueveYoZlibre;
float mueveCam;
float mueveCam2;
/////---------------------------------------------- VARIABLES PARA KEYFRAME-------------------------------------------------------------------------////

float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;

/////---------------------------------------------- VARIABLES PARA MUSICA----------------------------------------------------------------------------////
//bool musicFondo = true;
using namespace irrklang;

/////---------------------------------------------- void my_input(GLFWwindow *window);----------------------------------------------------------------////
void inputKeyframes(bool* keys);

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

/////---------------------------------------------- ----------DECLARACION DE CAMERA ------------------------------------------------------------------////

Camera camera;

/////------------------------------------------------------- DECLARACION DE TEXTURAS -----------------------------------------------------------------////

Texture pisoTexture;
Texture pastoTexture;


/////-------------------------------------------------------- DECLARACION DE MODELOS ----------------------------------------------------------------------////

//Modelo Cabeza
Model Cabeza_M;
//Modelo Alberca
Model Alberca_M;
//Modelo ALberca chica
Model Alberca1_M;
//Modelo de camastro
Model Silla_M;
//Modelo Maceta
Model Maceta_M;
//Modelo Palmera
Model Palmera_M;
//Modelo Casas
Model Casas_M;
//Modelo Escenario
Model Esce_M;
//Porteria
Model Porteria_M;
// Balon
Model Balon_M;
//Luz de los faros
Model Luz_M;
//Pista de Carreras
Model Race_M;
//-----------------------------------------------------Modelos BlackPanter Hombre----------------------------------------------------------------------//
Model TroncoHB_M;
Model BrazoDerHB_M;
Model BrazoIzqHB_M;
Model PiernaDerHB_M;
Model PiernaIzqHB_M;
Model CabezaHB_M;
//----------------------------------------------------Modelos Spiderman-------------------------------------------------------------------------------//
Model Tronco_M;
Model BrazoDer_M;
Model BrazoIzq_M;
Model PiernaDer_M;
Model PiernaIzq_M;
Model Rayo_M;
//Control Remoto
Model Remoto_M;
//Edificioo
Model Edificio_M;
//------------------------------------------------------------Modelos Pajaro-----------------------------------------------------------------------------//
Model TroncoPa_M;
Model AlaIzqPa_M;
Model AlaDerPa_M;
Model PataIzqPa_M;
Model PataDerPa_M;
//Flotador
Model Flotador_M;
//Basket
Model Basket_M;

/////-----------------------------------------------------Declaraci?n Variables Basket ----------------------------------------------------------------------////
float movXbasket = 0.0f;
float movYbasket = 0.0f;
float movZbasket = 0.0f;
float angub = 0.0f;
bool bake1 = true;
bool bake2 = false;
bool bake3 = false;
bool bake4 = false;
bool bake5 = false;
bool bake6 = false;
bool bake7 = false;
bool bake8 = false;
bool bake9 = false;
bool bake10 = false;
bool bake11= false;
bool bake12 = false;
bool bake13 = false;
bool bake14 = false;
bool bake15 = false;
bool bake16 = false;
bool bake17 = false;
bool bake18 = false;
/////-----------------------------------------------------Declaraci?n Variables Balon ----------------------------------------------------------------------////
float movXbalon = 0.0f;
float movYbalon = 0.0f;
float movZbalon = 0.0f;
/////-----------------------------------------------------Declaraci?n Variables Blackpanter ----------------------------------------------------------------------////
float rotaXblack = 0.0f;
float rotaYblack = 0.0f;
float rotaZblack = 0.0f;
float movXblack = 0.0f;
float movYblack = 0.0f;
float movZblack = 0.0f;
float muevePiernaDerblack = 0.0f;
float muevePiernaIzqblack = 0.0f;
bool iniPiernablack = true;
bool iniPierna2black = false;
bool iniBrazoblack1 = true;
bool iniBrazo2black1 = false;
bool movB1 = true;
bool mov2B1 = false;
float mueveBrazoDerblack = 0.0f;
float mueveBrazoIzqblack = 0.0f;
float contador2black = 0.0f;
float anguloblack = 0.0f;
bool estado1black = true;
bool estado2black = false;
bool estado3black = false;
bool estado4black = false;
bool estado5black = false;
bool estado6black = false;
bool estado7black = false;
bool estado8black = false;
bool estado9black = false;
bool estado10black = false;
bool estado11black = false;
bool estado12black = false;
bool estado13black = false;
bool estado14black = false;
bool estado15black = false;
bool estado16black = false;
bool estado17black = false;
bool estado18black = false;
bool estado19black = false;
/////-----------------------------------------------------Declaraci?n Variables Blackpanter2 ----------------------------------------------------------------------////
bool inib2bra = true;
bool inib2bra2 = false;
bool inib2pie = true;
bool inib2pie2 = false;
bool inib2brinco = true;
bool inib2brinco2 = false;
bool brazos = true;
bool brazos2=false;
bool arribita = true;
bool arribita2 = false;

float rotaXblack2 = 0.0f;
float rotaYblack2 = 0.0f;
float rotaZblack2 = 0.0f;
float movXblack2 = 0.0f;
float movYblack2 = 0.0f;
float movZblack2 = 0.0f;
float muevePiernaDerblack2 = 0.0f;
float muevePiernaIzqblack2 = 0.0f;
bool iniPiernablack2 = true;
bool iniPierna2black2 = false;
bool iniBrazoblack2 = true;
bool iniBrazo2black2 = false;
float mueveBrazoDerblack2 = 0.0f;
float mueveBrazoIzqblack2 = 0.0f;
float contador2black2 = 0.0f;
float anguloblack2 = 0.0f;

/////-----------------------------------------------------Declaraci?n Variables Spiderman ----------------------------------------------------------------------////
float rotaXSpider = 0.0f;
float rotaYSpider = 0.0f;
float rotaZSpider = 0.0f;
float movXspider = 0.0f;
float movYspider = 0.0f;
float movZspider = 0.0f;
float muevePiernaDer = 0.0f;
float muevePiernaIzq = 0.0f;
bool iniPierna = true;
bool iniPierna2 = false;
bool iniBrazo = true;
bool iniBrazo2 = false;
float mueveBrazoDer = 0.0f;
float mueveBrazoIzq = 0.0f;
float contador2 = 0.0f;
float contador3 = 0.0f;
float angulo = 0.0f;
bool estado1 = true;
bool estado2 = false;
bool estado3 = false;
bool estado4 = false;
bool estado5 = false;
bool estado6 = false;
bool estado7 = false;
bool estado8 = false;
bool estado9 = false;
bool estado10 = false;
bool estado11 = false;
bool estado12 = false;
bool estado13 = false;
bool estado14 = false;
bool estado15 = false;
bool estado16 = false;
bool estado17 = false;
bool estado18 = false;
bool estado19 = false;

/////---------------------------------------------- Declaraci?n Variables Flotador -------------------------------------------------------------------------////
float movXflotador = 0.0f;
float movYflotador = 0.0f;
float movZflotador = 0.0f;
bool es1 = true;
bool es2 = false;
bool es3 = false;
bool es4 = false;
bool es5 = false;
bool es6 = false;
bool es7 = false;
bool es8 = false;
bool es9 = false;
bool es10 = false;
bool es11 = false;
/////---------------------------------------------- Declaraci?n Variables Pajaro -------------------------------------------------------------------------////
float rotaXpajaro = 0.0f;
float rotaYpajaro = 0.0f;
float rotaZpajaro = 0.0f;
float movXpajaro = 0.0f;
float movYpajaro = 0.0f;
float movZpajaro = 0.0f;
float muevePataDer = 0.0f;
float muevePataIzq = 0.0f;
float mueveAlaDer = 0.0f;
float mueveAlaIzq = 0.0f;
bool iniAla = true;
bool iniAla2 = false;
bool iniPata = true;
bool iniPata2 = false;
bool est1 = true;
bool est2 = false;
bool est3 = false;
bool est4 = false;
bool est5 = false;
bool est6 = false;
bool est7 = false;
bool est8 = false;
bool est9 = false;
bool est10 = false;
bool est11 = false;
bool est12 = false;
bool est13 = false;
bool est14 = false;
bool est15 = false;
bool est16 = false;
bool est17 = false;
bool est18 = false;
bool est19 = false;
bool est20 = false;
bool est21 = false;
bool est22 = false;
/////-------------------------------------------------------------DECLARACION DE SKYBOX ----------------------------------------------------------------------////
Skybox skybox;

/////---------------------------------------------- DECLARACION DE MATERIALES ---------------------------------------------------------------------------------////
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

//----------------------------------------------------------------Declaracion de Variables para el coche------------------------------------------------------------//
float posXcoche = 0.0f;
float posYcoche = 0.0f;
float posZcoche = 0.0f;
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
//----------------------------------------------------------------Declaracion de Variables Show de luces------------------------------------------------------------//
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


//c?lculo del promedio de las normales para sombreado de Phong
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

//-------------------------------------------------------FUNCIONES----------------------------------------------------------------------------//
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
				//printf("entro aqu?\n");
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//printf("se qued? aqui\n");
			//printf("max steps: %f", i_max_steps);
			//Draw animation
			movAvion_x += KeyFrame[playIndex].movAvion_xInc;
			movAvion_y += KeyFrame[playIndex].movAvion_yInc;
			giroAvion += KeyFrame[playIndex].giroAvionInc;
			i_curr_steps++;
		}

	}
}
//-------------------------------------------------------FUNCION MOV PIERNAS----------------------------------------------------------------------------//
void movimientoPiernas() {
	if (true) {
		if (iniPierna) {
			muevePiernaDer += 2.0;
			muevePiernaIzq -= 2.0;
			if (muevePiernaDer > 30) {
				iniPierna = false;
				iniPierna2 = true;
			}
		}
		if (iniPierna2) {
			muevePiernaDer -= 2.0;
			muevePiernaIzq += 2.0;
			if (muevePiernaDer < -30) {
				iniPierna2 = false;
				iniPierna = true;
			}
		}
	}

}
//-------------------------------------------------------FUNCION MOV BRAZOS----------------------------------------------------------------------------//
void movimientoBrazos() {
	if (true) {
		if (iniBrazo) {
			mueveBrazoDer += 2.0;
			mueveBrazoIzq -= 2.0;
			if (mueveBrazoDer > 30) {
				iniBrazo = false;
				iniBrazo2 = true;
			}
		}
		if (iniBrazo2) {
			mueveBrazoDer -= 2.0;
			mueveBrazoIzq += 2.0;
			if (mueveBrazoDer < -30) {
				iniBrazo2 = false;
				iniBrazo = true;
			}
		}
	}

}
//-------------------------------------------------------FUNCION PARA ALAS----------------------------------------------------------------------------//
void movimientoAlas() {
	if (true) {
		if (iniAla) {
			mueveAlaDer += 2.0;
			mueveAlaIzq -= 2.0;
			if (mueveAlaDer > 50) {
				iniAla = false;
				iniAla2 = true;
			}
		}
		if (iniAla2) {
			mueveAlaDer -= 2.0;
			mueveAlaIzq += 2.0;
			if (mueveAlaDer < -50) {
				iniAla2 = false;
				iniAla = true;
			}
		}
	}

}
//-------------------------------------------------------FUNCION PARA PATAS----------------------------------------------------------------------------//
void movimientoPatas() {
	if (true) {
		if (iniPata) {
			muevePataDer += 2.0;
			muevePataIzq -= 2.0;
			if (muevePataDer > 25) {
				iniPata = false;
				iniPata2 = true;
			}
		}
		if (iniPata2) {
			muevePataDer -= 2.0;
			muevePataIzq += 2.0;
			if (muevePataDer < -25) {
				iniPata2 = false;
				iniPata = true;
			}
		}
	}

}


//-------------------------------------------------------MOVIMIENTO BRAZOS PANTERA 1----------------------------------------------------------------------------//
void movimientoBraB1() {
	if (true) {
		if (iniBrazoblack1) {
			mueveBrazoDerblack -= 5.3;
			mueveBrazoIzqblack -= 5.3;
			if (mueveBrazoDerblack < -180) {
				iniBrazoblack1 = false;
				iniBrazo2black1 = true;
			}
		}
		if (iniBrazo2black1) {
			mueveBrazoDerblack += 5.3;
			mueveBrazoIzqblack += 5.3;
			if (mueveBrazoDerblack >=0) {
				iniBrazo2black1 = false;
				iniBrazoblack1 = true;
			}
		}
	}

}
//-------------------------------------------------------MOVIMIENTO PIERNAS PANTERA 1----------------------------------------------------------------------------//
void movimientoPiernasB1() {
	if (true) {
		if (iniPiernablack) {
			muevePiernaDerblack += 4.3;
			muevePiernaIzqblack -= 4.3;
			if (muevePiernaDerblack > 15) {
				iniPiernablack = false;
				iniPierna2black = true;
			}
		}
		if (iniPierna2black) {
			muevePiernaDerblack -= 4.3;
			muevePiernaIzqblack += 4.3;
			if (muevePiernaDerblack <= 0) {
				iniPierna2black = false;
				iniPiernablack = true;
			}
		}
	}

}

//-------------------------------------------------------MOVIMIENTO DESPLAZAMIENTO PANTERA 1----------------------------------------------------------------------------//
void movimientoB1() {
	if (true) {
		if (movB1) {
			movXblack += 0.5;
			if (movXblack > 10) {
				movB1 = false;
				mov2B1 = true;
			}
		}
		if (mov2B1) {
			movXblack -= 0.5;
			if (movXblack <=-10) {
				mov2B1 = false;
				movB1 = true;
			}
		}
	}

}
//-------------------------------------------------------MOVIMIENTO BRAZOS PARA TIRAR PANTERA 2----------------------------------------------------------------------------//
void brazosB2() {
	if (true) {
		if (inib2bra) {
			//mueveAlaDer += 1.0;
			mueveBrazoDerblack2 += 8.0;
			mueveBrazoIzqblack2 -= 8.0;
			if (mueveBrazoDerblack2 > 30) {
				inib2bra = false;
				inib2bra2 = true;
			}
		}
		if (inib2bra2) {
			mueveBrazoDerblack2 -= 8.0;
			mueveBrazoIzqblack2 += 8.0;
			if (mueveBrazoDerblack2 < -30) {
				inib2bra2 = false;
				inib2bra = true;
			}
		}
	}

}
//-------------------------------------------------------MOVIMIENTO PIERNAS PARA TIRAR PANTERA 2----------------------------------------------------------------------------//

void piernasB2() {
	if (true) {
		if (inib2pie) {
			muevePiernaDerblack2 += 5.0;
			muevePiernaIzqblack2 -= 5.0;
			if (muevePiernaDerblack2 > 45) {
				inib2pie = false;
				inib2pie2 = true;
			}
		}
		if (inib2pie2) {
			muevePiernaDerblack2 -= 5.0;
			muevePiernaIzqblack2 += 5.0;
			if (muevePiernaDerblack2 < -45) {
				inib2pie2 = false;
				inib2pie = true;
			}
		}
	}

}

//-------------------------------------------------------MOVIMIENTO BRINCO PANTERA 2----------------------------------------------------------------------------//

void brincoB2() {
	if (true) {
		if (inib2brinco) {
			movYblack2 += 0.4;
			if (movYblack2 >= 5) {
				inib2brinco = false;
				inib2brinco2 = true;
			}
		}
		if (inib2brinco2) {
			movYblack2 -= 0.4;
			if (movYblack2 <= 0) {
				inib2brinco2 = false;
				inib2brinco = true;
			}
		}
	}

}
void arribitaT() {
	{
		if (true) {
			if (arribita) {
				mueveBrazoDerblack2 -= 4.0;
				mueveBrazoIzqblack2 -= 4.0;
				if (mueveBrazoDerblack2 < -180) {
					arribita = false;
					arribita2 = true;
				}
			}
			if (arribita2) {
				mueveBrazoDerblack2 += 4.0;
				mueveBrazoIzqblack2 += 4.0;
				if (mueveBrazoDerblack2 >= 0) {
					arribita2 = false;
					arribita = true;
				}
			}
		}

	}
}
///////////////* ---------------------------------------FIN KEYFRAMES*--------------------------------------------------------------------////////////////////////////


//-------------------------------------------------------------INICIA EL MAIN--------------------------------------------------------------------------------------//

int main()
{
	//ang += 0.1;
	//Variables activar spiderman//
	int activaS = 1;
	int desactivaS = 1;
	//Variables activas y desactivar camaras//
	int activaTer = 1;
	int desactivaTer = 1;
	//
	int activaArea = 1;
	int desactivaArea = 1;
	//Variables de Movimiento Camara
	mueveXlibre = 0.0f;
	mueveYoZlibre = 0.0f;
	mueveCam = 0.0f;
	mueveCam2 = 0.0f;
	
	//---------------------------------------------------//
	float brightness = 1.0, brightnesslights = 0.2;
	float brillodir = 1.0;
	float brillo = 1.0;
	float red = 1.0;
	float poSpotX = 0.0;
	float poSpotY = 0.0;
	float poSpotZ = 0.0;
	float poSpotZA = 0.0;
	float difusa = 0.0;

	int dia = 0.0;
	int day_state=0.0;
	/////---------------------------------------------- LLAMAR CANCION --------------------------------------------------------------------------////
	
	ISoundEngine* engine = createIrrKlangDevice();
	if (!engine)
		return 0;
	ISound* ambiental = engine->play2D("canciones/Stellar Wind - Unicorn Heads.mp3", true);
	
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
	//SE ACTIVA CON 6
	if (cambioArea == 0) {
		camera = Camera(glm::vec3(0.0f, 25.0f, -170.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 1.0f, 0.5f);
	}
	//----------------------Posicion de la camera------Sobre que eje esta-------angulo---//----//------//



	/////---------------------------------------------- CARGA DE TEXTURAS --------------------------------------------------------------------------////

	
	//Textura Piso
	pisoTexture = Texture("Textures/arena.jpg");
	pisoTexture.LoadTextureA();

	//Textura Pasto
	pastoTexture=Texture("Textures/pasto5.jpg");
	pastoTexture.LoadTextureA();

	/////---------------------------------------------- CARGA DE MODELOS --------------------------------------------------------------------------////


	//-----------------------------------------------Personaje BlackPanter Hombre----------------------------------------------------------------//
	//Modelo Tronco--1
	TroncoHB_M = Model();
	TroncoHB_M.LoadModel("Models/htronco.obj");

	//Modelo Cabeza--2
	CabezaHB_M = Model();
	CabezaHB_M.LoadModel("Models/hcabeza.obj");

	//Modelo Mano Derecha--3
	BrazoDerHB_M = Model();
	BrazoDerHB_M.LoadModel("Models/hbrazoDer.obj");

	//Modelo Mano Izquierda--4
	BrazoIzqHB_M = Model();
	BrazoIzqHB_M.LoadModel("Models/hbrazoIzq.obj");

	//Modelo Pierna Izquierda--5
	PiernaIzqHB_M = Model();
	PiernaIzqHB_M.LoadModel("Models/hpiernaIzq.obj");

	//Modelo Pierna Derecha--6
	PiernaDerHB_M = Model();
	PiernaDerHB_M.LoadModel("Models/hpiernaDer.obj");

	//-----------------------------------------------Personaje Spiderman----------------------------------------------------------------//
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
	PiernaDer_M.LoadModel("Models/piernader.obj");

	//Modelo Control Remoto
	Remoto_M = Model();
	Remoto_M.LoadModel("Models/controlremoto.obj");

	//--------------------------------------------------------Personaje Pajaro-----------------------------------------------------------------------------//
	
	//Tronco Pajaro
	TroncoPa_M = Model();
	TroncoPa_M.LoadModel("Models/troncoPA.obj");

	//Ala izquierda Pajaro
	AlaIzqPa_M = Model();
	AlaIzqPa_M.LoadModel("Models/alaizqPA.obj");
	
	//Ala derecha Pajaro
	AlaDerPa_M = Model();
	AlaDerPa_M.LoadModel("Models/aladerPA.obj");

	//Pata izquierda Pajaro
	PataIzqPa_M = Model();
	PataIzqPa_M.LoadModel("Models/pataizqPA.obj");

	//Pata derecha Pajaro
	PataDerPa_M = Model();
	PataDerPa_M.LoadModel("Models/pataderPA.obj");

	//------------------------------------------------------------Mas modelos----------------------------------------------------------------------------//
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

	//Modelo Porteia
	Porteria_M = Model();
	Porteria_M.LoadModel("Models/porteria.obj");

	//Modelo Balon
	Balon_M = Model();
	Balon_M.LoadModel("Models/balonobj.obj");


	//Modelo Edificio
	Edificio_M = Model();
	Edificio_M.LoadModel("Models/edificio.obj");

	//Modelo Flotador
	Flotador_M = Model();
	Flotador_M.LoadModel("Models/flotador.obj");

	//Modelo Basket
	Basket_M = Model();
	Basket_M.LoadModel("Models/basket.obj");

	/////---------------------------------------------- CARGA DE CARAS DEL SKYBOX -----------------------------------------------------------------------////


	int sec;

	
		std::vector<std::string> skyboxFaces2;
		skyboxFaces2.push_back("Textures/Skybox/posx1.jpg");//RIGHT
		skyboxFaces2.push_back("Textures/Skybox/negx1.jpg");//LEFT
		skyboxFaces2.push_back("Textures/Skybox/negy1.jpg");//DOWN
		skyboxFaces2.push_back("Textures/Skybox/posy1.jpg");//TOP
		skyboxFaces2.push_back("Textures/Skybox/posz1.jpg");//FRONT
		skyboxFaces2.push_back("Textures/Skybox/negz1.jpg");//BACK
		skybox = Skybox(skyboxFaces2);

	
	
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

	//Posici?n incial del coche
	glm::vec3 poscoche = glm::vec3(0.0f, -0.4f, 70.6f);

	//Posicion inicial del faro
	glm::vec3 posfaro = glm::vec3(12.0f, -1.0f, 70.6f);

	//Posicion inicial de Spiderman
	glm::vec3 spiderpos = glm::vec3(75.0f, 4.7f, 60.0f);


	//Posicion inicial de BlackPanter
	glm::vec3 blackpos = glm::vec3(160.0f, 4.7f, -100.0f);

	//Posicion inicial de BlackPanter2
	glm::vec3 blackpos2 = glm::vec3(160.0f, 4.7f, -10.0f);
	
	//Posicion inicial del pajaro
	glm::vec3 pospajaro = glm::vec3(0.0f, 5.0f, -100.0f);


	/////---------------------------------------------- LO QUE SE PODRA VISUALIZAR CON CAMARA -------------------------------------------------------------////


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	
	//--------------------------------------------Variables Utilizadas para cambiar la luz de escenario-----------------------------------------------------//
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
		//------------------------------------------ CONDICION PARA CAMBIAR DE CAMARAS-------------------------------------------------------------------------------------//
		if (cambioArea == 1) {
			
			if (cambioTer == 1) {

				camera = Camera(glm::vec3(spiderpos.x + movXspider+ mueveXlibre, spiderpos.y + movYspider, spiderpos.z + mueveYoZlibre + movZspider - 50.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90, 0.0f, 1.0f, 0.5f);

			}
			else if (cambioTer == 0) {
				
				camera = Camera(glm::vec3(0.0f + mueveCam, 200.0f, mueveCam2+0.0f), glm::vec3(1.0f, 0.0f, 0.0f),180, -180.0f, 1.0f, 0.5f);
				
			}
		}
		//----------------------------------------DECLARACION DE LAS LUCES DE NUESTRO MUNDO----------------------------------------------------------------//
		
		//---------------------DirectionalLight-----------------------------------------------------------------------------------------------------------// 
		//Madre de todas las luces, es como el sol. Solo existe una.
		mainLight = DirectionalLight(1.0f, 1.0f, 1.0f, //RGB - Color blanco- se usa este para qye se vean todos los colores
			brillodir, brightnesslights,	//Coeficiente de intensidad ambiental y difusa.
			0.0f, 0.0f, -1.0f);//Posicion en x, y , z

		//--------------------PointlLight-----------------------------------------------------------------------------------------------------------//
		unsigned int pointLightCount = 0; //Contador de luces puntuales, se tendra m?s de una
		//pointLights[0]
		pointLights[0] = PointLight(1.0f, red, 0.0f, //RGB
			brillo, brillo,//Intensidad ambiental y difusa
			30.0f, 25.0f, -93.0f,//Valor de posici?n 
			0.3f, 0.2f, 0.1f);//Coeficientes de ecuaci?n de segundo grado
		pointLightCount++;//Aumenta contador


		//pointLights[1]

		pointLights[1] = PointLight(1.0f, red, 0.0f, //RGB
			brillo, brillo,//Intensidad ambiental y difusa
			30.0f, 25.0f, 13.0f,//Valor de posici?n 
			0.3f, 0.2f, 0.1f);//Coeficientes de ecuaci?n de segundo grado
		pointLightCount++;//Aumenta contador

		//pointLights[2]

		pointLights[2] = PointLight(1.0f, red, 0.0f, //RGB
			brillo, brillo,//Intensidad ambiental y difusa
			-30.0f, 25.0f, -93.0f,//Valor de posici?n 
			0.3f, 0.2f, 0.1f);//Coeficientes de ecuaci?n de segundo grado
		pointLightCount++;//Aumenta contador


		//pointLights[3]

		pointLights[3] = PointLight(1.0f, red, 0.0f, //RGB
			brillo, brillo,//Intensidad ambiental y difusa
			-30.0f, 25.0f, 13.0f,//Valor de posici?n 
			0.3f, 0.2f, 0.1f);//Coeficientes de ecuaci?n de segundo grado
		pointLightCount++;//Aumenta contador


		//---------------------SpotLight----------------------------------------------------------------------------------------------------------------// 

		unsigned int spotLightCount = 0;// Contador Luces SpotLight


		//Luz de Camara-spotLights[0]

		spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f, //RGB
			0.0f, 2.0f,//Coeficiente ambiental y difuso
			0.0f + poSpotX, 40.0f + poSpotY, 75.0f + poSpotZ,//Posici?n x,y,z
			0.0f, -1.0f, 0.0f,//Vector de cirecci?n, apunta hacia -y//DONDE APUNTA
			1.0f, 0.0f, 0.0f,//Valores de ecuaci?n de segundo grado
			5.0f);//Radio de nuestro cono invicible//RADIO DEL CONO
		spotLightCount++;
		//---------------------Luces Fiesta----------------------------------------------------------------------------------------------------------------// 

		//Luz Fiesta-spotLights[1]
		spotLights[1] = SpotLight(1.0f, 0.0f, 0.0f,//RGB-Roja
			1.0f, 1.0f,//Coefciente ambient y difuso
			10.4f + poSpotX, 40.5f + poSpotY, 94.5f + poSpotZ,//Posici?n x,y,x
			0.0f, -1.0f, -0.5f,//Vector de direcci?n
			1.0f, 0.0f, 0.0f,//Valores de ecuaci?n
			10.0f);
		spotLightCount++;

		//Luz Fiesta-spotLights[2]
		spotLights[2] = SpotLight(0.0f, 0.0f, 1.0f,//RGB-Azul
			1.0f, 1.0f,//Coeficiente ambiental y difuso
			-4.4f + poSpotX, 40.5f + poSpotY, 94.5f + poSpotZA, //Posici?n x,y,z
			0.0f, -1.0f, -0.5f,//Vector de direcci?n
			1.0f, 0.0f, 0.0f,
			10.0f);
		spotLightCount++;



		//Luz Fiesta- spotLights[3]
		spotLights[3] = SpotLight(0.0f, 1.0f, 0.0f,//luz verde
			1.0f, 1.0f,//Coeficiente ambiental y difuso
			-19.4f + poSpotX, 40.5f + poSpotY, 94.5f + poSpotZ, //Posici?n x,y,z
			0.0f, -1.0f, -0.5f,//Vector de direcci?n
			1.0f, 0.0f, 0.0f,
			10.0f);
		spotLightCount++;

		//----------------------------------------------------Switch para cambiar entre el d?a y la noche----------------------------------------------------------------// 

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
		
		//----------------------------Condicion para enceder y apagar las luces del escenario, y activar el show------------------------------------------------------------// 
		
		if (mainWindow.getshow() == 1)
		{
			//if (activa == 1) {
				activa = 0;
				desactiva = 0;
				//printf("Aprieto M y activo");

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
				//printf("Aprieto N y desactivo");
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
		//------------------------------------------------------------------Fin de la condicion------------------------------------------------------------//
	
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

		//----------------informaci?n en el shader de intensidad especular y brillo----------------------------------------------------------------//
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		//----------------Esto se uso para realizar el setflash a la camara-----------------------------------------------------------------------//
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);


		//----------------Uso de SetFlash y SetPos dentro del loop------------------------------------------------------------------------------//

		//luz ligada a la c?mara de tipo flash 
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//luz ligada al faro
		//spotLights[2].SetPos(poscoche + desplazamiento);


		//luz ligada al helicoptero
		//spotLights[3].SetPos(posblackhawk + desplazamiento2);

		//informaci?n al shader de fuentes de iluminaci?n
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		//------------------------------------CONDICION PARA APAGAR LAS LUCES SPOTLIGHT DEL SHOW------------------------------------------------------------------------------//
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
		glm::mat4 modelaux2(1.0);

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



		//--------------------------------------------------------------MOVIMIENTO DE COCHE---------------------------------------------------------------------//
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
		//-------------------------------------------------Animaci?n Pajaro--------------------------------------------------------------------------//
		
		if (true) {//Principal if
			
			if (est1) {//SUBE ROTA  en X=80?
				movimientoAlas();
				movYpajaro += 0.1;//Mueve en Y
				rotaXpajaro += 0.5;//Rota en X
				if (rotaXpajaro >= 80) {
					est1 = false;
					est2 = true;
				}
			}
			if (est2) {//AVANZA EN Z=200
				movimientoAlas();
				movZpajaro += 0.5;//Mueve e Z
				//rotaXpajaro -= 0.4;
				if (movZpajaro >= 200) {
					est2 = false;
					est3 = true;
				}
			}
			if (est3) {//SUBE Y ROTA EN X=-80?
				movimientoAlas();
				movYpajaro += 0.1;//Mueve en Y
				rotaXpajaro -= 0.4;//Rota en X
				if (rotaXpajaro <= -90) {
					est3 = false;
					est4 = true;
				}
			}

			if (est4) {
				movimientoAlas();
				//movYpajaro += 0.1;
				//rotaXpajaro += 0.6;
				rotaYpajaro += 0.6;//Rota en Y
				if (rotaYpajaro >= 180) {
					est4 = false;
					est5 = true;
				}
			}

			if (est5) {
				movimientoAlas();
				movZpajaro -= 0.3;
				//rotaXpajaro -= 0.4;
				if (movZpajaro <= 150) {
					est5 = false;
					est6 = true;
				}
			}

			if (est6) {
				movimientoAlas();
				rotaZpajaro -= 0.5;
				movXpajaro -= 0.1;

				//rotaXpajaro -= 0.4;
				if (rotaZpajaro <= -90) {
					est6 = false;
					est7 = true;
				}
			}
			if (est7) {
				movimientoAlas();
				//rotaZpajaro -= 0.5;
				movXpajaro -= 0.2;

				//rotaXpajaro -= 0.4;
				if (movXpajaro <= -80) {
					est7 = false;
					est8 = true;
				}
			}

			if (est8) {
				movimientoAlas();
				rotaZpajaro += 0.5;
				movZpajaro -= 0.2;

				//rotaXpajaro -= 0.4;
				if (rotaZpajaro >= 0) {
					est8 = false;
					est9 = true;
				}
			}

			if (est9) {
				movimientoAlas();
				movZpajaro -= 0.2;

				//rotaXpajaro -= 0.4;
				if (movZpajaro <=-100) {
					est9 = false;
					est10 = true;
				}
			}

			if (est10) {
				movimientoAlas();
				rotaZpajaro += 0.5;
				movXpajaro += 0.2;

				//rotaXpajaro -= 0.4;
				if (rotaZpajaro >= 90) {
					est10 = false;
					est11 = true;
				}
			}

			if (est11) {
				movimientoAlas();
				movXpajaro += 0.2;

				//rotaXpajaro -= 0.4;
				if (movXpajaro >= 100) {
					est11 = false;
					est12 = true;
				}
			}

			if (est12) {
				movimientoAlas();
				rotaZpajaro += 0.5;
				movZpajaro += 0.2;

				//rotaXpajaro -= 0.4;
				if (rotaZpajaro >= 180) {
					est12 = false;
					est13 = true;
				}
			}

			if (est13) {
				movimientoAlas();
				//rotaZpajaro += 0.5;
				movZpajaro += 0.2;

				//rotaXpajaro -= 0.4;
				if (movZpajaro >= 100) {
					est13 = false;
					est14 = true;
				}
			}


			if (est14) {
				movimientoAlas();
				rotaZpajaro += 0.5;
				movXpajaro -= 0.2;

				//rotaXpajaro -= 0.4;
				if (rotaZpajaro >= 270) {
					est14 = false;
					est15 = true;
				}
			}

			if (est15) {
				movimientoAlas();
				//rotaZpajaro += 0.5;
				movXpajaro -= 0.2;

				//rotaXpajaro -= 0.4;
				if (movXpajaro <= -30) {
					est15 = false;
					est16 = true;
				}
			}

			if (est16) {
				movimientoAlas();
				rotaZpajaro += 0.5;
				movZpajaro -= 0.2;

				//rotaXpajaro -= 0.4;
				if (rotaZpajaro >= 360) {
					est16 = false;
					est17 = true;
				}
			}

			if (est17) {
				movimientoAlas();
				
				movZpajaro -= 0.2;

				//rotaXpajaro -= 0.4;
				if (movZpajaro<=0) {
					est17 = false;
					est18 = true;
				}
			}

			if (est18) {
				movimientoAlas();
				movYpajaro -= 0.1;
				rotaXpajaro += 0.5;

				//rotaXpajaro -= 0.4;
				if (rotaXpajaro >= 0) {
					est18 = false;
					est19 = true;
				}
			}
			if (est19) {
				movimientoAlas();
				movYpajaro -= 0.1;
			

				//rotaXpajaro -= 0.4;
				if (movYpajaro <= 0) {
					est19 = false;
					est20 = true;
				}
			}
			if (est20) {
				movimientoPatas();
				movXpajaro += 0.05;
				rotaYpajaro -= 0.5;
				//rotaXpajaro -= 0.4;
				if (rotaYpajaro <= 90) {
					est20 = false;
					est21 = true;
				}
			}
			if (est21) {
				movimientoPatas();
				movXpajaro += 0.05;
				//rotaZpajaro >= 0.5;
				//rotaXpajaro -= 0.4;
				if (movXpajaro >= 0) {
					est21 = false;
					est22 = true;
				}
			}
			if (est22) {
				movimientoPatas();
				rotaYpajaro -= 0.5;
				//rotaXpajaro -= 0.4;
				if (rotaYpajaro <= 0) {
					est22 = false;
					rotaXpajaro = 0.0f;
					rotaYpajaro = 0.0f;
					rotaZpajaro = 0.0f;
					est1 = true;
				}
			}

		}
		//-------------------------------------------------------------Animaci?n de Flotador---------------------------------------------------------//
		if (flota==1) {
			if (es1) {
				movXflotador -= 0.1;
				movZflotador += 0.1;
				if (movXflotador<=-5) {
					es1 = false;
					es2 = true;
				}
			}
			if (es2) {
				movXflotador += 0.1;
				movZflotador += 0.1;
				if (movXflotador >= 0) {
					es2 = false;
					es3 = true;
				}
			}

			if (es3) {
				movXflotador -= 0.1;
				movZflotador += 0.1;
				if (movXflotador <= -5) {
					es3 = false;
					es4 = true;
				}
			}

			if (es4) {
				movXflotador += 0.1;
				movZflotador += 0.1;
				if (movXflotador >= 0) {
					es4 = false;
					es5 = true;
				}
			}

			if (es5) {
				movXflotador -= 0.1;
				movZflotador += 0.1;
				if (movXflotador <= -5) {
					es5 = false;
					es6 = true;
				}
			}
			if (es6) {
				movXflotador += 0.1;
				movZflotador += 0.1;
				if (movXflotador >= 0) {
					es6 = false;
					es7 = true;
				}
			}
			if (es7) {
				movXflotador -= 0.1;
				movZflotador += 0.1;
				if (movXflotador <= -5) {
					es7 = false;
					//es8 = true;
				}
			}

		}
		else if (flota == 0) {
			movXflotador = 0.0;
			movZflotador = 0.0f;
			es1 = true;
			es2 = false;
			es3 = false;
			es4 = false;
			es5 = false;
			es6 = false;
			es7 = false;

		}

		//-------------------------------------------------Animaci?n Spiderman Activa:3 y Reset:4----------------------------------------------------//
		if (spiderman==1) {
			activaS = 0;
			desactivaS = 0;
			
			if (estado1) {
				movimientoPiernas();
				movimientoBrazos();
				movZspider += 0.1;
				if (movZspider > 10) {
					estado1 = false;
					estado2 = true;
				}
			}
			if (estado2) {
				movimientoPiernas();
				movimientoBrazos();
				rotaXSpider -= 0.9;
				movYspider += 0.01;
				if (rotaXSpider < -90) {
					estado2 = false;
					estado3 = true;
				}

			}
			if (estado3) {
				movimientoPiernas();
				movimientoBrazos();
				//rotaXSpider -= 0.9;
				movYspider += 0.1;
				if (movYspider > 38) {
					estado3 = false;
					estado4 = true;
				}

			}

			if (estado4) {
				movimientoPiernas();
				movimientoBrazos();
				rotaXSpider += 0.9;
				movYspider += 0.05;
				movZspider += 0.05;
				if (rotaXSpider >=0) {
					estado4 = false;
					estado5 = true;
				}

			}
			if (estado5) {
				movimientoPiernas();
				movimientoBrazos();
				//rotaXSpider += 0.9;
				//movYspider += 0.05;
				movZspider += 0.1;
				if (movZspider >24) {
					estado5 = false;
					estado6 = true;
				}

			}
			if (estado6) {
				movimientoPiernas();
				movimientoBrazos();
				rotaXSpider += 0.9;
				movYspider -= 0.05;
				movZspider += 0.059;
				if (rotaXSpider > 90) {
					estado6 = false;
					estado7 = true;
				}

			}
			if (estado7) {
				movimientoPiernas();
				movimientoBrazos();
				//rotaXSpider -= 0.9;
				movYspider -= 0.1;
				if (movYspider <=1) {
					estado7 = false;
					estado8 = true;
				}

			}
			if (estado8) {
				movimientoPiernas();
				movimientoBrazos();
				rotaXSpider -= 0.9;
				movYspider -= 0.01;
				if (rotaXSpider <= 0) {
					estado8 = false;
					estado9 = true;
				}

			}
			if (estado9) {
				movimientoPiernas();
				movimientoBrazos();
				rotaYSpider -= 0.9;
				movXspider -= 0.1;
				if (rotaYSpider <= -90) {
					estado9 = false;
					estado10 = true;
				}

			}
			if (estado10) {
				movimientoPiernas();
				movimientoBrazos();
				//rotaYSpider -= 0.9;
				movXspider -= 0.1;
				if (movXspider <= -30) {
					estado10 = false;
					estado11 = true;
				}

			}
			if (estado11) {
				movimientoPiernas();
				movimientoBrazos();
				rotaYSpider -= 0.9;
				movZspider -= 0.05;
				if (rotaYSpider <= -180) {
					estado11 = false;
					estado12 = true;
				}

			}

			if (estado12) {
				movimientoPiernas();
				movimientoBrazos();
				//movZspider -= 0.9;
				movZspider -= 0.1;
				if (movZspider <= -20) {
					estado12 = false;
					estado13 = true;
				}

			}

			if (estado13) {
				movimientoPiernas();
				movimientoBrazos();
				rotaYSpider += 0.9;
				movXspider -= 0.1;
				if (rotaYSpider> -90) {
					estado13 = false;
					estado14 = true;
				}

			}

			if (estado14) {
				movimientoPiernas();
				movimientoBrazos();
				//rotaYSpider += 0.9;
				movXspider -= 0.1;
				if (movXspider < -70) {
					estado14 = false;
					estado15 = true;
				}

			}
			if (estado15) {
				movimientoPiernas();
				movimientoBrazos();
				rotaYSpider -= 0.9;
				movZspider -= 0.05;
				if (rotaYSpider < -180) {
					estado15 = false;
					estado16 = true;
				}

			}
			if (estado16) {////////////////////COLOR
				mueveBrazoIzq -= 0.5;
				if (mueveBrazoIzq < -80) {
					mueveBrazoIzq = -80;
					contador2 += 0.5;
						red = 0.0f;
						brillo = 10.0f;
						if (contador2 >= 5) {
							estado16 = false;
							estado17 = true;
						}
					
					

				}
			}
			if (estado17) {////////////////////COLOR
				mueveBrazoIzq += 0.5;
				if (mueveBrazoIzq > 0) {
					red = 1.0f;
					brillo = 0.0f;
					estado17 = false;

				}
			}
		}else if (spiderman == 0) 
		{
			if (desactivaS == 0) {
			//printf("Aprieto N y desactivo");
				//Reseteamos todo
				movXspider = 0.0f;
				movZspider = 0.0f;
				mueveBrazoDer = 0.0f;
				mueveBrazoIzq = 0.0f;
				muevePiernaDer = 0.0f;
				muevePiernaIzq = 0.0f;
				rotaXSpider = 0.0f;
				rotaYSpider = 0.0f;
				rotaZSpider = 0.0f;
				estado1 = true;
				estado2 = false;
				estado3 = false;
				estado4 = false;
				estado5 = false;
				estado6 = false;
				estado7 = false;
				estado8 = false;
				estado9 = false;
				estado10 = false;
				estado11 = false;
				estado12 = false;
				estado13 = false;
				estado14 = false;
				estado15 = false;
				estado16 = false;
				estado17 = false;
			//estado18 = false;
			//estado19 = false;

			activaS = 1;
			desactivaS = 1;

			}
		}
		//------------------------------------------------------------Animacion Futbol--------------------------------------------------------//
		float count5 = 0.0;
		if (true) {
			if (estado1black) {
				movimientoBraB1();
				movimientoPiernasB1();
				movimientoB1();
				brazosB2();
				piernasB2();
				movZblack2 -= 0.45;
				if (movZblack2 <= -39) {
					estado1black = false;
					estado2black = true;
				}
				//angulo += 3.0;
			}

			if (estado2black) {
				movimientoBraB1();
				movimientoPiernasB1();
				movimientoB1();
				//brazosB2();
				//piernasB2();
				//movZblack2 -= 0.05;
				muevePiernaDerblack2 -= 3.0;
				if (muevePiernaDerblack2 <= -40) {
					estado2black = false;
					estado3black = true;
				}
				//angulo += 3.0;
			}
			if (estado3black) {
				movimientoBraB1();
				movimientoPiernasB1();
				movimientoB1();
				movZbalon -= 0.9;
				movXbalon -= 0.04;
				movYbalon += 0.025;
				angulo += 6.0;
				if (movZbalon <= -60) {
					estado3black = false;
					estado4black = true;
				}
				//angulo += 3.0;
			}
			if (estado4black) {
				//movimientoBraB1();
				//movimientoPiernasB1();
				//movimientoB1();
	
				movYbalon -= 0.8;
				angulo += 6.0;
				if (movYbalon <= 0) {
					angulo = 0;
					estado4black = false;
					estado5black = true;
				}
			}

			if (estado5black) {
				contador3 += 0.01;
				arribitaT();
				brincoB2();
				
				if (contador3>= 4) {
					estado5black = false;
					estado6black = true;
					contador3 = 0;
				}
			}

			if (estado6black) {
				contador3 += 0.01;
				movXbalon = 0.0;
				movYbalon = 0.0;
				movZbalon = 0.0;
				muevePiernaDerblack2 = 0.0;
				muevePiernaIzqblack2 = 0.0;
				movZblack2 = 0.0f;
				mueveBrazoDerblack2 = 0.0;
				mueveBrazoIzqblack2 = 0.0;
				angulo = 0.0;
				movXblack = 0.0;
				muevePiernaDerblack = 0.0;
				muevePiernaIzqblack = 0.0;
				mueveBrazoDerblack = 0.0;
				mueveBrazoIzqblack = 0.0;


				if (contador3 >= 2) {
					estado6black = false;
					estado1black = true;
					contador3 = 0;
				}
			}
			//-------------------------------------------------------------Animaci?n de Basket---------------------------------------------------------//
			if (basketball == 1) {
				if (bake1) {
					angub += 6.5;
					movXbasket -= 0.9;
					movYbasket -= 0.3;
					if (movXbasket <= -10) {
						bake1 = false;
						bake2 = true;
					}
				}
				if (bake2) {//BAJA
					angub += 6.0;
					movYbasket -= 1.0;//0.6
					if (movYbasket <=-50) {
						bake2 = false;
						bake3 = true;
					}
				}

				if (bake3) {//SUBE
					angub -= 6.0;
					movYbasket += 0.9;
					if (movYbasket >= 0) {
						bake3 = false;
						bake4 = true;
					}
				}

				if (bake4) {//BAJA
					angub += 6.0;
					movYbasket -= 0.8;
					if (movYbasket <= -50) {
						bake4 = false;
						bake5 = true;
					}
				}

				if (bake5) {//SUBE
					angub -= 6.0;
					movYbasket += 0.8;
					if (movYbasket >= -10) {
						bake5 = false;
						bake6 = true;
					}
				}

				if (bake6) {//BAJA
					angub += 6.0;
					movYbasket -= 0.8;
					if (movYbasket <= -50) {
						bake6 = false;
						bake7 = true;
					}
				}
				
				if (bake7) {//SUBE
					angub -= 6.0;
					movYbasket += 0.8;
					if (movYbasket >= -20) {
						bake7 = false;
						bake8 = true;
					}
				}

				if (bake8) {//BAJA
					angub += 6.0;
					movYbasket -= 0.8;
					if (movYbasket <= -50) {
						bake8 = false;
						bake9 = true;
					}
				}

				if (bake9) {//SUBE
					angub -= 6.0;
					movYbasket += 0.7;
					if (movYbasket >= -30) {
						bake9 = false;
						bake10 = true;
					}
				}

				if (bake10) {//BAJA
					angub += 6.0;
					movYbasket -= 0.7;
					if (movYbasket <= -50) {
						bake10 = false;
						bake11 = true;
					}
				}

				if (bake11) {//SUBE
					angub -= 6.0;
					movYbasket += 0.7;
					if (movYbasket >= -40) {
						bake11 = false;
						bake12 = true;
					}
				}

				if (bake12) {//BAJA
					angub += 6.0;
					movYbasket -= 0.7;
					if (movYbasket <= -50) {
						bake12 = false;
						bake13 = true;
					}
				}

				if (bake13) {//SUBE
					angub -= 6.0;
					movYbasket += 0.7;
					if (movYbasket >= -45) {
						bake13 = false;
						bake14 = true;
					}
				}

				if (bake14) {//BAJA
					angub += 6.0;
					movYbasket -= 0.7;
					if (movYbasket <= -50) {
						bake14 = false;
						//bake15 = true;
					}
				}

				
			}else if (basketball == 0) {
				movXbasket = 0.0;
				movYbasket = 0.0f;
				movZbasket = 0.0f;
				bake1 = true;
				bake2 = false;
				bake3 = false;
				bake4 = false;
				bake5 = false;
				bake6 = false;
				bake7 = false;
				bake8 = false;
				bake9 = false;
				bake10 = false;
				bake11 = false;
				bake12 = false;
				bake13 = false;
				bake14 = false;
				
			}

		}


		/////----------------------------------------------------VARIABLES DE DESPLAZAMIENTO ----------------------------------------------------------------////

		//Para el coche
		desplazamiento = glm::vec3(posXcoche, posYcoche, posZcoche);//COCHE Se mueve en X y Z

		//Para el Helicoptero
		desplazamiento2 = glm::vec3(posXavion, posYavion, posZavion);//HELICOPTERO se mueve en x & y 

		/////---------------------------------------------------DIBUJAR OBJETOS EN ESCENARIO ----------------------------------------------------------------////




		//----------------------------------------------------DIBUJAR HOMBRE BLACK PANTER 1-------------------------------------------------------------------//
		//Modelo Tronco//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(blackpos.x+movXblack+ -0.012439f,blackpos.y+movYblack+ -0.060164f,blackpos.z+movZblack+ -0.073148f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, (0+rotaXblack) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, (0 + rotaYblack) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, (0 + rotaZblack) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		TroncoHB_M.RenderModel();
		
		//Modelo de cabeza//
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.634567f, -0.036493f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CabezaHB_M.RenderModel();

		//Modelo Brazo Der//
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.446364f, 0.380999f, 0.034415f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, (0+ mueveBrazoDerblack) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//MOVIMIENTO BRAZO DER
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BrazoDerHB_M.RenderModel();

		//Modelo Brazo Izq//
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.450342f, 0.441965f, 0.026008f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, (0+ mueveBrazoIzqblack) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//MOVIMIENTO BRAZO IZQ
		modelaux2 = model;
		//model = glm::rotate(model, (-30 + angulo) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BrazoIzqHB_M.RenderModel();


		//Modelo Pierna Der//
		model = modelaux; 
		model = glm::translate(model, glm::vec3(-0.364119f, -0.708628f, 0.008785f));
		model = glm::rotate(model, (muevePiernaIzqblack + 0) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));//Movimiento de PIERNA DERECHA 
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PiernaDerHB_M.RenderModel();

		//Modelo Pierna Izq//
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.371392f, -0.675755f, 0.027448f));
		model = glm::rotate(model, (muevePiernaDerblack +0) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));//Movimiento de PIERNA DERECHA 
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PiernaIzqHB_M.RenderModel();
		
		//------------------------------------------------------------------DIBUJAR PORTERIA 1----------------------------------------------------------------------------//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(180.0f, 0.35f, -110.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Porteria_M.RenderModel();

		//------------------------------------------------------------------DIBUJAR UNICO BALON----------------------------------------------------------------------------//
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(160.0f + movXbalon, 0.11f + movYbalon, -50.0f + movZbalon));
		model = glm::rotate(model, (0+angulo) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Balon_M.RenderModel();


		//------------------------------------------------------------------DIBUJAR BlackPanter 2----------------------------------------------------------------------------//
		//Modelo Tronco//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(blackpos2.x + movXblack2 + -0.012439f, blackpos2.y + movYblack2 + -0.060164f, blackpos2.z + movZblack2 + -0.073148f));
		//model = glm::rotate(model, glm::radians(movCoc), glm::vec3(0.0f, 1.0f, 0.0f));////MOVIMIENTO CIRCULAR Y
		//model = glm::rotate(model, glm::radians(movZ), glm::vec3(0.0f, 0.0f, 1.0f));////MOVIMIENTO CIRCULAR Z
		//model = glm::rotate(model, glm::radians(movX), glm::vec3(1.0f, 0.0f, 0.0f));////MOVIMIENTO CIRCULAR X
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, (0 + rotaXblack2) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, (-180 + rotaYblack2) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, (0 + rotaZblack2) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		TroncoHB_M.RenderModel();

		//Modelo de cabeza//
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.634567f, -0.036493f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CabezaHB_M.RenderModel();

		//Modelo Brazo Der//
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.446364f, 0.380999f, 0.034415f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, (0 + mueveBrazoDerblack2) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//MOVIMIENTO BRAZO DER
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BrazoDerHB_M.RenderModel();

		//Modelo Brazo Izq//
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.450342f, 0.441965f, 0.026008f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, (0 + mueveBrazoIzqblack2) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//MOVIMIENTO BRAZO IZQ
		modelaux2 = model;
		//model = glm::rotate(model, (-30 + angulo) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BrazoIzqHB_M.RenderModel();


		//Modelo Pierna Der//
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.364119f, -0.708628f, 0.008785f));
		model = glm::rotate(model, (muevePiernaIzqblack2 + 0) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Movimiento de PIERNA DERECHA 
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PiernaDerHB_M.RenderModel();

		//Modelo Pierna Izq//
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.371392f, -0.675755f, 0.027448f));
		model = glm::rotate(model, (muevePiernaDerblack2 + 0) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Movimiento de PIERNA DERECHA 
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PiernaIzqHB_M.RenderModel();



		//------------------------------------------------------------------DIBUJAR PORTERIA 2----------------------------------------------------------------------------//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(140.0f, 0.35f, 0.0f));
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Porteria_M.RenderModel();

		
		//------------------------------------------------------------------DIBUJAR SPIDERMAN----------------------------------------------------------------------------//
		
		//Modelo Tronco//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(spiderpos.x+movXspider,spiderpos.y+movYspider,spiderpos.z+movZspider));
		//model = glm::rotate(model, glm::radians(movCoc), glm::vec3(0.0f, 1.0f, 0.0f));////MOVIMIENTO CIRCULAR Y
		//model = glm::rotate(model, glm::radians(movZ), glm::vec3(0.0f, 0.0f, 1.0f));////MOVIMIENTO CIRCULAR Z
		//model = glm::rotate(model, glm::radians(movX), glm::vec3(1.0f, 0.0f, 0.0f));////MOVIMIENTO CIRCULAR X
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, (0+rotaXSpider) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, (0 + rotaYSpider) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, (0 + rotaZSpider) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_M.RenderModel();
		
		//Modelo de cabeza//
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 11.9253f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cabeza_M.RenderModel();

		//Modelo Brazo Der//
		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.08385f, 1.99403f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, (0+ mueveBrazoDer) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//MOVIMIENTO BRAZO DER
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BrazoDer_M.RenderModel();

		//Modelo Brazo Izq//
		model = modelaux;
		model = glm::translate(model, glm::vec3(2.79578f, 1.93207f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, (0+ mueveBrazoIzq) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//MOVIMIENTO BRAZO IZQ
		modelaux2 = model;
		//model = glm::rotate(model, (-30 + angulo) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BrazoIzq_M.RenderModel();

		/////////////////////////// Control Remoto
		model = modelaux2;
		model = glm::translate(model, glm::vec3(7.09784f, -9.75398f, 6.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//model = glm::rotate(model, (0 + mueveBrazoIzq) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//MOVIMIENTO BRAZO IZQ
		//model = glm::rotate(model, (-30 + angulo) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Remoto_M.RenderModel();
		///////////////////////////

		//Modelo Pierna Der//
		model = modelaux; 
		model = glm::translate(model, glm::vec3(-4.27498f, -7.65392f, 0.0f));
		model = glm::rotate(model, (muevePiernaIzq + 0) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Movimiento de PIERNA DERECHA 
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PiernaDer_M.RenderModel();

		//Modelo Pierna Izq//
		model = modelaux;
		model = glm::translate(model, glm::vec3(4.04199f, -7.61498f, 0.0f));
		model = glm::rotate(model, (muevePiernaDer+0) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Movimiento de PIERNA DERECHA 
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PiernaIzq_M.RenderModel();
		
		
		
		//--------------------------------------------------------DIBUJAR PAJARO--------------------------------------------------------------------------------------//

		//Tronco de Pajaro//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(pospajaro.x + movXpajaro, pospajaro.y + movYpajaro, pospajaro.z + movZpajaro));
		//model = glm::rotate(model, glm::radians(movCoc), glm::vec3(0.0f, 1.0f, 0.0f));////MOVIMIENTO CIRCULAR Y
		//model = glm::rotate(model, glm::radians(movZ), glm::vec3(0.0f, 0.0f, 1.0f));////MOVIMIENTO CIRCULAR Z
		//model = glm::rotate(model, glm::radians(movX), glm::vec3(1.0f, 0.0f, 0.0f));////MOVIMIENTO CIRCULAR X
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, (0 + rotaXpajaro) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, (0 + rotaYpajaro) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, (0 + rotaZpajaro) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		TroncoPa_M.RenderModel();

		angulo += 0.5;
		//Modelo Ala derecha//
		model = modelaux;
		model = glm::translate(model, glm::vec3(-13.8f, 12.7f,- 2.6f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, (0 + mueveAlaDer) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));//MOVIMIENTO BRAZO DER
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AlaDerPa_M.RenderModel();

		//Modelo Ala Izquierda//
		model = modelaux;
		model = glm::translate(model, glm::vec3(14.1, 11.7f, -1.6678f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, (0 + mueveAlaIzq) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));//MOVIMIENTO BRAZO DER
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AlaIzqPa_M.RenderModel();

		//Modelo Pata Derechha//
		model = modelaux;
		model = glm::translate(model, glm::vec3(-9.4f, -35.1f, -15.5f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, (0 + muevePataDer) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//MOVIMIENTO BRAZO DER
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PataDerPa_M.RenderModel();

		//Modelo Pata Izquierda///////////////
		model = modelaux;
		model = glm::translate(model, glm::vec3(10.2f, -35.3f, -13.8f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, (0 + muevePataIzq) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//MOVIMIENTO BRAZO DER
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PataIzqPa_M.RenderModel();


		//-------------------------------------------------------------DIBUJAR PELOTA BASKET----------------------------------------------------------------------------//

		//Modelo  Basket//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-38.0f + movXbasket, 52.5f + movYbasket, 53.5f + movZbasket));//model = glm::translate(model, glm::vec3(75.0f, 0.5f, 80.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, angub * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Basket_M.RenderModel();
		
		
		//-------------------------------------------------------------DIBUJAR FLOTADOR--------------------------------------------------------------------------------//
		
		//Modelo Flotador//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(2.7f + movXflotador, 3.5f + movYflotador, -45.0f + movZflotador));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 180  * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flotador_M.RenderModel();

		//-------------------------------------------------------------DIBUJAR ALBERCA LARGA-----------------------------------------------------------------------------//

		//Modelo de Alberca//
		model = glm::mat4(1.0);
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.11f, -25.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Alberca_M.RenderModel();

		

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
		model = glm::translate(model, glm::vec3(75.0f, 3.5f, -60.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casas_M.RenderModel();
		glDisable(GL_BLEND);
		
		//--------------------------------------------------------------------------------------------------------------------------------------------------
		//Modelo de Edificio
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(75.0f, 0.5f, 80.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio_M.RenderModel();
		glDisable(GL_BLEND);
		

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
		
	
		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
//---------------------------------------------------- FUNCION PARA CARGAR LAS TECLAS-------------------------------------------------------------------//

void inputKeyframes(bool* keys)
{

	//-------------------------------------------------------------------------ACTIVA SPIDERMAN [3]----------------------------------------------------------------------------//
	if (keys[GLFW_KEY_3])//
	{
		spiderman = 1;
	}
	//-------------------------------------------------------------------------RESET SPIDERMAN [4]----------------------------------------------------------------------------//
	if (keys[GLFW_KEY_4])//
	{
		spiderman = 0;
	}
	//---------------------------------------------------------------------ACTIVAR CAMARAS 3RA PERSONA Y AREA [5]--------------------------------------------------------------//
	if (keys[GLFW_KEY_5])//
	{
		cambioArea = 1;///
	}
	//---------------------------------------------------------------------------ACTIVA CAMARA 3RA PERSONA [6]-----------------------------------------------------------------//
	if (keys[GLFW_KEY_6])//
	{
		cambioTer = 1;//
		
	}
	//-----------------------------------------------------------------------------ACTIVA CAMARA AREA[7]----------------------------------------------------------------------//
	if (keys[GLFW_KEY_7])//
	{
		cambioTer = 0;///
				
	}
	//---------------------------------------------------------------------------------DESACTIVA CAMARAS [8]--------------------------------------------------------------------//
	if (keys[GLFW_KEY_8])//
	{
		cambioArea = 0;
	
	}
	//--------------------------------------------------------------------MOVIMIENTOS CAMARA 3RA PERSONA-------------------------------------------------------------------//
	if (keys[GLFW_KEY_I])//+Z se entiende por arriba
	{
		mueveYoZlibre += 1.0;
	}
	if (keys[GLFW_KEY_K])//-Z se entiende por abajo
	{
		mueveYoZlibre -= 1.0;
	}
 
	if (keys[GLFW_KEY_J])
	{
		mueveXlibre += 1.0;
	}
	if (keys[GLFW_KEY_L])
	{
		mueveXlibre -= 1.0;
	}

	//--------------------------------------------------------------------MOVIMIENTOS CAMARA AREA-------------------------------------------------------------------------//
	if (keys[GLFW_KEY_T])//-X se entiende por arriba
	{
		mueveCam += 1.0;
	}
	if (keys[GLFW_KEY_G])//+X se entiende por abajo
	{
		mueveCam -= 1.0;
	}

	if (keys[GLFW_KEY_F])//-Z se entiende por izquierda
	{
		mueveCam2-= 1.0;
	}
	if (keys[GLFW_KEY_H])//+Z se entiende por derecha
	{
		mueveCam2 += 1.0;
	}
	//--------------------------------------------------------------------ANIMACION FLOTADOR-------------------------------------------------------------------------//
	if (keys[GLFW_KEY_C])//Activa
	{
		flota = 1;
	}
	if (keys[GLFW_KEY_V])//Desactiva
	{
		flota = 0;
	}

	//--------------------------------------------------------------------ANIMACION BASKETBALL----------------------------------------------------------------------//
	if (keys[GLFW_KEY_E])//Activa
	{
		basketball = 1;
	}
	if (keys[GLFW_KEY_R])//Desactiva
	{
		basketball = 0;
	}

}