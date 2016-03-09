<?php

    // configuration
    require("../includes/config.php");
    
    $id = $_SESSION["id"];

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET") {
        render("deposit_form.php", ["title" => "Add funds"]);
    }
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST") {
        
        $amount = $_POST["amount"];
        
        if ($amount == NULL || $amount < 0) {
            render("apology.php", ["message" => "Please enter a positive number."]);
        } else {
            CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $amount, $id);
        }

        redirect("/");

    }
    


?>