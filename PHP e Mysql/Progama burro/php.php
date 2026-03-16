<?php
    $ser = '127.0.0.1'; //nosso servidor
    $usu = 'root'; //usuario mysql
    $sen = ''; //senha
    $banDa = 'doideira'; //nome do banco

    $con = mysqli_connect( $ser, $usu, $sen, $banDa) or die(mysqli_connect_error()); //Seleciona o banco aulaban

    $a = $_POST["A"]; 
    $b = $_POST["B"]; 
    $c = $_POST["C"]; 

        
    $sql = "SELECT * FROM doide WHERE A = '$a' AND B = '$b' AND C = '$c' ";

        
        $res_A = $con->query("SELECT A FROM doide ORDER BY id DESC LIMIT 1");
        $row_A = $result->fetch_assoc();
        echo json_encode($row_A);

        $res_B = $con->query("SELECT B FROM doide ORDER BY id DESC LIMIT 1");
        $row_B = $result->fetch_assoc();
        echo json_encode($row_B);

        $res_C = $con->query("SELECT C FROM doide ORDER BY id DESC LIMIT 1");
        $row_C = $result->fetch_assoc();
        echo json_encode($row_C);

?>