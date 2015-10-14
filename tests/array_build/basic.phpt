--TEST--
Check array_build basic
--FILE--
<?php
$a = array(
    array("name" => "John", "id" => "j"),
    array("name" => "Mary", "id" => "m"),
    array("name" => "Lisa", "id" => "l"),
);
$b = array_build($a, function($key, $value) use(&$b) {
    return array($value['id'], $value['name']);
});
print_r($b);
--EXPECT--
Array
(
    [j] => John
    [m] => Mary
    [l] => Lisa
)
