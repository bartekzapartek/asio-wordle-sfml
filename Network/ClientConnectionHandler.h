#pragma once
#include "Connection.h"

namespace network
{
	class ClientConnectionHandler : public Connection
	{
	private:
	

		ThreadSafeQueue<Message>& mMessagesComingIn;

	public:

		ClientConnectionHandler(asio::io_context& asioContextHandler, asio::ip::tcp::socket connectionSocket, ThreadSafeQueue<Message>& messagesComingIn);

		void Connect(const asio::ip::tcp::resolver::results_type& connectionEndpoint);

		void JoinIncomingMessageToQueue() override;
	};
}