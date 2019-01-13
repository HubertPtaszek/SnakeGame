#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd) : wnd(wnd), gfx(wnd), brd(settings, gfx), rng(std::random_device()()), snake({ 2,2 }), nPoison(settings.GetPoisonAmount()), nFood(settings.GetFoodAmount()), snakeSpeedupFactor(settings.GetSpeedupRate())
{
	for (int i = 0; i < nPoison; i++)
	{
		brd.SpawnContents(rng, snake, Frame::CellContents::Poison);
	}
	for (int i = 0; i < nFood; i++)
	{
		brd.SpawnContents(rng, snake, Frame::CellContents::Food);
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();
	if (gameIsStarted)
	{
		int scoreInt = snake.GetLength() - 1;
		string score = to_string(scoreInt);
		font.DrawTextSub("Punkty: ", { 261, 550 }, textColor, gfx);
		font.DrawTextSub(score, { 380, 550 }, textColor, gfx);
		if (!gameIsOver)
		{
			if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				const Location new_delta_loc = { 0,-1 };
				if (delta_loc != -new_delta_loc || snake.GetLength() <= 2)
				{
					delta_loc = new_delta_loc;
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				const Location new_delta_loc = { 0,1 };
				if (delta_loc != -new_delta_loc || snake.GetLength() <= 2)
				{
					delta_loc = new_delta_loc;
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				const Location new_delta_loc = { -1,0 };
				if (delta_loc != -new_delta_loc || snake.GetLength() <= 2)
				{
					delta_loc = new_delta_loc;
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				const Location new_delta_loc = { 1,0 };
				if (delta_loc != -new_delta_loc || snake.GetLength() <= 2)
				{
					delta_loc = new_delta_loc;
				}
			}

			float snekModifiedMovePeriod = snakeMovePeriod;
			if (wnd.kbd.KeyIsPressed(VK_CONTROL))
			{
				snekModifiedMovePeriod = min(snakeMovePeriod, snekMovePeriodSpeedup);
			}

			snakeMoveCounter += dt;
			if (snakeMoveCounter >= snekModifiedMovePeriod)
			{
				snakeMoveCounter -= snekModifiedMovePeriod;
				const Location next = snake.GetNextHeadLocation(delta_loc);
				const Frame::CellContents contents = brd.IsInsideFrame(next) ? brd.GetContents(next) : Frame::CellContents::Empty;
				if (!brd.IsInsideFrame(next) || snake.IsInTileExceptEnd(next) || contents == Frame::CellContents::Obstacle)
				{
					gameIsOver = true;
				}
				else if (contents == Frame::CellContents::Food)
				{
					snake.GrowAndMoveBy(delta_loc);
					brd.ConsumeContents(next);
					brd.SpawnContents(rng, snake, Frame::CellContents::Obstacle);
					brd.SpawnContents(rng, snake, Frame::CellContents::Food);
					sfxEat.Play(rng, 0.8f);
				}
				else if (contents == Frame::CellContents::Poison)
				{
					snake.MoveBy(delta_loc);
					brd.ConsumeContents(next);
					snakeMovePeriod = max(snakeMovePeriod * snakeSpeedupFactor, snekMovePeriodMin);

				}
				else
				{
					snake.MoveBy(delta_loc);
					sfxSlither.Play(rng, 0.08f);
				}
			}
		}
	}
	else
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			gameIsStarted = true;
		}
	}
}

void Game::ComposeFrame()
{
	if (gameIsStarted)
	{
		snake.Draw(brd);
		brd.DrawCells();
		if (gameIsOver)
		{
			font.DrawTextSub("Przegrana :(", { 261, 299 }, textColor, gfx);
			if (wnd.kbd.KeyIsPressed(VK_RETURN))
				exit(0);
		}
		brd.DrawFrame();
	}
	else
	{
		font.DrawTextSub("Snake Game 2.0", { 238, 10 }, textColor, gfx);
		gfx.DrawSprite(200, 150, s, SpriteEffect::Copy{});
		font.DrawTextSub("Wcisnij ENTER, aby rozpoczac gre!", { 85, 560 }, textColor, gfx);
	}
}
