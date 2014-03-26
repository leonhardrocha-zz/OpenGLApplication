#include "../OpenGLApplication/OpenGLHelper.h"
#include "OpenGLWindow.h"

class AssetWindow : public OpenGLWindow, CToeInStereoView
{
public:
    AssetWindow();

    void initialize();
    void render();
	virtual void SetupWindow();
	// virtual void SetupScene();
	virtual void RenderScene();

protected:

	OpenGL21Renderer renderer;

};