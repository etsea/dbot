#ifndef DEFS_H
#define DEFS_H

#include <concord/discord.h>

typedef struct {
    u64snowflake id;
    char *name;
    char *trigger_word;
} UserInfo;

typedef struct {
    char *name;
    char *unicode;
} Emoji;

extern UserInfo user_db[];
extern Emoji emojis[];
extern const size_t SIZE_USER_DB;
extern const size_t SIZE_EMOJIS;

// Function prototypes
char *get_random_message_template();

#endif // DEFS_H
