--TEST--
Check array_keys_suffix basic
--FILE--
<?php
$a = array(
    "name" => "John",
    "id" => "j",
    "phone" => "+886975123123",
);
$b = array_keys_suffix($a, "_string");
print_r($b);
--EXPECT--
Array
(
    [name_string] => John
    [id_string] => j
    [phone_string] => +886975123123
)
