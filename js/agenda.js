/**
 * @file
 * Newsroom newsletter list.
 */

(function ($) {
  Drupal.behaviors.nexteuropa_newsroom = {
    attach: function (context, settings) {
      $('.newsroom-display-more').click(function () {
        $(this).next().show();
        $(this).hide();
      });
    }
  };
})(jQuery);
