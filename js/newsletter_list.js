/**
 * @file
 * Newsroom newsletter list.
 */

(function ($) {
    Drupal.behaviors.nexteuropa_newsroom = {
        attach: function (context, settings) {

            // Disable all subscribe buttons before accepting privacy statement.
            $('.newsroom-service-page button[type="submit"]').each(function () {
                if ($(this).text() != "Unsubscribe") {
                    $(this).prop('disabled', true);
                }
                else {
                    $(this).parents('form').first().prev('div').remove();
                }

            });

            if (Drupal.settings.nexteuropa_newsroom.user_is_logged_in) {
                // Logged user.
                $(".gdpr_checkbox input[type='checkbox']").each(function () {
                    $(this).change(function () {
                        var status = true;
                        if (!$(this).prop('checked')) {
                            status = true;
                        }
                        else {
                            status = false;
                        }
                        $(this).parent().next('form').find('button[type="submit"]').prop("disabled", status);
                    });
                });

            }
            else {
                // Not logged user & no valid email entered yet.
                // Disable privacy policy agreement checkboxes.
                $(".gdpr_checkbox input[type='checkbox']").each(function () {
                    $(this).prop("disabled", true);
                })
                // Give "disable look and feel" to these privacy policy labels.
                $(".gdpr_checkbox label").css({opacity: 0.6});

                // Test if valid email submitted.
                $('#newsroom-service-email').change(function () {
                    var regex = /^([a-zA-Z0-9_.+-])+\@(([a-zA-Z0-9-])+\.)+([a-zA-Z0-9]{2,4})+$/;
                    var email = $(this).val();
                    if (regex.test(email)) {
                        $('.newsroom-service-page input[name="email"]').each(function () {
                            $(this).val(email);
                        });

                        $('.gdpr_checkbox label').animate({opacity: 1}, 300);
                        $(".gdpr_checkbox input[type='checkbox']").each(function () {

                            $(this).prop('disabled', false);

                            $(this).change(function () {
                                var status = true;
                                if (!$(this).prop('checked')) {
                                    status = true;
                                }
                                else {
                                    status = false;
                                }
                                $(this).parent().next('form').find('button[type="submit"]').prop("disabled", status);
                            });
                        });

                    }
                    else {
                        alert(Drupal.settings.nexteuropa_newsroom.error_message);
                    }
                });

            }

        }
    };
})(jQuery);
