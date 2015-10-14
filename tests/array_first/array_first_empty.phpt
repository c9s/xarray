--TEST--
Check array_first with empty array
--FILE--
<?php
$a = array();
$a = array_first($a, function($key, $value) {
    if ($key !== 1) {
        return true;
    }
    return false;
}, 10);
print_r($a);
--EXPECT--
10
