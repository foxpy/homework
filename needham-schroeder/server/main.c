#include <stdio.h>
#include <string.h>
#include <qc.h>
#include "server.h"

static void help(void* help_data) {
    char const* program_name = help_data;
    fprintf(stderr, "Usage: %s --database=DB_PATH --mode=MODE -- <MODE_ARGS>\n", program_name);
    fprintf(stderr, "Where MODE is one of:\n");
    fprintf(stderr, "\tget-credentials -- USERNAME: print credentials for specified user\n");
    fprintf(stderr, "\tadd-user -- USERNAME: adds user USERNAME to database and outputs his data\n");
    fprintf(stderr, "\tremove-user -- USERNAME: removes user USERNAME from database\n");
    fprintf(stderr, "\tlist-users: list all users registered in database\n");
    fprintf(stderr, "\tlisten -- QNAMEIN QNAMEOUT: starts listen server and serves user requests\n");
}

static qc_result add_user_cmd(server_ctx* ctx, int extra_args_idx, int extra_args_cnt, char* argv[], qc_err* err) {
    if (extra_args_cnt != 1) {
        qc_err_set(err, "Add user command: expected exactly one argument, got %d", extra_args_cnt);
        return QC_FAILURE;
    } else {
        char const* name = argv[extra_args_idx+0];
        if (server_register(ctx, name, err) == QC_SUCCESS) {
            user* user;
            if (server_query(ctx, name, &user, err) == QC_FAILURE) {
                qc_err_append_front(err, "Failed to get data of freshly registered user");
                return QC_FAILURE;
            } else if (user == NULL) {
                qc_err_set(err, "Freshly inserted user does not exist in database");
                return QC_FAILURE;
            } else {
                printf("Successfully registered user \"%s\", id: %s, key: %s\n", user->name, user->id, user->key);
                user_free(user);
                return QC_SUCCESS;
            }
        } else {
            return QC_FAILURE;
        }
    }
}

static qc_result get_credentials_cmd(server_ctx* ctx, int extra_args_idx, int extra_args_cnt, char* argv[], qc_err* err) {
    if (extra_args_cnt != 1) {
        qc_err_set(err, "Get credentials command: expected exactly one argument, got %s", extra_args_cnt);
        return QC_FAILURE;
    } else {
        char const* name = argv[extra_args_idx+0];
        user* user;
        if (server_query(ctx, name, &user, err) == QC_FAILURE) {
            qc_err_append_front(err, "Failed to read user credentials");
            return QC_FAILURE;
        } else if (user == NULL) {
            printf("User \"%s\" is not currently registered in database\n", name);
            return QC_SUCCESS;
        } else {
            printf("Found user \"%s\", id: %s, key: %s\n", user->name, user->id, user->key);
            user_free(user);
            return QC_SUCCESS;
        }
    }
}

static qc_result remove_user_cmd(server_ctx* ctx, int extra_args_idx, int extra_args_cnt, char* argv[], qc_err* err) {
    if (extra_args_cnt != 1) {
        qc_err_set(err, "Remove user command: expected exactly one argument, got %s", extra_args_cnt);
        return QC_FAILURE;
    } else {
        char const* name = argv[extra_args_idx+0];
        user* user;
        if (server_query(ctx, name, &user, err) != QC_SUCCESS) {
            qc_err_append_front(err, "Failed to obtain user data for deletion");
            return QC_FAILURE;
        } else if (user == NULL) {
            printf("Warning: user \"%s\" does not exist\n", name);
            return QC_SUCCESS;
        } else {
            user_free(user);
        }
        if (server_unregister(ctx, name, err) != QC_SUCCESS) {
            qc_err_append_front(err, "Failed to delete user from database");
            return QC_FAILURE;
        } else {
            printf("Successfully deleted user \"%s\"\n", name);
            return QC_SUCCESS;
        }
    }
}

static qc_result list_users_cmd(server_ctx* ctx, int extra_args_idx, int extra_args_cnt, char* argv[], qc_err* err) {
    QC_UNUSED(extra_args_idx);
    QC_UNUSED(argv);
    if (extra_args_cnt > 0) {
        qc_err_set(err, "List users command does not accept any arguments");
        return QC_FAILURE;
    } else {
        if (server_dump_users(ctx, stdout, err) == QC_FAILURE) {
            qc_err_append_front(err, "Failed to obtain list of users");
            return QC_FAILURE;
        } else {
            return QC_SUCCESS;
        }
    }
}

static void listen_cmd(server_ctx* ctx, int extra_args_idx, int extra_args_cnt, char* argv[], qc_err* err) {
    if (extra_args_cnt != 2) {
        qc_err_set(err, "Server listen command: expected exactly two arguments, got %d", extra_args_cnt);
        return;
    } else {
        char const* mqueue_in_name = argv[extra_args_idx+0];
        char const* mqueue_out_name = argv[extra_args_idx+1];
        server_listen(ctx, mqueue_in_name, mqueue_out_name, err);
        qc_err_append_front(err, "Server encountered error during request serving");
        return;
    }
}

int main(int argc, char* argv[]) {
    char const* database_path;
    char const* mode;
    qc_err* err = qc_err_new();
    qc_args* args = qc_args_new();
    qc_args_set_help(args, help, argv[0]);
    qc_args_string(args, "database", &database_path, "Path to server database file");
    qc_args_string(args, "mode", &mode, "Server operation mode");
    if (qc_args_parse(args, argc, argv, err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to parse CLI arguments");
    } else {
        server_ctx* ctx;
        qc_result result;
        int extra_idx = qc_args_extras_index(args);
        int extra_cnt = qc_args_extras_count(args);
        if ((ctx = server_init(database_path, err)) == NULL) {
            qc_err_fatal(err, "Failed to initialize server");
        } else if (strcmp(mode, "add-user") == 0) {
            result = add_user_cmd(ctx, extra_idx, extra_cnt, argv, err);
        } else if (strcmp(mode, "remove-user") == 0) {
            result = remove_user_cmd(ctx, extra_idx, extra_cnt, argv, err);
        } else if (strcmp(mode, "listen") == 0) {
            listen_cmd(ctx, extra_idx, extra_cnt, argv, err);
            // Listen command is expected to run forever, if it returns — there is an error
            result = QC_FAILURE;
        } else if (strcmp(mode, "list-users") == 0) {
            result = list_users_cmd(ctx, extra_idx, extra_cnt, argv, err);
        } else if (strcmp(mode, "get-credentials") == 0) {
            result = get_credentials_cmd(ctx, extra_idx, extra_cnt, argv, err);
        } else {
            qc_err_set(err, "Unknown operating mode: %s", mode);
            qc_err_fatal(err, "Failed to start server");
        }
        server_close(ctx);
        if (result == QC_FAILURE) {
            qc_err_fatal(err, "Failed to execute command %s", mode);
        }
    }
    qc_args_free(args);
    qc_err_free(err);
}
