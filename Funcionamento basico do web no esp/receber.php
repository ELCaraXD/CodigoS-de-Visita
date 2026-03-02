<?php

$dados = file_get_contents("php://input"); //lugar onde vem as conversa do esp
$json = json_decode($dados, true);//transformando o json do esp e array

$temperatura = $json["temperatura"];//pegando so o valor da array

$con = new mysqli("localhost","root","","teste");//conectando no msqli

$sql = "INSERT INTO sensores (temperatura) VALUES ('$temperatura')";//colocando no banco de dados o valor que ta chegando
$con->query($sql);

echo "OK";

?>