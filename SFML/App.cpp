#include "App.h"

App::App()
{
	mGame = std::make_unique<Game>();
	mRenderer = std::make_unique<Renderer>(mWindow, mGame->GetLetters());

	mClient.Connect("127.0.0.1", 60000);

}

App::~App()
{
}

bool App::IsWindowOpen() const
{
	return mWindow->isOpen();
}

void App::PollEvents()
{
	while (mWindow->pollEvent(mEventHandler))
	{
		switch (mEventHandler.type)
		{
		case sf::Event::KeyPressed: OnKeyboradPressed(); break;
		case sf::Event::Closed: mWindow->close();
		}
	}
}

void App::GrabServerMessages()
{
	
		if (!mClient.IsConntected()) return;


		if (mClient.IsThereIncomingMessage())
		{
			network::Message message = mClient.GetIncomingMessage();
			std::string messageContext = message.GetMessageWord();
			switch (message.GetMessageHeaderInfo())
			{
			case network::Message::message_header_info::server_guess_again: mGame->SetNextRound(messageContext); break;
			case network::Message::message_header_info::server_establish_you_as_winner: mGame->SetWinGameState(); break;
			case network::Message::message_header_info::server_established_you_as_defeated: mGame->SetDefeatedGameState(messageContext); break;
			case network::Message::message_header_info::server_word_not_in_dictionary: mGame->SetWordNotInDictionaryGameState(); break;
			}
		}
	
}

void App::OnKeyboradPressed()
{

	if (mGame->GetGameState() == Game::game_state::user_lost || mGame->GetGameState() == Game::game_state::user_won)
	{
		if (mEventHandler.key.code == sf::Keyboard::Enter) mGame->ResetGame();
	}

	switch (mEventHandler.key.code)
	{

	case sf::Keyboard::Enter: mGame->SendGuessedWordToValidationCheck(mClient); return; break;

	case sf::Keyboard::Escape: mGame->InformServerAboutDisconnection(mClient); mWindow->close(); return;  break;

	case sf::Keyboard::BackSpace: mGame->DeleteLeastTypedCharacter(); break;

	}
	
	char letterPressed = (mEventHandler.key.code + 65);
	if (letterPressed >= 65 && letterPressed <= 90) mGame->UpdateTypedWord(letterPressed);
}


void App::UpdateGameState()
{
	switch (mGame->GetGameState())
	{
	case Game::game_state::user_is_playing:
	{
		mWindow->clear();
		mRenderer->RenderUserPlayingScreen(*mWindow, mGame->GetLetters());
		mWindow->display();

	} break;

	case Game::game_state::user_won:
	{
		mWindow->clear();
		mRenderer->RenderVictoryScreen(*mWindow, mGame->GetLetters());
		mWindow->display();

	} break;

	case Game::game_state::user_lost:
	{
		mWindow->clear();
		mRenderer->RenderDefeatedScreen(*mWindow, mGame->GetLetters(), mGame->GetWordDrawnByServer());
		mWindow->display();

	} break;
	
	case Game::game_state::user_word_not_in_dictionary:
	{
		using namespace std::chrono_literals;

		mWindow->clear();
		mRenderer->RenderNotInDictionaryScreen(*mWindow, mGame->GetLetters());
		mWindow->display();

		std::this_thread::sleep_for(2s);

		mGame->SetUserPlayingGameState();

	} break;
	}
}

void App::Update()
{
	PollEvents();
	GrabServerMessages();
	UpdateGameState();
	
}
