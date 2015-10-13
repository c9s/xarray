--TEST--
Check array_keys_join
--FILE--
<?php
echo array_keys_join(array("foo" => 0, "bar" => 0), "-");
--EXPECT--
foo-bar
