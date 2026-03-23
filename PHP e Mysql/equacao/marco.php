<?php
extract($_POST);
if(isset($b1)) {
        $d = ($b *$b)-(4*$a*$c);
        if($d < 0) $texto = "não é definido como real <br/>";
        if($d == 0) $texto = "x1 => x2 = ".-$b/(2*$a)."<br/>";
        if($d > 0){
            $x1 = (-$b + sqrt($d))/(2*$a);
            $x2 = (-$b - sqrt($d))/(2*$a);
            $texto = "x1 = ".$x1." x2= ".$x2."<br/>";
        }
        
	 
         $arq=fopen("resultados.txt","a");
	   fwrite($arq,$texto);
	   fclose($arq);
}
if(isset($b2)){
           $arq = fopen ("resultados.txt","r");
	     $texto = fgets ($arq,1000);
	     fclose ($arq);
}
echo $texto."<br/>";
echo "<a href= 'marco.html'>voltar</a>";
?>
