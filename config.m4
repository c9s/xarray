PHP_ARG_ENABLE(xarray, whether to enable foo extension support,
  [--enable-xarray Enable xarray extension support])
PHP_NEW_EXTENSION(xarray, php_xarray.c php_char_to_str.c, $ext_shared)
