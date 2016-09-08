<?php

/**
 * @file
 * Page newsroom featured item.
 */
	$l = variable_get('newsroom_legacy', 1);
?>

<div class="newsroom-item newsroom-item--featured">
  <div class="newsroom-item__type<?php if ($l) { echo ' newsroom-type'; } ?>">
  <?php echo $type; ?>
  </div>
  <div class="newsroom-item__title<?php if ($l) { echo ' newsroom-title'; } ?>"><?php echo $title; ?></div>
  <div class="newsroom--item__image<?php if ($l) { echo ' newsroom-image'; } ?>"><?php echo $title; ?>"><?php echo $image; ?></div>
  <div class="newsroom--item__date<?php if ($l) { echo ' newsroom-date'; } ?>"><?php echo $created; ?></div>
  <div class="newsroom--item__teaser<?php if ($l) { echo ' newsroom-teaser'; } ?>"><?php echo $teaser; ?></div>
</div>
