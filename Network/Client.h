#pragma once

#include "ClientConnectionHandler.h"


namespace network
{
	class ClientInterace
	{
	protected:
	
		asio::io_context mAsioContextHandler;

		std::thread mThreadForAsioContext;
		std::unique_ptr<ClientConnectionHandler> mClientConnectionHandler;

		ThreadSafeQueue<Message> mMessagesComingIn;

	public:

		ClientInterace() = default;
		virtual ~ClientInterace();

	public:

		bool IsConntected() const;
		void Disconnect();

		void Connect(const std::string& serverIP, const unsigned int& port);
		void Send(const Message& message);

		Message GetIncomingMessage();
		bool IsThereIncomingMessage();


	};
}