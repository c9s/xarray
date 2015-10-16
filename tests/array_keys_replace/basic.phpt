--TEST--
Check array_keys_replace basic
--FILE--
<?php
$a = array(
    "id" => 12345,
    "name" => "John",
    "phone" => "+886975123123",
    "created_at" => "2012-01-01",
    "updated_at" => "2012-02-02",
);
array_keys_replace($a, array(
    "_at" => "_on",
));
print_r($a);
--EXPECT--
Array
(
    [name] => John
    [phone] => +886975123123
    [created_on] => 2012-01-01
    [updated_on] => 2012-02-02
    [id] => 12345
)
