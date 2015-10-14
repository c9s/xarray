--TEST--
Check for non-indexed array
--FILE--
<?php
$ret = array_is_indexed(array( 0 => "a", "foo" => "b" ));
echo $ret == false ? "ok" : "fail";
--EXPECT--
ok
