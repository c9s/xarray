#include "php_xarray.h"
#include "Zend/zend_hash.h"

PHP_MINIT_FUNCTION(xarray);
PHP_MSHUTDOWN_FUNCTION(xarray);
PHP_MINFO_FUNCTION(xarray);

#if COMPILE_DL_XARRAY
ZEND_GET_MODULE(xarray)
#endif


ZEND_BEGIN_ARG_INFO_EX(arginfo_array_target, 0, 0, 2)
    ZEND_ARG_ARRAY_INFO(0, environment, 0)
    ZEND_ARG_ARRAY_INFO(0, response, 0)
ZEND_END_ARG_INFO()

static const zend_function_entry xarray_functions[] = {
    PHP_FE(array_is_indexed, NULL)
    PHP_FE(array_is_assoc, NULL)
    PHP_FE_END
};

zend_module_entry xarray_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "Foo",
    xarray_functions, // where you define your functions
    PHP_MINIT(xarray),
    PHP_MSHUTDOWN(xarray),
    NULL, // PHP_RINIT(xarray)
    NULL, // PHP_RSHUTDOWN(xarray)
    PHP_MINFO(xarray),
#if ZEND_MODULE_API_NO >= 20010901
    "0.1",
#endif
    STANDARD_MODULE_PROPERTIES
};

PHP_MINIT_FUNCTION(xarray) {
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(xarray) {
    return SUCCESS;
}

PHP_MINFO_FUNCTION(xarray) {
}


/*
static function is_indexed_array( & $array) {
    $keys = array_keys($array);
    $keys2 = array_filter($keys,'is_numeric');
    return count($keys) == count($keys2);
}
*/
PHP_FUNCTION(array_is_indexed) {
    zval *array;

    // for php7
    // zend_ulong num_key;
    // zend_string *key;
    char *key;
    uint key_len;
    ulong num_index;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &array) == FAILURE) {
        RETURN_FALSE;
    }

    HashTable *arr_hash = Z_ARRVAL_P(array);
    HashPosition pos;
    zval **data;

    for(zend_hash_internal_pointer_reset_ex(arr_hash, &pos);
        zend_hash_get_current_data_ex(arr_hash, (void**) &data, &pos) == SUCCESS; 
        zend_hash_move_forward_ex(arr_hash, &pos)) 
    {
        if (zend_hash_get_current_key_ex(arr_hash, &key, &key_len, &num_index, 0, &pos) == HASH_KEY_IS_STRING) {
            RETURN_FALSE;
        }
    }
    RETURN_TRUE;
}


PHP_FUNCTION(array_is_assoc) {
    zval *array;

    // for php7
    // zend_ulong num_key;
    // zend_string *key;
    char *key;
    uint key_len;
    ulong num_index;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &array) == FAILURE) {
        RETURN_FALSE;
    }

    HashTable *arr_hash = Z_ARRVAL_P(array);
    HashPosition pos;
    zval **data;

    for(zend_hash_internal_pointer_reset_ex(arr_hash, &pos);
        zend_hash_get_current_data_ex(arr_hash, (void**) &data, &pos) == SUCCESS; 
        zend_hash_move_forward_ex(arr_hash, &pos)) 
    {
        if (zend_hash_get_current_key_ex(arr_hash, &key, &key_len, &num_index, 0, &pos) == HASH_KEY_IS_LONG) {
            RETURN_FALSE;
        }
    }
    RETURN_TRUE;
}


