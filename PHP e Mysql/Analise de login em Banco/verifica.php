<?php
$ser = '127.0.0.1'; //nosso servidor
$usu = 'root'; //usuario mysql
$sen = ''; //senha
$banDa = 'aulaban'; //nome do banco

$con = mysqli_connect( $ser, $usu, $sen, $banDa) or die(mysqli_connect_error()); //Seleciona o banco aulaban


if ($con){
    echo "conexao ta mec";
}else{
    echo "Poblema para conectar no Banco";
}


$login = $_POST["login"];
$senha = $_POST["senha"];

$sql = "SELECT * FROM cadastro WHERE login = '$login' AND senha = '$senha' ";

$selecao = mysqli_query($con,$sql);

$row = mysqli_fetch_array($selecao);

if ($row == ""){
    echo "<br>Login e/ou senha invalidos.<center>";
    echo "<br><br>";
    echo "Volte e tente Novamente";
}else{
    echo "<br><br>Bem Vindo(a) <b>$login</b>";
}

?>