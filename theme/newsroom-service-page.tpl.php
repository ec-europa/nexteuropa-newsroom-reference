<?php

/**
 * @file
 * Service list page.
 */
global $user;
?>
<div class="newsroom-service-page">
  <h2 id="subscribe-to-newsletters"><?php echo t('Subscribe to newsletters'); ?></h2>
  <div class="newsroom-service-widget">
    <h4><?php echo t('Your e-mail'); ?></h4>
    <?php if (user_is_logged_in()): ?>
       <div class="middle-step">
        <?php echo $user->mail; ?>
      </div>
    <?php else: ?>
      <div class="middle-step">
        <input type="text" class="newsroom-service-email" id="newsroom-service-email" />
        <div class="newsroom-service-email-description">
          <span><?php echo t('or'); ?></span> <?php echo l(t('login'), 'user/login'); ?> <?php echo t('to manage your subscriptions.'); ?>
        </div>
      </div>
    <?php endif; ?>
  </div>

  <?php echo $central_items; ?>
  <?php echo $basic_items; ?>    

  <?php if (!empty($privacy_text)): ?>
    <h2 id="privacy-statement"><?php echo t('Privacy Statement'); ?></h2>
    <?php echo $privacy_text; ?>
  <?php endif; ?>
</div>
