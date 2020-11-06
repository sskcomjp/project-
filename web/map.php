<?php


$file_handler=fopen("lat.csv","r");
$lat_array=fgetcsv($file_handler);
fclose("lat.csv");

$file_handler_2=fopen("lng.csv","r");
$lng_array=fgetcsv($file_handler_2);
fclose("lng.csv");

$file_size=count($lat_array)-1;
for($i=0;$i<$file_size;$i++){
print('緯度:');
echo" $lat_array[$i]";
print(' 経度:');
echo" $lng_array[$i]</br>";
}

$current_nom=$file_size;
$info_data_array;
for($i=0;$i<$file_size;$i++){

   for($j=$i;$j>=0;$j--){
    if($lat_array[$i]==$lat_array[$j] and $lng_array[$i]==$lng_array[$j]){
        $current_nom=$current_nom-1;
        break;
       }
    }


    for($k=$current_nom;$k<$file_size;$k++){
       $l=$k-$current_nom;
       $info_data_array[$l][0]=$i;
       $info_data_array[$l][2]=$lat_array[$i];
       $info_data_array[$l][3]=$lng_array[$i];
       if($lat_array[$i]==$lat_array[$k] and $lng_array[$i]==$lng_array[$k]){
         $info_data_array[$l][1]=$info_data_array[$l][1]+1;
          }
        }
}
$info_file_size=count($info_data_array)-1;

for($i=0;$i<$info_file_size;$i++){
    for($j=$i+1;$j<$info_file_size;$j++){
       if($info_data_array[$i][1]>$info_data_array[$j][1]){
                $tmp=$info_data_array[$i];
          $info_data_array[$i]=$info_data_array[$j];
          $info_data_array[$j]=$tmp;
         }
        }
     }

$json_lat_array=json_encode($lat_array);
$json_lng_array=json_encode($lng_array);
$json_info_data_array=json_encode($info_data_array);

?>



<!DOCTYPE html>
  <html lang = "ja">
  <head>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
  <meta charset = "UTF-8">
  <title>ソーシャルディスタンス</title>
  <style>
  #gmap {
    height: 1300px;
    width: 1000px;
  }
  </style>
  </head>
  <body>


  <button>LINEに通知 </button>
  <div id="gmap"></div>

  <script>

  var map;
  function initMap() {
    var target = document.getElementById('gmap');
    var empire = {lat:34.3919 ,lng:135.2912 };
    map = new google.maps.Map(target, {
      center: empire,
      zoom: 14
    });
         map.addListener('drag', function(e){
                           this.panTo(e.latLng); //アニメーションで中心位置を移動
           });
var markers = new Array();
let value = <?php echo $file_size; ?>;
let data_lat_array= <?php echo $json_lat_array; ?>;
let data_lng_array= <?php echo $json_lng_array; ?>;
var data;


//マーカの作成

 for (var i = 0; i < value; i++) {
   let data_lat=parseFloat(data_lat_array[i]);
   let data_lng=parseFloat(data_lng_array[i]);
   data = {lat:data_lat,lng:data_lng};
   markers[i] = new google.maps.Marker({
   position: data,
   map: map
  });
 }

var info_data_array=<?php echo $json_info_data_array; ?>;

 var data = '魔界';

      $('button').click(function(){
        $.ajax({
         type: "GET", //　POSTでも可
         url: "line_send.php?", //　送り先
         data: { 'data': data }, //　渡したいデータ
         dataType : "json", //　データ形式を指定
         scriptCharset: 'UTF-8' //　文字コードを指定
        })
location.href ="http://3.112.225.241/line_send.html";
});



}




 </script>
 <script src="https://maps.googleapis.com/maps/api/js?language=ja&region=JP&key=    AIzaSyCM6ph4cWgk7fkg8YkfKViFwuSnX5uc8sw&callback=initMap" async defer></script>
 <form action = "entry.php" method = "get">
 <input type = "submit" value ="入力フォームに戻る">
 </form>
 </body>
 </html>
