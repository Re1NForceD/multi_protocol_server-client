#pragma once
#include <service_base.hpp>
#include <boost/array.hpp>

namespace ip = boost::asio::ip;

class UDPServer: public ServiceBase
{
    ip::udp::socket m_socket;
public:
    UDPServer(unsigned port);
    void process() override;
};
