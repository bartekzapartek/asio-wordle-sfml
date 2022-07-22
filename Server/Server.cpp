#include "Server.h"

network::ServerInterface::ServerInterface(unsigned int port):
	mAsioConnectionAccpetHandler(mAsioContextHandler, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{

}

network::ServerInterface::~ServerInterface()
{
	StopServerRunning();
}

void network::ServerInterface::InitiateServerRunning()
{
	AcceptArrivingConnections();

	mThreadForAsioContext = std::thread([this]() { mAsioContextHandler.run(); });
}

void network::ServerInterface::StopServerRunning()
{
	mAsioContextHandler.stop();

	if (mThreadForAsioContext.joinable()) mThreadForAsioContext.join();
}

void network::ServerInterface::Update()
{
	while (!mMessagesComingIn.Empty())
	{
		auto [message, client] = mMessagesComingIn.PopFront();

		ActionAfterMessageFromClientArrives(message, client);
	}
}

void network::ServerInterface::SendMessageToValidClient(Message& message, std::shared_ptr<ServerConnectionHandler> serverWithClientHandler)
{
	if (serverWithClientHandler && serverWithClientHandler->IsConnected()) serverWithClientHandler->Send(message);
	else RemoveClientFromActiveConnections(serverWithClientHandler);
}

void network::ServerInterface::RemoveClientFromActiveConnections(std::shared_ptr<ServerConnectionHandler> serverWithClientHandler)
{
	
		//mEstablishedConnectionsWithClients.remove_if()
	
}

void network::ServerInterface::AcceptArrivingConnections()
{
	mAsioConnectionAccpetHandler.async_accept(
		[this](std::error_code errorOccured, asio::ip::tcp::socket connectionSocket)
		{

			if (!errorOccured)
			{
				std::shared_ptr<ServerConnectionHandler> newConnectionHandler = CreateNewConnectionHandler(std::move(connectionSocket));
				AddNewConnectionToList(newConnectionHandler);
				
				ActionAfterConnectionWihClientWasEstablished(newConnectionHandler);

				newConnectionHandler->Connect(1);
			}
			else
			{
				std::cout << "POSSIBLE_ERROR::SERVER_INTERFACE::ACCEPT_ARRIVING_CONNECTIONS():: connection with client denied.\n";
			}

			AcceptArrivingConnections();
		}
	);
}

std::shared_ptr<network::ServerConnectionHandler> network::ServerInterface::CreateNewConnectionHandler(asio::ip::tcp::socket connectionSocket)
{
	return std::make_shared<ServerConnectionHandler>(mAsioContextHandler, std::move(connectionSocket), mMessagesComingIn);
}

void network::ServerInterface::AddNewConnectionToList(std::shared_ptr<ServerConnectionHandler> connecitonWithClientHandler)
{
	mEstablishedConnectionsWithClients.push_back(connecitonWithClientHandler);
}

