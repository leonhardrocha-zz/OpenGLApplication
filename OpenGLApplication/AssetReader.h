#ifndef _ASSET_VIEW_H_
#define _ASSET_VIEW_H_


#include <vector>
#include <map>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

// assimp include files. These three are usually needed.
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

class AssetReader
{

public:

	//	Constructor / Destructor.
	AssetReader();
	virtual ~AssetReader();

// Attributes
public:

// Operations
public:

protected:
	virtual bool Import3DFromFile( const std::string& pFile);
	virtual void SetupLog();

private:
	
	// Create an instance of the Importer class
	Assimp::Importer importer;

	// the global Assimp scene object
	const aiScene* scene;// = NULL;	
	aiVector3D scene_min, scene_max, scene_center;

	// scale factor for the model to fit in the window
	float scaleFactor;
	
	// Replace the model name by your model's filename
	std::string modelname;// = "../Mickey Mouse/Mickey Mouse.obj";

	void GetBoundingBox (aiVector3D* min, aiVector3D* max);
	void GetBoundingBoxForNode (const aiNode* nd, 
								aiVector3D* min, 
								aiVector3D* max, 
								aiMatrix4x4* trafo);
	void color4_to_float4(const aiColor4D *c, float f[4]);
	void set_float4(float f[4], float a, float b, float c, float d);
};

#endif