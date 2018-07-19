#include <json-c/json.h>
#include <respondd.h>
#include <uci.h>
#include <string.h>

#include "alert.h"

int get_nodealert_isactive(void) {
	const char *c = NULL;
	struct uci_context *ctx = NULL;
	struct uci_package *p = NULL;
	int zero_if_active_is_true = -2;

	ctx = uci_alloc_context();
	if (!ctx)
		goto error;
	ctx->flags &= ~UCI_FLAG_STRICT;

	if (uci_load(ctx, "nodealert", &p))
		goto error;

	struct uci_section *s = uci_lookup_section(ctx, p, "nodealert");
	if (!s)
		goto error;

	c = uci_lookup_option_string(ctx, p, "active");
	if (! c)
		goto error;
	printf("uci looked up: %s\n", c);

	zero_if_active_is_true = strncmp(c, "true", 4);

error:
	if (ctx) {
		if (p)
			uci_unload(ctx, p);
		uci_free_context(ctx);
	}

	return zero_if_active_is_true;
}

struct json_object *alertme(void) {
	struct json_object *ret = json_object_new_object();

	if (!ret)
		return NULL;

	int isactive_nodealert = get_nodealert_isactive();
	struct json_object *j_isactive = json_object_new_boolean(isactive_nodealert == 0 ? 1 : 0);

	if (!j_isactive)
		return NULL;

	json_object_object_add(ret, "nodealert_active", j_isactive);

	return ret;
}

