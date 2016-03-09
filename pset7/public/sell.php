<?php

    // configuration
    require("../includes/config.php"); 

    $id = $_SESSION["id"];
        
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = $id");
        
        $shares = [];
        foreach ($rows as $row)
        {
            $shares[] = [
                "symbol"   => $row["symbol"],
                "quantity" => $row["shares"]
            ];
    
        }
        
        // render form
        render("sell_form.php", ["title" => "Sell", "shares" => $shares]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
        if (!$stock = lookup($_POST["stock"])) {
            render("apology.php", ["message" => "You need to pick a stock."]);
        }
        
        $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = ? AND symbol = ?", $id, $_POST["stock"]);
        $quantity = $rows[0]["shares"];
        $total = $stock["price"] * $quantity;
        
        CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $id, $_POST["stock"]);
        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $total, $id);
        CS50::query("INSERT INTO histories (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)", $id, strtoupper($stock["symbol"]), $quantity, $total);
            
        // render portfolio
        redirect("/");
    }

?>
