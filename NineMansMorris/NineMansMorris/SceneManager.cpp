#include "SceneManager.h"
#include "ImageBox.h"

SceneManager::SceneManager()
{
}

void SceneManager::Draw()
{
	for (unsigned int i = 0; i < _viewBoxes.size(); i++)
	{
		_viewBoxes[i]->Draw();
	}
}

void SceneManager::AddViewBox(ViewBox* viewBox)
{
	_viewBoxes.push_back(viewBox);
}