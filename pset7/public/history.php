<?php

    // configuration
    require("../includes/config.php"); 

    $id = $_SESSION["id"];
    $rows = CS50::query("SELECT * FROM histories WHERE user_id = ? ORDER BY time DESC", $id);
    
    $transactions = [];
    foreach ($rows as $row)
    {
        $date = date_create($row["time"]);

        $transactions[] = [
            "time"   => $date,
            "symbol" => $row["symbol"],
            "bought" => $row["bought"],
            "shares" => $row["shares"],
            "price"  => $row["price"]
        ];
    }    
    
    render("history.php", ["title" => "History", "transactions" => $transactions]);
?>