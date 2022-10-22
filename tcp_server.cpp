#include <tcp_server.hpp>
#include <iostream>

TCPServer::TCPServer(unsigned port)
: m_acceptor{m_io_service, ip::tcp::endpoint(ip::tcp::v4(), port)}
{
	std::cout << "Initiate TCP Server on port " << port << std::endl;
}

void TCPServer::process()
{
	std::cout << "Server process" << std::endl;

    while (true)
	{
		ip::tcp::socket socket{m_io_service};
		m_acceptor.accept(socket);

		std::cout << "Client with address " << socket.remote_endpoint().address().to_string() << " connected. Reading message..." << std::endl;
		while (true)
		{
			boost::array<char, 128> buf;
      		boost::system::error_code error;
	        size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
	        	break;
	      	else if (error)
	        	throw boost::system::system_error(error);

      		std::cout.write(buf.data(), len);
		}
        std::cout << std::endl;
    }
}
