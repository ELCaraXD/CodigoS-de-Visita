<?php


$num1 = $_POST["n1"];
$num2 = $_POST["n2"];
$num3 = $_POST["n3"];
$bot = $_POST["divertir"];

echo $num1;
echo $num2;
echo $num3;
echo $bot;

?>
<?php

$num1 = (float) $_POST["n1"];
$num2 = (float) $_POST["n2"];
$num3 = (float) $_POST["n3"];

$soma = $num1 + $num2 + $num3;
$subt = $num1 - $num2 - $num3;

$pot = pow($num1, $num2);
$raiz = sqrt($num3);

$men = 0;
$mai = 0;

if ($num1 > $num2 && $num1 > $num3){
    $mai = $num1;
}else{
    if ($num2 > $num3){
        $mai = $num2;
    }else{
        $mai = $num3;
    }
}

if ($num1 < $num2 && $num1 < $num3){
    $men = $num1;
}else{
    if ($num2 < $num3){
        $men = $num2;
    }else{
        $men = $num3;
    }
}

if (isset($_POST['caulcular'])) {
    echo "Soma de todos os numeros = $soma<br>";
    echo "Subtração de todos os numeros = $subt<br>";
    echo "Potencia do primeiro numero elevado pelo segundo = $pot<br>";
    echo "Raiz quadrada do terceiro numero = $raiz<br>";
    echo "Maior numero  $mai<br>";
    echo "Menor numero $men<br>";
}
if (isset($_POST['divertir'])) {
        
}



?>