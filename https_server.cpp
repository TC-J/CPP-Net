#include "ssl.hpp"

int main() {
    SSL_CTX *ctx;
    BIO *bio;

    ssl_init();
    ctx = create_ssl_ctx("server-certificate.pem", "server-private-key.pem");

    bio = BIO_new_accept("443");
    if (bio <= 0) {
        SSL_ERROR();
        exit(1);
    }

    if (BIO_do_accept(bio) <= 0) {
        SSL_ERROR();
        exit(1);
    }

    while (1) {
        BIO *conn;

        if (BIO_do_accept(bio) <= 0) {
            SSL_ERROR();
            exit(1);
        }

        conn = BIO_pop(bio);
        conn = BIO_push(BIO_new_ssl(ctx, 0), conn);
        if (conn == nullptr) {
            printf("null conn\n");
            break;
        }

        char buf[4096];
        int n;
        n = BIO_read(conn, (void*)buf, 4096);
        if (n <= 0) {
            SSL_ERROR();
            exit(1);
        }
        for (int i = 0; i < n; i++) {
            printf("%c", buf[i]);
        }
        printf("\n");
    }

}