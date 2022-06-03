#if !defined(__NET_SSL__)
#define __NET_SSL__

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <unistd.h>
#include <stdio.h>

static void ssl_init () 
{
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();
}

#define SSL_ERROR() fprintf(stderr, "[FATAL] %s\n", ERR_error_string(ERR_get_error(), nullptr))

void generate_server_selfsigned_cert() {
    system("openssl ecparam -genkey -name prime256v1 -noout -out server-private-key.pem");
    system("openssl ec -in server-private-key.pem -pubout -out server-public-key.pem");
    system("openssl req -new -x509 -sha256 -key server-private-key.pem -subj \"/CN=localhost\" -out server-certificate.pem");
}

SSL_CTX *create_ssl_ctx(const char *cert, const char *privkey) {
    SSL_CTX *ctx;

    ctx = SSL_CTX_new(TLS_method());
    if (SSL_CTX_use_certificate_file(ctx, cert, SSL_FILETYPE_PEM) <= 0) {
        SSL_ERROR();
        exit(1);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, privkey, SSL_FILETYPE_PEM) <= 0) {
        SSL_ERROR();
        exit(1);
    }

    return ctx;
}

#endif // __NET_SSL__