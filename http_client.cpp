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

int main () {
    BIO *bio;
    int n;
    char buf[4096];

    init_openssl();

    bio = BIO_new_connect("google.com:80");
    if (bio == NULL) {
        printf("BIO_new_connect failed\n");
        exit(1);
    }

    if (BIO_do_connect(bio) <= 0) {
        printf("BIO_do_connect failed\n");
        exit(1);
    }
    printf("Connection Succeeded\n----------------\n\n");

    n = BIO_write(bio, (void *)&"GET /\n\n", 7);
    if (n <= 0) {
        printf("failed to BIO_write\n");
        exit(1);
    }

    n = BIO_read(bio, (void *)&buf, 4096);
    if (n > 0) {
        for (int i = 0; i < n; i++) {
            printf("%c", buf[i]);
        }
        printf("\n");
    }

    BIO_reset(bio);
    BIO_free_all(bio);
}