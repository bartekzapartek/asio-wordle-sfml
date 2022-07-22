#include "Connection.h"

network::Connection::Connection(asio::io_context& asioContextHandler, asio::ip::tcp::socket connectionSocket) :
		 mAsioContextHandler(asioContextHandler), mConnectionSocket(std::move(connectionSocket)), mTemporaryReadMessage(Message::message_header_info::none)
{
}

network::Connection::~Connection()
{
	Disconnect();
}



bool network::Connection::IsConnected()
{
	return mConnectionSocket.is_open();
}



void network::Connection::ReadMessageHeaderComingIn()
{
		asio::async_read(mConnectionSocket, asio::buffer(mTemporaryReadMessage.GetHeaderInfoBuffer(), sizeof(int)),
		[this](std::error_code errorOccured, std::size_t messageLength)
		{
				if (!errorOccured)
				{
					if (mTemporaryReadMessage.GetMessageHeaderInfo() != Message::message_header_info::none)	ReadMessageWordComingIn();
					else ReadMessageHeaderComingIn();
				}
				else
				{
					std::cout << "ERROR::NETWORK::CONNECTION::READ_MESSAGE_HEADER_COMING_IN():: read message fail.\n";
					Disconnect();
				}
		}
		);
}

void network::Connection::ReadMessageWordComingIn()
{
	asio::async_read(mConnectionSocket, asio::buffer(mTemporaryReadMessage.GetMessageWordBuffer(), mTemporaryReadMessage.GetMessageWord().size()),
		[this](std::error_code errorOccured, std::size_t messageLength)
		{
			if (!errorOccured) JoinIncomingMessageToQueue();
			else
			{
				std::cout << "ERROR::NETWORK::CONNECTION::READ_MESSAGE_WORD_COMING_IN():: read message fail.\n";
				Disconnect();
			}
		}
	);
}

void network::Connection::WriteMessageHeaderComingOut()
{
		 Message messageOut = mMessagesCommingOut.PopFront();

		asio::async_write(mConnectionSocket, asio::buffer(messageOut.GetHeaderInfoBuffer(), sizeof(Message::message_header_info)),
		[this, messageOut](std::error_code errorOccured, std::size_t messageLength)
		{
			if (!errorOccured)
			{
			
				if (messageOut.GetMessageHeaderInfo() != Message::message_header_info::none) WriteMessageWordComingOut(messageOut);
				else if (!mMessagesCommingOut.Empty()) WriteMessageHeaderComingOut();
			
			}
			else
			{
				std::cout << "ERROR::NETWORK::CONNECTION::COMPOSE_MESSSAGE_HEADER_COMING_OUT():: write message fail.\n";
				Disconnect();
			}
		}
		);
}

void network::Connection::WriteMessageWordComingOut(Message messageOut)
{
		asio::async_write(mConnectionSocket, asio::buffer(messageOut.GetMessageWordBuffer(), messageOut.GetMessageWord().size()),
		[this](std::error_code errorOccured, std::size_t messageLength)
		{
			if (!errorOccured)
			{
				if (!mMessagesCommingOut.Empty()) WriteMessageHeaderComingOut();
				
			}
			else
			{
				std::cout << "ERROR::NETWORK::CONNECTION::COMPOSE_MESSSAGE_WORD_COMING_OUT():: write message fail.\n";
				Disconnect();
			}
		}
	);
}

void network::Connection::Send(const Message& message)
{
		asio::post(mAsioContextHandler,
			[this, message]()
			{
				bool shouldStartComposingMessage = mMessagesCommingOut.Empty();

				mMessagesCommingOut.PushBack(message);

				if (shouldStartComposingMessage) WriteMessageHeaderComingOut();
			}
		);
}

void network::Connection::Disconnect()
{
	if (IsConnected()) asio::post(mAsioContextHandler, [this]() { mConnectionSocket.close(); });
}

