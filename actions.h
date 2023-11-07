#ifndef ACTIONS_H
#define ACTIONS_H

void on_ready(struct discord *client, const struct discord_ready *event);
void on_message_create(struct discord *client, const struct discord_message *event);

#endif
