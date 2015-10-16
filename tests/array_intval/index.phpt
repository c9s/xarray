--TEST--
Check array_intval on index array
--FILE--
<?php
$a = array( "1", "2", "3", "10", 100 => "20");
$b = array_intval($a);
print_r($b);
foreach ($b as $val) {
    echo gettype($val), PHP_EOL;
}
--EXPECT--
Array
(
    [0] => 1
    [1] => 2
    [2] => 3
    [3] => 10
    [4] => 20
)
integer
integer
integer
integer
integer
