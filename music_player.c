
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure to represent a song
struct Song {
    int id;
    char title[100];
    char artist[100];
    char album[100];
    int duration; // in seconds
    struct Song* next;
    struct Song* prev; // for doubly linked list
};

// Structure for the music player
struct MusicPlayer {
    struct Song* head;
    struct Song* tail;
    struct Song* current;
    int totalSongs;
    int isPlaying;
    int currentPosition; // position in seconds
};

// Function prototypes
struct Song* createSong(int id, const char* title, const char* artist, const char* album, int duration);
void initPlayer(struct MusicPlayer* player);
void addSong(struct MusicPlayer* player, int id, const char* title, const char* artist, const char* album, int duration);
void addSongAtPosition(struct MusicPlayer* player, int position, int id, const char* title, const char* artist, const char* album, int duration);
void deleteSong(struct MusicPlayer* player, int id);
void deleteSongByTitle(struct MusicPlayer* player, const char* title);
void playCurrentSong(struct MusicPlayer* player);
void playNext(struct MusicPlayer* player);
void playPrevious(struct MusicPlayer* player);
struct Song* peekNext(struct MusicPlayer* player);
struct Song* peekPrevious(struct MusicPlayer* player);
void pauseSong(struct MusicPlayer* player);
void stopSong(struct MusicPlayer* player);
void displayPlaylist(struct MusicPlayer* player);
void displayCurrentSong(struct MusicPlayer* player);
void shufflePlaylist(struct MusicPlayer* player);
void reversePlaylist(struct MusicPlayer* player);
struct Song* searchSong(struct MusicPlayer* player, const char* title);
struct Song* searchSongByArtist(struct MusicPlayer* player, const char* artist);
void jumpToSong(struct MusicPlayer* player, int id);
void clearPlaylist(struct MusicPlayer* player);
int getPlaylistLength(struct MusicPlayer* player);
void displayMenu();

// Function to create a new song node
struct Song* createSong(int id, const char* title, const char* artist, const char* album, int duration) {
    struct Song* newSong = (struct Song*)malloc(sizeof(struct Song));
    if (newSong == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    newSong->id = id;
    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    strcpy(newSong->album, album);
    newSong->duration = duration;
    newSong->next = NULL;
    newSong->prev = NULL;

    return newSong;
}

// Initialize the music player
void initPlayer(struct MusicPlayer* player) {
    player->head = NULL;
    player->tail = NULL;
    player->current = NULL;
    player->totalSongs = 0;
    player->isPlaying = 0;
    player->currentPosition = 0;
}

// Add a song to the end of the playlist
void addSong(struct MusicPlayer* player, int id, const char* title, const char* artist, const char* album, int duration) {
    struct Song* newSong = createSong(id, title, artist, album, duration);
    if (newSong == NULL) return;

    if (player->head == NULL) {
        // First song in playlist
        player->head = newSong;
        player->tail = newSong;
        player->current = newSong;
    } else {
        // Add to end
        player->tail->next = newSong;
        newSong->prev = player->tail;
        player->tail = newSong;
    }

    player->totalSongs++;
    printf("Song '%s' by %s added to playlist!\n", title, artist);
}

// Add song at specific position
void addSongAtPosition(struct MusicPlayer* player, int position, int id, const char* title, const char* artist, const char* album, int duration) {
    if (position < 1 || position > player->totalSongs + 1) {
        printf("Invalid position!\n");
        return;
    }

    if (position == player->totalSongs + 1) {
        addSong(player, id, title, artist, album, duration);
        return;
    }

    struct Song* newSong = createSong(id, title, artist, album, duration);
    if (newSong == NULL) return;

    if (position == 1) {
        // Insert at beginning
        newSong->next = player->head;
        player->head->prev = newSong;
        player->head = newSong;
    } else {
        // Insert at middle
        struct Song* temp = player->head;
        for (int i = 1; i < position; i++) {
            temp = temp->next;
        }

        newSong->next = temp;
        newSong->prev = temp->prev;
        temp->prev->next = newSong;
        temp->prev = newSong;
    }

    player->totalSongs++;
    printf("Song '%s' by %s inserted at position %d!\n", title, artist, position);
}

// Delete song by ID
void deleteSong(struct MusicPlayer* player, int id) {
    if (player->head == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    struct Song* temp = player->head;

    // Find the song
    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Song with ID %d not found!\n", id);
        return;
    }

    // Update current pointer if necessary
    if (player->current == temp) {
        if (temp->next != NULL) {
            player->current = temp->next;
        } else if (temp->prev != NULL) {
            player->current = temp->prev;
        } else {
            player->current = NULL;
        }
    }

    // Remove from list
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        player->head = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    } else {
        player->tail = temp->prev;
    }

    printf("Song '%s' deleted from playlist!\n", temp->title);
    free(temp);
    player->totalSongs--;
}

// Delete song by title
void deleteSongByTitle(struct MusicPlayer* player, const char* title) {
    if (player->head == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    struct Song* temp = player->head;

    // Find the song
    while (temp != NULL && strcmp(temp->title, title) != 0) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Song '%s' not found!\n", title);
        return;
    }

    deleteSong(player, temp->id);
}

// Play current song
void playCurrentSong(struct MusicPlayer* player) {
    if (player->current == NULL) {
        printf("No song selected or playlist is empty!\n");
        return;
    }

    player->isPlaying = 1;
    player->currentPosition = 0;
    printf("\nNow Playing: '%s' by %s\n", player->current->title, player->current->artist);
    printf("Album: %s | Duration: %d:%02d\n", 
           player->current->album, 
           player->current->duration / 60, 
           player->current->duration % 60);
}

// Play next song
void playNext(struct MusicPlayer* player) {
    if (player->current == NULL) {
        printf("No current song!\n");
        return;
    }

    if (player->current->next != NULL) {
        player->current = player->current->next;
        playCurrentSong(player);
    } else {
        printf("This is the last song in the playlist!\n");
    }
}

// Play previous song
void playPrevious(struct MusicPlayer* player) {
    if (player->current == NULL) {
        printf("No current song!\n");
        return;
    }

    if (player->current->prev != NULL) {
        player->current = player->current->prev;
        playCurrentSong(player);
    } else {
        printf("This is the first song in the playlist!\n");
    }
}

// Peek at next song without playing
struct Song* peekNext(struct MusicPlayer* player) {
    if (player->current == NULL) {
        printf("No current song!\n");
        return NULL;
    }

    if (player->current->next != NULL) {
        printf("Next song: '%s' by %s\n", 
               player->current->next->title, 
               player->current->next->artist);
        return player->current->next;
    } else {
        printf("No next song available!\n");
        return NULL;
    }
}

// Peek at previous song without playing
struct Song* peekPrevious(struct MusicPlayer* player) {
    if (player->current == NULL) {
        printf("No current song!\n");
        return NULL;
    }

    if (player->current->prev != NULL) {
        printf("Previous song: '%s' by %s\n", 
               player->current->prev->title, 
               player->current->prev->artist);
        return player->current->prev;
    } else {
        printf("No previous song available!\n");
        return NULL;
    }
}

// Pause current song
void pauseSong(struct MusicPlayer* player) {
    if (player->isPlaying) {
        player->isPlaying = 0;
        printf("Song paused!\n");
    } else {
        printf("No song is currently playing!\n");
    }
}

// Stop current song
void stopSong(struct MusicPlayer* player) {
    if (player->isPlaying || player->currentPosition > 0) {
        player->isPlaying = 0;
        player->currentPosition = 0;
        printf("Song stopped!\n");
    } else {
        printf("No song is currently playing!\n");
    }
}

// Display entire playlist
void displayPlaylist(struct MusicPlayer* player) {
    if (player->head == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    printf("\n=== PLAYLIST ===\n");
    printf("Total Songs: %d\n", player->totalSongs);
    printf("%-3s %-25s %-20s %-20s %-8s\n", "ID", "Title", "Artist", "Album", "Duration");
    printf("-------------------------------------------------------------------------\n");

    struct Song* temp = player->head;
    int position = 1;

    while (temp != NULL) {
        char indicator = (temp == player->current) ? '>' : ' ';
        printf("%c%-3d %-25s %-20s %-20s %02d:%02d\n", 
               indicator,
               temp->id, 
               temp->title, 
               temp->artist, 
               temp->album,
               temp->duration / 60, 
               temp->duration % 60);
        temp = temp->next;
        position++;
    }
    printf("\n");
}

// Display current song information
void displayCurrentSong(struct MusicPlayer* player) {
    if (player->current == NULL) {
        printf("No song selected!\n");
        return;
    }

    printf("\n=== CURRENT SONG ===\n");
    printf("Title: %s\n", player->current->title);
    printf("Artist: %s\n", player->current->artist);
    printf("Album: %s\n", player->current->album);
    printf("Duration: %02d:%02d\n", 
           player->current->duration / 60, 
           player->current->duration % 60);
    printf("Status: %s\n", player->isPlaying ? "Playing" : "Stopped/Paused");
    printf("Current Position: %02d:%02d\n", 
           player->currentPosition / 60, 
           player->currentPosition % 60);
}

// Shuffle playlist
void shufflePlaylist(struct MusicPlayer* player) {
    if (player->totalSongs < 2) {
        printf("Need at least 2 songs to shuffle!\n");
        return;
    }

    // Create array of song pointers
    struct Song** songArray = (struct Song**)malloc(player->totalSongs * sizeof(struct Song*));
    struct Song* temp = player->head;

    // Fill array
    for (int i = 0; i < player->totalSongs; i++) {
        songArray[i] = temp;
        temp = temp->next;
    }

    // Shuffle using Fisher-Yates algorithm
    srand(time(NULL));
    for (int i = player->totalSongs - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        struct Song* tempSong = songArray[i];
        songArray[i] = songArray[j];
        songArray[j] = tempSong;
    }

    // Rebuild the linked list
    player->head = songArray[0];
    player->head->prev = NULL;

    for (int i = 0; i < player->totalSongs - 1; i++) {
        songArray[i]->next = songArray[i + 1];
        songArray[i + 1]->prev = songArray[i];
    }

    player->tail = songArray[player->totalSongs - 1];
    player->tail->next = NULL;

    // Set current to first song after shuffle
    player->current = player->head;

    free(songArray);
    printf("Playlist shuffled successfully!\n");
}

// Reverse playlist
void reversePlaylist(struct MusicPlayer* player) {
    if (player->head == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    struct Song* current = player->head;
    struct Song* temp = NULL;

    // Swap next and prev for all nodes
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    // Swap head and tail
    temp = player->head;
    player->head = player->tail;
    player->tail = temp;

    printf("Playlist reversed successfully!\n");
}

// Search song by title
struct Song* searchSong(struct MusicPlayer* player, const char* title) {
    struct Song* temp = player->head;

    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0) {
            printf("Song found: '%s' by %s (ID: %d)\n", 
                   temp->title, temp->artist, temp->id);
            return temp;
        }
        temp = temp->next;
    }

    printf("Song '%s' not found!\n", title);
    return NULL;
}

// Search songs by artist
struct Song* searchSongByArtist(struct MusicPlayer* player, const char* artist) {
    struct Song* temp = player->head;
    struct Song* found = NULL;
    int count = 0;

    printf("Songs by %s:\n", artist);

    while (temp != NULL) {
        if (strcmp(temp->artist, artist) == 0) {
            printf("- '%s' (ID: %d)\n", temp->title, temp->id);
            if (found == NULL) found = temp; // Return first match
            count++;
        }
        temp = temp->next;
    }

    if (count == 0) {
        printf("No songs by '%s' found!\n", artist);
    } else {
        printf("Found %d song(s) by %s\n", count, artist);
    }

    return found;
}

// Jump to specific song by ID
void jumpToSong(struct MusicPlayer* player, int id) {
    struct Song* temp = player->head;

    while (temp != NULL) {
        if (temp->id == id) {
            player->current = temp;
            playCurrentSong(player);
            return;
        }
        temp = temp->next;
    }

    printf("Song with ID %d not found!\n", id);
}

// Clear entire playlist
void clearPlaylist(struct MusicPlayer* player) {
    while (player->head != NULL) {
        struct Song* temp = player->head;
        player->head = player->head->next;
        free(temp);
    }

    player->tail = NULL;
    player->current = NULL;
    player->totalSongs = 0;
    player->isPlaying = 0;
    player->currentPosition = 0;

    printf("Playlist cleared!\n");
}

// Get playlist length
int getPlaylistLength(struct MusicPlayer* player) {
    return player->totalSongs;
}

// Display menu
void displayMenu() {
    printf("\n=== MUSIC PLAYER MENU ===\n");
    printf("1.  Add song to playlist\n");
    printf("2.  Add song at specific position\n");
    printf("3.  Delete song by ID\n");
    printf("4.  Delete song by title\n");
    printf("5.  Play current song\n");
    printf("6.  Play next song\n");
    printf("7.  Play previous song\n");
    printf("8.  Peek next song\n");
    printf("9.  Peek previous song\n");
    printf("10. Pause song\n");
    printf("11. Stop song\n");
    printf("12. Display playlist\n");
    printf("13. Display current song\n");
    printf("14. Search song by title\n");
    printf("15. Search songs by artist\n");
    printf("16. Jump to song by ID\n");
    printf("17. Shuffle playlist\n");
    printf("18. Reverse playlist\n");
    printf("19. Clear playlist\n");
    printf("20. Get playlist length\n");
    printf("0.  Exit\n");
    printf("Enter your choice: ");
}

// Main function
int main() {
    struct MusicPlayer player;
    initPlayer(&player);

    int choice;
    int id, position, duration;
    char title[100], artist[100], album[100];

    printf("Welcome to the Music Player!\n");

    // Add some sample songs
    addSong(&player, 1, "Bohemian Rhapsody", "Queen", "A Night at the Opera", 355);
    addSong(&player, 2, "Hotel California", "Eagles", "Hotel California", 391);
    addSong(&player, 3, "Sweet Child O' Mine", "Guns N' Roses", "Appetite for Destruction", 356);
    addSong(&player, 4, "Stairway to Heaven", "Led Zeppelin", "Led Zeppelin IV", 482);
    addSong(&player, 5, "Imagine", "John Lennon", "Imagine", 183);

    do {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("Enter song details:\n");
                printf("ID: ");
                scanf("%d", &id);
                getchar();
                printf("Title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0; // remove newline
                printf("Artist: ");
                fgets(artist, sizeof(artist), stdin);
                artist[strcspn(artist, "\n")] = 0;
                printf("Album: ");
                fgets(album, sizeof(album), stdin);
                album[strcspn(album, "\n")] = 0;
                printf("Duration (seconds): ");
                scanf("%d", &duration);
                addSong(&player, id, title, artist, album, duration);
                break;

            case 2:
                printf("Enter position: ");
                scanf("%d", &position);
                printf("Enter song details:\n");
                printf("ID: ");
                scanf("%d", &id);
                getchar();
                printf("Title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;
                printf("Artist: ");
                fgets(artist, sizeof(artist), stdin);
                artist[strcspn(artist, "\n")] = 0;
                printf("Album: ");
                fgets(album, sizeof(album), stdin);
                album[strcspn(album, "\n")] = 0;
                printf("Duration (seconds): ");
                scanf("%d", &duration);
                addSongAtPosition(&player, position, id, title, artist, album, duration);
                break;

            case 3:
                printf("Enter song ID to delete: ");
                scanf("%d", &id);
                deleteSong(&player, id);
                break;

            case 4:
                printf("Enter song title to delete: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;
                deleteSongByTitle(&player, title);
                break;

            case 5:
                playCurrentSong(&player);
                break;

            case 6:
                playNext(&player);
                break;

            case 7:
                playPrevious(&player);
                break;

            case 8:
                peekNext(&player);
                break;

            case 9:
                peekPrevious(&player);
                break;

            case 10:
                pauseSong(&player);
                break;

            case 11:
                stopSong(&player);
                break;

            case 12:
                displayPlaylist(&player);
                break;

            case 13:
                displayCurrentSong(&player);
                break;

            case 14:
                printf("Enter song title to search: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;
                searchSong(&player, title);
                break;

            case 15:
                printf("Enter artist name to search: ");
                fgets(artist, sizeof(artist), stdin);
                artist[strcspn(artist, "\n")] = 0;
                searchSongByArtist(&player, artist);
                break;

            case 16:
                printf("Enter song ID to jump to: ");
                scanf("%d", &id);
                jumpToSong(&player, id);
                break;

            case 17:
                shufflePlaylist(&player);
                break;

            case 18:
                reversePlaylist(&player);
                break;

            case 19:
                clearPlaylist(&player);
                break;

            case 20:
                printf("Total songs in playlist: %d\n", getPlaylistLength(&player));
                break;

            case 0:
                printf("Thank you for using the Music Player!\n");
                clearPlaylist(&player);
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }

        if (choice != 0) {
            printf("\nPress Enter to continue...");
            getchar();
        }

    } while (choice != 0);

    return 0;
}
