--TEST--
Check array_pluck
--FILE--
<?php
$a = array(
    array( 'name' => "John" ),
    array( 'name' => "Mary" ),
    array( 'name' => "Lisa" ),
);
$a = array_pluck($a, 'name');
print_r($a);
--EXPECT--
Array
(
    [0] => John
    [1] => Mary
    [2] => Lisa
)
