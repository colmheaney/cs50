<?php

    // configuration
    require("../includes/config.php"); 
    
    $id = $_SESSION["id"];
    $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = ? ORDER BY symbol ASC", $id);
    $user = CS50::query("SELECT * FROM users WHERE id = ?", $id);
    
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "symbol" => $row["symbol"],
                "name"   => $stock["name"],
                "price"  => $stock["price"],
                "shares" => $row["shares"],
                "total"  => $stock["price"] * $row["shares"]
            ];
        }
    }

    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "user" => $user[0]]);

?>
