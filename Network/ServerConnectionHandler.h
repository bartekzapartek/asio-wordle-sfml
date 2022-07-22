#pragma once
#include "Connection.h"

namespace network
{
	

	class ServerConnectionHandler : public Connection, public std::enable_shared_from_this<ServerConnectionHandler>
	{
	private:

		typedef std::pair<Message, std::shared_ptr<ServerConnectionHandler>> MessageBoundWithClient;

		ThreadSafeQueue<MessageBoundWithClient>& mMessagesComingIn;
		unsigned int mClientConnectionID;
		

	public:

		ServerConnectionHandler(asio::io_context& contextHandler, asio::ip::tcp::socket connectionSocket, ThreadSafeQueue<MessageBoundWithClient>& messagesComingIn);

		void Connect(unsigned int clientID = 1);

		void JoinIncomingMessageToQueue() override;

	};


}