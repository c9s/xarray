--TEST--
Check array_intval on assoc array
--FILE--
<?php
$a = array(
    "foo" => "1",
    "bar" => "2",
    "zoo" => "3",
    "xee" => "10",
    "yaa" => "20"
    );
$b = array_intval($a);
print_r($b);
foreach ($b as $val) {
    echo gettype($val), PHP_EOL;
}
--EXPECT--
Array
(
    [foo] => 1
    [bar] => 2
    [zoo] => 3
    [xee] => 10
    [yaa] => 20
)
integer
integer
integer
integer
integer
