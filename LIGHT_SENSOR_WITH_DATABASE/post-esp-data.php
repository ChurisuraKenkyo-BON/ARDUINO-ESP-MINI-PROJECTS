<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "lightsensordata";

$api_key_value = "tPmAT5Ab3j7F9";
$api_key = $LSDATA = $BSTATE = "";


    $api_key = test_input($_GET["api_key"]);
    if ($api_key == $api_key_value) {
        $LSDATA = test_input($_GET["LSDATA"]);
        $BSTATE = test_input($_GET["BSTATE"]);
        $conn = new mysqli($servername, $username, $password, $dbname);
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        }

        $sql = "INSERT INTO data (LSDATA, BSTATE) VALUES ('$LSDATA', '$BSTATE')";

        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }

        $conn->close();
    } else {
        echo "Wrong API Key provided.";
    }


function test_input($data)
{
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}
?>
