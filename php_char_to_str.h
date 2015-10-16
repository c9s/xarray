#ifndef PHP_CHAR_TO_STR_H
#define PHP_CHAR_TO_STR_H

#include <php.h>
#include <php_variables.h>
#include "standard/php_string.h"

PHPAPI int php_char_to_str_cs(char *str, uint len, char from, char *to, int to_len, zval *result);

#endif
