PHP_ARG_ENABLE(xarray, whether to enable foo extension support,
  [--enable-xarray Enable xarray extension support])
PHP_NEW_EXTENSION(xarray, php_xarray.c, $ext_shared)
