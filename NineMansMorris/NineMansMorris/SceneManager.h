#pragma once

#include <vector>

#include "ViewBox.h"

class SceneManager
{
public:
	SceneManager();
	void Draw();
	void AddViewBox(ViewBox* viewBox);

private:
	std::vector<ViewBox*> _viewBoxes;
};