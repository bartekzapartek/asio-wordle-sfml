#pragma once
#include "Game.h"
#include "Renderer.h"
#include <cctype>
#include "Include.h"

class App
{
public:


private:
	sf::RenderWindow* mWindow;
	sf::Event mEventHandler;

	std::unique_ptr<Renderer> mRenderer;
	std::unique_ptr<Game> mGame;
	
	network::ClientInterace mClient;

private:

	void UpdateGameState();
	void GrabServerMessages();
	void PollEvents();
	void OnKeyboradPressed();

public:

	App();
	~App();

public:

	bool IsWindowOpen() const;
	void Update();

};