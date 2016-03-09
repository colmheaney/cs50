<form action="sell.php" method="post">
    <fieldset>
        <div>
            <select class="form-control" name="stock">
                <option value="">My Stocks</option>
                <?php foreach ($shares as $share): ?>
                <option><?= $share["symbol"] ?></option>
                <?php endforeach ?>
            </select>
        </div>
        <br />
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                Sell
            </button>
        </div>
    </fieldset> 
</form>