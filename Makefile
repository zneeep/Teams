##
## EPITECH PROJECT, 2023
## B-NWP-400-LYN-4-1-myteams-lucas.siraux
## File description:
## Makefile
##

OUTPUT_SERVER = myteams_server
OUTPUT_CLIENT = myteams_cli

BUILD_DIR = build

CC = gcc -g
CFLAGS += -Wall -Wextra -I./libs/myteams -I./include
LDFLAGS += -L./libs -lmyteams -luuid

OBJ_SERVER = $(SRC_SERVER_MAIN:%.c=$(BUILD_DIR)/%.o)

SRC_COMMON = src/mylib/concat_biggest_to_smallest.c \
			 src/mylib/remove_newlines.c \
			 src/mylib/str_to_wrd_arr.c \
			 src/mylib/free_data.c

SRC_SERVER =	    src/common/ip_port_validation.c \
					src/server/connections/client_connections.c \
                    src/server/connections/close_connections.c \
                    src/server/connections/create_server_socket.c \
                    src/server/database/add_row_to_table.c \
                    src/server/database/common_functions.c \
                    src/server/database/create_table_struct.c \
                    src/server/database/get_rows_from_key.c \
                    src/server/features/fea_functions/fea_create.c \
                    src/server/features/fea_functions/fea_help.c \
                    src/server/features/fea_functions/fea_load_users.c \
                    src/server/features/fea_functions/fea_login.c \
                    src/server/features/fea_functions/fea_messages.c \
                    src/server/features/fea_functions/fea_send.c \
                    src/server/features/fea_functions/fea_subscribe.c \
                    src/server/features/fea_functions/fea_subscribed.c \
                    src/server/features/fea_functions/fea_use.c \
                    src/server/features/fea_functions/fea_user.c \
                    src/server/features/fea_functions/fea_users.c \
					src/server/features/fea_functions/fea_list.c \
					src/server/features/fea_functions/fea_info.c \
					src/server/features/fea_functions/fea_logout.c \
                    src/server/features/find_feature.c \
					src/server/features/save_string.c \
					src/server/messages/client_messages.c \
					src/server/messages/handle_client_read_messages.c \
					src/server/messages/handle_client_write_message.c \
					src/server/messages/handle_connections.c

SRC_SERVER_MAIN =	src/server/main.c \
					$(SRC_COMMON) \
					$(SRC_SERVER)

OBJ_CLIENT = $(SRC_CLIENT_MAIN:%.c=%.o)
SRC_CLIENT =	src/client/connect.c \
				src/common/ip_port_validation.c \
				src/client/send_messages.c \
				src/client/receive_message.c

SRC_CLIENT_MAIN =	src/client/main.c \
					$(SRC_COMMON) \
					$(SRC_CLIENT)

all: options server client

options:
	@echo "  CC       $(CC)"
	@echo "  CFLAGS   $(CFLAGS)"
	@echo "  LDFLAGS  $(LDFLAGS)"

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "  CC       $<"
	@$(CC) $(CFLAGS) -c $< -o $@

server: $(OBJ_SERVER)
	$(CC) $(OBJ_SERVER) -o $(OUTPUT_SERVER) $(LDFLAGS)

client: $(OBJ_CLIENT)
	$(CC) $(OBJ_CLIENT) -o $(OUTPUT_CLIENT) $(LDFLAGS)

clean:
	rm -rf build

fclean:
	rm -rf $(OUTPUT_SERVER)
	rm -rf $(OUTPUT_CLIENT)
	find . -name "*.o" -type f -delete

re: fclean all