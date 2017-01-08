<?php
$url=$_SERVER['REQUEST_URI'];
header("Refresh:6;URL=$url"); //Refresh Every 6 seconds
?>
<!doctype html>
<html>
<head></head>
<body>
<div  style="height:600px; overflow: auto;">
<table align="left" border="*" BORDERCOLOR="GREEN  "cellspacing="0" cellpadding="10">
<tr bgcolor="#339966">
<td>Id</td>
<td>Time</td>
<td>Hum%</td>
<td>Temp°C</td>
</tr>
<!-- PHP starts .. Connect to SQL Database and Fetch Data -->
<?php
$con=mysqli_connect("localhost","root","root","sensor"); //Localhost, Username, Password, Database Name
$result=mysqli_query($con,'SELECT * FROM mydata ORDER BY id DESC'); // Run SELECT query
while($row=mysqli_fetch_array($result)) // Fetch the table from the Database
{
echo"<tr>";
echo"<td bgcolor=#0066FF>".$row['id']."</td>";
echo"<td bgcolor=#6699FF>".$row['time']."</td>";
echo"<td bgcolor=#99CCFF>".$row['hum']."</td>";
echo"<td bgcolor=#99CCFF>".$row['temp']."</td>";
echo"<tr>";
}
mysqli_close($con); // Close Connection
?>
</table>
</div>
</body>
</html>