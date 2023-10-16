class Node:
    def __init__(self, artist, song):
        self.artist = artist
        self.song = song
        self.next = None
        self.prev = None

class CircularDoublyLinkedList:
    def __init__(self):
        self.head = None
        self.current = None

    def insert(self, artist, song):
        new_node = Node(artist, song)
        if not self.head:
            self.head = new_node
            new_node.next = self.head
            new_node.prev = self.head
            self.current = self.head
        else:
            new_node.next = self.head
            new_node.prev = self.head.prev
            self.head.prev.next = new_node
            self.head.prev = new_node

    def display(self):
        if not self.head:
            print("A playlist está vazia.")
            return
        current = self.head
        while True:
            print(f"Artista: {current.artist}, Música: {current.song}")
            current = current.next
            if current == self.head:
                break

    def sort_playlist(self):
        if not self.head:
            print("A playlist está vazia.")
            return
        sorted_list = []
        current = self.head
        while True:
            sorted_list.append((current.artist, current.song))
            current = current.next
            if current == self.head:
                break
        sorted_list.sort(key=lambda x: x[1])
        sorted_playlist = CircularDoublyLinkedList()
        for artist, song in sorted_list:
            sorted_playlist.insert(artist, song)
        return sorted_playlist

    def remove(self, artist, song):
        if not self.head:
            print("A playlist está vazia.")
            return
        current = self.head
        while True:
            if current.artist == artist and current.song == song:
                if current == self.head:
                    if current.next == self.head:
                        self.head = None
                    else:
                        self.head = current.next
                        self.head.prev = current.prev
                        current.prev.next = self.head
                else:
                    current.prev.next = current.next
                    current.next.prev = current.prev
                return
            current = current.next
            if current == self.head:
                break
        print("Música não encontrada na playlist.")

    def search(self, artist, song):
        if not self.head:
            print("A playlist está vazia.")
            return
        current = self.head
        while True:
            if current.artist == artist and current.song == song:
                print(f"Artista: {current.artist}, Música: {current.song}")
                return
            current = current.next
            if current == self.head:
                break
        print("Música não encontrada na playlist.")

    def next_song(self):
        if not self.head:
            print("A playlist está vazia.")
            return
        self.current = self.current.next
        print(f"Tocando: Artista: {self.current.artist}, Música: {self.current.song}")

    def previous_song(self):
        if not self.head:
            print("A playlist está vazia.")
            return
        self.current = self.current.prev
        print(f"Tocando: Artista: {self.current.artist}, Música: {self.current.song}")

def read_playlist_from_file(file_name):
    playlist = CircularDoublyLinkedList()
    with open(file_name, 'r') as file:
        for line in file:
            artist, song = line.strip().split(';')
            playlist.insert(artist, song)
    return playlist

def save_playlist_to_file(playlist, file_name):
    with open(file_name, 'w') as file:
        current = playlist.head
        while True:
            file.write(f"{current.artist};{current.song}\n")
            current = current.next
            if current == playlist.head:
                break

if __name__ == "__main__":
    file_name = "musicas.txt"
    playlist = read_playlist_from_file(file_name)

    while True:
        print("\nMenu:")
        print("1. Exibição da playlist pela ordem de cadastro")
        print("2. Exibição da playlist ordenada pelo nome das músicas")
        print("3. Inserção de novas músicas")
        print("4. Remoção de uma música")
        print("5. Busca por uma música")
        print("6. Avançar para próxima música")
        print("7. Retornar a música anterior")
        print("8. Sair")
        choice = input("Escolha uma opção: ")

        if choice == '1':
            playlist.display()
        elif choice == '2':
            sorted_playlist = playlist.sort_playlist()
            sorted_playlist.display()
        elif choice == '3':
            artist = input("Digite o nome do artista: ")
            song = input("Digite o nome da música: ")
            playlist.insert(artist, song)
            save_playlist_to_file(playlist, file_name)
        elif choice == '4':
            artist = input("Digite o nome do artista da música a ser removida: ")
            song = input("Digite o nome da música a ser removida: ")
            playlist.remove(artist, song)
            save_playlist_to_file(playlist, file_name)
        elif choice == '5':
            artist = input("Digite o nome do artista da música a ser buscada: ")
            song = input("Digite o nome da música a ser buscada: ")
            playlist.search(artist, song)
        elif choice == '6':
            playlist.next_song()
        elif choice == '7':
            playlist.previous_song()
        elif choice == '8':
            break
        else:
            print("Escolha uma opção válida.")
