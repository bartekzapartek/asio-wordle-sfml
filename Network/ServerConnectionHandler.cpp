#include "ServerConnectionHandler.h"
//, mMessagesComingIn(messagesComingIn) , ThreadSafeQueue<MessageBoundWithClient>& messagesComingIn
network::ServerConnectionHandler::ServerConnectionHandler(asio::io_context& contextHandler, 
										asio::ip::tcp::socket connectionSocket, ThreadSafeQueue<MessageBoundWithClient>& messagesComingIn) :
					Connection(contextHandler, std::move(connectionSocket)), mMessagesComingIn(messagesComingIn), mClientConnectionID(0)
{
}

void network::ServerConnectionHandler::JoinIncomingMessageToQueue()
{
	mMessagesComingIn.PushBack(MessageBoundWithClient(mTemporaryReadMessage, this->shared_from_this()));
	ReadMessageHeaderComingIn();
}

void network::ServerConnectionHandler::Connect(unsigned int clientID)
{
	if (IsConnected())
	{
		mClientConnectionID = clientID;
		ReadMessageHeaderComingIn();
	}
}

