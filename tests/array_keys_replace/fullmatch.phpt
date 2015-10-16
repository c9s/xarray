--TEST--
Check array_keys_replace full match
--FILE--
<?php
$a = array(
    "id" => 12345,
    "name" => "John",
    "first_name" => "Lin",
    "phone" => "+886975123123",
    "created_at" => "2012-01-01",
    "updated_at" => "2012-02-02",
);
array_keys_replace($a, array("name" => "nickname"), XARRAY_FULLMATCH);
print_r($a);
--EXPECT--
Array
(
    [id] => 12345
    [first_name] => Lin
    [phone] => +886975123123
    [created_at] => 2012-01-01
    [updated_at] => 2012-02-02
    [nickname] => John
)
