#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition des constantes
#define CMD_SIZE 1024
#define TOKEN_SIZE 128

// Déclaration des fonctions externes (elles doivent être définies ailleurs)
void engine_stop();
void engine_set_ponderhit(int value);
void engine_send_info();
void engine_get_options();
void engine_go(char *params);
void engine_set_position(char *params);
void engine_search_clear();
void engine_flip();
void engine_bench(char *params);
void engine_benchmark(char *params);
void engine_visualize();
void engine_trace_eval();
void engine_compiler_info();
void engine_save_network(char *file1, char *file2);

// Fonction principale de la boucle UCI
void uci_loop() {
    char cmd[CMD_SIZE];
    char token[TOKEN_SIZE];

    // Boucle principale
    while (1) {
        // Lire une ligne de commande
        if (!fgets(cmd, CMD_SIZE, stdin)) {
            strcpy(cmd, "quit");  // Quitter si erreur ou EOF
        }

        // Extraire le premier mot (commande)
        if (sscanf(cmd, "%s", token) != 1) {
            continue; // Ignore une ligne vide
        }

        // Gestion des commandes UCI
        if (strcmp(token, "quit") == 0 || strcmp(token, "stop") == 0) {
            engine_stop();
            break;
        } 
        else if (strcmp(token, "ponderhit") == 0) {
            engine_set_ponderhit(0);
        }
        else if (strcmp(token, "uci") == 0) {
            printf("id name MyEngine 1.0\n");
            engine_get_options();
            printf("uciok\n");
        } 
        else if (strcmp(token, "setoption") == 0) {
            // Appeler une fonction externe qui gère les options
            engine_send_info();
        } 
        else if (strcmp(token, "go") == 0) {
            engine_go(cmd + 3);  // Passer le reste de la ligne comme paramètre
        } 
        else if (strcmp(token, "position") == 0) {
            engine_set_position(cmd + 9);
        } 
        else if (strcmp(token, "ucinewgame") == 0) {
            engine_search_clear();
        } 
        else if (strcmp(token, "isready") == 0) {
            printf("readyok\n");
        } 
        else if (strcmp(token, "flip") == 0) {
            engine_flip();
        } 
        else if (strcmp(token, "bench") == 0) {
            engine_bench(cmd + 6);
        } 
        else if (strcmp(token, "d") == 0) {
            engine_visualize();
        } 
        else if (strcmp(token, "eval") == 0) {
            engine_trace_eval();
        } 
        else if (strcmp(token, "compiler") == 0) {
            engine_compiler_info();
        } 
        else if (strcmp(token, "export_net") == 0) {
            char file1[TOKEN_SIZE] = "", file2[TOKEN_SIZE] = "";
            sscanf(cmd, "%*s %s %s", file1, file2);
            engine_save_network(file1, file2);
        } 
        else if (strcmp(token, "help") == 0 || strcmp(token, "license") == 0) {
            printf("MyEngine is a chess engine following the UCI protocol.\n");
            printf("Released under GPLv3.\n");
        } 
        else {
            printf("Unknown command: '%s'. Type help for more information.\n", cmd);
        }
    }
}
