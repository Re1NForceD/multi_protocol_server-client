#pragma once
#include <service_base.hpp>
#include <boost/array.hpp>

namespace ip = boost::asio::ip;

class TCPServer: public ServiceBase
{
    ip::tcp::acceptor m_acceptor;
public:
    TCPServer(unsigned port);
    void process() override;
};
