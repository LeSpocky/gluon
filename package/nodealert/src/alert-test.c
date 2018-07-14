#include <stdio.h>

#include "ffffm.h"

int main() {
	printf("%s\n---\n", json_object_to_json_string_ext(alertme(), 0));
}
