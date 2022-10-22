#include <tcp_client.hpp>

#include <iostream>
#include <boost/array.hpp>

TCPClient::TCPClient(std::string host, unsigned port)
: m_endpoint{ip::address::from_string(host), port}, m_socket{m_io_service}
{
	std::cout << "Initiate TCP Client: target address - " << host << " and port - " << port << std::endl;
}

void TCPClient::process()
{
	std::cout << "Client process" << std::endl;
    m_socket.connect(m_endpoint);

    std::string msg;
    getline(std::cin, msg);

	boost::asio::write(m_socket, boost::asio::buffer(msg));
}
