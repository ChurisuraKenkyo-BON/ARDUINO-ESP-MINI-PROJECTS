<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="refresh" content="5" >
    <link rel="stylesheet" type="text/css" href="style.css" media="screen"/>

	<title> Sensor Data </title>

</head>

<body>

    <h1>SENSOR DATA</h1>
<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "lightsensordata";


$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT ID, LSDATA, BSTATE,DATE FROM data ORDER BY ID DESC"; 

echo '<table cellspacing="5" cellpadding="5">
      <tr> 
        <th>ID</th> 
        <th>LSDATA</th> 
        <th>BSTATE</thh> 
        <th>DATE</th>      
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_ID = $row["ID"];
        $row_LSDATA = $row["LSDATA"];
        $row_BSTATE = $row["BSTATE"];
        $row_DATE = $row["DATE"];
        echo '<tr> 
                <td>' . $row_ID . '</td> 
                <td>' . $row_LSDATA . '</td> 
                <td>' . $row_BSTATE . '</td> 
                <td>' . $row_DATE . '</td> 
           
              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
</table>

</body>
</html>

	</body>
</html>