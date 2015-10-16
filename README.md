xarray
========================================================

The missing array functions you are looking for.


[![Build Status](https://travis-ci.org/c9s/xarray.svg)](https://travis-ci.org/c9s/xarray)


## Requirement

- PHP 5.5.x
- PHP 5.6.x

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
array array_pluck(array $array, [long $key | string $key])
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
mixed array_first(array $array, callable $callable)
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
    return $key == 1;
});
print_r($a);
```

Outputs:

```
Mary
```



### array\_each

```php
void array_each(array $array, callable $builder)
```

`array_each` iterates the array keys and values through a callback.

If false value is returned from the callback, the iteration will stop.

##### FAQ

> `array_each` - this is just a foreach with an isolated scope and function
overhead on every iteration, why would I want that?

`array_each` is pretty much like `array_map` except it doesn't return any value.

Sometimes you want to pass a iteration handler from external, and `array_map`
is a way to do this, but `array_map` only pass array value to your closure.

`array_each` is faster than `array_map` because it's simpler and it doesn't
return value.

##### Examples

```php
$a = array(
    0 => "John",
    1 => "Mary",
    2 => "Lisa",
);
$b = [];
array_each($a, function($key, $value) use(&$b) {
    $b[$key] = $value;
});
print_r($b);
```

The example above will output:

```
Array
(
    [0] => John
    [1] => Mary
    [2] => Lisa
)
```










### array\_build

```php
array array_build(array $array, callable $builder)
```

`array_build` builds the new array with new keys and new values. 


##### Builder

The array builder must return a key-value pair to insert a new item.
If null value or false value is returned, the entry will be ignored.

```php
list($newKey, $newValue) = $builder($key, $value);
```

##### Examples

```php
$a = array(
    array("name" => "John", "id" => "j"),
    array("name" => "Mary", "id" => "m"),
    array("name" => "Lisa", "id" => "l"),
);
$b = array();
$b = array_build($a, function($key, $value) {
    return array($value['id'], $value['name']);
});
print_r($b);
```

The example above will output:

```
Array
(
    [j] => John
    [m] => Mary
    [l] => Lisa
)
```




### array\_keys\_prefix

```php
array array_keys_prefix(array $array, string $prefix)
```

`array_keys_prefix` returns a new array by prepending prefix string from the original keys.

##### Examples

```php
$a = array(
    "name" => "John",
    "id" => "j",
    "phone" => "+886975123123",
);
$b = array_keys_prefix($a, "my_");
print_r($b);
```

The example above will output:

```
Array
(
    [my_name] => John
    [my_id] => j
    [my_phone] => +886975123123
)
```




### array\_keys\_suffix

```php
array array_keys_suffix(array $array, string $suffix)
```

Append suffix string to the keys.

##### Examples

```php
$a = array(
    "create" => 1,
    "update" => 2,
);
$b = array_keys_suffix($a, "_at");
print_r($b);
```

The example above will output:

```
Array
(
    [create_at] => 1
    [update_at] => 2
)
```



### array\_keys\_replace

```php
array_keys_replace(array & $array, array $replacements)
```

Replace all occurrences of the keys in the array with the replacement string

##### Examples

```php
$a = array(
    "id" => 12345,
    "name" => "John",
    "phone" => "+886975123123",
    "created_at" => "2012-01-01",
    "updated_at" => "2012-02-02",
);
array_keys_replace($a, array(
    "_at" => "_on",
));
print_r($a);
```

The example above will output:

```
Array
(
    [name] => John
    [phone] => +886975123123
    [created_on] => 2012-01-01
    [updated_on] => 2012-02-02
    [id] => 12345
)
```




### array\_add

```php
string array_add(array $array, string|long $key, $elemnt)
```

`array_add` add the new element into the given array only when the key is not set.

##### FAQ

> `array_add` - why do I need the overhead of a function call, when I can do `$a[*key*] = *value*`

The reason has been described in the document:  array_add only adds data when the key doesn't exist.

You can treat it as a set operation, you used to write:

```php
$array = [];
if (!isset($array["key"])) {
    $array["key"] = 10;
}
if (!isset($array["key"])) {
    $array["key"] = 20;
}
```

Now you can write:

```php
$array = [  ];
array_add($array, "key", 10);   // key => 10, return true
array_add($array, "key", 20);   // key => 10 still, return false
```



##### Examples

```php
$a = array(
    "foo" => "a",
    "zoo" => "c",
);
array_add($a, "bar", "b");
print_r($a);
```

The example above will output:

```
Array
(
    [foo] => a
    [zoo] => c
    [bar] => b
)
```





### array\_remove

```php
string array_remove(array $array, callable $callback)
```

`array_remove` remove the element from the given array by the callback.

##### FAQ

> `array_remove` is just `array_filter`, why do I need another function for that?

`array_filter` only passes value to the callback. in PHP 5.6, there is a new option to pass both key and value,
however PHP 5.5 doesn't have this option.

Implementing this function in extension make it possible.

##### Examples

```php
$a = array(
    "foo" => "a",
    "bar" => "b",
    "zoo" => "c",
);
// delete "foo" key from $a
array_remove($a, function($key, $value) {
    return $value === "b";
});
print_r($a);
```

The example above will output:

```
Array
(
    [foo] => a
    [zoo] => c
)
```
















## FAQ

Q: Why `array_keys_join` and `array_keys_prefix` are named with `keys` in plural.

A: The `keys` means the operation works on multiple keys, not just one of them.






