#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "ESP32"                         //change this. Will be the client identifier for MQTT
 
const char WIFI_SSID[] = "ssid";               //change this
const char WIFI_PASSWORD[] = "password";           //change this
const char AWS_IOT_ENDPOINT[] = "xxxxxxxxxx-xxx.iot.us-east-1.amazonaws.com";       //change this
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAMr9xx0nTNH14OIVqNktn4AGFUGZMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMjA5MDIxNjI4
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
Fzdwe7ZpktyuLDpHwEQejYFSyWOIB77/mkghRZjTKKpKTUZBRXfZktOETWApY/mQ
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
SSIfC9kVfzvXk0tL9yrakd4bHJKKNwu31X1WJKnEAtREh8fHC4DMmHAxpIQ8SjqZ
45c1RnXiloKsDRBPiYOBuQKjbqFKs5N0EVStVliZAOnfeb6l6tTQuXq592p28Q2/
/aHRzKnbDeKuw64+XBsBbjYjOFq5+WJT2x4PT43M/INTKJyddlRDMTwBO6zZqA3h
bqR5AgMBAAGjYDBeMB8GA1UdIwQYMBaAFPx8LKefF/WUn8AoUHiQaEZQKTAFMB0G
A1UdDgQWBBSQlXdm/cxMCbaTb5B2oFZUfYaWbjAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAicOuuOTFVh+EPBAm0x3YKmuk
0QmE6/Acjk0Ikqud7WVirWiLWnJ+Hwki+CrT4wZXGxLEbGEQn9xfVU/LEiwCcdgV
EUrQ7VF5H35kDERleWVSHXge9GHjZK6ANSqEbm+ZmSYzZg8x+hn9Qtm5kl8hdogT
EicJ9JhMMwhIHoZ/S1wPg0QhJvNHXW6jE1NvzUkfXXTJXbs3V11wqzOyVsazSfBw
y5NAoQypS4sGVb/8VO+KqHICn0xh4Qr3tUuH54dzanpSp3T82u08TrywuXnw22XI
fjWeim8RVyTZhUdd8c+ysCfBDpcQbIJu8ygnWZ+fdTL+IPxiBgUfbs3rvdyYnQ==
-----END CERTIFICATE-----
 
 
)KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEAyXz6IBTgguplIHnPGRc3cHu2aZLcriw6R8BEHo2BUsljiAe+
/5pIIUWY0yiqSk1GQUV32ZLThE1gKWP5kCadyqp08bAQEIw6NcngOv5KLYmXG0Yi
Pw9porCR+t4kaMrVTii1FfyPO0zvfFpvFkkiHwvZFX8715NLS/cq2pHeGxySijcL
t9V9ViSpxALURIfHxwuAzJhwMaSEPEo6meOXNUZ14paCrA0QT4mDgbkCo26hSrOT
dBFUrVZYmQDp33m+perU0Ll6ufdqdvENv/2h0cyp2w3irsOuPlwbAW42Izhaufli
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
wWGe39aKlvfb1BMYkAhka+W2ftfh7ix5qgFFBGCVC2iutEJDnBonLAKRV773afqG
x/H5UUQjkl2xD3XNQvCEyJPEo9meis1wPNdGYxY0/OgI4QiAaOjSewbyx2HkvCMP
XLjknho8ntaU0T/Nsa4wdiuBQm8p8fQVn73ae65n7AmNciGTmB4SAGS9Cr8bu8WO
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
sBCaXC3I2TS30pLXuiqxxlYNzSwRfrsco+g1LN2NbBiZxgYqUlU5Frzp4fBov4Rc
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
EiYQGTxmPz8ZMTlqu4vtC845r5N9v7pybLySOm0CgYEA6aX8DjraHyKxp/qccTp2
87ObzPS5uAxO4hrqwyIWxHa3SUFfPww4//NV80B9OIPjRLx6dHvX/mYj/6czFhfS
DwdI3rg1evvJfPs2iGqOl0QZxSCpXylz+n3qJdDLhOSJTUJxWvcLnrR1/nGn1qVn
7ye5mbwia4kFOH6tKA8fUpECgYB4+uhrxUTUK7h1OvxP4eEQB/Q4MbagdvBjdLLh
7xriQXNf7MNeGydQOzbsBpnaFuS5e1E/ZctfAzu98RKjLIcZrkijohfa9R2OPvVR
Hxmu2j2+upP1nTp5PMciVgI079Ce4zLqFtEeVWH0y9+/DnhP3xy39T/7mKe2BCTl
BBaiHQKBgEXsA/zi5jgyFqos4G+g1QHHJrNSWjGYNOMa3rG8N5lwEDOOJ1RVVVAe
3RemMSYp2UuXgEtBKLEgda/BwGL5P2zJTtLaJs9sri/ZU5AW3+IzX/H8+PooQeIX
z/aonMCg4WhDZQuk2JYI5216u230RqiQPKpLsIWrHZMqvUl5eCot
-----END RSA PRIVATE KEY-----
 
 
)KEY";
