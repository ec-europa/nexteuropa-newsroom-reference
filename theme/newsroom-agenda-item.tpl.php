<?php

/**
 * @file
 * Agenda items.
 */
?>
<?php if (!empty($item)): ?>
<div class="listing__wrapper">
    <ul class="listing listing--agenda listing--column-left">
        <li>
            <div class="listing__item__wrapper newsroom-agenda-items">
                <div class="listing__column-second">
                    <?php echo $date; ?>
                </div>
                <div class="listing__column-main">
                    <div class="listing__wrapper">
                            <div class="meta">
                        <span class="meta__item">
                            <?php //if (!empty($item->end_date) && $item->end_date != $item->start_date): ?>
                              <?php //echo t('From @start_date', ['@start_date' => $item->prepared_start_date]); ?>
                              <?php //echo t('to @end_date', ['@end_date' => $item->prepared_end_date]); ?>
                            <?php //else: ?>
                              <?php //echo $item->prepared_start_date; ?>
                            <?php //endif; ?>
                        </span>
                            </div>
                            <h3 class="listing__title">
                              <?php $title_text = check_plain($item->title); ?>
                              <?php echo l($title_text, $item->url, [
                                'html' => TRUE,
                                'absolute' => TRUE,
                              ]); ?>
                            </h3>
                      <?php if ($item->venue): ?>
                        <div class="listing__status-container"></div>
                        <span class="icon icon--location icon--text-small icon--margin-right"><?php echo $item->venue ?></span>
                      <?php endif; ?>
                         <?php echo $item->related_items; ?>
                    </div>
                </div>
            </div>
        </li>
    </ul>
</div>
<?php endif; ?>
