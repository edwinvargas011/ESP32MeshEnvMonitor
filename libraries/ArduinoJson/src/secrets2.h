#include <pgmspace.h>
#include <string.h>

#define SECRET
#define THINGNAME "MyESP32TTGO"
char WIFI_SSID[] = "FIBRA_MOVISTAR_0822";
char* WIFI_PASSWORD = "EAVJ4090#*";
char* AWS_IOT_ENDPOINT = "adwm4t0deqwu5-ats.iot.us-east-1.amazonaws.com";

// Amazon Root CA 1
const char* AWS_CERT_CA PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate
const char* AWS_CERT_CRT PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUBWfB/ywGxUwifrx4CtYj9syGGDUwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIzMDYxOTAxMDU0
M1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAJwW/fFDwy7zPlLo4Fns
Fv3URoil/QMiPndq8eEKF1srOb2Dn5blEUW3NgHjJ9p3RFdJCif1kEGX32gFFFFA
8uzih0pNcVyRISN8O9docQetPGgq+QwDU/RNZ34mAP1lqdNNUQH7o2Ts5N2ZGOPc
r/LWWxiW+l950zWg8E5eenKNg3ugTOKytLzkQwqKBZ57iMfuc8a/phoo/5/l1vmA
LyBQSq9na0JCBbHsA67hffKu3yxIRJJrsQl5PRPv0io9025nhk+ND6xek/f/jPuw
S4uFTBy/jqeCN9i/vuH2JmWEYnaSCs937cK26ohoZujr0fOZvw4HWcwGumKsczYp
+68CAwEAAaNgMF4wHwYDVR0jBBgwFoAUMRGg18PrYIESuHj/eIcAf0jtIbUwHQYD
VR0OBBYEFCtV2sBZMkTMV9rHCISZ0d9q1lCxMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQACCQW1HT8axKwiWE4YIiO/k8h3
YdWuR1cY8Ejzo4lkl7uLzNKOD9qttjGTrwmuWTmEg6vpMd4fRdRx77gFAkQmn4Kv
EZyqWZ8lZdWiQyrJ+KpXz7qb7h666SlCII9viifFuUciGpEwX1wYkttDCtbpoKR9
gRgr1Z+qnzszj+FPUqgV/aOj35jO7WxXKz9SMSyxxQK3qo2SJgCM7jkyZirBKphX
D2+rX78a1V7fvUI8SwYVNUC73koVN02boVhoMkR478PkG472655ZCjB1ZqqcG3pI
S7xU6w0yKhxsNmBUTHq71NmoD12vtF4Rd98SIqGDd9AaiRuuQJ3ubU9kKDGO
-----END CERTIFICATE-----
)KEY";

// Device Private Key
const char* AWS_CERT_PRIVATE PROGMEM= R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEogIBAAKCAQEAnBb98UPDLvM+UujgWewW/dRGiKX9AyI+d2rx4QoXWys5vYOf
luURRbc2AeMn2ndEV0kKJ/WQQZffaAUUUUDy7OKHSk1xXJEhI3w712hxB608aCr5
DANT9E1nfiYA/WWp001RAfujZOzk3ZkY49yv8tZbGJb6X3nTNaDwTl56co2De6BM
4rK0vORDCooFnnuIx+5zxr+mGij/n+XW+YAvIFBKr2drQkIFsewDruF98q7fLEhE
kmuxCXk9E+/SKj3TbmeGT40PrF6T9/+M+7BLi4VMHL+Op4I32L++4fYmZYRidpIK
z3ftwrbqiGhm6OvR85m/DgdZzAa6YqxzNin7rwIDAQABAoIBABj/lawOLjRWwKSG
p2e/Z+8/EAzSiLL3yQlXF2XzN8piId04N1bzWNDRhtTGjJtwfoF8MSQ1L+VRbXY7
WgWpYT6PCRvdS0qH88a7Htpg37lbBVGpkDlcTxXRT8HkVERBA/HTcCXhJ0oCpqTW
4CWeMo+xxOUrSO4BlNIB9HqYpwOxZlUGbuDuWzFhtDMyhhSVXiEQtHnjGBBQOZNg
J2eITVeSnMywrzpJDurhJY1q//VFTDtq7BLxe/g3spVNtmF/NDjcWAu1Fp55Q464
bMrRLqe9g5f/z+f/ZuNzkpRBwP/zQDbkU9eSe+BhxUmgAOAgaK+Ng7x0KHUcVgnP
0OeRKAECgYEAydyHXOkgmgJmUUB/aZCa4CYuTU9FVIk5KAAB3loHP1KciqQiMXrJ
VyvhzuD4mY5rQolgROtLCYWUEwtREzpps+g3Oj9OoLcc7ybr63s+oulel9pcuW4w
BmpP4qtiPBQQC4/BYk7xd5p6EiTT7+VG/OTNwPYpFwaH3/Av7JrK77MCgYEAxfPb
9tHVUiZGZMqobpzRX3/T6uQr1P7Ik6JiiZsv15yIU5K/FNQlub6fqL3lcadCA6Su
1x6aC/YlrmZFfDly0BujZZ+IheVCX/Bk6To/3eES6l5miuMYEuw7B7rDyX8CYlyO
1d7PWmFFSte+WunbQGA041BC0u+GYuH0Eb5xZhUCgYA/flQ9jz6n8rVIPWdWRxvQ
AXJy8so16uvFfysXS24YJt4CZdozghGuj6j5L55Cfp+SUC+tvezeU9vdmaOozqjM
4+/rLFqJBs/dEXsHmL5887bDQPYFhXkpq2rxO0Ms7oqVeGQ1jes52acn6dmYDaAk
j7uARG1sRquabqxEWfQXLQKBgGGVFEM5L5K+oYcATEWy8pfEWQB7GIx4SQJWU4MI
SG5ekOm59o5bAnntWaGCc0Aytp07KqGLSV9KKUsuyWQyocGrTkJDgbaXzL+kruo2
N9O2J2/3t08SIgT6BSOLUwbaoJ9Ch3swykEAoHsDnagNjnLOumOwZjC7uSC3yGyS
2C39AoGAPLKxBXkicBqAVeqHKWihOO61rk1pv7OX0BzVWWasZvri+NkXIl+wOGkA
sUKCatIUCBdhfowWTpSozLYiZ++DKOdGCGI1ieaOLBXz6XiduwcG8++hREa104rQ
QTNITA3PKw5KoY3oi/2ni1VQwRKD8SQCeqMVQgzT+a5l7itntZM=
-----END RSA PRIVATE KEY-----
)KEY";