--TEST--
Check array_keys_prefix basic
--FILE--
<?php
$a = array(
    "name" => "John",
    "id" => "j",
    "phone" => "+886975123123",
);
$b = array_keys_prefix($a, "my_");
print_r($b);
--EXPECT--
Array
(
    [my_name] => John
    [my_id] => j
    [my_phone] => +886975123123
)
