#include "AssetWindow.h"

AssetWindow::AssetWindow()
{
}

void AssetWindow::SetupWindow()
{
	windowWidth = width();
	windowHeight = height();
	windowOffsetX = 0;
	windowOffsetY = 0;
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

void AssetWindow::resizeWindow()
{
	SetupWindow();
	SetupView();
	SetupScene();
}