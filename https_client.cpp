#include <stdio.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <unistd.h>

void init_openssl() {
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();
}

#if !defined(SSL_CERT_PATH)
#define SSL_CERT_PATH "server.crt"
#endif

#define SSL_ERROR() fprintf(stderr, "[FATAL] %s\n", ERR_error_string(ERR_get_error(), nullptr))

int main() {

    SSL_CTX *ctx; 
    SSL *ssl;
    BIO *bio;
    int n, total = 0;
    char buf[512];

    init_openssl();
    ctx = SSL_CTX_new(SSLv23_client_method());

    if (! SSL_CTX_load_verify_locations(ctx, SSL_CERT_PATH, nullptr)) {
        SSL_ERROR();
        exit(1);
    }

    bio = BIO_new_ssl_connect(ctx);
    if (bio == nullptr) {
        SSL_ERROR();
        exit(1);
    }

    BIO_get_ssl(bio, &ssl);
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
    if (SSL_get_verify_result(ssl) != X509_V_OK) {
        SSL_ERROR();
        exit(1);
    }


    BIO_set_conn_hostname(bio, "0.0.0.0:443");
    if (BIO_do_connect(bio) <= 0) {
        SSL_ERROR();
        exit(1);
    }

    n = BIO_write(bio, (void *)&"GET /\n\n", 7);
    if (n <= 0) {
        SSL_ERROR();
        exit(1);
    }

    do {
        n = BIO_read(bio, (void *)buf, 256);
        if (n <= 0) {
            SSL_ERROR();
            exit(1);
        }
        for (int i = 0; i < n; i++) {
            printf("%c", buf[i]);
        }
        total += n;
    } while (n == 256);

    printf("\n\nTotal: %d bytes\n\n", total);

    BIO_reset(bio);

    BIO_free_all(bio);
    SSL_CTX_free(ctx);
}