#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <concord/discord.h>
#include <concord/log.h>
#include "utils.h"
#include "dbase.h"
#include "defs.h"

#define SQLITE_DB "/etc/dbot/dbot_counts.db"

UserInfo* find_user_info_by_name(char *name) {
    for (size_t i = 0; i < SIZE_USER_DB; ++i) {
        if (strcmp(user_db[i].name, name) == 0) {
            return &user_db[i];
        }
    }
    return NULL; // name was not found
}

UserInfo* find_user_info_by_id(u64snowflake id) {
    for (size_t i = 0; i < SIZE_USER_DB; ++i) {
        if (user_db[i].id == id) {
            return &user_db[i];
        }
    }
    return NULL; // id was not found
}

u64snowflake find_user_id_by_name(char *name) {
    for (size_t i = 0; i < SIZE_USER_DB; ++i) {
        if (strcmp(user_db[i].name, name) == 0) {
            return user_db[i].id;
        }
    }
    return 0; // name was not found
}

int is_user_id_in_array(u64snowflake id) {
    for (size_t i = 0; i < SIZE_USER_DB; ++i) {
        if (user_db[i].id == id) {
            return 1;
        }
    }
    return 0;
}

char *get_emoji(const char *name) {
    for (int i = 0; i < SIZE_EMOJIS; i++) {
        if (strcmp(emojis[i].name, name) == 0) {
            return emojis[i].unicode;
        }
    }
    return NULL;
}

char *get_random_emoji() {
    int random = rand() % SIZE_EMOJIS;
    return emojis[random].unicode;
}


void on_ready(struct discord *client, const struct discord_ready *event) {
    const char *ready_string = "DBOT successfully connected to Discord as %s#%s!";
    log_info(ready_string, event->user->username, event->user->discriminator);
}

void send_announcement(struct discord *client, const struct discord_message *event, int count, char *name, char *word) {
    count++;

    char announce[256];

    char *base_msg = get_random_message_template();
    snprintf(announce, 256, base_msg, name, word, count);

    struct discord_create_message params = {
        .content = announce,
    };

    discord_create_message(client, event->channel_id, &params, NULL);
}

void on_word_trigger(struct discord *client, const struct discord_message *event, char *name, char *word) {
    int count = check_count(SQLITE_DB, name);
    send_announcement(client, event, count, name, word);
    log_info("%s said %s %d times!", name, word, count);
    increment_count(SQLITE_DB, name);
}

void on_message_create(struct discord *client, const struct discord_message *event) {
    if (event->author->bot) return;

    if (rand() % 100 < 33) {
        char *emoji = get_random_emoji();
        discord_create_reaction(client, event->channel_id, event->id,
                                0, emoji, NULL);
    }

    if (is_user_id_in_array(event->author->id) == 1) {
        UserInfo *user_info = find_user_info_by_id(event->author->id);
        if (user_info != NULL) {
            if (strcasestr(event->content, user_info->trigger_word) == 0) {
                on_word_trigger(client, event, user_info->name, user_info->trigger_word);
            }
        }   
    }
    
    /* FEATURE TESTING
     * THESE FUNCTIONS ARE ONLY TRIGGERED
     * ON THE TEST SERVER */

    if (event->guild_id == 1171468612670857217) {
        if (event->author->id == 623685890824470548) {
            print_mplus_leaderboards("mplus.db");
        }
    }
}
