xarray
========================================================

The missing array functions you are looking for.


[![Build Status](https://travis-ci.org/c9s/xarray.svg)](https://travis-ci.org/c9s/xarray)


## Requirement

PHP 5.5.x, 5.6.x



## Installation

    phpize
    ./configure
    make install

## Functions

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

##### Examples

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

##### Examples

Extracting element by string key:


```php
$a = array(
    array( 'name' => "John", 'phone' => '123456' ),
    array( 'name' => "Mary", 'phone' => '123457' ),
    array( 'name' => "Lisa", 'phone' => '123458' ),
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



### array\_first

```php
string array_first(array $array, callable $callable)
```

`array_first` returns the first element in an array passing a given truth test.

##### Examples

```php
$a = array(
    0 => "John",
    1 => "Mary",
    2 => "Lisa",
);
$a = array_first($a, function($key, $value) {
    if ($key !== 1) {
        return true;
    }
    return false;
});
print_r($a);
```

Outputs:

```
Array
(
    [0] => John
    [1] => Lisa
)
```


