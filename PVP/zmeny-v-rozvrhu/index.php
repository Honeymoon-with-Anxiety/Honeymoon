<?php
$servername = "localhost";
$username = "e424";
$password = "e424";
$dbname = "zmeny_v_rozvrhu";

function cesky_den($den) {
    static $nazvy = array('ned&#283le', 'pond&#283l&#237', '&#250ter&#253', 'st&#345eda', '&#269tvrtek', 'p&#225tek', 'sobota');
    return $nazvy[$den];
}

try{
    // This block of code establishes a connection to a MySQL database using PHP Data Objects (PDO).
	$conn = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch(PDOException $e) {
    die("Connection failed: " . $e->getMessage());
}
?>

<!DOCTYPE html>
<html>
<head>
    <meta charset='utf-8'>
    <title>Změny v rozvrhu</title>
    <link rel='stylesheet' type='text/css' href='style.css'>
	<link rel="preconnect" href="https://fonts.googleapis.com">
	<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
	<link href="https://fonts.googleapis.com/css2?family=Oxanium:wght@200..800&display=swap" rel="stylesheet">
</head>
<body>
    <h1>Změny v rozvrhu <?php echo cesky_den(date("w")) . " " . date("d.m.Y") ?></h1>
    <div id="time_bar"><div id="time_display"></div></div>
    <table>
        <tr>
            <th>Třída</th>
            <th>Hodina</th>
            <th>Předmět</th>
            <th>Skupina</th>
            <th>Učebna</th>
            <th>Změna</th>
            <th>Učitel</th>
            <th>Poznámka</th>
        </tr>
        <?php
			// This block of code is preparing and executing a SQL query to select all records from the `zmeny` table in the database.
			$stmt = $conn->prepare("SELECT * FROM `zmeny` WHERE datum=\"".date("Y-m-d")."\"");
			$stmt->execute();
			$stmt->setFetchMode(PDO::FETCH_ASSOC);
			$resultArray = $stmt->fetchAll();
			
            // This block of code is iterating over the ``, which contains the fetched records from the database table `zmeny`.
			for($c = 0; $c<sizeof($resultArray);$c++){
				$result = explode('ß', implode('ß', $resultArray[$c])); //schvalne pouzit malo uzivany znak pro zmenseni nahody rozbiti kvuli poznamce
                echo "<tr>";
                for($i = 1; $i < 9; $i++){
                    echo "<td>";
                    echo $result[$i];
                    echo "</td>";
                }
                echo "</tr>";
            }
        ?>
    </table>

    <script>
        setInterval(function () {
            var local_time = new Date();
            local_time.setTime(local_time.getTime());
            var min = local_time.getMinutes();
            var sec = local_time.getSeconds();
            document.getElementById('time_display').innerHTML = local_time.getHours() + ':' + (min < 10 ? '0' : '') + min + ':' + (sec < 10 ? '0' : '') + sec;
        }, 1000);
    </script>
</body>
</html>