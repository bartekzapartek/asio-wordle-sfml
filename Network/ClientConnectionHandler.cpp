#include "ClientConnectionHandler.h"

network::ClientConnectionHandler::ClientConnectionHandler(asio::io_context& contextHandler,
									asio::ip::tcp::socket connectionSocket, ThreadSafeQueue<Message>& messagesComingIn) :
						Connection(contextHandler, std::move(connectionSocket)), mMessagesComingIn(messagesComingIn)	
{
}

void network::ClientConnectionHandler::JoinIncomingMessageToQueue()
{
	mMessagesComingIn.PushBack(mTemporaryReadMessage);
	ReadMessageHeaderComingIn();
}

void network::ClientConnectionHandler::Connect(const asio::ip::tcp::resolver::results_type& connectionEndpoint)
{
	asio::async_connect(mConnectionSocket, connectionEndpoint,
		[this](std::error_code errorOccured, asio::ip::tcp::endpoint endpoint)
		{
			if (!errorOccured) ReadMessageHeaderComingIn();
			else
			{
				std::cout << "ERROR::CLIENT_CONNECTION_HANDLER::CONNECT():: connection establishment fail.\n";
			}
		}
		);
}

