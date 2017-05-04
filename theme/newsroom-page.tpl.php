<?php

/**
 * @file
 * Page wrapper.
 */
?>
<div class="newsroomPage-container">
  <div class="newsroomPage-filterForm">
    <h2><?php echo t('Filter by');?></h2>
    <?php echo $filter_form; ?>
  </div>
  <div class="newsroom-page view-content">
    <?php echo $featured_item; ?>
    <?php if ($items): ?>
      <?php echo $items; ?>
    <?php else: ?>
      <div class="no-result"><?php echo t("No results"); ?></div>
    <?php endif; ?>
  </div>
</div>
