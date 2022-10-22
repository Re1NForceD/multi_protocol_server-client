#include <udp_server.hpp>
#include <iostream>

UDPServer::UDPServer(unsigned port)
: m_socket{m_io_service, ip::udp::endpoint(ip::udp::v4(), port)}
{
	std::cout << "Initiate UDP Server on port " << port << std::endl;
}

void UDPServer::process()
{
	std::cout << "Server process" << std::endl;

    boost::array<char, 1024> recv_buf;

    ip::udp::endpoint remote_endpoint;
    boost::system::error_code error;
    while (true)
    {
        size_t len = m_socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint, 0, error);

        if (error && error != boost::asio::error::message_size)
            throw boost::system::system_error(error);

        std::cout << "Message from client with address " << remote_endpoint.address().to_string() << ":" << std::endl;
        std::cout.write(recv_buf.data(), len);
        std::cout << std::endl;
    }
}
