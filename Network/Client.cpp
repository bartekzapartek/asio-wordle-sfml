#include "Client.h"

network::ClientInterace::~ClientInterace()
{
    Disconnect();
}

bool network::ClientInterace::IsConntected() const
{
    return (mClientConnectionHandler && mClientConnectionHandler->IsConnected() ? true : false);
}

void network::ClientInterace::Disconnect()
{
    if (IsConntected()) mClientConnectionHandler->Disconnect();

    mAsioContextHandler.stop();

    if (mThreadForAsioContext.joinable()) mThreadForAsioContext.join();

    mClientConnectionHandler.release();
}

void network::ClientInterace::Connect(const std::string& serverIP, const unsigned int& port)
{
    asio::ip::tcp::resolver resolveIPaddres(mAsioContextHandler);
    asio::ip::tcp::resolver::results_type serverEndpoint = resolveIPaddres.resolve(serverIP, std::to_string(port));

    asio::ip::tcp::socket socket(mAsioContextHandler);

    mClientConnectionHandler = std::make_unique<ClientConnectionHandler>(mAsioContextHandler, std::move(socket), mMessagesComingIn);

    mClientConnectionHandler->Connect(serverEndpoint);

    mThreadForAsioContext = std::thread([this]() { mAsioContextHandler.run(); });
}

void network::ClientInterace::Send(const Message& message)
{
    if (IsConntected()) mClientConnectionHandler->Send(message);
}

network::Message network::ClientInterace::GetIncomingMessage()
{
    if (!mMessagesComingIn.Empty()) return mMessagesComingIn.PopFront();
    else return Message(Message::message_header_info::none, "");
}

bool network::ClientInterace::IsThereIncomingMessage()
{
    return !mMessagesComingIn.Empty();
}
