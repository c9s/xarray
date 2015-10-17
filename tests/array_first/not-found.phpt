--TEST--
Check array_first not found should return null
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
});
print_r($b);
--EXPECT--
