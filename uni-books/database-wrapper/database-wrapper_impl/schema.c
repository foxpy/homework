char const* schema =
        "CREATE TABLE Users (\n"
        "    user_id INTEGER PRIMARY KEY,\n"
        "    is_admin INTEGER NOT NULL,\n"
        "    username TEXT NOT NULL UNIQUE,\n"
        "    password_hash TEXT NOT NULL\n"
        ");\n"
        "\n"
        "CREATE TABLE Books (\n"
        "    book_id INTEGER PRIMARY KEY,\n"
        "    exists_flag INTEGER NOT NULL,\n"
        "    isbn TEXT NOT NULL,\n"
        "    name TEXT NOT NULL,\n"
        "    author TEXT NOT NULL,\n"
        "    catalog TEXT NOT NULL\n"
        ");\n";
