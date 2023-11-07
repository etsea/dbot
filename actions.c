#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sqlite3.h>
#include <concord/discord.h>
#include <concord/log.h>
#include "utils.h"

void on_ready(struct discord *client, const struct discord_ready *event) {
    const char *ready_string = "DBOT successfully connected to Discord as %s#%s!";
    log_info(ready_string, event->user->username, event->user->discriminator);
}

void send_announcement(struct discord *client, const struct discord_message *event, int count, char *name, char *word) {
    count++;

    char announce[100];
    sprintf(announce, "%s has now said '%s' %d times!", name, word, count);

    struct discord_create_message params = {
        .content = announce,
    };

    discord_create_message(client, 1171550749407313950, &params, NULL);
}

int check_count(char *dbname, char *name) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc, count = 0;
    char *sql;

    rc = sqlite3_open(dbname, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sql = "CREATE TABLE IF NOT EXISTS counts(name TEXT UNIQUE NOT NULL, count INT NOT NULL)";
    rc = sqlite3_exec(db, sql, 0, 0, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sql = "SELECT count FROM counts WHERE name = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    } else {
        sqlite3_finalize(stmt); // Finalize the previous statement first

        sql = "INSERT INTO counts (name, count) VALUES (?, 0)";
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Failed to prepare insert statement: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return -1;
        }

        sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            fprintf(stderr, "Failed to insert new name: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return -1;
        }
        count = 0;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return count;
}

int increment_count(char *dbname, char *name) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(dbname, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    char *sql = "UPDATE counts SET count = count + 1 WHERE name = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to increment count: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return -1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0; // Success
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
