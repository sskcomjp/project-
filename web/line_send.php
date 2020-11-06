<?php
define('LINE_API_URL'  ,'https://notify-api.line.me/api/notify');
define('LINE_API_TOKEN','dPfhsqsvL8c3egPKoI9Ina8xOmCCgcYXMiNrU50rh7m');





$data_2 =$_GET['data']; //filter_input( INPUT_GET, 'data' );
print($data_2);


$line_send_data=$data_2."付近での接触が多いですね!!";


function post_message($message){

    $data = http_build_query( [ 'message' => $message ], '', '&');

    $options = [
        'http'=> [
            'method'=>'POST',
            'header'=>'Authorization: Bearer ' . LINE_API_TOKEN . "\r\n"
                    . "Content-Type: application/x-www-form-urlencoded\r\n"
                    . 'Content-Length: ' . strlen($data)  . "\r\n" ,
            'content' => $data,
            ]
        ];

    $context = stream_context_create($options);
    $resultJson = file_get_contents(LINE_API_URL, false, $context);
    $resultArray = json_decode($resultJson, true);
    if($resultArray['status'] != 200)  {
        return false;
    }
    return true;
}

post_message($line_send_data);

?>

<!DOCTYPE html>
<html lang = "ja">
<head>
<meta charset = "UTF-8">
<title>ソーシャルディスタンス</title>
</head>
<body>

<h1>LINEに通知が送られました</h1>


</body>
</html>
