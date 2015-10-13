--TEST--
Check array_is_indexed
--FILE--
<?php
$ret = array_is_indexed(array( 0 => "a", "foo" => "b" ));
echo $ret ? "ok\n" : "fail\n";
--EXPECT--
fail
