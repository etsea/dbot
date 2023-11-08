#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <concord/discord.h>
#include <concord/log.h>
#include "utils.h"
#include "dbase.h"

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
    sprintf(announce, base_msg, name, word, count);

    struct discord_create_message params = {
        .content = announce,
    };

    discord_create_message(client, 1171550749407313950, &params, NULL);
}

void on_message_create(struct discord *client, const struct discord_message *event) {
    if (event->author->bot) return;

    if (event->author->id == 572541399745167390 && strcasestr(event->content, "hello") == 0) {
        int tots_count = check_count("counts.db", "Tots");
        send_announcement(client, event, tots_count, "Tots", "hello");
        log_info("Tots said hello %d times!", tots_count);
        increment_count("counts.db", "Tots");

    } else if (event->author->id == 217825266246877184 && strcasestr(event->content, "nagger") == 0) {
        int ros_count = check_count("counts.db", "Ros");
        send_announcement(client, event, ros_count, "Ros", "nagger");
        log_info("Ros said nagger %d times!", ros_count);
        increment_count("counts.db", "Ros");

    } else if (event->author->id == 145303994959527937 && strcasestr(event->content, "bro") == 0) {
        int oresmun_count = check_count("counts.db", "Oresmun");
        send_announcement(client, event, oresmun_count, "Oresmun", "bro");
        log_info("Oresmun said bro %d times!", oresmun_count);
        increment_count("counts.db", "Oresmun");
        
    } else if (event->author->id == 169188484303552517 && strcasestr(event->content, "what doin") == 0) {
        int jin_count = check_count("counts.db", "Jin");
        send_announcement(client, event, jin_count, "Jin", "what doin");
        log_info("Jin said what doin %d times!", jin_count);
        increment_count("counts.db", "Jin");
        
    } else if (event->author->id == 430820138254860328 && strcasestr(event->content, "help") == 0) {
        int cato_count = check_count("counts.db", "Cato");
        send_announcement(client, event, cato_count, "Cato", "help");
        log_info("Cato said help %d times!", cato_count);
        increment_count("counts.db", "Cato");

    } else if (event->author->id == 343223573806317572 & strcasestr(event->content, "rub") == 0) {
        int mat_count = check_count("counts.db", "Mat");
        send_announcement(client, event, mat_count, "Mat", "rub");
        log_info("Mat said rub %d times!", mat_count);
        increment_count("counts.db", "Mat");

    } 
}
