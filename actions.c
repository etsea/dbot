#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <concord/discord.h>
#include <concord/log.h>
#include "utils.h"
#include "dbase.h"

#define SQLITE_DB "/etc/dbot/dbot_counts.db"

#define ID_TOTS     572541399745167390
#define ID_ROS      217825266246877184
#define ID_ORESMUN  145303994959527937
#define ID_JIN      169188484303552517
#define ID_CATO     430820138254860328
#define ID_MAT      343223573806317572
#define ID_RUB      623685890824470548
#define ID_DEATH    905121536686579733
#define ID_DOUG     304132255650152448

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

void on_message_create(struct discord *client, const struct discord_message *event) {
    if (event->author->bot) return;

    if (event->author->id == ID_TOTS) {
        discord_create_reaction(client, event->channel_id, event->id,
                                0, "\xF0\x9F\x8D\x86", NULL);
    } else if (event->author->id == ID_ORESMUN) {
        discord_create_reaction(client, event->channel_id, event->id,
                                0, "\xF0\x9F\xA4\xA1", NULL);
    } else if (event->author->id == ID_DOUG) {
        discord_create_reaction(client, event->channel_id, event->id,
                                0, "\xF0\x9F\x90\x94", NULL);
    }

    if (event->author->id == ID_TOTS && strcasestr(event->content, "hello") == 0) {
        int count = check_count(SQLITE_DB, "Tots");
        send_announcement(client, event, count, "Tots", "hello");
        log_info("Tots said hello %d times!", count);
        increment_count(SQLITE_DB, "Tots");

    } else if (event->author->id == ID_ROS && strcasestr(event->content, "nagger") == 0) {
        int count = check_count(SQLITE_DB, "Ros");
        send_announcement(client, event, count, "Ros", "nagger");
        log_info("Ros said nagger %d times!", count);
        increment_count(SQLITE_DB, "Ros");

    } else if (event->author->id == ID_ORESMUN && strcasestr(event->content, "bro") == 0) {
        int count = check_count(SQLITE_DB, "Oresmun");
        send_announcement(client, event, count, "Oresmun", "bro");
        log_info("Oresmun said bro %d times!", count);
        increment_count(SQLITE_DB, "Oresmun");
        
    } else if (event->author->id == ID_JIN && strcasestr(event->content, "what doin") == 0) {
        int count = check_count(SQLITE_DB, "Jin");
        send_announcement(client, event, count, "Jin", "what doin");
        log_info("Jin said what doin %d times!", count);
        increment_count(SQLITE_DB, "Jin");
        
    } else if (event->author->id == ID_CATO && strcasestr(event->content, "help") == 0) {
        int count = check_count(SQLITE_DB, "Cato");
        send_announcement(client, event, count, "Cato", "help");
        log_info("Cato said help %d times!", count);
        increment_count(SQLITE_DB, "Cato");

    } else if (event->author->id == ID_MAT & strcasestr(event->content, "rub") == 0) {
        int count = check_count(SQLITE_DB, "Mat");
        send_announcement(client, event, count, "Mat", "rub");
        log_info("Mat said rub %d times!", count);
        increment_count(SQLITE_DB, "Mat");

    } else if (event->author->id == ID_RUB & strcasestr(event->content, "fuck") == 0) {
        int count = check_count(SQLITE_DB, "Rub");
        send_announcement(client, event, count, "Rub", "fuck");
        log_info("Rub said fuck %d times!", count);
        increment_count(SQLITE_DB, "Rub");

    } else if (event->author->id == ID_DEATH & strcasestr(event->content, "key") == 0) {
        int count = check_count(SQLITE_DB, "Death");
        send_announcement(client, event, count, "Death", "keys");
        log_info("Death said key %d times!", count);
        increment_count(SQLITE_DB, "Death");

    } 
}
