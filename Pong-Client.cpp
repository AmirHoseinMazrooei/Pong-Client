#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <conio.h>

using asio::ip::tcp;

void send_input(tcp::socket& socket) {
    try {
        while (true) {
            char key = _getch();
            std::string message;
            if (key == 'w') message = "UP";
            if (key == 's') message = "DOWN";
            asio::write(socket, asio::buffer(message));
        }
    }
    catch (...) {
        std::cerr << "Disconnected.\n";
    }
}

void receive_state(tcp::socket& socket) {
    try {
        while (true) {
            char buffer[128];
            size_t length = socket.read_some(asio::buffer(buffer));
            std::cout << "Game State: " << std::string(buffer, length) << "\n";
        }
    }
    catch (...) {
        std::cerr << "Lost connection.\n";
    }
}

int main() {
    asio::io_context io_context;
    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve("127.0.0.1", "12345");
    tcp::socket socket(io_context);
    asio::connect(socket, endpoints);

    std::cout << "Connected to server. Use W/S to move.\n";

    std::thread input_thread(send_input, std::ref(socket));
    std::thread receive_thread(receive_state, std::ref(socket));

    input_thread.join();
    receive_thread.join();
}
