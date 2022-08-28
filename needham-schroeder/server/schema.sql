create table if not exists users(
    name text unique not null,
    id blob unique not null,
    key blob unique not null
);
