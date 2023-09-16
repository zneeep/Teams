/*
** EPITECH PROJECT, 2023
** ip_port_validation.h
** File description:
** Created by Arthur MAQUET
** First edition:
** 13:35:18 08/04/2023
*/

#ifndef B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_SRC_COMMON_IP_PORT_VALIDATION_H_
#define B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_SRC_COMMON_IP_PORT_VALIDATION_H_

#include <stdbool.h>

bool is_valid_ipv4_address(const char *ip_address);
bool is_valid_port(const char *port);

#endif //B_NWP_400_LYN_4_1_MYTEAMS_LUCAS_SIRAUX_SRC_COMMON_IP_PORT_VALIDATION_H_
