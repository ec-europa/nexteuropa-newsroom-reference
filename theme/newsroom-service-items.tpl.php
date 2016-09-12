<?php

/**
 * @file
 * Service items template.
 */
?>

<?php if (count($items) > 0) : ?>
  <div class="<?php echo $css_class; ?>-items-container serviceItemContainer">
    <h3><?php echo $title; ?></h3>

    <div class="subscrNewsletterList">
    <?php foreach ($items as $item) : ?>

      <div class="subscrNewsletterItem clearfix">
        <h4><?php echo $item->title; ?></h4>
        
      <?php if($item->image || $item->service_id): ?>
        <div class="image">
          <img typeof="foaf:Image" src="https://ec.europa.eu/digital-single-market/sites/digital-agenda/files/newsroom-service/banner3_16.jpg" width="214" height="129">
            <?php if ($item->image): ?>
                <?php echo $item->image; ?>
            <?php endif; ?>
        </div>
      <?php endif; ?>

      <?php if ($item->service_sample): ?>
        <div class="sample">
          <?php echo $item->service_sample; ?>
        </div>
      <?php endif; ?>

        <div class="description">
          <?php echo $item->description; ?>
        </div>
        
      <?php if ($item->form): ?>
        <div class="form">
          <?php echo $item->form; ?>
        </div>
      <?php endif; ?>
      </div>
    <?php endforeach; ?> 
    </div>
  </div>
<?php endif; ?>
