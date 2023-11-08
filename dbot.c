#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <concord/discord.h>
#include <concord/log.h>
#include "utils.h"
#include "actions.h"

#define DBOT_CONFIG_FILE "/etc/dbot/config.json"

void print_usage() {
    int terminal_width = get_terminal_width();
    static const char* header = "DBOT: A Discord bot written in C";
    static const char* status[] = {
        "Version: 0.0.1",
        "Tracks instances of key phrases said by specific users",
        "Author: github.com/etsea",
        NULL
    };

    clear_terminal();

    print_newlines(1);
    printf("%s\n", header);
    draw_line(terminal_width, '=');

    print_newlines(1);
    print_unordered_list(status);
    print_newlines(1);
    draw_line(terminal_width, '=');

    print_newlines(2);
}

int main(int argc, char* argv[]) {
    srand(time(NULL));

    const char *config_file = DBOT_CONFIG_FILE;
    
    ccord_global_init();
    struct discord *client = discord_config_init(config_file);
    assert(NULL != client && "Could not initialize discord client");

    discord_add_intents(client, DISCORD_GATEWAY_MESSAGE_CONTENT);

    discord_set_on_ready(client, &on_ready);
    discord_set_on_message_create(client, &on_message_create);

    print_usage();

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
