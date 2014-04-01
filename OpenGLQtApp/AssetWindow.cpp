#include "AssetWindow.h"

AssetWindow::AssetWindow()
{
}

void AssetWindow::SetupWindow()
{
	windowWidth = width();
	windowHeight = height();
}

void AssetWindow::initialize()
{
	SetupWindow();
	SetupView();
	SetupScene();
	renderer.Initialize();
	SetRenderer((BaseAssetRenderer&) renderer);
}

void AssetWindow::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
	RenderStereoView();
}

void AssetWindow::RenderScene()
{
	renderer.Render();
}