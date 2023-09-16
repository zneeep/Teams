/*
** EPITECH PROJECT, 2023
** ip_port_validation.c
** File description:
** Created by Arthur MAQUET
** First edition:
** 13:35:18 08/04/2023
*/

#include <regex.h>
#include <stdio.h>

#include "../../include/common/ip_port_validation.h"

static bool execute_regex(const char *str, const char *pattern) {
  regex_t regex;
  int ret;

  // Compile regular expression
  ret = regcomp(&regex, pattern, REG_EXTENDED);
  if (ret) {
    fprintf(stderr, "Could not compile regex\n");
    regfree(&regex);
    return false;
  }

  // Execute regular expression
  ret = regexec(&regex, str, 0, NULL, 0);
  regfree(&regex);

  return (ret == 0);
}

bool is_valid_ipv4_address(const char *ip_address) {
  // Regular expression pattern to match a valid IPv4 address
  const char *pattern = "^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"
                        "(\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)){3}$";

  return execute_regex(ip_address, pattern);
}

bool is_valid_port(const char *port) {
  // Regular expression pattern to match a valid port number
  const char *pattern = "^((6553[0-5])|(655[0-2][0-9])|(65[0-4][0-9]{2})|"
                        "(6[0-4][0-9]{3})|([1-5][0-9]{4})|([0-5]{0,5})|"
                        "([0-9]{1,4}))$";

  return execute_regex(port, pattern);
}
