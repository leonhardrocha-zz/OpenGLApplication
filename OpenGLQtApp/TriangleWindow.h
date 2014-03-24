#include "OpenGLWindow.h"
#include "../OpenGLApplication/OpenGLHelper.h"

class TriangleWindow : public OpenGLWindow, CToeInStereoView
{
public:
    TriangleWindow();

    void initialize();
    void render();
	virtual void SetupView();
	virtual void RenderScene();

private:
    GLuint loadShader(GLenum type, const char *source);

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    int m_frame;
};