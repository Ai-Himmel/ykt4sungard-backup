<?php
$cookies = $_COOKIE['iPlanetDirectoryPro'];
$gotoUrl = "http://lah.zty.com/index.php";
$currentuser = ids_GetCurrentUser( $cookies );
if ( strlen($currentuser) > 0)
{
	echo "Search User <B>".$currentuser."</B>'s Attributes <br>";
?>
	<a href="test2.php">Return</a>
	<br>
	<form>
		Attibute Name:<input type="text" name="attr"><input type="submit">
	</form>
	<hr>
	User Attribute values are :<br>
<?
	$attrName = $_REQUEST['attr'];
	if ($attrName)
		print_r(ids_GetUserAttribute( $currentuser , $attrName ));
#	$attributes = ids_GetUserAttribute( $currentuser , $attr);
#	print_r( $attributes );
}
else 
{
	print("you must login first");
	
	$inurl = ids_GetLoginURL()."?goto=".urlencode($gotoUrl);
	echo "<a href=\"".$inurl."\"> Login</a>";

}
?>
