#include <asio.hpp>
#include <SDL.h>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <array>

using asio::ip::tcp;

class Client {
public:
	Client(const std::string& host, const std::string& port)
		: socket_(io_context_) {
		try {
			tcp::resolver resolver(io_context_);
			auto endpoints = resolver.resolve(host, port);
			asio::connect(socket_, endpoints);
			std::cout << "Connected to server.\n";
		}
		catch (const std::exception& e) {
			std::cerr << "Connection failed: " << e.what() << "\n";
			throw;
		}
	}

	void sendInput(const std::string& input) {
		asio::write(socket_, asio::buffer(input + "\n"));
	}

	std::string receiveData() {
		asio::error_code ec;
		std::size_t length = socket_.read_some(asio::buffer(buffer_), ec);
		if (ec == asio::error::eof) {
			std::cout << "Server disconnected.\n";
			return "";
		}
		else if (ec) {
			throw asio::system_error(ec);
		}
		return std::string(buffer_.data(), length);
	}

private:
	asio::io_context io_context_;
	tcp::socket socket_;
	std::array<char, 1024> buffer_;
};

struct GameState {
	float player1_y, player2_y;
	float ball_x, ball_y;
};

// Shared game state
GameState gameState = { 300.0f, 300.0f, 400.0f, 300.0f };
std::mutex gameStateMutex;
bool running = true;

void parseGameState(const std::string& data, GameState& state) {
	sscanf_s(data.c_str(), "%f %f %f %f",
		&state.player1_y, &state.player2_y, &state.ball_x, &state.ball_y);
}

void networkThreadFunc(Client& client) {
	try {
		while (running) {
			// Receive data from server
			std::string data = client.receiveData();
			if (data.empty()) {
				running = false;
				break;
			}

			GameState newState;
			parseGameState(data, newState);

			// Update shared game state
			{
				std::lock_guard<std::mutex> lock(gameStateMutex);
				gameState = newState;
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Network error: " << e.what() << "\n";
		running = false;
	}
}

int main1(int argc, char* argv[]) {
	// SDL Initialization
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL Init Failed: " << SDL_GetError() << "\n";
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow("Pong Client",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cerr << "Window Creation Failed: " << SDL_GetError() << "\n";
		SDL_Quit();
		return -1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cerr << "Renderer Creation Failed: " << SDL_GetError() << "\n";
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	// Networking
	Client client("127.0.0.1", "12345");

	// Start network thread
	std::thread networkThread(networkThreadFunc, std::ref(client));

	SDL_Event event;

	while (running) {
		// Event handling
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}

		// Input handling
		const Uint8* keys = SDL_GetKeyboardState(NULL);
		std::string input;
		if (keys[SDL_SCANCODE_UP]) {
			input = "UP";
			printf_s("keys[SDL_SCANCODE_UP]: %d\n", keys[SDL_SCANCODE_UP]);
		}
		else if (keys[SDL_SCANCODE_DOWN]) {
			input = "DOWN";
			printf_s("keys[SDL_SCANCODE_DOWN]: %d\n", keys[SDL_SCANCODE_DOWN]);
		}
		else {
			input = "NONE";
		}

		try {
			client.sendInput(input);
		}
		catch (const std::exception& e) {
			std::cerr << "Error sending input: " << e.what() << "\n";
			running = false;
		}

		// Render game state
		{
			std::lock_guard<std::mutex> lock(gameStateMutex);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Clear screen
			SDL_RenderClear(renderer);

			// Draw player paddles
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

			SDL_Rect paddle1 = { 50, static_cast<int>(gameState.player1_y), 10, 100 };
			SDL_Rect paddle2 = { 740, static_cast<int>(gameState.player2_y), 10, 100 };
			SDL_RenderFillRect(renderer, &paddle1);
			SDL_RenderFillRect(renderer, &paddle2);

			// Draw ball
			SDL_Rect ball = { static_cast<int>(gameState.ball_x), static_cast<int>(gameState.ball_y), 10, 10 };
			SDL_RenderFillRect(renderer, &ball);

			SDL_RenderPresent(renderer);
		}

		SDL_Delay(16); // Roughly 60 FPS
	}

	// Clean up
	networkThread.join();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}