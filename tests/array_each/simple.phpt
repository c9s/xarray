--TEST--
Check array_each
--FILE--
<?php
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
--EXPECT--
Array
(
    [0] => John
    [1] => Mary
    [2] => Lisa
)
