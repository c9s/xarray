--TEST--
Check array_remove
--FILE--
<?php
$a = array(
    "foo" => "a",
    "bar" => "b",
    "zoo" => "c",
);
// delete "foo" key from $a
array_remove($a, function($key, $value) {
    return $value === "b";
});
print_r($a);
--EXPECT--
Array
(
    [foo] => a
    [zoo] => c
)
