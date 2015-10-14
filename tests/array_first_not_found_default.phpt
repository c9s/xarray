--TEST--
Check array_first not found should return default value
--FILE--
<?php
$a = array(
    0 => "a",
    1 => "b",
    2 => "c"
);
$a = array_first($a, function($key, $value) {
    if ($value == "d") {
        return true;
    }
    return false;
}, "x");
print_r($a);
--EXPECT--
x
