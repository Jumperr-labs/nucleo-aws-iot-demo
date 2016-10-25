/**
 ******************************************************************************
 * @file    aws_nucleo_certificates.c
 * @author  Central LAB
 * @version V0.1.0
 * @date    10-March-2016
 * @brief   AWS IoT Device Certificates, Private Key file
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */


#include "stdint.h"


/**********************************************************************************************
***********************************************************************************************
													Root CA certificate: Never modify
***********************************************************************************************
***********************************************************************************************/

/************************************************************************
Downloaded from https://www.symantec.com/content/en/us/enterprise/verisign/roots/VeriSign-Class%203-Public-Primary-Certification-Authority-G5.pem
*************************************************************************/
//This root CA can be used.
uint8_t rootCA[] = "\
-----BEGIN CERTIFICATE-----\n\
MIIE0zCCA7ugAwIBAgIQGNrRniZ96LtKIVjNzGs7SjANBgkqhkiG9w0BAQUFADCBy\
jELMAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQLEx\
ZWZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJpU2l\
nbiwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxWZXJp\
U2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0aG9ya\
XR5IC0gRzUwHhcNMDYxMTA4MDAwMDAwWhcNMzYwNzE2MjM1OTU5WjCByjELMAkGA1\
UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQLExZWZXJpU2l\
nbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJpU2lnbiwgSW5j\
LiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxWZXJpU2lnbiBDb\
GFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0aG9yaXR5IC0gRz\
UwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCvJAgIKXo1nmAMqudLO07\
cfLw8RRy7K+D+KQL5VwijZIUVJ/XxrcgxiV0i6CqqpkKzj/i5Vbext0uz/o9+B1fs\
70PbZmIVYc9gDaTY3vjgw2IIPVQT60nKWVSFJuUrjxuf6/WhkcIzSdhDY2pSS9KP6\
HBRTdGJaXvHcPaz3BJ023tdS1bTlr8Vd6Gw9KIl8q8ckmcY5fQGBO+QueQA5N06tR\
n/Arr0PO7gi+s3i+z016zy9vA9r911kTMZHRxAy3QkGSGT2RT+rCpSx4/VBEnkjWN\
HiDxpg8v+R70rfk/Fla4OndTRQ8Bnc+MUCH7lP59zuDMKz10/NIeWiu5T6CUVAgMB\
AAGjgbIwga8wDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAQYwbQYIKwYBB\
QUHAQwEYTBfoV2gWzBZMFcwVRYJaW1hZ2UvZ2lmMCEwHzAHBgUrDgMCGgQUj+XTGo\
asjY5rw8+AatRIGCx7GS4wJRYjaHR0cDovL2xvZ28udmVyaXNpZ24uY29tL3ZzbG9\
nby5naWYwHQYDVR0OBBYEFH/TZafC3ey78DAJ80M5+gKvMzEzMA0GCSqGSIb3DQEB\
BQUAA4IBAQCTJEowX2LP2BqYLz3q3JktvXf2pXkiOOzEp6B4Eq1iDkVwZMXnl2Ytm\
Al+X6/WzChl8gGqCBpH3vn5fJJaCGkgDdk+bW48DW7Y5gaRQBi5+MHt39tBquCWIM\
nNZBU4gcmU7qKEKQsTb47bDN0lAtukixlE0kF6BWlKWE9gyn6CagsCqiUXObXbf+e\
EZSqVir2G3l6BFoMtEMze/aiCKm0oHw0LxOXnGiYZ4fQRbxC1lfznQgUy286dUV4o\
tp6F01vvpX1FQHKOtw5rDgb7MzVIcbidJ4vEZV8NhnacRHr2lVz2XTIIM6RUthg/a\
FzyQkqFOFSDX9HoLPKsEdao7WNq\
\n-----END CERTIFICATE-----\n";

/**********************************************************************************************
***********************************************************************************************
													Device Identity Certificates: Modify for your AWS IoT Thing
***********************************************************************************************
***********************************************************************************************/

/****************************************
(somecode)-certificate.pem.crt - Amazon signed PEM sertificate.
*****************************************/

//This Client cert is example. Use own instead.
uint8_t clientCRT[] = "\
-----BEGIN CERTIFICATE-----\n\
MIIDWjCCAkKgAwIBAgIVAMzXgq65I1qEyFjWe9geIhrbIjlPMA0GCSqGSIb3DQEB\
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0xNjEwMjUwNzE0\
MzVaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCiIGcivHAYe9hiSGih\
sh+6+nX6WY5sx3m4TtH2+GyUyXSjhj24ToTY2uipaMaduo//JaRNlOgWRM0DDwNY\
v5CAWxnBh0NHWKa9vCvtmFWVkGbIycBIqIONKM9kzO53Z3Rl0j0qDJf/gvRkhYCt\
hUnSJbgETnBlkIAAo8mIrIbd6SImP85rNU0Xm6x/lxYEMAddDfgGQ/+kZGI6apmh\
wlzgqDI8iHr6Ql2QSKyT10mY+qeoFXfe7lkfVcLR57QL/VyVrwBF2aUbFZiex9Kc\
rGQesGatI2PEWArEEExH8hZMMcE2eT938hLCihLqkAyZUVVYgUhxl5EHd2xLaaIN\
yrNPAgMBAAGjYDBeMB8GA1UdIwQYMBaAFGlHhhcpVTr/BFyLRP2rnr9/cV5UMB0G\
A1UdDgQWBBT5vIj8MZ7YNrhcDw+QNQaf3MD30jAMBgNVHRMBAf8EAjAAMA4GA1Ud\
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAV6YoS8AIE1PNe6R8h0jZ5CXW\
e34x9g/Ic6N8maGggJDIR/VHd8ZpwH5eDFkcGNrmF3sBqq2fAj/AFu0OxyPzLXFZ\
vugmPoX4070yF6SrBVI4CsB40opr+9MoKfgzGmRnKV5evesLkzijPDR9fcgMg2rQ\
3XEkbqzSrPnJJXn1qAqG/Hm9PzQYt5SV3y6CzgrHahfEz0Ngir9iQ3XTkXs2Rjhu\
Rz8NGGPg4EsMTrVYC7buB3vpZb/wnS8+ZBPLQ6ETc35SZxmgXdnpZ2PMPDW+E/L/\
f1skwyCmdwsJ07eC9Ec+HN2xfft5k7M4Za1PbEUI+MCmkSDPZR2qJNz1p3LGRw==\
\n-----END CERTIFICATE-----\n";


/**********************************************************************************************
***********************************************************************************************
													Private Key: Modify for your AWS IoT Thing
***********************************************************************************************
***********************************************************************************************/


/********************************************************************8****************************************
nucleo.key.pem - client key generated according to readme.
**************************************************************************************************************/

//This Client Key is example. Use own instead.
uint8_t clientKey[] ="\
-----BEGIN RSA PRIVATE KEY-----\n\
MIIEowIBAAKCAQEAoiBnIrxwGHvYYkhoobIfuvp1+lmObMd5uE7R9vhslMl0o4Y9\
uE6E2NroqWjGnbqP/yWkTZToFkTNAw8DWL+QgFsZwYdDR1imvbwr7ZhVlZBmyMnA\
SKiDjSjPZMzud2d0ZdI9KgyX/4L0ZIWArYVJ0iW4BE5wZZCAAKPJiKyG3ekiJj/O\
azVNF5usf5cWBDAHXQ34BkP/pGRiOmqZocJc4KgyPIh6+kJdkEisk9dJmPqnqBV3\
3u5ZH1XC0ee0C/1cla8ARdmlGxWYnsfSnKxkHrBmrSNjxFgKxBBMR/IWTDHBNnk/\
d/ISwooS6pAMmVFVWIFIcZeRB3dsS2miDcqzTwIDAQABAoIBACg92LuzgDNjkhsb\
E/WGq/+SKXSBhCuV+612ywD9Op5Xvr7UFD/KJYlaFMPwANSnuRRAuJ6VJmJYo3Zt\
5IvDyM9DTYpO07FC3Ohda53m4N9l301ZXoPqZ/TCu2+uukYjBK49V/c29wdx7s2A\
oabwXZluyVUwTw+2pT8DaIOnJzavP5HcNVJGYt+qt8StjNwmKftpnKWIBrL31wTO\
Kgl9S8JRP9IhT1RgVR3wKulJdH32j/pgn9mZP3B/a/4Cr+/55XZUFvxnDPlakTmk\
OQS8kC7rFjF/T+BA/NILNU6xrtTwFN7eTbffZT9zp/K3iG7qncBISoTlqrd3zhwG\
3Ti1bzECgYEA803xTcoj4Ew/uOfEg7UMSElrmDrAD89+wHyziXkN6Vp7eNYDuOMo\
4LQMV+beYWoDoNo/4JQ/HDSGMi0P/grKzvW0H5uvmea/HKmN/Ilske/0Le6uAd+t\
w0eudAE4LD5vFU8B4WXScjmE/F+5Ovy/EvAR2olo5T76/H7ScxcMjacCgYEAqpYW\
VTfGGoC1HNmpqV5/urVXnuZOOLYnRcsKsa1do9QHA+k3KmcNAA7//vp9JtPQLAIW\
tWzhXGVgLxC6OEy9UY1Ccj5Uw8wt53TpeIRgTeL0m2BveZm92vnjK0rhjGgUIZbP\
OFRsYFxPvWppnV9GAFQJ+TofugHzZvkgtWIv8hkCgYBmDV5Wk6ACt9jOlSBfYjRZ\
qbogqxveRdlTobqowgbsx1Ac+h+rkFSYE81NnX/Pemk1MfYzG9tw2DMlnrMjiqFQ\
t8yqqWG5ewjUW+Y7c+T/PZe9IG0KSikXTNzGubA3FqT/Whle0pe345p9RSVrsZHv\
vpSuho5iAc3C1Osu7Q8N5wKBgEZAlWX3GEDl7LC6+2JjJptP/4vTMTet3LKjkf3m\
df/4XANCUpPF6NazVr49jrkk1kCpg4yoEI+quFfpvadeA0HIuSqvfN0+A1GlFlmp\
ureY1j//ESm1JTk/XE0CA619V30VzLVYH2H34mcRoflLuVp9QbZAN7y0/PbVdqD8\
lN5RAoGBAKWasSzHWuruNGBfNRWh2+jQTobE6RgaqlCm+KemIEPlAwS0MOC/hiIF\
hkM479ikPXhdRDpfC4hx5nBgqGF+srNfI4plbV2aqduAK9QN94JJiWFSip+z54oY\
+uGeT3140qDMcuQv4+gOn1y0yGw6xLpFtJZEtKpxCnLDt4YGDnKQ\
-----END RSA PRIVATE KEY-----\n";
