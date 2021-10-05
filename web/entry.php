<?php

   $data_lat;
   $data_lng;
   $data_delete;


  if(isset($_GET['comment'])){
           $data_lat = $_GET["comment"];

  }
  if(isset($_GET['comment2'])){
          $data_lng =$_GET["comment2"];
  }

  if(isset($_GET['comment3'])){
          $data_delete =$_GET["comment3"];
  }



  function file_open_write($data,$file){
  $fp = fopen($file, 'ab');

  if ($fp){
          if (flock($fp, LOCK_EX)){
          if (fwrite($fp,  $data.",") === FALSE){
            //  print('ファイル書き込みに失敗しました<br>');
          }else{
             //  print($data.'をファイルに書き込みました<br>');

          }

          flock($fp, LOCK_UN);
      }else{
          print('ファイルロックに失敗しました<br>');
      }
  }

  $flag = fclose($fp);

  if ($flag){
      print('無事クローズしました<br>');
  }else{
      print('クローズに失敗しました<br>');
  }
}

  file_open_write($data_lat,"lat.csv");
  file_open_write($data_lng,"lng.csv");

  ?>

<!DOCTYPE html>
  <html lang = "ja">
  <head>
  <meta charset = "UTF-8">
  <title>ソーシャルディスタンス</title>
  </head>
  <body bgcolor="azure">

 <h1>緯度を入力</h1>
 <form action = "entry.php" method = "get">
 <input type = "text" name = "comment"><br/>
 <input type = "submit" value ="送信">

 <h1>経度を入力</h1>
 <input type = "text" name = "comment2"><br/>
 <input type = "submit" value ="送信">

 </form>
 <form action = "map.php" method = "get">
 <input type = "submit" value ="マップを表示">
 </form>

 <h1>deleteを送るとファイルの中身を削除</h1>
 <form action = "entry.php" method = "get">
 <input type = "text" name = "comment3"><br/>
 <input type = "submit" value ="送信">
 </form>
 </body>
 </html>

<?php
if('delete'==$data_delete){
        $fp = fopen('lat.csv','wb');
        flock($fp, LOCK_EX);
        ftruncate($fp,0);
        flock($fp, LOCK_UN);
        fclose($fp);
        $fp = fopen('lng.csv','wb');
        flock($fp, LOCK_EX);
        ftruncate($fp,0);
        flock($fp, LOCK_UN);
        fclose($fp);
        print('ファイルの中身を削除しました<br>');
}

?>
