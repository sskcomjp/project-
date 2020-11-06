<!DOCTYPE html>
  <html lang = "ja">
  <head>
  <meta charset = "UTF-8">
  <title>ソーシャルディスタンス</title>
  </head>
  <body>

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
