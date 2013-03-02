<?php
#ids_Init("client2.properties");
$cookies = $_COOKIE['iPlanetDirectoryPro'];
$gotoUrl = "http://lah.zty.com/index.php";
$currentuser = ids_GetCurrentUser( $cookies );
if ( strlen($currentuser) > 0)
{
	echo "the current user is ".$currentuser.".<br>";
	$outurl = ids_GetLogoutURL()."?goto=".urlencode($gotoUrl);
	echo "<a href=\"".$outurl."\"> Logout</a><br>";
	echo "<a href=\"search.php\">Attributes Search</a>";
}
else 
{
	print("you must login first   ");
	
	$inurl = ids_GetLoginURL()."?goto=".urlencode($gotoUrl);
	echo "<a href=".$inurl."> Login</a>";

}
?>
