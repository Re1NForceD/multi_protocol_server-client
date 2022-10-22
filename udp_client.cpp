#include <udp_client.hpp>

#include <iostream>
#include <boost/array.hpp>

UDPClient::UDPClient(std::string host, unsigned port)
: m_endpoint{ip::address::from_string(host), port}, m_socket{m_io_service}
{
	std::cout << "Initiate UDP Client: target address - " << host << " and port - " << port << std::endl;
}

void UDPClient::process()
{
	std::cout << "Client process" << std::endl;
    m_socket.open(ip::udp::v4());

    std::string msg;
    getline(std::cin, msg);

    m_socket.send_to(boost::asio::buffer(msg), m_endpoint);
}
