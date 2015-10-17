--TEST--
Check array_first not found should return default value
--FILE--
<?php
$a = array(
    0 => "a",
    1 => "b",
    2 => "c"
);
$b = array_first($a, function($key, $value) {
    if ($value == "d") {
        return true;
    }
    return false;
}, "not-found-default");
print_r($b);
--EXPECT--
not-found-default
