#pragma once
#include <string>
#include <boost/asio.hpp>

class ServiceBase
{
protected:
    boost::asio::io_service m_io_service;
public:
    virtual void process() =0;
};
