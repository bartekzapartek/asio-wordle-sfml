#pragma once

#include "ServerConnectionHandler.h"
#include "ThreadSafeQueue.h"

#include <list>

namespace network
{
	class ServerInterface
	{
	protected:

		typedef std::pair<Message, std::shared_ptr<ServerConnectionHandler>> MessageBoundWithClient;

		asio::io_context mAsioContextHandler;
		std::thread mThreadForAsioContext;


		asio::ip::tcp::acceptor mAsioConnectionAccpetHandler;

		ThreadSafeQueue<MessageBoundWithClient> mMessagesComingIn;
		std::list<std::shared_ptr<ServerConnectionHandler>> mEstablishedConnectionsWithClients;

	public:

		ServerInterface(unsigned int port);
		virtual ~ServerInterface();

	public:

		void InitiateServerRunning();
		void StopServerRunning();

		void Update();

		void SendMessageToValidClient(const Message& message, std::shared_ptr<ServerConnectionHandler> serverWithClientHandler);
		void SendMessageToOtherClients(const Message& message, std::shared_ptr<ServerConnectionHandler> serverWithClientHandler);


	private:

		void AcceptArrivingConnections();

		void AddNewConnectionToList(std::shared_ptr<ServerConnectionHandler> connecitonWithClientHandler);
		void RemoveClientFromActiveConnections(std::shared_ptr<ServerConnectionHandler> serverWithClientHandler);

		std::shared_ptr<ServerConnectionHandler> CreateNewConnectionHandler(asio::ip::tcp::socket connectionSocket);


	protected:

		virtual void ActionAfterConnectionWihClientWasEstablished(std::shared_ptr<ServerConnectionHandler> serverWithClientHandler) = 0;
		virtual void ActionAfterClientDisconnect(std::shared_ptr<ServerConnectionHandler> serverWithClientHandler) = 0;
		virtual void ActionAfterMessageFromClientArrives(Message& message, std::shared_ptr<ServerConnectionHandler> serverWithClientHandler) = 0;

	};
};