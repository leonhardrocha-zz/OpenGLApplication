#ifndef _OPENGGL_HELPER_H_
#define _OPENGGL_HELPER_H_

#ifdef _WIN32
#include <windows.h>
#endif

//	Entry point for OpenGLHelper library
#include "BaseStereoView.h"
#include "ToeInStereoView.h"
#include "AssetReader.h"
#include "BaseAssetRenderer.h"
#include "OpenGL21Renderer.h"

#define printOpenGLError() OpenGLHelper::PrintOglError(__FILE__, __LINE__)

int PrintOglError(char *file, int line);

#endif