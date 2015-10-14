--TEST--
Check array_add assoc
--FILE--
<?php
$a = array(
    "foo" => "a",
    "zoo" => "c",
);
array_add($a, "bar", "b");
print_r($a);
--EXPECT--
Array
(
    [foo] => a
    [zoo] => c
    [bar] => b
)
