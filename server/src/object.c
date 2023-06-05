/*
** EPITECH PROJECT, 2023
** object.c
** File description:
** object
*/

#include "../include/server.h"

int check_if_player_has_item(client_t *client, char *to_find)
{
    if (strcmp(to_find, "food") == 0) {
        if (client->player->inv->food > 0)
            return 1;
        else
            return 0;
    }
    if (strcmp(to_find, "linemate") == 0) {
        if (client->player->inv->linemate > 0)
            return 1;
        else
            return 0;
    }
    if (strcmp(to_find, "deraumere") == 0) {
        if (client->player->inv->deraumere > 0)
            return 1;
        else
            return 0;
    }
    if (strcmp(to_find, "sibur") == 0) {
        if (client->player->inv->sibur > 0)
            return 1;
        else
            return 0;
    }
    if (strcmp(to_find, "mendiane") == 0) {
        if (client->player->inv->mendiane > 0)
            return 1;
        else
            return 0;
    }
    if (strcmp(to_find, "phiras") == 0) {
        if (client->player->inv->phiras > 0)
            return 1;
        else
            return 0;
    }
    if (strcmp(to_find, "thystame") == 0) {
        if (client->player->inv->thystame > 0)
            return 1;
        else
            return 0;
    }
    return 0;
}

int set_object(server_t *server, client_t *client, char *buffer)
{
    buffer += 4;
    if (check_if_is_resources(buffer) == 0)
        return 0;
    if (check_if_player_has_item(client, buffer) == 0)
        return 0;
    if (strcmp(buffer, "food") == 0) {
        client->player->inv->food--;
        server->game->map[client->player->x][client->player->y].food++;
    }
    if (strcmp(buffer, "linemate") == 0) {
        client->player->inv->linemate--;
        server->game->map[client->player->x][client->player->y].linemate++;
    }
    if (strcmp(buffer, "deraumere") == 0) {
        client->player->inv->deraumere--;
        server->game->map[client->player->x][client->player->y].deraumere++;
    }
    if (strcmp(buffer, "sibur") == 0) {
        client->player->inv->sibur--;
        server->game->map[client->player->x][client->player->y].sibur++;
    }
    if (strcmp(buffer, "mendiane") == 0) {
        client->player->inv->mendiane--;
        server->game->map[client->player->x][client->player->y].mendiane++;
    }
    if (strcmp(buffer, "phiras") == 0) {
        client->player->inv->phiras--;
        server->game->map[client->player->x][client->player->y].phiras++;
    }
    if (strcmp(buffer, "thystame") == 0) {
        client->player->inv->thystame--;
        server->game->map[client->player->x][client->player->y].thystame++;
    }
    return 1;
}