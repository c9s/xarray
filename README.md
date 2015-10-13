xarray
========================================================

The missing array functions you are looking for.

### `bool array_is_indexed(array $array)`

`array_is_assoc` function returns true when all the keys in the given array are
long integer keys. (0, 1, 3, 100).

### `bool array_is_assoc(array $array)`

`array_is_assoc` function returns true when all the keys in the given array are
string type keys. ('foo', 'bar').

### `string array_keys_join(array $array, [string $delim])`

`array_keys_join` is useful when generating cache keys from array keys, this
reduces the overhead of using `join('-', array_keys($array));`.

Examples:

```php
echo array_keys_join([ "foo" => 1, "bar" => 123], "-");
```
