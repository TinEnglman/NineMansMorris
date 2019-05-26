#pragma once

const int SCREEN_W = 768;
const int SCREEN_H = 1024;

const int FIGURE_WIDTH = 48;
const int FIGURE_HEIGHT = 48;

const int FIGURE_SELECTED_WIDTH = 52;
const int FIGURE_SELECTED_HEIGHT = 52;

const int MATCH_SIZE = 3;
const int FONT_SIZE = 60;

const int NUM_SLOTS = 24;
const int NUM_FIGURES = 9;

enum class Player
{
	NONE,
	PLAYER1,
	PLAYER2,
};

enum class GamePhase
{
	PLACING,
	MOVING,
	FLYING,
	REMOVING,
};

enum class Direction
{
	VERTICAL,
	HORIZONTAL
};