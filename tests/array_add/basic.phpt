--TEST--
Check array_add index
--FILE--
<?php
$a = array(
    0 => "a",
    2 => "c",
);
array_add($a, 1, "b");
print_r($a);
--EXPECT--
Array
(
    [0] => a
    [2] => c
    [1] => b
)
