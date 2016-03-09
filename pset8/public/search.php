<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // TODO: search database for places matching $_GET["geo"], store in $places
    $geo = $_GET["geo"] . "%";
    $places = CS50::query("
        SELECT * 
        FROM places 
        WHERE ((postal_code LIKE ?) 
        OR (place_name LIKE ?) 
        OR (admin_name1 LIKE ?) 
        OR (admin_name2 LIKE ?))",  
        $geo, $geo, $geo, $geo);

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
