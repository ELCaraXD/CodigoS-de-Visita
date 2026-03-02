<?php

header("Access-Control-Allow-Origin: *");//dando acesso para o site no esp acessar o banco de dados

$con = new mysqli("localhost","root","","teste"); //conversando com o Mysqli

$result = $con->query("SELECT temperatura FROM sensores ORDER BY id DESC LIMIT 1");//chamando a ultima coisa do banco de dados

$row = $result->fetch_assoc();//tranformando em um numero

echo json_encode($row);//mandando como json pro html

?>