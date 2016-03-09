<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["password"]) || empty($_POST["confirmation"]))
        {
            render("apology.php", ["message" => "Please confirm your password"]);
            return;
        }

        if (empty($_POST["username"]))
        {
            render("apology.php", ["message" => "Please enter a username"]);
            return;
        }

        if ($_POST["password"] != $_POST["confirmation"])
        {
            render("apology.php", ["message" => "Your passwords do not match"]);
            return;
        }

        $query = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));

        if ($query == 0) {
            render("apology.php", ["message" => "Something went wrong"]);
            return;
        }
        else {
            $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
            $id = $rows[0]["id"];
            
            // remember that user's now logged in by caching user's ID in session
            $_SESSION["id"] = $id;
        }

        // redirect to portfolio
        redirect("index.php");

    }

?>
