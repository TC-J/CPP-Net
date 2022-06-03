#include "ssl.hpp"
int main () {
    ssl_init();
    generate_server_selfsigned_cert();
}