# Pong Client

This is a Pong game client implemented in C++ using SDL2 for rendering, ASIO for networking, and FlatBuffers for data serialization. The client connects to a Pong game server, receives game state updates, and renders the game accordingly.

## Features

- **Classic Pong Gameplay**: Enjoy a modern take on the classic Pong game.
- **Smooth Player Movement**: Implemented frame-independent movement for fluid and responsive controls.
- **Client-Server Architecture**: Communicates with a server to handle multiplayer gameplay.
- **Real-Time Synchronization**: Uses FlatBuffers for efficient game state serialization and synchronization.
- **Component-Based Design**: Organized codebase with a focus on modular components.

## Getting Started

### Prerequisites

- **Operating System**: Windows
- **Development Environment**: Visual Studio 2022 or later
- **Dependencies**:
  - [SDL2](https://www.libsdl.org/) (Simple DirectMedia Layer)
  - [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/) (SDL extension for TrueType fonts)
  - [ASIO](https://think-async.com/Asio/) (Standalone Asio for networking)
  - [FlatBuffers](https://google.github.io/flatbuffers/) (Serialization library)

### Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/yourusername/pong-client.git
   ```

2. **Open the Solution**

   - Navigate to the project directory.
   - Open `Pong-Client.sln` with Visual Studio.

3. **Configure Dependencies**

   - Ensure all dependencies are installed and paths are correctly set in the project configuration.
   - NuGet packages are used for SDL2 and SDL2_ttf; restore NuGet packages if prompted.

4. **Build the Project**

   - Select the appropriate build configuration (`Debug` or `Release`) and platform (`x64`).
   - Build the solution using Visual Studio.

### Running the Game

1. **Start the Pong Server**

   - Ensure the Pong server is running and accessible at `127.0.0.1` on port `12345`.

2. **Run the Client**

   - Launch the compiled executable or run the project from Visual Studio.
   - A window titled "Pong Client" should appear.

3. **Controls**

   - **Player Movement**:
     - Use `W` and `S` keys to move your paddle up and down.
     - Alternatively, use the `Up` and `Down` arrow keys.

## Project Structure

- **`Pong-Client.cpp`**: Main application file handling initialization, the game loop, event handling, rendering, and networking.
- **GameObject and Component Classes**: Implement a simple entity-component system for game objects.
- **Rendering Components**:
  - **SDLRectRenderer**: Renders rectangular shapes (used for paddles).
  - **SDLCircleRenderer**: Renders circular shapes (used for the ball).
- **Transform Component**: Holds position, rotation, and scale data for game objects.
- **Networking**:
  - Uses ASIO for asynchronous TCP communication with the server.
  - Game state updates are received and applied to local game objects.
- **Serialization**:
  - Utilizes FlatBuffers (`game_state.h`) for efficient serialization and deserialization of game state data.
- **Utilities**:
  - **`utils.h` and `utils.cpp`**: Helper functions for loading fonts and rendering text.

## Acknowledgments

- **SDL2**: Provides the foundational library for rendering and handling inputs.
- **SDL2_ttf**: Enables text rendering using TrueType fonts.
- **ASIO**: Facilitates asynchronous networking capabilities.
- **FlatBuffers**: Used for serializing complex data structures efficiently.

---

Feel free to contribute to the project by submitting issues or pull requests. For any questions or support, please contact the project maintainer.
