#ifndef DBASE_H
#define DBASE_H

int check_count(char *dbname, char *name);
int increment_count(char *dbname, char *name);
int callback(void *NotUsed, int argc, char **argv, char **azColName);
int print_mplus_leaderboards(char *dbname);

#endif
