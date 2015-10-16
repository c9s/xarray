#ifndef _PHP_XARRAY_H
#define _PHP_XARRAY_H
#ifdef HAVE_CONFIG_H
    #include "config.h"
#endif

#ifdef ZTS
    #warning php_ext_uv module will *NEVER* be thread-safe
    #include <TSRM.h>
#endif

#include <php.h>

#define PHP_XARRAY_FULLMATCH 1
#define PHP_XARRAY_PARTIALMATCH (1<<1)

extern zend_module_entry xarray_module_entry;

PHP_FUNCTION(array_is_indexed);

PHP_FUNCTION(array_is_assoc);

PHP_FUNCTION(array_keys_join);

PHP_FUNCTION(array_pluck);

PHP_FUNCTION(array_first);

PHP_FUNCTION(array_each);

PHP_FUNCTION(array_intval);

PHP_FUNCTION(array_build);

PHP_FUNCTION(array_remove);

PHP_FUNCTION(array_keys_prefix);

PHP_FUNCTION(array_keys_suffix);

PHP_FUNCTION(array_add);

PHP_FUNCTION(array_keys_replace);


#endif
