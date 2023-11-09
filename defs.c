#include "defs.h"
#include <stdlib.h>
#include <string.h>

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

const size_t SIZE_USER_DB = sizeof(user_db) / sizeof(user_db[0]);

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

const size_t SIZE_EMOJIS = sizeof(emojis) / sizeof(emojis[0]);

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
