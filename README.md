# 🎵 Music Player - DSA Project

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Data Structure](https://img.shields.io/badge/Data%20Structure-Doubly%20Linked%20List-green.svg)](#data-structures)
[![Platform](https://img.shields.io/badge/Platform-Cross%20Platform-lightgrey.svg)](#compilation)

A feature-rich console-based music player implemented in C using doubly linked lists. This project demonstrates core data structure concepts and algorithms while providing practical music player functionality.

## 🚀 Features

### Core Functionality
- ✅ **Add Songs** - Add songs to playlist with metadata (title, artist, album, duration)
- ✅ **Smart Insertion** - Insert songs at specific positions in the playlist
- ✅ **Delete Operations** - Remove songs by ID or title
- ✅ **Playback Control** - Play, pause, stop, next, and previous functionality
- ✅ **Song Preview** - Peek at next/previous songs without playing
- ✅ **Current Song Display** - Show detailed information about playing track

### Advanced Features
- ✅ **Search & Filter** - Find songs by title or artist
- ✅ **Playlist Management** - Display formatted playlist with indicators
- ✅ **Shuffle Algorithm** - Randomize playlist using Fisher-Yates algorithm
- ✅ **Reverse Playlist** - Reverse the order of all songs
- ✅ **Jump Navigation** - Directly jump to any song by ID
- ✅ **Memory Management** - Efficient dynamic memory allocation and cleanup

## 🛠️ Technology Stack

- **Language**: C (C99 Standard)
- **Data Structure**: Doubly Linked List
- **Algorithms**: Fisher-Yates Shuffle, Linear Search, In-place Reversal
- **Memory Management**: Dynamic allocation with proper cleanup
- **Platform**: Cross-platform (Windows, Linux, macOS)

## 📋 Prerequisites

- GCC compiler or any C compiler supporting C99 standard
- Terminal/Command prompt
- Basic understanding of C programming (for modification)

## 🔧 Compilation

### Quick Start
```bash
# Clone the repository
git clone https://github.com/yourusername/music-player-dsa.git
cd music-player-dsa

# Compile the program
gcc -Wall -Wextra -std=c99 -o music_player main.c

# Run the program
./music_player
```

### Using Makefile (if provided)
```bash
make all        # Compile the program
make run        # Compile and run
make clean      # Remove compiled files
make debug      # Compile with debug symbols
```

### Platform-Specific Instructions

**Windows (MinGW/MSYS2)**
```cmd
gcc -o music_player.exe main.c
music_player.exe
```

**Linux/Ubuntu**
```bash
sudo apt update
sudo apt install gcc
gcc -o music_player main.c
./music_player
```

**macOS**
```bash
# Install Xcode command line tools if not already installed
xcode-select --install
gcc -o music_player main.c
./music_player
```

## 🎮 Usage

1. **Start the program** - Run the compiled executable
2. **Sample playlist** - The program starts with 5 pre-loaded classic songs
3. **Menu navigation** - Use the numbered menu options to perform operations
4. **Add your songs** - Input song details including title, artist, album, and duration
5. **Control playback** - Use play, pause, next, previous commands
6. **Explore features** - Try shuffle, search, and other advanced features

### Example Session
```
Welcome to the Music Player!
Song 'Bohemian Rhapsody' by Queen added to playlist!
Song 'Hotel California' by Eagles added to playlist!

=== PLAYLIST ===
Total Songs: 5
ID  Title                     Artist               Album                Duration
-------------------------------------------------------------------------
>1   Bohemian Rhapsody         Queen                A Night at the Opera    05:55
 2   Hotel California          Eagles               Hotel California         06:31
 3   Sweet Child O' Mine       Guns N' Roses        Appetite for Destruction 05:56

🎵 Now Playing: 'Bohemian Rhapsody' by Queen
Album: A Night at the Opera | Duration: 5:55
```

## 🏗️ Data Structures

### Primary Structure: Doubly Linked List
```c
struct Song {
    int id;                    // Unique identifier
    char title[100];           // Song title
    char artist[100];          // Artist name  
    char album[100];           // Album name
    int duration;              // Duration in seconds
    struct Song* next;         // Pointer to next song
    struct Song* prev;         // Pointer to previous song
};
```

### Player Management
```c
struct MusicPlayer {
    struct Song* head;         // First song in playlist
    struct Song* tail;         // Last song in playlist
    struct Song* current;      // Currently playing song
    int totalSongs;           // Total number of songs
    int isPlaying;            // Playing status flag
    int currentPosition;      // Current position in song
};
```

## ⚡ Algorithm Complexity

| Operation | Time Complexity | Space Complexity | Description |
|-----------|----------------|------------------|-------------|
| Add Song (End) | O(1) | O(1) | Using tail pointer |
| Add Song (Position) | O(n) | O(1) | Linear traversal required |
| Delete Song | O(n) | O(1) | Search + constant deletion |
| Play Next/Previous | O(1) | O(1) | Direct pointer access |
| Search Song | O(n) | O(1) | Linear search |
| Shuffle Playlist | O(n) | O(n) | Fisher-Yates algorithm |
| Reverse Playlist | O(n) | O(1) | In-place pointer reversal |
| Display Playlist | O(n) | O(1) | Complete traversal |

## 🔍 Key Algorithms Implemented

1. **Fisher-Yates Shuffle** - Unbiased randomization of playlist
2. **Linear Search** - Song lookup by title/artist
3. **Doubly Linked List Operations** - Insertion, deletion, traversal
4. **In-place Reversal** - Memory-efficient playlist reversal
5. **Dynamic Memory Management** - Efficient allocation/deallocation

## 📁 Project Structure

```
music-player-dsa/
├── main.c              # Main source code
├── README.md           # Project documentation
├── test_cases.txt      # test case
```

## 🧪 Testing

The program includes comprehensive error handling for:
- Empty playlist operations
- Invalid user inputs
- Memory allocation failures
- Boundary conditions (first/last song operations)
- Non-existent song searches

### Test Cases Covered
- ✅ Basic CRUD operations
- ✅ Navigation edge cases
- ✅ Memory management validation
- ✅ Invalid input handling
- ✅ Large playlist performance

## 🚀 Future Enhancements

- [ ] **File I/O** - Save/load playlists from files
- [ ] **Multiple Playlists** - Support for different playlists
- [ ] **Audio Integration** - Actual audio playback using SDL/FMOD
- [ ] **GUI Interface** - Graphical user interface
- [ ] **Network Features** - Shared playlists
- [ ] **Advanced Search** - Fuzzy search and filters
- [ ] **Statistics** - Play counts and analytics

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. **Fork the repository**
2. **Create a feature branch** (`git checkout -b feature/AmazingFeature`)
3. **Commit your changes** (`git commit -m 'Add some AmazingFeature'`)
4. **Push to the branch** (`git push origin feature/AmazingFeature`)
5. **Open a Pull Request**

### Development Guidelines
- Follow existing code style and conventions
- Add comments for complex logic
- Test thoroughly before submitting
- Update documentation for new features

## 📚 Learning Objectives

This project demonstrates mastery of:
- ✅ **Data Structures** - Doubly linked lists implementation
- ✅ **Algorithms** - Search, shuffle, and sorting algorithms
- ✅ **Memory Management** - Dynamic allocation and deallocation
- ✅ **Software Design** - Modular programming and clean code
- ✅ **Problem Solving** - Real-world application development
- ✅ **C Programming** - Advanced C concepts and best practices

## 👤 Author

**Pranav Harlalka**
- GitHub: [@PranavHarlalka](https://github.com/PranavHarlalka)
- LinkedIn: [Pranav Harlalka](https://www.linkedin.com/in/pranav-harlalka-799a9b30b)
- Email: pranavharlalka2@gmail.com

## 🙏 Acknowledgments

- Classic rock songs used as sample data
- Data Structures and Algorithms community
- Open source C programming resources
- Fisher-Yates shuffle algorithm reference

## ⭐ Show Your Support

Give a ⭐️ if this project helped you learn about data structures!

---

**Made with ❤️ and C programming**
