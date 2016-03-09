<?php

    // configuration
    require("../includes/config.php"); 

    $id = $_SESSION["id"];
        
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("buy_form.php", ["title" => "Buy"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["name"])) {
            render("apology.php", ["message" => "You need to enter a share symbol."]);
        } 
        
        if (!$stock = lookup($_POST["name"])) {
            render("apology.php", ["message" => "Please enter a valid share name."]);
        }

        if (!preg_match("/^\d+$/", $_POST["quantity"])) {
            render("apology.php", ["message" => "You need to enter a whole number of shares."]);
        } else {
            $quantity = $_POST["quantity"];
        }
        
        $user = CS50::query("SELECT * FROM users WHERE id = ?", $id);
        $cost = $stock["price"] * $quantity;
        
        if ($user[0]["cash"] - $cost < 0) {
            render("apology.php", ["message" => "You don't have enough funds."]);
        } else {
            CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $id, strtoupper($stock["symbol"]), $quantity);
            CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $cost, $id);
            CS50::query("INSERT INTO histories (user_id, symbol, shares, price, bought) VALUES (?, ?, ?, ?, ?)", $id, strtoupper($stock["symbol"]), $quantity, $cost, 1);
        }
        
        // render portfolio
        redirect("/");
    }

?>
