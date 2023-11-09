#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <concord/discord.h>
#include <concord/log.h>
#include "utils.h"
#include "dbase.h"

#define SQLITE_DB "/etc/dbot/dbot_counts.db"

typedef struct {
    u64snowflake id;
    char *name;
    char *trigger_word;
} UserInfo;

UserInfo user_db[] = {
    {
        572541399745167390,
        "Tots",
        "hello"
    },
    {
        217825266246877184,
        "Ros",
        "nagger"
    },
    {
        145303994959527937,
        "Oresmun",
        "bro"
    },
    {
        169188484303552517,
        "Jin",
        "what doin"
    },
    {
        430820138254860328,
        "Cato",
        "help"
    },
    {
        343223573806317572,
        "Mat",
        "rub"
    },
    {
        623685890824470548,
        "Rub",
        "wtf"
    },
    {
        905121536686579733,
        "Death",
        "key"
    },
    {
        304132255650152448,
        "Doug",
        "fuck"
    }
};

const size_t NUM_USERS = sizeof(user_db) / sizeof(user_db[0]);

UserInfo* find_user_info_by_name(char *name) {
    for (size_t i = 0; i < NUM_USERS; ++i) {
        if (strcmp(user_db[i].name, name) == 0) {
            return &user_db[i];
        }
    }
    return NULL; // name was not found
}

UserInfo* find_user_info_by_id(u64snowflake id) {
    for (size_t i = 0; i < NUM_USERS; ++i) {
        if (user_db[i].id == id) {
            return &user_db[i];
        }
    }
    return NULL; // id was not found
}

u64snowflake find_user_id_by_name(char *name) {
    for (size_t i = 0; i < NUM_USERS; ++i) {
        if (strcmp(user_db[i].name, name) == 0) {
            return user_db[i].id;
        }
    }
    return 0; // name was not found
}

typedef struct {
    char *name;
    char *unicode;
} Emoji;

Emoji emojis[] = {
    {
        "eggplant",
        "\xf0\x9f\x8d\x86"
    },
    {
        "clown",
        "\xf0\x9f\xa4\xa1"
    },
    {
        "clown",
        "\xf0\x9f\xa4\xa1"
    },
    {
        "chicken",
        "\xf0\x9f\x90\x94"
    },
    {
        "beer-mugs",
        "\xf0\x9f\x8d\xbb"
    },
    {
        "hand-vulcan",
        "\xf0\x9f\x96\x96"
    },
    {
        "hand-vulcan",
        "\xf0\x9f\x96\x96"
    },
    {
        "hand-middle-finger",
        "\xf0\x9f\x96\x95"
    },
    {
        "hand-horns",
        "\xf0\x9f\xa4\x98"
    },
    {
        "ninja",
        "\xf0\x9f\xa5\xb7"
    },
    {
        "two-men",
        "\xf0\x9f\x91\xac"
    },
    {
        "100-points",
        "\xf0\x9f\x92\xaf"
    },
    {
        "tp-roll",
        "\xf0\x9f\xa7\xbb"
    },
};

char *get_emoji(const char *name) {
    for (int i = 0; i < sizeof(emojis) / sizeof(emojis[0]); i++) {
        if (strcmp(emojis[i].name, name) == 0) {
            return emojis[i].unicode;
        }
    }
    return NULL;
}

char *get_random_emoji() {
    int random = rand() % (sizeof(emojis) / sizeof(emojis[0]));
    return emojis[random].unicode;
}


void on_ready(struct discord *client, const struct discord_ready *event) {
    const char *ready_string = "DBOT successfully connected to Discord as %s#%s!";
    log_info(ready_string, event->user->username, event->user->discriminator);
}

char *get_random_message_template() {
    int random = rand() % 10;
    switch (random) {
        case 0:
            return "\xF0\x9F\x8E\xBA\xF0\x9F\x8E\x89 **Attention everyone!** %s just mentioned \"%s\", making it a total of **%d** times! Let's give them a round of applause for their dedication! \xF0\x9F\x91\x8F\xF0\x9F\x91\x8F";
        case 1:
            return "\xF0\x9F\x95\xB5\xEF\xB8\x8F\xE2\x80\x8D\xE2\x99\x82\xEF\xB8\x8F **A wild clue appeared!** It seems %s is discussing \"%s\" again, now for a total of **%d** occasions. Can you solve the mystery of their fascination?";
        case 2:
            return "\xF0\x9F\x93\xA2 **Breaking News!** %s has brought up \"%s\" yet again, reaching **%d** mentions so far. Stay tuned as we dive deeper into this developing story!";
        case 3:
            return "\xF0\x9F\x91\x91 **Hear ye, hear ye!** Royal decree from %s about \"%s\", which has been mentioned **%d** times. All subjects are advised to lend an ear!";
        case 4:
            return "\xF0\x9F\x9A\x80 **Houston, we have a situation.** %s is talking about \"%s\" again, now hitting the **%d-time** mark. Are they trying to make contact with an alien topic?";
        case 5:
            return "\xE2\x8F\xB0 **Time travelers alert!** %s just mentioned \"%s\", altering the timeline. This has happened **%d** times now. Brace for temporal impact!";
        case 6:
            return "\xE2\x98\x81\xEF\xB8\x8F **Today's forecast:** a high chance of %s mentioning \"%s\", which has occurred **%d** times to date, with scattered opinions throughout the day.";
        case 7:
            return "\xF0\x9F\x8C\xBF **In the wild habitat of our chat,** observe as %s is drawn to discussing \"%s\". This behavior has been noted **%d** times. A fascinating ritual!";
        case 8:
            return "\xF0\x9F\x8F\x86 **And here comes %s,** racing towards their favorite topic \"%s\". This makes **%d** occurrences. Will they set a new record today?";
        case 9:
            return "\xF0\x9F\x8C\x9F **You heard it here first!** %s is back at it, discussing \"%s\". This topic has come up **%d** times. What's the buzz? Stay tuned for the exclusive scoop!";
        default:
            return "[%s] has said [%s] %d times.";
    }
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

int is_user_id_in_array(u64snowflake id) {
    for (size_t i = 0; i < NUM_USERS; ++i) {
        if (user_db[i].id == id) {
            return 1;
        }
    }
    return 0;
}

void on_message_create(struct discord *client, const struct discord_message *event) {
    if (event->author->bot) return;

    char *emoji = get_random_emoji();

    if (rand() % 100 < 33) {
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
}
