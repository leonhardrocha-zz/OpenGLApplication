#ifndef _MODEL_VIEW_H_
#define _MODEL_VIEW_H_


#include <vector>
#include <map>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <IL/il.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

// assimp include files. These three are usually needed.
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

class CModelView
{

public:

	//	Constructor / Destructor.
	CModelView();
	virtual ~CModelView();

// Attributes
public:

// Operations
public:
// Overrides
protected:
	//	Main OpenGL functions.
	virtual void SetupScene();
	virtual void RenderScene();
	virtual void FinishScene();
	virtual bool Import3DFromFile( const std::string& pFile);
	virtual void DoOpenGLDraw();
	virtual void DoOpenGLResize(int nWidth, int nHeight);
	virtual void SetupLog();

	virtual int LoadGLTextures(const aiScene* scene);
	virtual void RecursiveRender (const aiScene *sc, const aiNode* nd);
	virtual void GenerateVAOsAndUniformBuffer(const aiScene *sc);

private:
		// Model Matrix (part of the OpenGL Model View Matrix)
	float modelMatrix[16];

	// For push and pop matrix
	std::vector<float *> matrixStack;

	// Vertex Attribute Locations
	GLuint vertexLoc, normalLoc, texCoordLoc;//=0,1,2

	// Uniform Bindings Points
	GLuint matricesUniLoc, materialUniLoc;//=1,2

	// The sampler uniform for textured models
	// we are assuming a single texture so this will
	//always be texture unit 0
	GLuint texUnit;//=0

	// Uniform Buffer for Matrices
	// this buffer will contain 3 matrices: projection, view and model
	// each matrix is a float array with 16 components
	GLuint matricesUniBuffer;
	
	// Program and Shader Identifiers
	GLuint program, vertexShader, fragmentShader;

	// Shader Names
	std::string vertexFileName;// = "dirlightdiffambpix.vert";
	std::string fragmentFileName;// = "dirlightdiffambpix.frag";

	// Create an instance of the Importer class
	Assimp::Importer importer;

	// the global Assimp scene object
	const aiScene* scene;// = NULL;

	// scale factor for the model to fit in the window
	float scaleFactor;
	
	// images / texture
	// map image filenames to textureIds
	// pointer to texture Array
	std::map<std::string, GLuint> textureIdMap;	

	// Replace the model name by your model's filename
	std::string modelname;// = "../Mickey Mouse/Mickey Mouse.obj";

	// Camera Position
	float camX, camY, camZ;

	// Mouse Tracking Variables
	int startX, startY, tracking;

	// Camera Spherical Coordinates
	float alpha, beta;
	float r;

	#define M_PI       3.14159265358979323846f

	static inline float 
	DegToRad(float degrees) 
	{ 
		return (float)(degrees * (M_PI / 180.0f));
	};

	// Frame counting and FPS computation
	long time,timebase,frame;
	char fpsBuffer[32];
	
	void GetBoundingBox (aiVector3D* min, aiVector3D* max);
	void GetBoundingBoxForNode (const aiNode* nd, 
								aiVector3D* min, 
								aiVector3D* max, 
								aiMatrix4x4* trafo);
	void color4_to_float4(const aiColor4D *c, float f[4]);
	void set_float4(float f[4], float a, float b, float c, float d);
	void PrintShaderInfoLog(GLuint obj);
	void PrintProgramInfoLog(GLuint obj);
	GLuint CModelView::SetupShaders();
	char *TextFileRead(const char *filename);
	int TextFileWrite(const char *filename, char *s);
};

#endif