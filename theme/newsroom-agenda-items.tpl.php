<?php

/**
 * @file
 * Agenda items.
 */
?>
<?php if (!empty($items)): ?>
<div class="listing__wrapper">
    <ul class="listing listing--agenda listing--column-left">
        <li>
            <div class="listing__item__wrapper newsroom-agenda-items">
                <?php echo $date; ?>
                <div class="listing__column-main">
                    <div class="listing__wrapper">
                        <ul class="listing listing--no-border">
                        <?php $type_name = ''; ?>
                        <?php foreach ($items as $item): ?>
                            <li class="listing__item">
                                <div class="listing__item__wrapper">
                                    <div class="listing__column-main">

                                        <?php if (empty($type_id) && $type_name != $item->name): ?>
                                            <h2><?php echo $item->name; ?></h2>
                                            <?php $type_name = $item->name; ?>
                                        <?php endif; ?>

                                        <div class="meta">
                                            <span class="meta__item">
                                                <?php echo t('From @start_date', ['@start_date' => $item->prepared_start_date]); ?>
                                                <?php if (!empty($item->end_date)): ?>
                                                <?php echo t('to @end_date', ['@end_date' => $item->prepared_end_date]); ?>
                                                <?php endif; ?>
                                            </span>
                                        </div>
                                        <h3 class="listing__title">
                                            <?php $title_text = $prefix . check_plain($item->title); ?>
                                            <?php echo l($title_text, $item->url, [
                                            'html' => TRUE,
                                            'absolute' => TRUE,
                                            ]); ?>
                                        </h3>
                                    </div>
                                </div>
                            </li>
                        <?php endforeach; ?>
                        </ul>
                    </div>
                </div>
            </div>
        </li>
    </ul>
</div>
<?php endif; ?>
