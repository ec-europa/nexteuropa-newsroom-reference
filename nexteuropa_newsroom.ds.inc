<?php
/**
 * @file
 * nexteuropa_newsroom.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function nexteuropa_newsroom_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|newsroom_item|newsroom_consultations';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'newsroom_item';
  $ds_fieldsetting->view_mode = 'newsroom_consultations';
  $ds_fieldsetting->settings = array(
    'newsroom_share_block' => array(
      'weight' => '16',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'nr_related_categories' => array(
      'weight' => '14',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'nr_related_items' => array(
      'weight' => '15',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'ds_nr_related_content' => array(
      'weight' => '13',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'newsroom_related_documents' => array(
      'weight' => '8',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb' => 'Related documents',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(),
      ),
    ),
    'post_date' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'ds_post_date_newsroom_date_only',
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'lb-col' => TRUE,
          'meta_modifier' => 'meta__item--type',
        ),
      ),
    ),
    'field_newsroom_docsroom_ids' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
        ),
      ),
    ),
    'field_newsroom_item_date' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb' => 'Consultation period',
          'lb-el' => 'h3',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_newsroom_item_linked_obj' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_newsroom_item_main_link' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'prefix' => '<div>',
          'suffix' => '</div>',
        ),
      ),
    ),
    'field_newsroom_item_other_link' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Read more',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_newsroom_item_quote_box' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'prefix' => '<blockquote><p>',
          'suffix' => '</p></blockquote>',
        ),
      ),
    ),
    'field_newsroom_item_type' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'meta_modifier' => 'meta__item--type',
        ),
      ),
    ),
    'field_newsroom_teaser' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fis' => TRUE,
          'fis-el' => 'div',
          'fis-cl' => 'teaser-content',
          'fis-at' => '',
          'fis-def-at' => FALSE,
        ),
      ),
    ),
  );
  $export['node|newsroom_item|newsroom_consultations'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|newsroom_item|newsroom_default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'newsroom_item';
  $ds_fieldsetting->view_mode = 'newsroom_default';
  $ds_fieldsetting->settings = array(
    'newsroom_share_block' => array(
      'weight' => '15',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'nr_related_categories' => array(
      'weight' => '13',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'nr_related_items' => array(
      'weight' => '14',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'ds_nr_related_content' => array(
      'weight' => '12',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'newsroom_related_documents' => array(
      'weight' => '7',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb' => 'Related documents',
          'lb-el' => 'h2',
        ),
      ),
    ),
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'post_date' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'ds_post_date_dsm_long_type_without_time',
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'meta_modifier' => 'meta__item--type',
        ),
      ),
    ),
    'field_newsroom_docsroom_ids' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
        ),
      ),
    ),
    'field_newsroom_item_linked_obj' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_newsroom_item_main_link' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'prefix' => '<div>',
          'suffix' => '</div>',
        ),
      ),
    ),
    'field_newsroom_item_other_link' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Read more',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_newsroom_item_quote_box' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'prefix' => '<blockquote><p>',
          'suffix' => '</p></blockquote>',
        ),
      ),
    ),
    'field_newsroom_item_type' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'meta_modifier' => 'meta__item--type',
        ),
      ),
    ),
    'field_newsroom_teaser' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fis' => TRUE,
          'fis-el' => 'div',
          'fis-cl' => 'teaser-content',
          'fis-at' => '',
          'fis-def-at' => FALSE,
        ),
      ),
    ),
  );
  $export['node|newsroom_item|newsroom_default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|newsroom_item|newsroom_events';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'newsroom_item';
  $ds_fieldsetting->view_mode = 'newsroom_events';
  $ds_fieldsetting->settings = array(
    'newsroom_share_block' => array(
      'weight' => '20',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'nr_related_categories' => array(
      'weight' => '18',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'nr_related_items' => array(
      'weight' => '19',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'ds_nr_related_content' => array(
      'weight' => '17',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'newsroom_related_documents' => array(
      'weight' => '11',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb' => 'Related documents',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'post_date' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'ds_post_date_time_only',
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'meta_modifier' => 'meta__item--type',
        ),
      ),
    ),
    'field_newsroom_docsroom_ids' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
        ),
      ),
    ),
    'field_newsroom_item_contact_mail' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Contact information',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_newsroom_item_main_link' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-col' => TRUE,
          'prefix' => '<div>',
          'suffix' => '</div>',
        ),
      ),
    ),
    'field_newsroom_item_other_link' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Read more',
        ),
      ),
    ),
    'field_newsroom_item_speaker' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_newsroom_item_type' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'meta_modifier' => 'meta__item--type',
        ),
      ),
    ),
    'field_newsroom_item_venue' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'meta_modifier' => 'meta__item--type',
        ),
      ),
    ),
    'field_newsroom_location' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb' => 'Location / Map',
          'lb-el' => 'h2',
        ),
      ),
    ),
    'field_newsroom_teaser' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fis' => TRUE,
          'fis-el' => 'div',
          'fis-cl' => 'teaser-content',
          'fis-at' => '',
          'fis-def-at' => FALSE,
        ),
      ),
    ),
  );
  $export['node|newsroom_item|newsroom_events'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|newsroom_item|newsroom_fundings';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'newsroom_item';
  $ds_fieldsetting->view_mode = 'newsroom_fundings';
  $ds_fieldsetting->settings = array(
    'newsroom_share_block' => array(
      'weight' => '16',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'nr_related_categories' => array(
      'weight' => '14',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'nr_related_items' => array(
      'weight' => '15',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'ds_nr_related_content' => array(
      'weight' => '13',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'newsroom_related_documents' => array(
      'weight' => '8',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb' => 'Related documents',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'post_date' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'ds_post_date_newsroom_date_only',
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'meta_modifier' => 'meta__item--type',
        ),
      ),
    ),
    'field_newsroom_docsroom_ids' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
        ),
      ),
    ),
    'field_newsroom_item_date' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb' => 'Tender period',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_newsroom_item_linked_obj' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_newsroom_item_main_link' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-el' => 'h2',
          'prefix' => '<div>',
          'suffix' => '</div>',
        ),
      ),
    ),
    'field_newsroom_item_other_link' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Read more',
          'lb-col' => TRUE,
        ),
      ),
    ),
    'field_newsroom_item_quote_box' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb-col' => TRUE,
          'prefix' => '<blockquote><p>',
          'suffix' => '</p></blockquote>',
        ),
      ),
    ),
    'field_newsroom_item_type' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_nexteuropa_formatters_meta_item',
          'meta_modifier' => 'meta__item--type',
        ),
      ),
    ),
    'field_newsroom_teaser' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fis' => TRUE,
          'fis-el' => 'div',
          'fis-cl' => 'teaser-content',
          'fis-at' => '',
          'fis-def-at' => FALSE,
        ),
      ),
    ),
  );
  $export['node|newsroom_item|newsroom_fundings'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function nexteuropa_newsroom_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'newsroom_related_documents';
  $ds_field->label = 'Newsroom page : Related documents';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'views|39e10d54fad34071dca96fe7d7133f38',
    'block_render' => '1',
  );
  $export['newsroom_related_documents'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'newsroom_share_block';
  $ds_field->label = 'Newsroom share block';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'nexteuropa_newsroom|newsroom_share_block',
    'block_render' => '1',
  );
  $export['newsroom_share_block'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function nexteuropa_newsroom_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|newsroom_item|newsroom_consultations';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'newsroom_item';
  $ds_layout->view_mode = 'newsroom_consultations';
  $ds_layout->layout = 'ne_bootstrap_1col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left_header' => array(
        0 => 'group_newsroom_meta',
        1 => 'field_newsroom_item_type',
        2 => 'title',
        4 => 'post_date',
      ),
      'central' => array(
        3 => 'field_newsroom_item_date',
        5 => 'field_newsroom_teaser',
        6 => 'field_newsroom_illustrative_img',
        7 => 'field_newsroom_private_img',
        8 => 'field_newsroom_item_quote_box',
        9 => 'body',
        10 => 'newsroom_related_documents',
        11 => 'field_newsroom_docsroom_ids',
        12 => 'field_newsroom_item_linked_obj',
        13 => 'field_newsroom_item_other_link',
        14 => 'field_newsroom_item_main_link',
        15 => 'ds_nr_related_content',
        16 => 'nr_related_categories',
        17 => 'nr_related_items',
        18 => 'newsroom_share_block',
      ),
    ),
    'fields' => array(
      'group_newsroom_meta' => 'left_header',
      'field_newsroom_item_type' => 'left_header',
      'title' => 'left_header',
      'field_newsroom_item_date' => 'central',
      'post_date' => 'left_header',
      'field_newsroom_teaser' => 'central',
      'field_newsroom_illustrative_img' => 'central',
      'field_newsroom_private_img' => 'central',
      'field_newsroom_item_quote_box' => 'central',
      'body' => 'central',
      'newsroom_related_documents' => 'central',
      'field_newsroom_docsroom_ids' => 'central',
      'field_newsroom_item_linked_obj' => 'central',
      'field_newsroom_item_other_link' => 'central',
      'field_newsroom_item_main_link' => 'central',
      'ds_nr_related_content' => 'central',
      'nr_related_categories' => 'central',
      'nr_related_items' => 'central',
      'newsroom_share_block' => 'central',
    ),
    'classes' => array(),
    'wrappers' => array(
      'left_header' => 'div',
      'right_header' => 'div',
      'top' => 'div',
      'central' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
  );
  $export['node|newsroom_item|newsroom_consultations'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|newsroom_item|newsroom_default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'newsroom_item';
  $ds_layout->view_mode = 'newsroom_default';
  $ds_layout->layout = 'ne_bootstrap_1col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left_header' => array(
        0 => 'group_newsroom_meta',
        1 => 'title',
        2 => 'field_newsroom_item_type',
        3 => 'post_date',
      ),
      'central' => array(
        4 => 'field_newsroom_teaser',
        5 => 'field_newsroom_illustrative_img',
        6 => 'field_newsroom_private_img',
        7 => 'field_newsroom_item_quote_box',
        8 => 'body',
        9 => 'newsroom_related_documents',
        10 => 'field_newsroom_docsroom_ids',
        11 => 'field_newsroom_item_linked_obj',
        12 => 'field_newsroom_item_other_link',
        13 => 'field_newsroom_item_main_link',
        14 => 'ds_nr_related_content',
        15 => 'nr_related_categories',
        16 => 'nr_related_items',
        17 => 'newsroom_share_block',
      ),
    ),
    'fields' => array(
      'group_newsroom_meta' => 'left_header',
      'title' => 'left_header',
      'field_newsroom_item_type' => 'left_header',
      'post_date' => 'left_header',
      'field_newsroom_teaser' => 'central',
      'field_newsroom_illustrative_img' => 'central',
      'field_newsroom_private_img' => 'central',
      'field_newsroom_item_quote_box' => 'central',
      'body' => 'central',
      'newsroom_related_documents' => 'central',
      'field_newsroom_docsroom_ids' => 'central',
      'field_newsroom_item_linked_obj' => 'central',
      'field_newsroom_item_other_link' => 'central',
      'field_newsroom_item_main_link' => 'central',
      'ds_nr_related_content' => 'central',
      'nr_related_categories' => 'central',
      'nr_related_items' => 'central',
      'newsroom_share_block' => 'central',
    ),
    'classes' => array(),
    'wrappers' => array(
      'left_header' => 'div',
      'right_header' => 'div',
      'top' => 'div',
      'central' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
  );
  $export['node|newsroom_item|newsroom_default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|newsroom_item|newsroom_events';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'newsroom_item';
  $ds_layout->view_mode = 'newsroom_events';
  $ds_layout->layout = 'ne_bootstrap_1col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left_header' => array(
        0 => 'group_newsroom_meta',
        1 => 'title',
        2 => 'field_newsroom_item_type',
        4 => 'post_date',
        6 => 'field_newsroom_item_venue',
      ),
      'central' => array(
        3 => 'field_newsroom_item_date',
        5 => 'field_newsroom_teaser',
        7 => 'field_newsroom_illustrative_img',
        8 => 'field_newsroom_private_img',
        9 => 'field_newsroom_item_quote_box',
        10 => 'body',
        11 => 'field_newsroom_item_speaker',
        12 => 'field_newsroom_organiser',
        13 => 'field_newsroom_item_contact_mail',
        14 => 'newsroom_related_documents',
        15 => 'field_newsroom_docsroom_ids',
        16 => 'field_newsroom_item_other_link',
        17 => 'field_newsroom_location',
        18 => 'field_newsroom_registration_link',
        19 => 'field_newsroom_item_main_link',
        20 => 'ds_nr_related_content',
        21 => 'nr_related_categories',
        22 => 'nr_related_items',
        23 => 'newsroom_share_block',
      ),
    ),
    'fields' => array(
      'group_newsroom_meta' => 'left_header',
      'title' => 'left_header',
      'field_newsroom_item_type' => 'left_header',
      'field_newsroom_item_date' => 'central',
      'post_date' => 'left_header',
      'field_newsroom_teaser' => 'central',
      'field_newsroom_item_venue' => 'left_header',
      'field_newsroom_illustrative_img' => 'central',
      'field_newsroom_private_img' => 'central',
      'field_newsroom_item_quote_box' => 'central',
      'body' => 'central',
      'field_newsroom_item_speaker' => 'central',
      'field_newsroom_organiser' => 'central',
      'field_newsroom_item_contact_mail' => 'central',
      'newsroom_related_documents' => 'central',
      'field_newsroom_docsroom_ids' => 'central',
      'field_newsroom_item_other_link' => 'central',
      'field_newsroom_location' => 'central',
      'field_newsroom_registration_link' => 'central',
      'field_newsroom_item_main_link' => 'central',
      'ds_nr_related_content' => 'central',
      'nr_related_categories' => 'central',
      'nr_related_items' => 'central',
      'newsroom_share_block' => 'central',
    ),
    'classes' => array(),
    'wrappers' => array(
      'left_header' => 'div',
      'right_header' => 'div',
      'top' => 'div',
      'central' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
  );
  $export['node|newsroom_item|newsroom_events'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|newsroom_item|newsroom_fundings';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'newsroom_item';
  $ds_layout->view_mode = 'newsroom_fundings';
  $ds_layout->layout = 'ne_bootstrap_1col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left_header' => array(
        0 => 'group_newsroom_meta',
        1 => 'field_newsroom_item_type',
        2 => 'title',
        4 => 'post_date',
      ),
      'central' => array(
        3 => 'field_newsroom_item_date',
        5 => 'field_newsroom_teaser',
        6 => 'field_newsroom_private_img',
        7 => 'field_newsroom_illustrative_img',
        8 => 'field_newsroom_item_quote_box',
        9 => 'body',
        10 => 'newsroom_related_documents',
        11 => 'field_newsroom_docsroom_ids',
        12 => 'field_newsroom_item_linked_obj',
        13 => 'field_newsroom_item_other_link',
        14 => 'field_newsroom_item_main_link',
        15 => 'ds_nr_related_content',
        16 => 'nr_related_categories',
        17 => 'nr_related_items',
        18 => 'newsroom_share_block',
      ),
    ),
    'fields' => array(
      'group_newsroom_meta' => 'left_header',
      'field_newsroom_item_type' => 'left_header',
      'title' => 'left_header',
      'field_newsroom_item_date' => 'central',
      'post_date' => 'left_header',
      'field_newsroom_teaser' => 'central',
      'field_newsroom_private_img' => 'central',
      'field_newsroom_illustrative_img' => 'central',
      'field_newsroom_item_quote_box' => 'central',
      'body' => 'central',
      'newsroom_related_documents' => 'central',
      'field_newsroom_docsroom_ids' => 'central',
      'field_newsroom_item_linked_obj' => 'central',
      'field_newsroom_item_other_link' => 'central',
      'field_newsroom_item_main_link' => 'central',
      'ds_nr_related_content' => 'central',
      'nr_related_categories' => 'central',
      'nr_related_items' => 'central',
      'newsroom_share_block' => 'central',
    ),
    'classes' => array(),
    'wrappers' => array(
      'left_header' => 'div',
      'right_header' => 'div',
      'top' => 'div',
      'central' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
  );
  $export['node|newsroom_item|newsroom_fundings'] = $ds_layout;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function nexteuropa_newsroom_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'newsroom_consultations';
  $ds_view_mode->label = 'Newsroom consultations';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['newsroom_consultations'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'newsroom_default';
  $ds_view_mode->label = 'Newsroom default';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['newsroom_default'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'newsroom_events';
  $ds_view_mode->label = 'Events';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['newsroom_events'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'newsroom_fundings';
  $ds_view_mode->label = 'Newsroom fundings';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['newsroom_fundings'] = $ds_view_mode;

  return $export;
}
