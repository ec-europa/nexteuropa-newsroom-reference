<?php

/**
 * @file
 * Nexteuropa Newsroom Forms.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function nexteuropa_newsroom_form_nexteuropa_newsroom_admin_settings_alter(&$form, &$form_state, $form_id) {

  // If we are in a confimation step, change the form visualization.
  if (!empty($form_state['storage']['confirm'])) {
    drupal_set_message(t('You are in a confirmation page, to submit all the form settings check the box below.'), 'warning');
    $form['newsroom_universe']['#collapsible'] = TRUE;
    $form['newsroom_universe']['#collapsed'] = TRUE;
    $form['newsroom_fields']['#collapsed'] = FALSE;
  }
}

/**
 * Implements hook_date_popup_process_alter().
 */
function nexteuropa_newsroom_date_popup_process_alter(&$element, &$form_state, $context) {
  if ($form_state['build_info']['form_id'] == 'nexteuropa_newsroom_agenda_filter_form') {
    unset($element['date']['#title']);
    unset($element['date']['#description']);
  }
  elseif ($form_state['build_info']['form_id'] == 'nexteuropa_newsroom_page_filter_form') {
    unset($element['date']['#title']);
  }
}

/**
 * Implements hook_form_newsroom_item_node_form_alter().
 */
function nexteuropa_newsroom_form_newsroom_item_node_form_alter(&$form, &$form_state, $form_id) {
  // Build language aware options list for taxonomy reference fields.
  $taxonomy_fields = [
    'field_newsroom_item_type',
    'field_newsroom_primary_topic',
    'field_newsroom_topics',
    'field_newsroom_highlighted_topic',
  ];

  $type_options = NexteuropaNewsroomHelper::getNewsroomTypeOptions(FALSE, FALSE);
  $topic_options = NexteuropaNewsroomHelper::getNewsroomTopicOptions([], FALSE);

  // Fields with wrong translation in node edit form.
  foreach ($taxonomy_fields as $taxonomy_field) {
    $form[$taxonomy_field][LANGUAGE_NONE]['#options'] = $taxonomy_field == 'field_newsroom_item_type' ? $type_options : $topic_options;

    // The default value is lost in the translations,
    // so we need to set it this way.
    if (!empty($form['#node']->$taxonomy_field)) {
      $values = [];
      $value_array = $form['#node']->$taxonomy_field;
      foreach ($value_array[LANGUAGE_NONE] as $value) {
        $values[] = $value['tid'];
      }
      $form[$taxonomy_field][LANGUAGE_NONE]['#default_value'] = $values;
    }
  }
}

/**
 * Gets form rendable array for newsroom proposal page.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   Rendable form array.
 */
function nexteuropa_newsroom_proposal_form($form, $form_state) {

  global $user;

  $account = user_load($user->uid);
  $form['#action'] = NexteuropaNewsroomHelper::getUniverseUrl() . variable_get('nexteuropa_newsroom_proposal_script');
  $form['title'] = [
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('Title of your Newsroom item (mandatory).'),
    '#default_value' => '',
    '#required' => TRUE,
  ];

  $form['teaser'] = [
    '#title' => t('Teaser'),
    '#type' => 'textarea',
    '#description' => t('Teaser of your Newsroom item (a teaser is a brief description of the subject of your item).'),
    '#size' => 18,
  ];

  $form['body'] = [
    '#title' => t('Full content'),
    '#type' => 'textarea',
    '#description' => t('Full content of the Newsroom item (mandatory - The full content is the body of your item).'),
    '#required' => TRUE,
  ];

  $form['url'] = [
    '#title' => t('URL'),
    '#type' => 'textfield',
    '#description' => t('Add a link to another web page.'),
  ];

  $form['start_date'] = [
    '#title' => t('Date'),
    '#type' => 'date',
    '#description' => t('Publication or event date.'),
  ];

  $form['end_date'] = [
    '#title' => t('End date'),
    '#type' => 'date',
    '#description' => t('End date.'),
  ];

  $form['venue'] = [
    '#title' => t('Venue'),
    '#type' => 'textfield',
    '#description' => t('Name and address of the venue.'),
  ];

  $form['topic_id'] = [
    '#title' => t('Topic ID'),
    '#type' => 'hidden',
    '#value' => !empty($_REQUEST['topic_id']) ? filter_xss($_REQUEST['topic_id']) : NULL,
    '#required' => TRUE,
  ];

  $form['email'] = [
    '#title' => t('E-mail'),
    '#type' => 'hidden',
    '#value' => $account->mail,
    '#required' => TRUE,
  ];

  $form['lastname'] = [
    '#title' => t('Last name'),
    '#type' => 'hidden',
    '#value' => NexteuropaNewsroomHelper::getFieldValue($account, 'field_lastname'),
    '#required' => TRUE,
  ];

  $form['firstname'] = [
    '#title' => t('First name'),
    '#type' => 'hidden',
    '#value' => NexteuropaNewsroomHelper::getFieldValue($account, 'field_firstname'),
    '#required' => TRUE,
  ];

  $form['submit'] = [
    '#type' => 'submit',
    '#value' => t('Send'),
  ];

  return $form;
}

/**
 * Gets form rendable array for newsletter subscription block.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   Rendable form array.
 */
function nexteuropa_newsroom_newsletter_subscription_form($form, &$form_state) {

  $args = $form_state['build_info']['args'][0];
  $form = [];
  $form['#prefix'] = '<div class="CTAnewsletter">';
  $form['#suffix'] = '</div>';
  $form['#token'] = FALSE;
  $form['#action'] = NexteuropaNewsroomHelper::getNewsroomUrl('subscription-quick-generic.cfm');
  $form['intro'] = [
    '#markup' => '<div class="title">' . $args['name'] . '</div>',
  ];

  $form['feedback'] = [
    '#markup' => '<div class="feedback"></div>',
  ];

  $form['email'] = [
    '#prefix' => '<div class="inputMail">',
    '#suffix' => '</div>',
    '#type' => 'textfield',
    '#attributes' => [
      'placeholder' => t('Your e-mail'),
      'class' => [],
    ],
  ];

  $form['submit_email_prefix'] = [
    '#markup' => '<div class="inputSubscribe">',
  ];

  $form['submit_email'] = [
    '#type' => 'button',
    '#value' => t('Subscribe'),
    '#ajax' => [
      'callback' => '_nexteuropa_newsroom_newsletter_subscription_block_form_ajax',
    ],
  ];

  $form['submit_email_submit'] = [
    '#markup' => '</div>',
  ];

  $form['service_id'] = [
    '#type' => 'hidden',
    '#value' => $args['tid'],
  ];

  $form['previous'] = [
    '#markup' => '<div class="linkPreviousIssues"><a href="' . NexteuropaNewsroomHelper::getNewsroomUrl('newsletter-specific-archive.cfm?serviceId=' . $args['tid']) . '">' . t('Previous issues') . '</a></div>',
  ];

  return $form;
}

/**
 * Sends request to unsubscribe user.
 *
 * @param string $url
 *   Service URL.
 * @param string $email
 *   User email.
 *
 * @return string
 *   Object decoded from JSON.
 */
function _nexteuropa_newsroom_send_unsubscription_request($url, $email) {
  $input = [
    'key' => NexteuropaNewsroomHelper::getEmailHash($email),
    'app' => variable_get('nexteuropa_newsroom_app'),
  ];
  $request = drupal_http_request($url . '&' . drupal_http_build_query($input));
  return !empty($request->data) ? drupal_json_decode($request->data) : NULL;
}

/**
 * Sends request to the newsroom subscription script.
 *
 * @param string $url
 *   Service URL.
 * @param int $service_id
 *   ID.
 *   Service ID.
 * @param string $email
 *   User email.
 *
 * @return string
 *   Object decoded from JSON.
 */
function _nexteuropa_newsroom_send_subscription_request($url, $service_id, $email) {
  $input = [
    'service_id' => $service_id,
    'email' => $email,
    'response_type' => 'json',
  ];
  $request = drupal_http_request($url . '?' . drupal_http_build_query($input));
  if (!empty($request->data)) {
    $data = drupal_json_decode($request->data);
  }

  return !empty($data['subscription']) ? $data['subscription'] : NULL;
}

/**
 * Newsletter subscription form block ajax callback.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   Ajax callback array.
 */
function _nexteuropa_newsroom_newsletter_subscription_block_form_ajax($form, &$form_state) {
  $form_id = $form['#form_id'];
  $selector = '#' . str_replace('_', '-', $form_id);

  $subscription = _nexteuropa_newsroom_send_subscription_request($form['#action'], $form_state['values']['service_id'], $form_state['values']['email']);

  if ($subscription['status'] == 'Failed') {
    form_set_error('email', $subscription['feedbackMessage']);
    $commands[] = ajax_command_invoke($selector . ' #edit-email', 'addClass', ['error']);
  }
  else {
    $type = ($subscription['isNewUser'] === 'False' && $subscription['isNewSubscription'] === 'False') ? 'warning' : 'status';
    drupal_set_message($subscription['feedbackMessage'], $type);
    $commands[] = ajax_command_invoke($selector . ' #edit-email', 'removeClass', ['error']);
  }

  $replacement = theme('status_messages', ['display' => NULL]);
  $commands[] = ajax_command_replace($selector . ' .feedback', '<div class="feedback">' . $replacement . '</div>');

  return ['#type' => 'ajax', '#commands' => $commands];
}

/**
 * Gets form rendable array for filter on the agenda page.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 * @param int $type_id
 *   Newsroom type ID.
 * @param int $topic_id
 *   Newsroom Topic ID.
 * @param string $current_date
 *   Current date.
 * @param array $result_topics
 *   Topics to filter out the option list.
 *
 * @return array
 *   Rendable form array.
 */
function nexteuropa_newsroom_agenda_filter_form($form, &$form_state, $type_id, $topic_id, $current_date, $result_topics) {
  $topic_options = NexteuropaNewsroomHelper::getNewsroomTopicOptions($result_topics);
  $form = [];
  $form['type_id'] = [
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => NexteuropaNewsroomHelper::getNewsroomTypeOptions(TRUE),
    '#default_value' => $type_id,
  ];
  $form['topic_id'] = [
    '#type' => 'select',
    '#title' => t('Topic'),
    '#options' => $topic_options,
    '#default_value' => $topic_id,
  ];
  $form['current_date'] = [
    '#type' => 'date_popup',
    '#title' => t('Current date'),
    '#default_value' => $current_date,
    '#date_type' => DATE_DATETIME,
    '#date_timezone' => date_default_timezone(),
    '#date_format' => 'd-m-Y',
    '#date_increment' => 1,
    '#date_year_range' => '-2:+2',
  ];
  $form['button'] = [
    '#type' => 'submit',
    '#submit' => ['_nexteuropa_newsroom_agenda_form_submit'],
    '#button_type' => 'button',
    '#value' => t('Filter'),
    '#weight' => 2,
  ];

  return $form;
}

/**
 * Ajax submit handler.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 */
function _nexteuropa_newsroom_agenda_form_submit(&$form, &$form_state) {

  $topic_id = !empty($form_state['values']['topic_id']) ? $form_state['values']['topic_id'] : NULL;
  $type_id = !empty($form_state['values']['type_id']) ? $form_state['values']['type_id'] : NULL;
  $date = !empty($form_state['values']['current_date']) ? $form_state['values']['current_date'] : NexteuropaNewsroomHelper::getFormatedDate();
  $topic = NexteuropaNewsroomHelper::getNewsroomTopic($topic_id);
  $type = NexteuropaNewsroomHelper::getNewsroomType($type_id);
  $agenda = NexteuropaNewsroomBuilder::buildAgenda(NexteuropaNewsroomAgenda::AGENDA_VIEW_SCHEDULE, $type, $topic, new DateTime($date));

  drupal_goto($agenda->getNavigationUrl(NexteuropaNewsroomHelper::checkDateFormat($date)), [], 301);
}

/**
 * Gets form rendable array for subscription button on newsletter page.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 * @param int $service_id
 *   Newsletter subscription service ID.
 *
 * @return array
 *   Rendable form array.
 */
function nexteuropa_newsroom_subscription_newsletter_form($form, $form_state, $service_id = NULL) {
  global $user;

  $form['#action'] = NexteuropaNewsroomHelper::getNewsroomUrl('subscription-quick-generic.cfm');
  $form['email'] = [
    '#title' => t('E-mail'),
    '#type' => 'hidden',
    '#value' => user_is_logged_in() ? $user->mail : NULL,
    '#required' => TRUE,
  ];

  $form['service_id'] = [
    '#type' => 'hidden',
    '#value' => $service_id,
    '#required' => TRUE,
  ];

  $form['submit'] = [
    '#type' => 'submit',
    '#ajax' => [
      'callback' => '_nexteuropa_newsroom_newsletter_subscription_page_form_ajax',
    ],
    '#value' => t('Subscribe'),
  ];

  $form['submit-response'] = [
    '#markup' => '<div class="submit-response"></div>',
  ];

  return $form;
}

/**
 * Gets form rendable array for unsubscription button on newsletter page.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 * @param string $url
 *   Unsubscription URL.
 *
 * @return array
 *   Rendable form array.
 */
function nexteuropa_newsroom_unsubscription_newsletter_form($form, $form_state, $url = NULL) {
  global $user;
  $form['#action'] = $url;
  $form['email'] = [
    '#title' => t('E-mail'),
    '#type' => 'hidden',
    '#value' => user_is_logged_in() ? $user->mail : NULL,
    '#required' => TRUE,
  ];
  $form['submit'] = [
    '#type' => 'submit',
    '#ajax' => [
      'callback' => '_nexteuropa_newsroom_newsletter_unsubscription_form_ajax',
    ],
    '#value' => t('Unsubscribe'),
  ];

  $form['submit-response'] = [
    '#markup' => '<div class="submit-response"></div>',
  ];

  return $form;
}

/**
 * Newsletter subscription page form ajax callback.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   Ajax callback array.
 */
function _nexteuropa_newsroom_newsletter_subscription_page_form_ajax($form, &$form_state) {
  $subscription = _nexteuropa_newsroom_send_subscription_request($form['#action'], $form_state['values']['service_id'], $form_state['values']['email']);
  $message = $subscription['feedbackMessage'];
  if ($subscription['status'] == 'Failed') {
    $type = 'error';
  }
  else {
    if ($subscription['isNewUser'] === 'False' && $subscription['isNewSubscription'] === 'False') {
      $type = 'warning';
    }
    else {
      $message = t('You successfully subscribed to this newsletter.');
      $type = 'status';
    }
  }

  drupal_set_message($message, $type);
  $replacement = theme('status_messages', ['display' => NULL]);
  $commands[] = ajax_command_replace('#' . $form['#id'] . ' .submit-response', '<div class="submit-response">' . $replacement . '</div>');
  $commands[] = ajax_command_replace('#' . $form['#id'] . ' button', '');

  return ['#type' => 'ajax', '#commands' => $commands];
}

/**
 * Newsletter unsubscription form ajax callback.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   Ajax callback array.
 */
function _nexteuropa_newsroom_newsletter_unsubscription_form_ajax($form, &$form_state) {
  $subscription = _nexteuropa_newsroom_send_unsubscription_request($form['#action'], $form_state['values']['email']);

  if ($subscription && $subscription['SUCCESS'] == 1) {
    $text = t('You successfully unsubscribed from this newsletter.');
    $type = 'status';
  }
  else {
    $text = t('An error has happened during unsubscription process.');
    $type = 'error';
  }

  drupal_set_message($text, $type);
  $replacement = theme('status_messages', ['display' => NULL]);
  $commands[] = ajax_command_replace('#' . $form['#id'] . ' .submit-response', '<div class="submit-response">' . $replacement . '</div>');
  $commands[] = ajax_command_replace('#' . $form['#id'] . ' button', '');

  return ['#type' => 'ajax', '#commands' => $commands];
}

/**
 * Gets newsroom id values.
 *
 * @param string $voc
 *   Vocabulary name.
 * @param array $data
 *   Taxonomy term.
 *
 * @return int
 *   Newsroom ID.
 */
function _nexteuropa_newsroom_get_ids($voc, $data) {

  switch ($voc) {
    case NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY:
      $id = $data['field_newsroom_type_id'][LANGUAGE_NONE][0]['value'];
      break;

    case NEXTEUROPA_NEWSROOM_SERVICE_VOCABULARY:
      $id = $data['field_newsroom_service_id'][LANGUAGE_NONE][0]['value'];
      break;

    case NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY:
      $id = $data['field_newsroom_topic_id'][LANGUAGE_NONE][0]['value'];
      break;
  }
  return $id;
}

/**
 * Grabs the newsroom fields from a term.
 *
 * @param object $term
 *   The term to get the values from.
 *
 * @return array
 *   Formatted values for the newsroom related fields.
 */
function _nexteuropa_newsroom_export_prepare_values($term) {
  $term_array = get_object_vars($term);
  $voc = $term->vocabulary_machine_name;
  $id = _nexteuropa_newsroom_get_ids($voc, $term_array);
  $values = [];
  $values[$id] = [];
  $voc = str_replace('_item', '', $voc);

  foreach ($term_array as $propname => $prop) {
    // Should work only with custom fields.
    if (strpos($propname, 'field') === 0) {
      if ($propname == 'field_' . $voc . '_id') {
        continue;
      }

      $check_value = field_get_items('taxonomy_term', $term, $propname);

      if (!empty($check_value)) {
        foreach ($check_value as $value) {
          if (!empty($value['value'])) {
            $values[$id][$propname][] = $value['value'];
          }
          elseif (!empty($value['tid'])) {
            $values[$id][$propname][] = $value['tid'];
          }
          elseif (!empty($value['target_id'])) {
            $values[$id][$propname][] = $value['target_id'];
          }
        }
      }
    }
  }

  return $values;
}

/**
 * Finds a term basing on its newsroom id.
 *
 * @param string $id
 *   The id coming from the newsroom.
 * @param string $voc
 *   Vocabulay's machine name.
 *
 * @return object
 *   The term object.
 */
function _nexteuropa_newsroom_get_term_from_id($id, $voc) {

  $field = str_replace('_item', '', $voc);
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'taxonomy_term')
    ->entityCondition('bundle', $voc)
    ->fieldCondition('field_' . $field . '_id', 'value', $id, '=');

  $results = $query->execute();

  if (!empty($results)) {
    $result = reset($results['taxonomy_term']);
    $tid = $result->tid;
    $term = taxonomy_term_load($tid);
  }
  else {
    $term = FALSE;
  }
  return $term;
}

/**
 * Gets form rendable array for filter on the newsroom page.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 * @param object|null $type
 *   Newsroom type.
 * @param object|null $topic
 *   Newsroom Topic.
 * @param string $start_date
 *   Start date.
 * @param string $end_date
 *   End date.
 * @param string $ec_content
 *   Is EC content.
 *
 * @return array
 *   Rendable form array.
 */
function nexteuropa_newsroom_page_filter_form($form, &$form_state, $type = NULL, $topic = NULL, $start_date = NULL, $end_date = NULL, $ec_content = NEXTEUROPA_NEWSROOM_EC) {
  $topic_options = NexteuropaNewsroomHelper::getNewsroomTopicOptions(NexteuropaNewsroomHelper::getPageUsedTopicsIds());

  $form = [];
  $form['type_id'] = [
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => NexteuropaNewsroomHelper::getNewsroomTypeOptions(),
    '#default_value' => $type ? $type->tid : NULL,
  ];
  $form['topic_id'] = [
    '#type' => 'select',
    '#title' => t('Topic'),
    '#options' => $topic_options,
    '#default_value' => $topic ? $topic->tid : NULL,
  ];
  $form['start_date'] = [
    '#type' => 'date_popup',
    '#title' => t('From date'),
    '#default_value' => $start_date ? $start_date->format('Y-m-d') : NULL,
    '#date_type' => DATE_DATETIME,
    '#date_timezone' => date_default_timezone(),
    '#date_format' => 'd-m-Y',
    '#date_increment' => 1,
    '#date_year_range' => '-2:+2',
    '#element_validate' => NULL,
  ];
  $form['end_date'] = [
    '#type' => 'date_popup',
    '#title' => t('To date'),
    '#default_value' => $end_date ? $end_date->format('Y-m-d') : NULL,
    '#date_type' => DATE_DATETIME,
    '#date_timezone' => date_default_timezone(),
    '#date_format' => 'd-m-Y',
    '#date_increment' => 1,
    '#date_year_range' => '-2:+2',
    '#element_validate' => NULL,
    '#validate' => ['_nexteuropa_newsroom_validate_date'],
  ];
  $form['ec_content'] = [
    '#type' => 'checkbox',
    '#title' => t('EC content'),
    '#default_value' => empty($ec_content) || $ec_content == NEXTEUROPA_NEWSROOM_EC ? 1 : 0,
    '#weight' => 1,
  ];
  $form['button'] = [
    '#type' => 'submit',
    '#submit' => ['_nexteuropa_newsroom_page_filter_form_submit'],
    '#validate' => ['_nexteuropa_newsroom_validate_date'],
    '#button_type' => 'button',
    '#value' => t('Filter'),
    '#weight' => 2,
  ];

  return $form;
}

/**
 * Submit handler.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 */
function _nexteuropa_newsroom_page_filter_form_submit(&$form, &$form_state) {
  $topic_id = !empty($form_state['values']['topic_id']) ? $form_state['values']['topic_id'] : NULL;
  $type_id = !empty($form_state['values']['type_id']) ? $form_state['values']['type_id'] : NULL;
  $start_date = !empty($form_state['values']['start_date']) ? $form_state['values']['start_date'] : NULL;
  $end_date = !empty($form_state['values']['end_date']) ? $form_state['values']['end_date'] : NULL;
  $ec_content = !empty($form_state['values']['ec_content']);

  $newsroom_page = NexteuropaNewsroomBuilder::buildNewsroomPage($type_id, $topic_id, $start_date, $end_date, $ec_content);
  drupal_goto($newsroom_page->getNavigationUrl(), [], 301);
}

/**
 * Validation handler for date fields.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state.
 */
function _nexteuropa_newsroom_validate_date(&$form, &$form_state) {

  $start_date = NULL;
  $end_date = NULL;

  if (!empty($form_state['values']['start_date']) && is_string($form_state['values']['start_date'])) {
    if (!$start_date = NexteuropaNewsroomHelper::checkDateFormat($form_state['values']['start_date'])) {
      form_set_error('start_date', t('The wrond date format.'));
    }
  }

  if (!empty($form_state['values']['end_date']) && is_string($form_state['values']['end_date'])) {
    if (!$end_date = NexteuropaNewsroomHelper::checkDateFormat($form_state['values']['end_date'])) {
      form_set_error('end_date', t('The wrond date format.'));
    }
  }

  if ($start_date && $end_date &&  $start_date > $end_date) {
    form_set_error('end_date', t('The wrong date range.'));
  }
}
