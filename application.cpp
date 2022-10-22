#include <application.hpp>

#include <udp_server.hpp>
#include <udp_client.hpp>
#include <tcp_server.hpp>
#include <tcp_client.hpp>

#include <iostream>
#include <memory>

namespace program_options = boost::program_options;

Application::Application(int argc, char* argv[]) : _ac(argc), _av(argv), _desc("Options")
{
	_desc.add_options()
        ("help,h", "Show help")
		("tcp-server", "Use application as tcp-server")
        ("tcp-client", "Use application as tcp-client")
		("udp-server", "Use application as udp-server")
        ("udp-client", "Use application as udp-client")
        ("address,a", program_options::value<std::string>(), "Enter host address")
        ("port,p", program_options::value<unsigned>()->required(), "Enter port")
        ;
}

std::unique_ptr<ServiceBase> getService(unsigned type, std::string host, unsigned port)
{
	switch (type)
	{
	case 1:
		return std::make_unique<TCPServer>(port);
	case 2:
		return std::make_unique<TCPClient>(host, port);
	case 3:
		return std::make_unique<UDPServer>(port);
	case 4:
		return std::make_unique<UDPClient>(host, port);
	default:
		return nullptr;
	}
}

int Application::exec()
{
    try
	{
        program_options::variables_map vm;
        program_options::store(program_options::parse_command_line(_ac, _av, _desc), vm);
        program_options::notify(vm);

        if (vm.count("help") || _ac == 1)
		{
            std::cout << _desc << std::endl;
            return 0;
        }

		unsigned appType = 0;

        if (vm.count("tcp-server"))
		{
            appType = 1;
        }
        if (vm.count("tcp-client"))
		{
            appType = 2;
        }
        if (vm.count("udp-server"))
		{
            appType = 3;
        }
        if (vm.count("udp-client"))
		{
            appType = 4;
        }
		if (!appType) throw std::runtime_error("Type of service (--tcp-server, --tcp-client, --udp-server, --udp-client) did not specified");

        std::string host;
		unsigned port;
        if (vm.count("address"))
		{
            host = vm["address"].as<std::string>();
        }
        else if (appType == 2 || appType == 4)
		{
			throw std::runtime_error("Option -a [ --address ] did not specified");
        }

        if (vm.count("port"))
		{
            port = vm["port"].as<unsigned>();
        }
		else
		{
			throw std::runtime_error("Option -p [ --port ] did not specified");
        }

		std::unique_ptr<ServiceBase> service = getService(appType, host, port);
		service->process();
    }
    catch (std::exception& e)
	{
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 0;
    }
    catch (...)
	{
        std::cerr << "Exception of unknown type!" << std::endl;
    }

    return 0;
}
