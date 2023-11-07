#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>


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
