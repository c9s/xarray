--TEST--
Check array_first
--FILE--
<?php
$a = array(
    0 => "John",
    1 => "Mary",
    2 => "Lisa",
);
$b = array_first($a, function($key, $value) {
    if ($key !== 1) {
        return true;
    }
    return false;
});
print_r($b);
--EXPECT--
John
