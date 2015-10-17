CHANGELOG
=============================

### Sat Oct 17 19:06:41 2015 - 28d37d4850547a388f09fd09f9d3258633775415

- Fixes memory leak issues.
- Functions deleting keys now return new array instead of manipulating the
  array reference. (e.g. `array_remove`, `array_keys_replace`)

### alpha v0.1

- Added `array_keys_replace` function with `XARRAY_FULLMATCH` constant.
- Added `array_intval` function.
- Added `array_floatval` function.
- Added `array_add` function.
- Added `array_remove` function.

