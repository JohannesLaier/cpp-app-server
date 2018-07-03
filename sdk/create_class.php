<?php
	require_once("class/eroscloud.class.php");

	if ($argc < 3) die("Usage: php ".$argv[0]." [ClassName] [ProjectPath]\r\n"); 

	$_eroscloud = new eroscloud;
	$_eroscloud->createClass($argv[1], $argv[2]);
?>
