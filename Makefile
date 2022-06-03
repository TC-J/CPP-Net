default: all

all: http_client https_client

http_client: http_client.cpp
	@g++ -o $@ $< -lssl -lcrypto

https_client: https_client.cpp
	@g++ -DSSL_CERT_PATH="\"/etc/ssl/certs/Amazon_Root_CA_2.pem\"" -o $@ $< -lssl -lcrypto
# add -DSSL_CERT_PATH=/etc/ssl/certs/<pick> (ls /etc/ssl/certs)

clean:
	@rm -f http_client https_client