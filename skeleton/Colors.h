#pragma once
#include "core.hpp"
#include <vector>

enum ColorsEnum { YELLOW, GREEN, RED, BLUE, ORANGE, PURPLE, PINK, BROWN, BLACK, WHITE };

struct Colors
{
	std::vector<Vector4> c =
	{
		{ 1.0, 1.0, 0.0, 1.0 }, //Yellow
		{ 0.0, 1.0, 0.0, 1.0 }, //Green
		{ 1.0, 0.0, 0.0, 1.0 }, //Red
		{ 0.0, 0.0, 1.0, 1.0 }, //Blue
		{ 1.0, 0.5, 0.2, 1.0 }, //Orange
		{ 1.0, 0.0, 1.0, 1.0 }, //Purple
		{ 1.0, 0.25, 0.5, 1.0 }, //Pink
		{ 0.0, 0.0, 0.0, 1.0 }, //Black
		{ 1.0, 1.0, 1.0, 1.0 } //White
	};

	std::vector<Vector4> rainbow =
	{
		{ 1.0, 0.0, 0.0, 1.0 }, //Red
		{ 1.0, 0.5, 0.2, 1.0 }, //Orange
		{ 1.0, 1.0, 0.0, 1.0 }, //Yellow
		{ 0.0, 1.0, 0.0, 1.0 }, //Green
		{ 0.0, 1.0, 1.0, 1.0 }, //Cyan
		{ 0.0, 0.0, 1.0, 1.0 }, //Blue
		{ 1.0, 0.0, 1.0, 1.0 }, //Purple
		{ 1.0, 0.25, 0.5, 1.0 } //Pink
	};
};