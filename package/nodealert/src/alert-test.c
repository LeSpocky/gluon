#include <stdio.h>

#include "alert.h"

int main() {
	printf("%s\n---\n", json_object_to_json_string_ext(alertme(), 0));
}
