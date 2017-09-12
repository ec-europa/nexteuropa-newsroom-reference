<?php

/**
 * @file
 * Page newsroom featured item.
 */

// @todo: This should be in a preprocess.
$classes = array_combine(
  array(
    'type',
    'title',
    'image',
    'date',
    'teaser',
  ),
  array(
    'newsroom-item__type',
    'newsroom-item__title',
    'newsroom-item__image',
    'newsroom-item__date',
    'newsroom-item__teaser',
  )
);

if (variable_get('nexteuropa_newsroom_legacy', 1)) {
  array_walk($classes, function(&$value, $key) {
    $value .= ' newsroom-' . $key;
  });
}
?>
<div class="newsroom-item newsroom-featured-item">
    <div class="<?php print $classes['type']; ?>">
      <?php echo $type; ?>
    </div>
    <div class="<?php print $classes['title']; ?>">
      <?php echo $title; ?>
    </div>
  <?php if (!empty($image)): ?>
      <div class="<?php print $classes['image']; ?>">
        <?php echo $image; ?>
      </div>
  <?php endif; ?>
    <div class="<?php print $classes['date']; ?>">
      <?php echo $created; ?>
    </div>
    <div class="<?php print $classes['teaser']; ?>">
      <?php echo $teaser; ?>
    </div>
</div>
