<table class="table table-striped">
    <tr>
      <th>Symbol</th>
      <th>Company</th>
      <th>Shares</th>
      <th>Price</th>
      <th>Total</th>
    </tr>
    
    <tbody>
        <?php foreach ($positions as $position): ?>
    
        <tr>
            <td><?= $position["symbol"] ?></td>
            <td><?= $position["name"] ?></td>
            <td><?= $position["shares"] ?></td>
            <td>$<?= number_format($position["price"], 2, '.', ',') ?></td>
            <td>$<?= number_format($position["total"], 2, '.', ',') ?></td>
        </tr>
    
        <?php endforeach ?>
        <tr class="funds">
            <td colspan="4">FUNDS</td>
            <td>$<?= number_format($user["cash"], 2, '.', ',') ?></td>
        </tr>

    </tbody>
</table>


