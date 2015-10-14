--TEST--
Check array_each stop
--FILE--
<?php
$a = array(
    0 => "John",
    1 => "Mary",
    2 => "Lisa",
    3 => "Harry",
);
$b = [];
array_each($a, function($key, $value) use(&$b) {
    $b[$key] = $value;
    if ($key == 2) {
        return false;
    }
});
print_r($b);
--EXPECT--
Array
(
    [0] => John
    [1] => Mary
    [2] => Lisa
)
