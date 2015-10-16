--TEST--
Check array_floatval on index array
--FILE--
<?php
$a = array( "1.234", "2.222", "3.333", "10.0", 100 => "20");
$b = array_floatval($a);
print_r($b);
foreach ($b as $val) {
    echo gettype($val), PHP_EOL;
}
--EXPECT--
Array
(
    [0] => 1.234
    [1] => 2.222
    [2] => 3.333
    [3] => 10
    [4] => 20
)
double
double
double
double
double
