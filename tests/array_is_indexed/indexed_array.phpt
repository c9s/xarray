--TEST--
Check array_is_indexed
--FILE--
<?php
$ret = array_is_indexed(array( 0 => "a", 1 => "b" ));
echo $ret ? "ok\n" : "fail\n";
--EXPECT--
ok
