#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

// Inicializar a playlist
Playlist* criar_playlist() {
    Playlist* playlist = (Playlist*) malloc(sizeof(Playlist));
    playlist->atual = NULL;
    playlist->tamanho = 0;
    playlist->modo_repeticao = 0;
    return playlist;
}

// Liberar memória da playlist
void liberar_playlist(Playlist* playlist) {
    if (playlist->atual == NULL) {
        free(playlist);
        return;
    }

    Musica* temp = playlist->atual;
    Musica* inicio = temp;
    do {
        Musica* proxima = temp->proxima;
        free(temp);
        temp = proxima;
    } while (temp != inicio);

    free(playlist);
}

// Adicionar música
void adicionar_musica(Playlist* playlist, const char* titulo, const char* artista, int duracao) {
    Musica* nova = (Musica*) malloc(sizeof(Musica));
    strcpy(nova->titulo, titulo);
    strcpy(nova->artista, artista);
    nova->duracao = duracao;

    if (playlist->atual == NULL) {
        nova->proxima = nova;
        playlist->atual = nova;
    } else {
        Musica* temp = playlist->atual;
        while (temp->proxima != playlist->atual) {
            temp = temp->proxima;
        }
        temp->proxima = nova;
        nova->proxima = playlist->atual;
    }
    playlist->tamanho++;
}

// Remover música
int remover_musica(Playlist* playlist, const char* titulo) {
    if (playlist->atual == NULL) return 0;

    Musica* atual = playlist->atual;
    Musica* anterior = NULL;

    do {
        if (strcmp(atual->titulo, titulo) == 0) {
            if (anterior != NULL) {
                anterior->proxima = atual->proxima;
            } else {
                // Caso seja o único elemento
                Musica* temp = atual;
                while (temp->proxima != atual) {
                    temp = temp->proxima;
                }
                temp->proxima = atual->proxima;
                playlist->atual = atual->proxima;
            }

            if (atual == playlist->atual && atual->proxima == playlist->atual) {
                playlist->atual = NULL;
            }

            free(atual);
            playlist->tamanho--;
            return 1;
        }
        anterior = atual;
        atual = atual->proxima;
    } while (atual != playlist->atual);

    return 0; // Não encontrou
}

// Próxima música
void proxima_musica(Playlist* playlist) {
    if (playlist->atual != NULL) {
        playlist->atual = playlist->atual->proxima;
    }
}

// Música anterior
void musica_anterior(Playlist* playlist) {
    if (playlist->atual == NULL) return;

    Musica* temp = playlist->atual;
    while (temp->proxima != playlist->atual) {
        temp = temp->proxima;
    }
    playlist->atual = temp;
}

// Alternar modo repetição
void alternar_modo_repeticao(Playlist* playlist) {
    if (playlist->modo_repeticao == 0)
        playlist->modo_repeticao = 1;
    else
        playlist->modo_repeticao = 0;
}

// Listar músicas
void listar_musicas(Playlist* playlist) {
    if (playlist->atual == NULL) {
        printf("Playlist vazia!\n");
        return;
    }

    Musica* temp = playlist->atual;
    do {
        printf("Título: %s | Artista: %s | Duração: %d segundos\n", temp->titulo, temp->artista, temp->duracao);
        temp = temp->proxima;
    } while (temp != playlist->atual);
}

// Buscar música
Musica* buscar_musica(Playlist* playlist, const char* titulo) {
    if (playlist->atual == NULL) return NULL;

    Musica* temp = playlist->atual;
    do {
        if (strcmp(temp->titulo, titulo) == 0) {
            return temp;
        }
        temp = temp->proxima;
    } while (temp != playlist->atual);

    return NULL;
}

// Exibir música atual
void exibir_musica_atual(Playlist* playlist) {
    if (playlist->atual == NULL) {
        printf("Nenhuma música tocando.\n");
    } else {
        printf("Tocando agora: %s - %s\n", playlist->atual->titulo, playlist->atual->artista);
    }
}
