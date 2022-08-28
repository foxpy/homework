#!/bin/bash
set -euo pipefail

start_dir="$(pwd)"
build_dir="demo_build"
database="server.db"
alice="Alice"
bob="Bob"
queue_server_in="ns-c2s"
queue_server_out="ns-s2c"
bob_queue_in="ns-a2b"
bob_queue_out="ns-b2a"
server_pid="-1"
bob_pid="-1"

cleanup() {
  if [[ "$server_pid" != "-1" ]]; then
    kill "$server_pid" &>/dev/null || true
  fi
  if [[ "$bob_pid" != "-1" ]]; then
    kill "$bob_pid" &>/dev/null || true
  fi
  cd "$start_dir"
  rm -rf "$build_dir"
}
trap cleanup EXIT

build() {
  cmake ..
  cmake --build . -- "-j$(nproc)"
}

main() {
  mkdir "$build_dir"
  cd "$build_dir"
  build
  server/ns-server --database="$database" --mode=add-user -- "$alice"
  server/ns-server --database="$database" --mode=add-user -- "$bob"
  server/ns-server --database="$database" --mode=listen -- "$queue_server_in" "$queue_server_out" &
  server_pid=$!
  while [[ ! -f "/dev/mqueue/$queue_server_in" ]]; do ls / &>/dev/null; done
  while [[ ! -f "/dev/mqueue/$queue_server_out" ]]; do ls / &>/dev/null; done
  alice_id="$(printf "select lower(hex(id)) from users where name = '%s';" "$alice" | sqlite3 "$database")"
  alice_key="$(printf "select lower(hex(key)) from users where name = '%s';" "$alice" | sqlite3 "$database")"
  bob_id="$(printf "select lower(hex(id)) from users where name = '%s';" "$bob" | sqlite3 "$database")"
  bob_key="$(printf "select lower(hex(key)) from users where name = '%s';" "$bob" | sqlite3 "$database")"
  echo -e "\nxorshift mode"
  clientB/ns-client-b --my-key="$bob_key" --mqueue-in="$bob_queue_in" --mqueue-out="$bob_queue_out" &
  bob_pid=$!
  while [[ ! -f "/dev/mqueue/$bob_queue_in" ]]; do ls / &>/dev/null; done
  while [[ ! -f "/dev/mqueue/$bob_queue_out" ]]; do ls / &>/dev/null; done
  clientA/ns-client-a --mqueue-server-in="$queue_server_out" --mqueue-server-out="$queue_server_in" \
                      --mqueue-client-in="$bob_queue_out" --mqueue-client-out="$bob_queue_in" \
                      --id="$alice_id" --target-id="$bob_id" --my-key="$alice_key"
  kill "$bob_pid" &>/dev/null || true
  echo -e "\nchacha20 mode"
  clientB/ns-client-b --my-key="$bob_key" --mqueue-in="$bob_queue_in" --mqueue-out="$bob_queue_out" &
  bob_pid=$!
  while [[ ! -f "/dev/mqueue/$bob_queue_in" ]]; do ls / &>/dev/null; done
  while [[ ! -f "/dev/mqueue/$bob_queue_out" ]]; do ls / &>/dev/null; done
  clientA/ns-client-a --mqueue-server-in="$queue_server_out" --mqueue-server-out="$queue_server_in" \
                      --mqueue-client-in="$bob_queue_out" --mqueue-client-out="$bob_queue_in" \
                      --id="$alice_id" --target-id="$bob_id" --my-key="$alice_key" --use-chacha
  echo -e "\nno chacha20poly1305 mode unfortunately"
}
main
