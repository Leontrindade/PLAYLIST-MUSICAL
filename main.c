#include <stdio.h>
#include "playlist.h"

int main() {
    Playlist* minhaPlaylist = criar_playlist();

    adicionar_musica(minhaPlaylist, "Feel Special", "Twice", 210);
    adicionar_musica(minhaPlaylist, "Last Waltz", "Twice", 180);
    adicionar_musica(minhaPlaylist, "Kiss My Troubles Away", "Twice", 200);
    adicionar_musica(minhaPlaylist, "Nxde", "(G)I-DLE", 190);

    printf("\n--- Lista de Músicas ---\n");
    listar_musicas(minhaPlaylist);
    printf("\n");

    printf("--- Música Atual ---\n");
    exibir_musica_atual(minhaPlaylist);
    printf("\n");

    printf("--- Passando para a próxima música ---\n");
    proxima_musica(minhaPlaylist);
    exibir_musica_atual(minhaPlaylist);
    printf("\n");

    printf("--- Voltando para a música anterior ---\n");
    musica_anterior(minhaPlaylist);
    exibir_musica_atual(minhaPlaylist);
    printf("\n");

    printf("--- Buscando 'Nxde' ---\n");
    Musica* m = buscar_musica(minhaPlaylist, "Nxde");
    if (m != NULL) {
        printf("Encontrada: %s - %s\n", m->titulo, m->artista);
    } else {
        printf("Música não encontrada.\n");
    }
    printf("\n");

    printf("--- Removendo 'Last Waltz' ---\n");
    remover_musica(minhaPlaylist, "Last Waltz");
    listar_musicas(minhaPlaylist);
    printf("\n");

    liberar_playlist(minhaPlaylist);

    return 0;
}
