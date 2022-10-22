#pragma once
#include <service_base.hpp>

namespace ip = boost::asio::ip;

class UDPClient: public ServiceBase
{
    ip::udp::socket m_socket;
    ip::udp::endpoint m_endpoint;
public:
    UDPClient(std::string host, unsigned port);
    void process() override;
};
