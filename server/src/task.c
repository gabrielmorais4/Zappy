/*
** EPITECH PROJECT, 2023
** task.c
** File description:
** task
*/

#include "../include/server.h"

void add_task(server_t *server, char *cmd, double time, client_t *cli)
{
    if (check_task_nb(server, cli) == false) return;
    if (strcmp(cmd, "Incantation") == 0) {
        if (check_can_incantation(server, cli) == 0) {
            send(cli->socket, "ko\n", 3, 0); cli->player->state = INCANTATION;
            return;
        }
        send(cli->socket, "Elevation underway\n", 19, 0);
    }
    task_t *new_task = malloc(sizeof(task_t));
    new_task->cmd = strdup(cmd); new_task->time = time; new_task->client = cli;
    new_task->id = server->task_id; server->task_id++;
    new_task->next.le_next = NULL;
    if (LIST_EMPTY(&server->task_head)) {
        LIST_INSERT_HEAD(&server->task_head, new_task, next); return;
    }
    task_t *tmp;
    LIST_FOREACH(tmp, &server->task_head, next) {
        if (tmp->next.le_next == NULL) {
            LIST_INSERT_AFTER(tmp, new_task, next); break;
        }
    }
}

bool check_task_nb(server_t *server, client_t *client)
{
    int counter = 0;
    task_t *tmp;
    LIST_FOREACH(tmp, &server->task_head, next) {
        if (tmp->client->socket == client->socket) {
            counter++;
        }
    }
    if (counter < 10) {
        return true;
    }
    return false;
}

double calculate_time_for_task(server_t *server, char *buffer)
{
    struct timespec ts;
    clock_gettime(0, &ts);
    time_t diff = ts.tv_sec - server->server_time.tv_sec;
    if (strcmp(buffer, "Forward") == 0) return diff + (7.0 / server->freq);
    else if (strcmp(buffer, "Right") == 0) return diff + (7.0 / server->freq);
    else if (strcmp(buffer, "Left") == 0) return diff + (7.0 / server->freq);
    else if (strcmp(buffer, "Look") == 0) return diff + (7.0 / server->freq);
    else if (strcmp(buffer, "Inventory") == 0)
        return diff + (1.0 / server->freq);
    else if (strstr(buffer, "Broadcast")) return diff + (7.0 / server->freq);
    else if (strcmp(buffer, "Fork") == 0) return diff + (42.0 / server->freq);
    else if (strcmp(buffer, "Eject") == 0) return diff + (7.0 / server->freq);
    else if (strstr(buffer, "Take")) return diff + (7.0 / server->freq);
    else if (strstr(buffer, "Set")) return diff + (7.0 / server->freq);
    else if (strcmp(buffer, "Incantation") == 0)
        return diff + (300.0 / server->freq);
    else return 0.0;
}

void execute_tasks(server_t *server)
{
    struct timespec ts;
    task_t *tmp;
    clock_gettime(0, &ts);
    LIST_FOREACH(tmp, &server->task_head, next) {
        double value = (double)((ts.tv_sec - server->server_time.tv_sec));
        if (value >= tmp->time) {
            printf("command when removing : %s\n", tmp->cmd);
            send_task_response(server, tmp, tmp->cmd);
            LIST_REMOVE(tmp, next);
        }
    }
    return;
}