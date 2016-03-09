<table class="table table-striped">
    <tr>
        <th>Bought/Sold</th>
        <th>Symbol</th>
        <th>Time</th>
        <th>Shares</th>
        <th>Price</th>
    </tr>
    
    <tbody>
        <?php foreach ($transactions as $transaction): ?>

        <tr>
            <td><?= bought_sold($transaction["bought"]) ?></td>
            <td><?= $transaction["symbol"] ?></td>
            <td><?= date_format($transaction["time"], 'H:i:s d/m/Y') ?></td>
            <td><?= $transaction["shares"] ?></td>
            <td>$<?= number_format($transaction["price"], '2', '.', ',') ?></td>
        </tr>
        
        <?php endforeach ?>
    </tbody>
</table>