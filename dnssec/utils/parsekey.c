/*  Copyright (C) 2014 CZ.NIC, z.s.p.o. <knot-dns@labs.nic.cz>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <ctype.h>
#include <stdio.h>

#include <dnssec/crypto.h>
#include <dnssec/error.h>
#include <dnssec/kasp.h>

static void usage(void)
{
	fprintf(stderr, "parsekey <kasp-config-dir> <zone-name>\n");
}

static void error(const char *message, int err)
{
	fprintf(stderr, "%s: %s (%d).\n", message, dnssec_strerror(err), err);
}

int main(int argc, char *argv[])
{
	if (argc != 3) {
		usage();
		return 1;
	}

	const char *kasp_dir = argv[1];
	const char *zone_name = argv[2];
	int exit_code = 1;

	dnssec_crypto_init();

	dnssec_kasp_t *kasp = NULL;
	dnssec_kasp_zone_t *zone = NULL;

	int r = dnssec_kasp_init_dir(&kasp);
	if (r != DNSSEC_EOK) {
		error("dnssec_kasp_init_dir()", r);
		goto fail;
	}

	r = dnssec_kasp_open(kasp, kasp_dir);
	if (r != DNSSEC_EOK) {
		error("dnssec_kasp_open_dir()", r);
		goto fail;
	}

	r = dnssec_kasp_load_zone(kasp, zone_name, &zone);
	if (r != DNSSEC_EOK) {
		error("dnssec_kasp_load_zone()", r);
		goto fail;
	}

	dnssec_list_t *keys = dnssec_kasp_zone_get_keys(zone);
	if (!keys) {
		error("dnssec_kasp_zone_get_keys()", DNSSEC_ENOMEM);
		goto fail;
	}

	printf("keytag  ID\n");
	dnssec_list_foreach(item, keys) {
		dnssec_kasp_key_t *key = dnssec_item_get(item);

		const uint8_t *dname = dnssec_key_get_dname(key->key);
		const char *id = dnssec_key_get_id(key->key);
		uint16_t keytag = dnssec_key_get_keytag(key->key);
		printf("%06d  %s\n", keytag, id);
		for (int i = 0; dname[i]; i++) {
			if (isprint(dname[i])) { putchar(dname[i]); }
			else { printf("%02x", dname[i]); }
		}
		printf("\n");
	}

	r = dnssec_kasp_save_zone(kasp, zone);
	if (r != DNSSEC_EOK) {
		error("dnssec_kasp_save_zone()", r);
		goto fail;
	}

	exit_code = 0;

fail:
	dnssec_kasp_zone_free(zone);
	dnssec_kasp_deinit(kasp);
	dnssec_crypto_cleanup();

	return exit_code;
}
