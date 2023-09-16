/*
** EPITECH PROJECT, 2023
** teams
** File description:
** receive_message
*/

#include "../../libs/logging_client.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>

void interpret_login(char **command)
{
    client_event_logged_in(command[1], command[2]);
}

void interpret_logout(char **command)
{
    if (strcmp(command[1], "client") == 0)
        client_event_logged_out(command[2], command[3]);
    if (strcmp(command[1], "unauthorized") == 0)
        client_error_unauthorized();
}

void interpret_send(char **command)
{
    if (strcmp(command[1], "unknown_user") == 0)
        client_error_unknown_user(command[2]);
    if (strcmp(command[1], "unauthorized") == 0)
        client_error_unauthorized();
    if (strcmp(command[1], "authorized") == 0)
        client_event_private_message_received(command[2], command[3]);
}

void interpret_create(char **command)
{
    // if (strcmp(command[1], "event_thread_reply_received") == 0)
    //     client_event_thread_reply_received(command[1], command[2], command[3], command[4]);
    if (strcmp(command[1], "event_team_created") == 0)
        client_event_team_created(command[2], command[3], command[4]);
    if (strcmp(command[1], "event_channel_created") == 0)
        client_event_channel_created(command[2], command[3], command[4]);
    // if (strcmp(command[1], "event_thread_created") == 0)
    //     client_event_thread_created(command[1], command[2], command[3], command[4], command[5]);
    if (strcmp(command[1], "unknown_team") == 0)
        client_error_unknown_team(command[2]);
    if (strcmp(command[1], "unknown_channel") == 0)
        client_error_unknown_channel(command[2]);
    if (strcmp(command[1], "unknown_thread") == 0)
        client_error_unknown_thread(command[2]);
    if (strcmp(command[1], "already_exist") == 0)
        client_error_already_exist();
    if (strcmp(command[1], "unauthorized") == 0)
        client_error_unauthorized();
    if (strcmp(command[1], "team_created") == 0)
        client_print_team_created(command[1], command[2], command[3]);
    if (strcmp(command[1], "channel_created") == 0)
        client_print_channel_created(command[1], command[2], command[3]);
    // if (strcmp(command[1], "thread_created") == 0)
    //     client_print_thread_created(command[1], command[2], command[3], command[4], command[5]);
    // if (strcmp(command[1], "reply_created") == 0)
    //     client_print_reply_created(command[1], command[2], command[3], command[4]);
}

void interpret_users(char **command)
{
    
}

void interpret_list(char **command)
{
    if (strcmp(command[1], "teams") == 0)
        client_print_teams(command[2], command[3], command[4]);
    if (strcmp(command[1], "channels") == 0)
        client_print_channel(command[2], command[3], command[4]);
    // if (strcmp(command[1], "threads") == 0)
    //     client_channel_print_threads(command[1], command[2], command[3], command[4], command[5]);
    // if (strcmp(command[1], "replies") == 0)
    //     client_thread_print_replies(command[1], command[2], command[3], command[4]);
    if (strcmp(command[1], "unknown_team") == 0)
        client_error_unknown_team(command[2]);
    if (strcmp(command[1], "unknown_channel") == 0)
        client_error_unknown_channel(command[2]);
    if (strcmp(command[1], "unknown_thread") == 0)
        client_error_unknown_thread(command[2]);
    if (strcmp(command[1], "unauthorized") == 0)
        client_error_unauthorized();
}

void interpret_subscribed(char **command)
{
    if (strcmp(command[1], "unauthorized") == 0)
        client_error_unauthorized();
    if (strcmp(command[1], "unknown_team") == 0)
        client_error_unknown_team(command[2]);
    if (strcmp(command[1], "team") == 0)
        client_print_teams(command[2], command[3], command[4]);
    if (strcmp(command[1], "user") == 0)
        client_print_users(command[2], command[3], atoi(command[4]));
}

void interpret_messages(char **command)
{
    if (strcmp(command[1], "unauthorized") == 0)
        client_error_unauthorized();
    if (strcmp(command[1], "message") == 0)
        client_private_message_print_messages(command[2], command[3], command[4]);
    if (strcmp(command[1], "unknown_user") == 0)
         client_error_unknown_user(command[2]);
}

void interpret_subscribe(char **command)
{
    if (strcmp(command[1], "successful") == 0)
        client_print_subscribed(command[2], command[3]);
    if (strcmp(command[1], "unauthorized") == 0)
        client_error_unauthorized();
    if (strcmp(command[1], "unknown_team") == 0)
        client_error_unknown_team(command[2]);
}

void interpret_unsubscribe(char **command)
{
    
}

void interpret_info(char **command)
{
    
}

void interpret_user(char **command)
{
    
}

void interpret_command(char **command)
{
    if (strcmp(command[0], "/login") == 0)
        interpret_login(command);
    if (strcmp(command[0], "/logout") == 0)
        interpret_logout(command);
    if (strcmp(command[0], "/send") == 0)
        interpret_send(command);
    if (strcmp(command[0], "/create") == 0)
        interpret_create(command);
    if (strcmp(command[0], "/list") == 0)
        interpret_list(command);
    if (strcmp(command[0], "/messages") == 0)
        interpret_messages(command);
    if (strcmp(command[0], "/subscribe") == 0)
        interpret_subscribe(command);
    if (strcmp(command[0], "/subscribed") == 0)
        interpret_subscribed(command);
    // if (strcmp(command[0], "/users") == 0)
    // if (strcmp(command[0], "/unsubscribe") == 0)
    // if (strcmp(command[0], "/info") == 0)
    // if (strcmp(command[0], "/user") == 0)
}