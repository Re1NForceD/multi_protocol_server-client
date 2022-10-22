#pragma once
#include <service_base.hpp>

namespace ip = boost::asio::ip;

class TCPClient: public ServiceBase
{
    ip::tcp::socket m_socket;
    ip::tcp::endpoint m_endpoint;
public:
    TCPClient(std::string host, unsigned port);
    void process() override;
};
