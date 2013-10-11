<?php
/**
 * @file
 * Code for the CiviCRM Case Study feature.
 */

// 1) hook into drupal cron

// 2) drupal http get content (returns json) http://stats.civicrm.org/bgm/extensions.php?output=json

function civicrm_stats_extensions_store_usage_count($extensionName, $countUsers){
	// use int_val to prevent SQL injection
	echo "name: $extensionName total: $countUsers<br/>";
}

function civicrm_stats_extensions_process_returned_values($rawValues){

	// iterate through decoded array

	foreach($rawValues as $eachIndex => $eachValue){
		civicrm_stats_extensions_store_usage_count($eachValue->name, $eachValue->total);
	}
	die("finished processing stats for extensions");
}
// Create the database

function civicrm_stats_get_extension_count_values(){
	$returnedRawValues = drupal_http_request("http://stats.civicrm.org/bgm/extensions.php?output=json");

	$decodedValues = json_decode($returnedRawValues);

	civicrm_stats_extensions_process_returned_values($decodedValues);
}
