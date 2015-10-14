--TEST--
Check array_each but change the given value
--FILE--
<?php
$a = array(
    0 => "John",
    1 => "Mary",
    2 => "Lisa",
);
array_each($a, function($key, & $value) {
    $value = "123";
});
print_r($a);
--EXPECT--
Array
(
    [0] => 123
    [1] => 123
    [2] => 123
)
