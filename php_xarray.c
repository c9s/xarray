#include "php_xarray.h"
#include "Zend/zend_hash.h"
#include "standard/php_smart_str.h"

PHP_MINIT_FUNCTION(xarray);
PHP_MSHUTDOWN_FUNCTION(xarray);
PHP_MINFO_FUNCTION(xarray);

#if COMPILE_DL_XARRAY
ZEND_GET_MODULE(xarray)
#endif


ZEND_BEGIN_ARG_INFO_EX(arginfo_array_target, 0, 0, 1)
    ZEND_ARG_ARRAY_INFO(0, array, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_array_keys_join, 0, 0, 1)
    ZEND_ARG_ARRAY_INFO(0, array, 0)
    ZEND_ARG_INFO(0, delim)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_array_pluck, 0, 0, 2)
    ZEND_ARG_ARRAY_INFO(0, array, 0)
    ZEND_ARG_INFO(0, plurk key)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_array_first, 0, 0, 2)
    ZEND_ARG_ARRAY_INFO(0, array, 0)
    ZEND_ARG_INFO(0, callable_tester)
ZEND_END_ARG_INFO()



static const zend_function_entry xarray_functions[] = {
    PHP_FE(array_is_indexed, arginfo_array_target)
    PHP_FE(array_is_assoc, arginfo_array_target)
    PHP_FE(array_keys_join, arginfo_array_keys_join)
    PHP_FE(array_pluck, arginfo_array_pluck)
    PHP_FE(array_first, arginfo_array_first)
    PHP_FE(array_each, NULL)
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


PHP_FUNCTION(array_each) {

    zval *array;
    zend_fcall_info fci;
    zend_fcall_info_cache fci_cache = empty_fcall_info_cache;
    zval *default_value;

    zval **args[2];
    zval *retval;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "af|z", &array, &fci, &fci_cache, &default_value) == FAILURE) {
        RETURN_FALSE;
    }

    fci.retval_ptr_ptr = &retval;
    fci.param_count = 2;
    fci.no_separation = 0;

    HashTable *arr_hash;
    HashPosition pos;
    zval **arr_value;

    arr_hash = Z_ARRVAL_P(array);

    zval *arr_key = NULL;
    MAKE_STD_ZVAL(arr_key);
    zend_hash_internal_pointer_reset_ex(arr_hash, &pos);
    while (zend_hash_get_current_data_ex(arr_hash, (void **)&arr_value, &pos) == SUCCESS) {
        zend_hash_get_current_key_zval_ex(arr_hash, arr_key, &pos);
        args[0] = &arr_key;
        args[1] = arr_value;
        fci.params = args;
        zend_call_function(&fci, &fci_cache TSRMLS_CC);
        zend_hash_move_forward_ex(arr_hash, &pos);
    }
}






PHP_FUNCTION(array_first) {

    zval *array;
    zend_fcall_info fci;
    zend_fcall_info_cache fci_cache = empty_fcall_info_cache;
    zval *default_value;

    zval **args[2];
    zval *retval;


    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "af|z", &array, &fci, &fci_cache, &default_value) == FAILURE) {
        RETURN_FALSE;
    }


    // configure callable parameters
    fci.retval_ptr_ptr = &retval;
    fci.param_count = 2;
    fci.no_separation = 0;


    HashTable *arr_hash;
    HashPosition pos;
    zval **arr_value;

    arr_hash = Z_ARRVAL_P(array);

    int numelems = zend_hash_num_elements(arr_hash);
    if (numelems == 0) {
        if (default_value != NULL) {
            *return_value = *default_value;
            zval_copy_ctor(return_value);
        } else {
            RETURN_NULL();
        }
    }

    zval *arr_key = NULL;
    MAKE_STD_ZVAL(arr_key);
    // array_init(return_value);
    zend_hash_internal_pointer_reset_ex(arr_hash, &pos);
    while (zend_hash_get_current_data_ex(arr_hash, (void **)&arr_value, &pos) == SUCCESS) {
        zend_hash_get_current_key_zval_ex(arr_hash, arr_key, &pos);
        args[0] = &arr_key;
        args[1] = arr_value;
        fci.params = args;

        if (zend_call_function(&fci, &fci_cache TSRMLS_CC) == SUCCESS && retval) {
            if (Z_TYPE_P(retval) == IS_BOOL && Z_BVAL_P(retval)) {
                Z_ADDREF_PP(arr_value);
                *return_value = **arr_value;
                zval_copy_ctor(return_value);
                return;
                // add_next_index_zval(return_value, *arr_value);
            }
        }
        zend_hash_move_forward_ex(arr_hash, &pos);
    }

    if (default_value) {
        *return_value = *default_value;
        zval_copy_ctor(return_value);
        return;
    }
    RETURN_NULL();
}





PHP_FUNCTION(array_pluck) {
    zval *array;
    zval *plurk_key = NULL;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "az", &array, &plurk_key) == FAILURE) {
        RETURN_FALSE;
    }

    array_init(return_value);

    HashTable *arr_hash = Z_ARRVAL_P(array);
    HashPosition pos;
    zval **item;
    int numelems, i = 0;
    int str_len;

    numelems = zend_hash_num_elements(arr_hash);
    if (numelems == 0) {
        return;
    }

    zval **tmp;
    if (Z_TYPE_P(plurk_key) == IS_STRING) {
        for (zend_hash_internal_pointer_reset_ex(arr_hash, &pos);
            zend_hash_get_current_data_ex(arr_hash, (void**) &item, &pos) == SUCCESS; 
            zend_hash_move_forward_ex(arr_hash, &pos)) 
        {
            if (Z_TYPE_PP(item) != IS_ARRAY) {
                continue;
            }
            if (zend_hash_find(Z_ARRVAL_PP(item), Z_STRVAL_P(plurk_key), Z_STRLEN_P(plurk_key) + 1, (void **) &tmp) == SUCCESS) {
                Z_ADDREF_PP(tmp);
                add_next_index_zval(return_value, *tmp);
            }
        }
    } else if (Z_TYPE_P(plurk_key) == IS_LONG) {

        for (zend_hash_internal_pointer_reset_ex(arr_hash, &pos);
            zend_hash_get_current_data_ex(arr_hash, (void**) &item, &pos) == SUCCESS; 
            zend_hash_move_forward_ex(arr_hash, &pos)) 
        {
            if (Z_TYPE_PP(item) != IS_ARRAY) {
                continue;
            }
            if (zend_hash_index_find(Z_ARRVAL_PP(item), Z_LVAL_P(plurk_key), (void **) &tmp) == SUCCESS) {
                Z_ADDREF_PP(tmp);
                add_next_index_zval(return_value, *tmp);
            }
        }

    }

}


PHP_FUNCTION(array_keys_join) {
    zval *array;

    // for php7
    // zend_ulong num_key;
    // zend_string *key;
    char *key;
    uint key_len;
    ulong num_index;

    zval *delim = NULL;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a|z", &array, &delim) == FAILURE) {
        RETURN_FALSE;
    }





    HashTable *arr_hash = Z_ARRVAL_P(array);
    HashPosition pos;
    zval **item;
    int numelems, i = 0;
    int str_len;


    zval tmp_val;
    smart_str      implstr = {0};


    numelems = zend_hash_num_elements(arr_hash);
    if (numelems == 0) {
        RETURN_EMPTY_STRING();
    }



    if (delim == NULL) {
        MAKE_STD_ZVAL(delim);
#define _IMPL_EMPTY ""
        ZVAL_STRINGL(delim, _IMPL_EMPTY, sizeof(_IMPL_EMPTY) - 1, 0);
    }

    zval *arr_key = NULL;
    MAKE_STD_ZVAL(arr_key);

    for (zend_hash_internal_pointer_reset_ex(arr_hash, &pos);
        zend_hash_get_current_data_ex(arr_hash, (void**) &item, &pos) == SUCCESS; 
        zend_hash_move_forward_ex(arr_hash, &pos)) 
    {
        zend_hash_get_current_key_zval_ex(arr_hash, arr_key, &pos);

        /*
        if (zend_hash_get_current_key_ex(arr_hash, &key, &key_len, &num_index, 0, &pos) == HASH_KEY_IS_LONG) {
            RETURN_FALSE;
        }
        */

        switch ((arr_key)->type) {
            case IS_STRING:
                smart_str_appendl(&implstr, Z_STRVAL_P(arr_key), Z_STRLEN_P(arr_key));
                break;

            case IS_LONG: {
                char stmp[MAX_LENGTH_OF_LONG + 1];
                str_len = slprintf(stmp, sizeof(stmp), "%ld", Z_LVAL_P(arr_key));
                smart_str_appendl(&implstr, stmp, str_len);
            }
                break;

            case IS_BOOL:
                if (Z_LVAL_P(arr_key) == 1) {
                    smart_str_appendl(&implstr, "1", sizeof("1")-1);
                }
                break;

            case IS_NULL:
                break;

            case IS_DOUBLE: {
                char *stmp;
                str_len = spprintf(&stmp, 0, "%.*G", (int) EG(precision), Z_DVAL_P(arr_key));
                smart_str_appendl(&implstr, stmp, str_len);
                efree(stmp);
            }
                break;

            case IS_OBJECT: {
                int copy;
                zval expr;
                zend_make_printable_zval(arr_key, &expr, &copy);
                smart_str_appendl(&implstr, Z_STRVAL(expr), Z_STRLEN(expr));
                if (copy) {
                    zval_dtor(&expr);
                }
            }
                break;

            default:
                tmp_val = *arr_key;
                zval_copy_ctor(&tmp_val);
                convert_to_string(&tmp_val);
                smart_str_appendl(&implstr, Z_STRVAL(tmp_val), Z_STRLEN(tmp_val));
                zval_dtor(&tmp_val);
                break;
        }

        if (++i != numelems) {
            smart_str_appendl(&implstr, Z_STRVAL_P(delim), Z_STRLEN_P(delim));
        }
    }

    smart_str_0(&implstr);

    if (implstr.len) {
        RETURN_STRINGL(implstr.c, implstr.len, 0);
    } else {
        smart_str_free(&implstr);
        RETURN_EMPTY_STRING();
    }
}



