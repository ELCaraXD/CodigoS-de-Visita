<?php
$ser = "127.0.0.1";
$usu = "root";
$sen = "";
$banDa = "aulaban";

$con = mysqli_connect( $ser, $usu, $sen, $banDa);

if ($con){
    echo "conexao ta mec";  
}else{
    echo "Poblema para conectar no Banco";
}

?>