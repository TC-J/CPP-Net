### Before Building
Go into the makefile and scroll down to the "https_client" target, then change the -DSSL_CERT_PATH= to the path of a certificate, pick one from /etc/ssl/certs -- one of them is going to work

### Building & Running
Run make with no arguments.

http_client & https_client take no arguments, and each one requests the
home page of google.com

https_server also takes no arguments, first run "gen_server_cert" for a self-signed certificate and in order to test that it works use "curl --cacert server-certificate.pem https://localhost:443" it doesn't respond to the request it instead prints the request