#pragma once

#include <memory>
#include <mutex>

#include <boost/asio.hpp>

#include "ConnectionManager.h"
#include "IRequestHandlerFactory.h"

class Server {
public:
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    Server(
        const std::shared_ptr<IRequestHandlerFactory>& requestHandlerFactory,
        const ushort port,
        const std::size_t workersThreadsCount = 10);

    ~Server();

    void run();

private:
    void acceptNewConnection();
    void awaitStop();

    void runEventProcessingLoop();

    std::vector<std::thread> _workersThreads;
    std::size_t _workersThreadsCount;

    boost::asio::io_context _ioContext;
    boost::asio::ip::tcp::acceptor _tcpAcceptor;
    boost::asio::signal_set _signalSet;

    std::shared_ptr<ConnectionManager> _connectionManager;
    std::shared_ptr<IRequestHandlerFactory> _requestHandlerFactory;
};

