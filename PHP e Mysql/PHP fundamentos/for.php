<?php
echo "Soma dos numeros \n";
$soma = 0;

for ($x = 0;$x < 10; $x ++){
    $soma = $soma + $x;
}
echo "A soma e igual: $soma \n";

echo "---------------------------------\n";

echo "Tabuado do 2";
$numT = 2;

echo "\n";

for ($i = 1; $i <11; $i ++){
    echo "2 * $i" .  " = " . $numT * $i. "\n";
}


?>