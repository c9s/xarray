#include <php.h>
#include <php_variables.h>
#include "standard/php_string.h"






/**
 * Faster php_char_to_str_ex
 */
PHPAPI int php_char_to_str_cs(char *str, uint len, char from, char *to, int to_len, zval *result)
{
    int char_count = 0;
    int replaced = 0;
    char *source, *target, *tmp, *source_end=str+len, *tmp_end = NULL;

    char * p = str, * e = p + len;
    char * s;
    while ((p = memchr(p, from, (e - p)))) {
        char_count++;
        p++;
    }

    if (char_count == 0) {
        ZVAL_STRINGL(result, str, len, 1);
        return 0;
    }

    Z_STRLEN_P(result) = len + (char_count * (to_len - 1));
    Z_STRVAL_P(result) = target = safe_emalloc(char_count, to_len, len + 1);
    Z_TYPE_P(result) = IS_STRING;

    p = str, e = p + len, s = str;
    while ((p = memchr(p, from, (e - p)))) {
        memcpy(target, s, (p - s));
        target += p - s;
        memcpy(target, to, to_len);
        target += to_len;
        p++;
        s = p;
    }
    if (s < e) {
        memcpy(target, s, (e - s));
        target += e - s;
    }
    *target = 0;
    return replaced;
}

