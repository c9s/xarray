xarray
========================================================

The missing array functions you are looking for.


[![Build Status](https://travis-ci.org/c9s/xarray.svg)](https://travis-ci.org/c9s/xarray)


### array\_is\_indexed

```php
bool array_is_indexed(array $array)
```

`array_is_indexed` function returns true when all the keys in the given array are
long integer keys. (0, 1, 3, 100).


### array\_is\_assoc

```php
bool array_is_assoc(array $array)
```

`array_is_assoc` function returns true when all the keys in the given array are
string type keys. ('foo', 'bar').


### array\_keys\_join

```php
string array_keys_join(array $array, [string $delim])
```

`array_keys_join` is useful when generating cache keys from array keys, this
reduces the overhead of using `join('-', array_keys($array));`.

#### Examples

```php
echo array_keys_join([ "foo" => 1, "bar" => 123], "-");
echo array_keys_join([ "a" => 1, "b" => 123, "c" => "kkk" ], "-");
```

Which outputs:

```
foo-bar
a-b-c
```

### array\_pluck

```php
string array_pluck(array $array, [long $key | string $key])
```

`array_pluck` is used for extracting element from array inside the given array.

#### Examples

Extracting element by string key:


```php
$a = array(
    array( 'name' => "John" ),
    array( 'name' => "Mary" ),
    array( 'name' => "Lisa" ),
);
$a = array_pluck($a, 'name');
print_r($a);
```

Outputs:

```
Array
(
    [0] => John
    [1] => Mary
    [2] => Lisa
)
```

Extracting element by index key:

```php
$a = array(
    array(2 => "John"),
    array(2 => "Mary"),
    array(2 => "Lisa"),
);
$a = array_pluck($a, 2);
print_r($a);
```

Outputs:

```
Array
(
    [0] => John
    [1] => Mary
    [2] => Lisa
)
```
