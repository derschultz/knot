#pragma once

#include <binary.h>

typedef struct key_parameters {
	// DNSSEC fields
	uint16_t flags;
	uint8_t protocol;
	uint8_t algorithm;
	dnssec_binary_t public_key;

	// DNSSEC wire format
	dnssec_binary_t rdata;

	// Hashes
	const char *key_id;
	uint16_t keytag;

	// Key information
	unsigned bit_size;

	// Private key in PEM
	dnssec_binary_t pem;
} key_parameters_t;

/*

RSA-SHA-256

rsa.    IN      DNSKEY  256 3 8 AwEAAarbp0oh52KuF0SwXoSgMNRpcW/uPKCKQAu8NyYaY+e9G29rh7eqK1hqp7skbSvKKlItgAaFdDxZvPiD4AzBHQk= ;{id = 1506 (zsk), size = 512b}
rsa.    IN      DS      1506 8 2 253b099ff47b02c6ffa52695a30a94c6681c56befe0e71a5077d6f79514972f9

Modulus: qtunSiHnYq4XRLBehKAw1Glxb+48oIpAC7w3Jhpj570bb2uHt6orWGqnuyRtK8oqUi2ABoV0PFm8+IPgDMEdCQ==
PublicExponent: AQAB
PrivateExponent: MiItniUAngXzMeaGdWgDq/AcpvlCtOCcFlVt4TJRKkfp8DNRSxIxG53NNlOFkp1W00iLHqYC2GrH1qkKgT9l+Q==
Prime1: 3sZmM+5FKFy5xaRt0n2ZQOZ2C+CoKzVil6/al9LmYVs=
Prime2: xFcNWSIW6v8dDL2JQ1kxFDm/8RVeUSs1BNXXnvCjBGs=
Exponent1: WuUwhjfN1+4djlrMxHmisixWNfpwI1Eg7Ss/UXsnrMk=
Exponent2: vfMqas1cNsXRqP3Fym6D2Pl2BRuTQBv5E1B/ZrmQPTk=
Coefficient: Q10z43cA3hkwOkKsj5T0W5jrX97LBwZoY5lIjDCa4+M=

-----BEGIN PRIVATE KEY-----
MIIBVAIBADANBgkqhkiG9w0BAQEFAASCAT4wggE6AgEAAkEAqtunSiHnYq4XRLBe
hKAw1Glxb+48oIpAC7w3Jhpj570bb2uHt6orWGqnuyRtK8oqUi2ABoV0PFm8+IPg
DMEdCQIDAQABAkAyIi2eJQCeBfMx5oZ1aAOr8Bym+UK04JwWVW3hMlEqR+nwM1FL
EjEbnc02U4WSnVbTSIsepgLYasfWqQqBP2X5AiEA3sZmM+5FKFy5xaRt0n2ZQOZ2
C+CoKzVil6/al9LmYVsCIQDEVw1ZIhbq/x0MvYlDWTEUOb/xFV5RKzUE1dee8KME
awIgWuUwhjfN1+4djlrMxHmisixWNfpwI1Eg7Ss/UXsnrMkCIQC98ypqzVw2xdGo
/cXKboPY+XYFG5NAG/kTUH9muZA9OQIgQ10z43cA3hkwOkKsj5T0W5jrX97LBwZo
Y5lIjDCa4+M=
-----END PRIVATE KEY-----

*/

static const key_parameters_t SAMPLE_RSA_KEY = {
	.flags = 256,
	.protocol = 3,
	.algorithm = 8,
	.public_key = { .size = 68, .data = (uint8_t []) {
		0x03, 0x01, 0x00, 0x01, 0xaa, 0xdb, 0xa7, 0x4a, 0x21, 0xe7,
		0x62, 0xae, 0x17, 0x44, 0xb0, 0x5e, 0x84, 0xa0, 0x30, 0xd4,
		0x69, 0x71, 0x6f, 0xee, 0x3c, 0xa0, 0x8a, 0x40, 0x0b, 0xbc,
		0x37, 0x26, 0x1a, 0x63, 0xe7, 0xbd, 0x1b, 0x6f, 0x6b, 0x87,
		0xb7, 0xaa, 0x2b, 0x58, 0x6a, 0xa7, 0xbb, 0x24, 0x6d, 0x2b,
		0xca, 0x2a, 0x52, 0x2d, 0x80, 0x06, 0x85, 0x74, 0x3c, 0x59,
		0xbc, 0xf8, 0x83, 0xe0, 0x0c, 0xc1, 0x1d, 0x09,
	}},
	.rdata = { .size = 72, .data = (uint8_t []) {
		0x01, 0x00, 0x03, 0x08,
		0x03, 0x01, 0x00, 0x01, 0xaa, 0xdb, 0xa7, 0x4a, 0x21, 0xe7,
		0x62, 0xae, 0x17, 0x44, 0xb0, 0x5e, 0x84, 0xa0, 0x30, 0xd4,
		0x69, 0x71, 0x6f, 0xee, 0x3c, 0xa0, 0x8a, 0x40, 0x0b, 0xbc,
		0x37, 0x26, 0x1a, 0x63, 0xe7, 0xbd, 0x1b, 0x6f, 0x6b, 0x87,
		0xb7, 0xaa, 0x2b, 0x58, 0x6a, 0xa7, 0xbb, 0x24, 0x6d, 0x2b,
		0xca, 0x2a, 0x52, 0x2d, 0x80, 0x06, 0x85, 0x74, 0x3c, 0x59,
		0xbc, 0xf8, 0x83, 0xe0, 0x0c, 0xc1, 0x1d, 0x09,
	}},
	.key_id = "6d2b811564be0200132ef67d281de19e65ab3d1d",
	.keytag = 1506,
	.bit_size = 512,
	.pem = { .size = 522, .data = (uint8_t []) {
		0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x42, 0x45, 0x47, 0x49, 0x4e,
		0x20, 0x50, 0x52, 0x49, 0x56, 0x41, 0x54, 0x45, 0x20, 0x4b,
		0x45, 0x59, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x0a, 0x4d, 0x49,
		0x49, 0x42, 0x56, 0x41, 0x49, 0x42, 0x41, 0x44, 0x41, 0x4e,
		0x42, 0x67, 0x6b, 0x71, 0x68, 0x6b, 0x69, 0x47, 0x39, 0x77,
		0x30, 0x42, 0x41, 0x51, 0x45, 0x46, 0x41, 0x41, 0x53, 0x43,
		0x41, 0x54, 0x34, 0x77, 0x67, 0x67, 0x45, 0x36, 0x41, 0x67,
		0x45, 0x41, 0x41, 0x6b, 0x45, 0x41, 0x71, 0x74, 0x75, 0x6e,
		0x53, 0x69, 0x48, 0x6e, 0x59, 0x71, 0x34, 0x58, 0x52, 0x4c,
		0x42, 0x65, 0x0a, 0x68, 0x4b, 0x41, 0x77, 0x31, 0x47, 0x6c,
		0x78, 0x62, 0x2b, 0x34, 0x38, 0x6f, 0x49, 0x70, 0x41, 0x43,
		0x37, 0x77, 0x33, 0x4a, 0x68, 0x70, 0x6a, 0x35, 0x37, 0x30,
		0x62, 0x62, 0x32, 0x75, 0x48, 0x74, 0x36, 0x6f, 0x72, 0x57,
		0x47, 0x71, 0x6e, 0x75, 0x79, 0x52, 0x74, 0x4b, 0x38, 0x6f,
		0x71, 0x55, 0x69, 0x32, 0x41, 0x42, 0x6f, 0x56, 0x30, 0x50,
		0x46, 0x6d, 0x38, 0x2b, 0x49, 0x50, 0x67, 0x0a, 0x44, 0x4d,
		0x45, 0x64, 0x43, 0x51, 0x49, 0x44, 0x41, 0x51, 0x41, 0x42,
		0x41, 0x6b, 0x41, 0x79, 0x49, 0x69, 0x32, 0x65, 0x4a, 0x51,
		0x43, 0x65, 0x42, 0x66, 0x4d, 0x78, 0x35, 0x6f, 0x5a, 0x31,
		0x61, 0x41, 0x4f, 0x72, 0x38, 0x42, 0x79, 0x6d, 0x2b, 0x55,
		0x4b, 0x30, 0x34, 0x4a, 0x77, 0x57, 0x56, 0x57, 0x33, 0x68,
		0x4d, 0x6c, 0x45, 0x71, 0x52, 0x2b, 0x6e, 0x77, 0x4d, 0x31,
		0x46, 0x4c, 0x0a, 0x45, 0x6a, 0x45, 0x62, 0x6e, 0x63, 0x30,
		0x32, 0x55, 0x34, 0x57, 0x53, 0x6e, 0x56, 0x62, 0x54, 0x53,
		0x49, 0x73, 0x65, 0x70, 0x67, 0x4c, 0x59, 0x61, 0x73, 0x66,
		0x57, 0x71, 0x51, 0x71, 0x42, 0x50, 0x32, 0x58, 0x35, 0x41,
		0x69, 0x45, 0x41, 0x33, 0x73, 0x5a, 0x6d, 0x4d, 0x2b, 0x35,
		0x46, 0x4b, 0x46, 0x79, 0x35, 0x78, 0x61, 0x52, 0x74, 0x30,
		0x6e, 0x32, 0x5a, 0x51, 0x4f, 0x5a, 0x32, 0x0a, 0x43, 0x2b,
		0x43, 0x6f, 0x4b, 0x7a, 0x56, 0x69, 0x6c, 0x36, 0x2f, 0x61,
		0x6c, 0x39, 0x4c, 0x6d, 0x59, 0x56, 0x73, 0x43, 0x49, 0x51,
		0x44, 0x45, 0x56, 0x77, 0x31, 0x5a, 0x49, 0x68, 0x62, 0x71,
		0x2f, 0x78, 0x30, 0x4d, 0x76, 0x59, 0x6c, 0x44, 0x57, 0x54,
		0x45, 0x55, 0x4f, 0x62, 0x2f, 0x78, 0x46, 0x56, 0x35, 0x52,
		0x4b, 0x7a, 0x55, 0x45, 0x31, 0x64, 0x65, 0x65, 0x38, 0x4b,
		0x4d, 0x45, 0x0a, 0x61, 0x77, 0x49, 0x67, 0x57, 0x75, 0x55,
		0x77, 0x68, 0x6a, 0x66, 0x4e, 0x31, 0x2b, 0x34, 0x64, 0x6a,
		0x6c, 0x72, 0x4d, 0x78, 0x48, 0x6d, 0x69, 0x73, 0x69, 0x78,
		0x57, 0x4e, 0x66, 0x70, 0x77, 0x49, 0x31, 0x45, 0x67, 0x37,
		0x53, 0x73, 0x2f, 0x55, 0x58, 0x73, 0x6e, 0x72, 0x4d, 0x6b,
		0x43, 0x49, 0x51, 0x43, 0x39, 0x38, 0x79, 0x70, 0x71, 0x7a,
		0x56, 0x77, 0x32, 0x78, 0x64, 0x47, 0x6f, 0x0a, 0x2f, 0x63,
		0x58, 0x4b, 0x62, 0x6f, 0x50, 0x59, 0x2b, 0x58, 0x59, 0x46,
		0x47, 0x35, 0x4e, 0x41, 0x47, 0x2f, 0x6b, 0x54, 0x55, 0x48,
		0x39, 0x6d, 0x75, 0x5a, 0x41, 0x39, 0x4f, 0x51, 0x49, 0x67,
		0x51, 0x31, 0x30, 0x7a, 0x34, 0x33, 0x63, 0x41, 0x33, 0x68,
		0x6b, 0x77, 0x4f, 0x6b, 0x4b, 0x73, 0x6a, 0x35, 0x54, 0x30,
		0x57, 0x35, 0x6a, 0x72, 0x58, 0x39, 0x37, 0x4c, 0x42, 0x77,
		0x5a, 0x6f, 0x0a, 0x59, 0x35, 0x6c, 0x49, 0x6a, 0x44, 0x43,
		0x61, 0x34, 0x2b, 0x4d, 0x3d, 0x0a, 0x2d, 0x2d, 0x2d, 0x2d,
		0x2d, 0x45, 0x4e, 0x44, 0x20, 0x50, 0x52, 0x49, 0x56, 0x41,
		0x54, 0x45, 0x20, 0x4b, 0x45, 0x59, 0x2d, 0x2d, 0x2d, 0x2d,
		0x2d, 0x0a,
	}},
};

/*

DSA-NSEC3

dsa.    IN      DNSKEY  257 3 6 ALRB7JW8C3f9YYqtgW088YMR28u/tUD9ON0VGCNjvi6OFbTvuIP+Jaen8uFCpXy7KPPUXZQiDZrCvX5Vt0nvdAuHBk2Lqi9pn5nq3aWpOeer+L9o83KQ+jmCk1v1m+ryiNOCR1g14hmD6zF3x3Vncg0hrYRplMBB8UlgQKuCoJ2ktA9pTQYai0/TvXKVlqpXi41enyKld/E1Y7yDNjxDgGPROctlj8cYbs+6yjT4BbiQWG8qPCRsbfgqiLzjplQbGGkrSD08ozntKLD7XDCrq9RJP8gm ;{id = 1203 (ksk), size = 512b}
dsa.    IN      DS      1203 6 1 27a6bdcd62d80264ad71126adf9f2200e3c87f2f

Prime(p): tUD9ON0VGCNjvi6OFbTvuIP+Jaen8uFCpXy7KPPUXZQiDZrCvX5Vt0nvdAuHBk2Lqi9pn5nq3aWpOeer+L9o8w==
Subprime(q): tEHslbwLd/1hiq2BbTzxgxHby78=
Base(g): cpD6OYKTW/Wb6vKI04JHWDXiGYPrMXfHdWdyDSGthGmUwEHxSWBAq4KgnaS0D2lNBhqLT9O9cpWWqleLjV6fIg==
Private_value(x): NpQs24BFAPht/ohmNN9ioqQ1hiE=
Public_value(y): pXfxNWO8gzY8Q4Bj0TnLZY/HGG7Puso0+AW4kFhvKjwkbG34Koi846ZUGxhpK0g9PKM57Siw+1wwq6vUST/IJg==

-----BEGIN PRIVATE KEY-----
MIHGAgEAMIGoBgcqhkjOOAQBMIGcAkEAtUD9ON0VGCNjvi6OFbTvuIP+Jaen8uFC
pXy7KPPUXZQiDZrCvX5Vt0nvdAuHBk2Lqi9pn5nq3aWpOeer+L9o8wIVALRB7JW8
C3f9YYqtgW088YMR28u/AkBykPo5gpNb9Zvq8ojTgkdYNeIZg+sxd8d1Z3INIa2E
aZTAQfFJYECrgqCdpLQPaU0GGotP071ylZaqV4uNXp8iBBYCFDaULNuARQD4bf6I
ZjTfYqKkNYYh
-----END PRIVATE KEY-----

*/

static const key_parameters_t SAMPLE_DSA_KEY = {
	.flags = 257,
	.protocol = 3,
	.algorithm = 6,
	.public_key = { .size = 213, .data = (uint8_t []) {
		0x00, 0xb4, 0x41, 0xec, 0x95, 0xbc, 0x0b, 0x77, 0xfd, 0x61,
		0x8a, 0xad, 0x81, 0x6d, 0x3c, 0xf1, 0x83, 0x11, 0xdb, 0xcb,
		0xbf, 0xb5, 0x40, 0xfd, 0x38, 0xdd, 0x15, 0x18, 0x23, 0x63,
		0xbe, 0x2e, 0x8e, 0x15, 0xb4, 0xef, 0xb8, 0x83, 0xfe, 0x25,
		0xa7, 0xa7, 0xf2, 0xe1, 0x42, 0xa5, 0x7c, 0xbb, 0x28, 0xf3,
		0xd4, 0x5d, 0x94, 0x22, 0x0d, 0x9a, 0xc2, 0xbd, 0x7e, 0x55,
		0xb7, 0x49, 0xef, 0x74, 0x0b, 0x87, 0x06, 0x4d, 0x8b, 0xaa,
		0x2f, 0x69, 0x9f, 0x99, 0xea, 0xdd, 0xa5, 0xa9, 0x39, 0xe7,
		0xab, 0xf8, 0xbf, 0x68, 0xf3, 0x72, 0x90, 0xfa, 0x39, 0x82,
		0x93, 0x5b, 0xf5, 0x9b, 0xea, 0xf2, 0x88, 0xd3, 0x82, 0x47,
		0x58, 0x35, 0xe2, 0x19, 0x83, 0xeb, 0x31, 0x77, 0xc7, 0x75,
		0x67, 0x72, 0x0d, 0x21, 0xad, 0x84, 0x69, 0x94, 0xc0, 0x41,
		0xf1, 0x49, 0x60, 0x40, 0xab, 0x82, 0xa0, 0x9d, 0xa4, 0xb4,
		0x0f, 0x69, 0x4d, 0x06, 0x1a, 0x8b, 0x4f, 0xd3, 0xbd, 0x72,
		0x95, 0x96, 0xaa, 0x57, 0x8b, 0x8d, 0x5e, 0x9f, 0x22, 0xa5,
		0x77, 0xf1, 0x35, 0x63, 0xbc, 0x83, 0x36, 0x3c, 0x43, 0x80,
		0x63, 0xd1, 0x39, 0xcb, 0x65, 0x8f, 0xc7, 0x18, 0x6e, 0xcf,
		0xba, 0xca, 0x34, 0xf8, 0x05, 0xb8, 0x90, 0x58, 0x6f, 0x2a,
		0x3c, 0x24, 0x6c, 0x6d, 0xf8, 0x2a, 0x88, 0xbc, 0xe3, 0xa6,
		0x54, 0x1b, 0x18, 0x69, 0x2b, 0x48, 0x3d, 0x3c, 0xa3, 0x39,
		0xed, 0x28, 0xb0, 0xfb, 0x5c, 0x30, 0xab, 0xab, 0xd4, 0x49,
		0x3f, 0xc8, 0x26,
	}},
	.rdata = { .size = 217, .data = (uint8_t []) {
		0x01, 0x01, 0x03, 0x06,
		0x00, 0xb4, 0x41, 0xec, 0x95, 0xbc, 0x0b, 0x77, 0xfd, 0x61,
		0x8a, 0xad, 0x81, 0x6d, 0x3c, 0xf1, 0x83, 0x11, 0xdb, 0xcb,
		0xbf, 0xb5, 0x40, 0xfd, 0x38, 0xdd, 0x15, 0x18, 0x23, 0x63,
		0xbe, 0x2e, 0x8e, 0x15, 0xb4, 0xef, 0xb8, 0x83, 0xfe, 0x25,
		0xa7, 0xa7, 0xf2, 0xe1, 0x42, 0xa5, 0x7c, 0xbb, 0x28, 0xf3,
		0xd4, 0x5d, 0x94, 0x22, 0x0d, 0x9a, 0xc2, 0xbd, 0x7e, 0x55,
		0xb7, 0x49, 0xef, 0x74, 0x0b, 0x87, 0x06, 0x4d, 0x8b, 0xaa,
		0x2f, 0x69, 0x9f, 0x99, 0xea, 0xdd, 0xa5, 0xa9, 0x39, 0xe7,
		0xab, 0xf8, 0xbf, 0x68, 0xf3, 0x72, 0x90, 0xfa, 0x39, 0x82,
		0x93, 0x5b, 0xf5, 0x9b, 0xea, 0xf2, 0x88, 0xd3, 0x82, 0x47,
		0x58, 0x35, 0xe2, 0x19, 0x83, 0xeb, 0x31, 0x77, 0xc7, 0x75,
		0x67, 0x72, 0x0d, 0x21, 0xad, 0x84, 0x69, 0x94, 0xc0, 0x41,
		0xf1, 0x49, 0x60, 0x40, 0xab, 0x82, 0xa0, 0x9d, 0xa4, 0xb4,
		0x0f, 0x69, 0x4d, 0x06, 0x1a, 0x8b, 0x4f, 0xd3, 0xbd, 0x72,
		0x95, 0x96, 0xaa, 0x57, 0x8b, 0x8d, 0x5e, 0x9f, 0x22, 0xa5,
		0x77, 0xf1, 0x35, 0x63, 0xbc, 0x83, 0x36, 0x3c, 0x43, 0x80,
		0x63, 0xd1, 0x39, 0xcb, 0x65, 0x8f, 0xc7, 0x18, 0x6e, 0xcf,
		0xba, 0xca, 0x34, 0xf8, 0x05, 0xb8, 0x90, 0x58, 0x6f, 0x2a,
		0x3c, 0x24, 0x6c, 0x6d, 0xf8, 0x2a, 0x88, 0xbc, 0xe3, 0xa6,
		0x54, 0x1b, 0x18, 0x69, 0x2b, 0x48, 0x3d, 0x3c, 0xa3, 0x39,
		0xed, 0x28, 0xb0, 0xfb, 0x5c, 0x30, 0xab, 0xab, 0xd4, 0x49,
		0x3f, 0xc8, 0x26,
	}},
	.keytag = 1203,
	.key_id = "141b2d54837494735b53795bf0c1579bd9e12754",
	.bit_size = 512,
	.pem = { .size = 327, .data = (uint8_t []) {
		0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x42, 0x45, 0x47, 0x49, 0x4e,
		0x20, 0x50, 0x52, 0x49, 0x56, 0x41, 0x54, 0x45, 0x20, 0x4b,
		0x45, 0x59, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x0a, 0x4d, 0x49,
		0x48, 0x47, 0x41, 0x67, 0x45, 0x41, 0x4d, 0x49, 0x47, 0x6f,
		0x42, 0x67, 0x63, 0x71, 0x68, 0x6b, 0x6a, 0x4f, 0x4f, 0x41,
		0x51, 0x42, 0x4d, 0x49, 0x47, 0x63, 0x41, 0x6b, 0x45, 0x41,
		0x74, 0x55, 0x44, 0x39, 0x4f, 0x4e, 0x30, 0x56, 0x47, 0x43,
		0x4e, 0x6a, 0x76, 0x69, 0x36, 0x4f, 0x46, 0x62, 0x54, 0x76,
		0x75, 0x49, 0x50, 0x2b, 0x4a, 0x61, 0x65, 0x6e, 0x38, 0x75,
		0x46, 0x43, 0x0a, 0x70, 0x58, 0x79, 0x37, 0x4b, 0x50, 0x50,
		0x55, 0x58, 0x5a, 0x51, 0x69, 0x44, 0x5a, 0x72, 0x43, 0x76,
		0x58, 0x35, 0x56, 0x74, 0x30, 0x6e, 0x76, 0x64, 0x41, 0x75,
		0x48, 0x42, 0x6b, 0x32, 0x4c, 0x71, 0x69, 0x39, 0x70, 0x6e,
		0x35, 0x6e, 0x71, 0x33, 0x61, 0x57, 0x70, 0x4f, 0x65, 0x65,
		0x72, 0x2b, 0x4c, 0x39, 0x6f, 0x38, 0x77, 0x49, 0x56, 0x41,
		0x4c, 0x52, 0x42, 0x37, 0x4a, 0x57, 0x38, 0x0a, 0x43, 0x33,
		0x66, 0x39, 0x59, 0x59, 0x71, 0x74, 0x67, 0x57, 0x30, 0x38,
		0x38, 0x59, 0x4d, 0x52, 0x32, 0x38, 0x75, 0x2f, 0x41, 0x6b,
		0x42, 0x79, 0x6b, 0x50, 0x6f, 0x35, 0x67, 0x70, 0x4e, 0x62,
		0x39, 0x5a, 0x76, 0x71, 0x38, 0x6f, 0x6a, 0x54, 0x67, 0x6b,
		0x64, 0x59, 0x4e, 0x65, 0x49, 0x5a, 0x67, 0x2b, 0x73, 0x78,
		0x64, 0x38, 0x64, 0x31, 0x5a, 0x33, 0x49, 0x4e, 0x49, 0x61,
		0x32, 0x45, 0x0a, 0x61, 0x5a, 0x54, 0x41, 0x51, 0x66, 0x46,
		0x4a, 0x59, 0x45, 0x43, 0x72, 0x67, 0x71, 0x43, 0x64, 0x70,
		0x4c, 0x51, 0x50, 0x61, 0x55, 0x30, 0x47, 0x47, 0x6f, 0x74,
		0x50, 0x30, 0x37, 0x31, 0x79, 0x6c, 0x5a, 0x61, 0x71, 0x56,
		0x34, 0x75, 0x4e, 0x58, 0x70, 0x38, 0x69, 0x42, 0x42, 0x59,
		0x43, 0x46, 0x44, 0x61, 0x55, 0x4c, 0x4e, 0x75, 0x41, 0x52,
		0x51, 0x44, 0x34, 0x62, 0x66, 0x36, 0x49, 0x0a, 0x5a, 0x6a,
		0x54, 0x66, 0x59, 0x71, 0x4b, 0x6b, 0x4e, 0x59, 0x59, 0x68,
		0x0a, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x45, 0x4e, 0x44, 0x20,
		0x50, 0x52, 0x49, 0x56, 0x41, 0x54, 0x45, 0x20, 0x4b, 0x45,
		0x59, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x0a,
	}},
};

/*

ECDSA-P256-SHA256

ecdsa. IN DNSKEY 256 3 13 8uD7C4THTM/w7uhryRSToeE/jKT78/p853RX0L5EwrZrSLBubLPiBw7g bvUP6SsIga5ZQ4CSAxNmYA/gZsuXzA==
ecdsa. IN DS 5345 13 1 954103AC7C43810CE9F414E80F30AB1CBE49B236
ecdsa. IN DS 5345 13 2 BAC2107036E735B50F85006CE409A19A3438CAB272E70769EBDA032239A3D0CA

PrivateKey: iyLIPdk3DOIxVmmSYlmTstbtUPiVlEyDX46psyCwNVQ=

-----BEGIN PRIVATE KEY-----
MIGUAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBHoweAIBAQQhAIsiyD3ZNwziMVZp
kmJZk7LW7VD4lZRMg1+OqbMgsDVUoAoGCCqGSM49AwEHoUQDQgAE8uD7C4THTM/w
7uhryRSToeE/jKT78/p853RX0L5EwrZrSLBubLPiBw7gbvUP6SsIga5ZQ4CSAxNm
YA/gZsuXzA==
-----END PRIVATE KEY-----

*/

static const key_parameters_t SAMPLE_ECDSA_KEY = {
	.flags = 256,
	.protocol = 3,
	.algorithm = 13,
	.public_key = { .size = 64, .data = (uint8_t []) {
		0xf2, 0xe0, 0xfb, 0x0b, 0x84, 0xc7, 0x4c, 0xcf, 0xf0, 0xee,
		0xe8, 0x6b, 0xc9, 0x14, 0x93, 0xa1, 0xe1, 0x3f, 0x8c, 0xa4,
		0xfb, 0xf3, 0xfa, 0x7c, 0xe7, 0x74, 0x57, 0xd0, 0xbe, 0x44,
		0xc2, 0xb6, 0x6b, 0x48, 0xb0, 0x6e, 0x6c, 0xb3, 0xe2, 0x07,
		0x0e, 0xe0, 0x6e, 0xf5, 0x0f, 0xe9, 0x2b, 0x08, 0x81, 0xae,
		0x59, 0x43, 0x80, 0x92, 0x03, 0x13, 0x66, 0x60, 0x0f, 0xe0,
		0x66, 0xcb, 0x97, 0xcc,
	}},
	.rdata = { .size = 68, .data = (uint8_t []) {
		0x01, 0x00, 0x03, 0x0d,
		0xf2, 0xe0, 0xfb, 0x0b, 0x84, 0xc7, 0x4c, 0xcf, 0xf0, 0xee,
		0xe8, 0x6b, 0xc9, 0x14, 0x93, 0xa1, 0xe1, 0x3f, 0x8c, 0xa4,
		0xfb, 0xf3, 0xfa, 0x7c, 0xe7, 0x74, 0x57, 0xd0, 0xbe, 0x44,
		0xc2, 0xb6, 0x6b, 0x48, 0xb0, 0x6e, 0x6c, 0xb3, 0xe2, 0x07,
		0x0e, 0xe0, 0x6e, 0xf5, 0x0f, 0xe9, 0x2b, 0x08, 0x81, 0xae,
		0x59, 0x43, 0x80, 0x92, 0x03, 0x13, 0x66, 0x60, 0x0f, 0xe0,
		0x66, 0xcb, 0x97, 0xcc,
	}},
	.keytag = 5345,
	.key_id = "47fd10011e76cc6741af586041eae5519465fc8d",
	.bit_size = 256,
	.pem = { .size = 262, .data = (uint8_t []) {
		0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x42, 0x45, 0x47, 0x49, 0x4e,
		0x20, 0x50, 0x52, 0x49, 0x56, 0x41, 0x54, 0x45, 0x20, 0x4b,
		0x45, 0x59, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x0a, 0x4d, 0x49,
		0x47, 0x55, 0x41, 0x67, 0x45, 0x41, 0x4d, 0x42, 0x4d, 0x47,
		0x42, 0x79, 0x71, 0x47, 0x53, 0x4d, 0x34, 0x39, 0x41, 0x67,
		0x45, 0x47, 0x43, 0x43, 0x71, 0x47, 0x53, 0x4d, 0x34, 0x39,
		0x41, 0x77, 0x45, 0x48, 0x42, 0x48, 0x6f, 0x77, 0x65, 0x41,
		0x49, 0x42, 0x41, 0x51, 0x51, 0x68, 0x41, 0x49, 0x73, 0x69,
		0x79, 0x44, 0x33, 0x5a, 0x4e, 0x77, 0x7a, 0x69, 0x4d, 0x56,
		0x5a, 0x70, 0x0a, 0x6b, 0x6d, 0x4a, 0x5a, 0x6b, 0x37, 0x4c,
		0x57, 0x37, 0x56, 0x44, 0x34, 0x6c, 0x5a, 0x52, 0x4d, 0x67,
		0x31, 0x2b, 0x4f, 0x71, 0x62, 0x4d, 0x67, 0x73, 0x44, 0x56,
		0x55, 0x6f, 0x41, 0x6f, 0x47, 0x43, 0x43, 0x71, 0x47, 0x53,
		0x4d, 0x34, 0x39, 0x41, 0x77, 0x45, 0x48, 0x6f, 0x55, 0x51,
		0x44, 0x51, 0x67, 0x41, 0x45, 0x38, 0x75, 0x44, 0x37, 0x43,
		0x34, 0x54, 0x48, 0x54, 0x4d, 0x2f, 0x77, 0x0a, 0x37, 0x75,
		0x68, 0x72, 0x79, 0x52, 0x53, 0x54, 0x6f, 0x65, 0x45, 0x2f,
		0x6a, 0x4b, 0x54, 0x37, 0x38, 0x2f, 0x70, 0x38, 0x35, 0x33,
		0x52, 0x58, 0x30, 0x4c, 0x35, 0x45, 0x77, 0x72, 0x5a, 0x72,
		0x53, 0x4c, 0x42, 0x75, 0x62, 0x4c, 0x50, 0x69, 0x42, 0x77,
		0x37, 0x67, 0x62, 0x76, 0x55, 0x50, 0x36, 0x53, 0x73, 0x49,
		0x67, 0x61, 0x35, 0x5a, 0x51, 0x34, 0x43, 0x53, 0x41, 0x78,
		0x4e, 0x6d, 0x0a, 0x59, 0x41, 0x2f, 0x67, 0x5a, 0x73, 0x75,
		0x58, 0x7a, 0x41, 0x3d, 0x3d, 0x0a, 0x2d, 0x2d, 0x2d, 0x2d,
		0x2d, 0x45, 0x4e, 0x44, 0x20, 0x50, 0x52, 0x49, 0x56, 0x41,
		0x54, 0x45, 0x20, 0x4b, 0x45, 0x59, 0x2d, 0x2d, 0x2d, 0x2d,
		0x2d, 0x0a,
	}},
};
