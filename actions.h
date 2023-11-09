#include "defs.h"

#ifndef ACTIONS_H
#define ACTIONS_H

UserInfo* find_user_info_by_name(char *name);
UserInfo* find_user_info_by_id(u64snowflake id);
u64snowflake find_user_id_by_name(char *name);
int is_user_in_id_array(u64snowflake id);
char *get_emoji(const char *name);
char get_random_emoji();
void on_ready(struct discord *client, const struct discord_ready *event);
void send_announcement(struct discord *client, const struct discord_message *event, int count, char *name, char *word);
void on_word_trigger(struct discord *client, const struct discord_message *event, char *name, char *word);
void on_message_create(struct discord *client, const struct discord_message *event);

#endif
