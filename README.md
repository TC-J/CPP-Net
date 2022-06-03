### Before Building
Go into the makefile and scroll down to the "https_client" target, then change the -DSSL_CERT_PATH= to the path of a certificate, pick one from /etc/ssl/certs -- one of them is going to work

### Building & Running
Run make with no arguments.

http_client: takes no arguments
https_client: takes no arguments