--TEST--
Check array_pluck
--FILE--
<?php
$a = array(
    array(2 => "John"),
    array(2 => "Mary"),
    array(2 => "Lisa"),
);
$a = array_pluck($a, 2);
print_r($a);
--EXPECT--
Array
(
    [0] => John
    [1] => Mary
    [2] => Lisa
)
