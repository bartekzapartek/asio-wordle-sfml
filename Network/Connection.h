#pragma once

#include "CommonLibraries.h"
#include "Message.h"
#include "ThreadSafeQueue.h"

namespace network
{
	class Connection
	{
	protected:

		asio::io_context& mAsioContextHandler;
		asio::ip::tcp::socket mConnectionSocket;
		
		ThreadSafeQueue<Message> mMessagesCommingOut;

		Message mTemporaryReadMessage;

		

	public:
		
		Connection(asio::io_context& asioContextHandler, asio::ip::tcp::socket mConnectionSocket);
		virtual ~Connection();

	public:

		bool IsConnected();

		void Disconnect();
		void Send(const Message& message);

	protected:

		void ReadMessageHeaderComingIn();
		void ReadMessageWordComingIn();

		void WriteMessageHeaderComingOut();
		void WriteMessageWordComingOut(Message message);

	protected:

		virtual void JoinIncomingMessageToQueue() = 0;


	};
}