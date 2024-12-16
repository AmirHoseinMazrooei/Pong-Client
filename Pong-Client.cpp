#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <iostream>
#include <string>
#include <thread>

using asio::ip::tcp;

void send_message(tcp::socket& socket) {
    try {
        while (true) {
            std::string message;
            std::cout << "Enter message: ";
            std::getline(std::cin, message);

            if (message.empty()) {
                continue;
            }

            asio::write(socket, asio::buffer(message));
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error sending message: " << e.what() << "\n";
    }
}

void receive_messages(tcp::socket& socket) {
    try {
        while (true) {
            char buffer[1024];
            asio::error_code ec;
            size_t length = socket.read_some(asio::buffer(buffer), ec);

            if (ec == asio::error::eof) {
                std::cout << "Server disconnected.\n";
                break;
            }
            else if (ec) {
                throw asio::system_error(ec);
            }

            std::cout << "\n Server: " << std::string(buffer, length) << "\nEnter message: ";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error receiving message: " << e.what() << "\n";
    }
}

int main12() {
    try {
        asio::io_context io_context;

        tcp::socket socket(io_context);
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("127.0.0.1", "12345");

        asio::connect(socket, endpoints);
        std::cout << "Connected to server.\n";

        std::thread sender(send_message, std::ref(socket));
        std::thread receiver(receive_messages, std::ref(socket));

        sender.join();
        receiver.join();

    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
