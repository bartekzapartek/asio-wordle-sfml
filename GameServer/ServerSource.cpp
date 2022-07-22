#include "GameServer.h"

int main()
{
	WordleGameServer gameServer(60000);
	gameServer.InitiateServerRunning();

	while (true)
	{
		gameServer.Update();
	}

	std::cin.get();
	std::cin.get();
	std::cin.get();
}