<?php
	require_once("class/eroscloud.class.php");

	if ($argc < 3) die("Usage: php ".$argv[0]." [ProjectName] [ProjectPath]\r\n"); 

	$_eroscloud = new eroscloud;
	$_eroscloud->createProject($argv[1], $argv[2]);
?>
