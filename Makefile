default: all

all: http_client https_client https_server gen_server_cert

http_client: http_client.cpp
	@g++ -o $@ $< -lssl -lcrypto

https_client: https_client.cpp
	@g++ -DSSL_CERT_PATH="\"/etc/ssl/certs/Amazon_Root_CA_2.pem\"" -o $@ $< -lssl -lcrypto
# add -DSSL_CERT_PATH=/etc/ssl/certs/<pick> (ls /etc/ssl/certs)

gen_server_cert: gen_server_cert.cpp
	@g++ -o $@ $< -lssl -lcrypto

https_server: https_server.cpp ssl.hpp
	@g++ -o $@ $< -lssl -lcrypto

clean:
	@rm -f http_client https_client https_server gen_server_cert *.pem