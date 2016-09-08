<?php

/**
 * @file
 * Code for the nexteuropa newsroom menu hooks.
 */

/**
 * Implements hook_menu().
 */
function nexteuropa_newsroom_menu() {
  // Configuration page.
  $items['admin/config/content/newsroom'] = array(
    'title' => 'Newsroom',
    'description' => 'Configure Newsroom settings',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('nexteuropa_newsroom_admin_settings'),
    'access arguments' => array('administer newsroom settings'),
    'file' => 'nexteuropa_newsroom.admin.inc',
  );
  $items['news-redirect'] = array(
    'title' => 'Newsroom Item Redirect',
    'page callback' => '_nexteuropa_newsroom_item_redirect',
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK,
  );
  $items['news-proposal'] = array(
    'title' => 'Newsroom item proposal',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('nexteuropa_newsroom_newsroom_proposal_form'),
    'access arguments' => array(NEXTEUROPA_NEWSROOM_PROPOSAL_ACCESS),
  );
  $items['newsroom-agenda'] = array(
    'title' => 'Newsroom Agenda',
    'description' => 'Displays Newsroom items as Agenda',
    'page callback' => '_nexteuropa_newsroom_agenda',
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK,
    'file' => 'nexteuropa_newsroom.pages.inc',
  );
  $items['newsletters-list'] = array(
    'title' => 'Newsletters',
    'description' => 'Newsletters service list',
    'page callback' => '_nexteuropa_newsroom_newsletters_page',
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK,
    'file' => 'nexteuropa_newsroom.pages.inc',
  );
  $items['newsroom-redirect'] = array(
    'title' => 'Newsroom item redirect',
    'page callback' => '_nexteuropa_newsroom_redirect',
    'page arguments' => array(1, 2),
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK,
  );
  $items['newsroom-import'] = array(
    'title' => 'Newsroom item import',
    'page callback' => '_nexteuropa_newsroom_import_item',
    'page arguments' => array(1, 2),
    'access callback' => '_nexteuropa_nexteuropa_newsroom_item_import_access',
    'type' => MENU_CALLBACK,
  );
  $items['newsroom-delete'] = array(
    'title' => 'Newsroom item delete',
    'page callback' => '_nexteuropa_newsroom_delete_item',
    'page arguments' => array(1, 2),
    'access callback' => '_nexteuropa_nexteuropa_newsroom_item_import_access',
    'type' => MENU_CALLBACK,
  );
  $items['newsroom'] = array(
    'page callback' => '_nexteuropa_newsroom_newsroom_page',
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK,
    'file' => 'nexteuropa_newsroom.pages.inc',
  );
  $items['newsroom-rss'] = array(
    'title' => 'Newsroom RSS feed',
    'description' => 'Newsroom RSS feed',
    'page callback' => '_nexteuropa_newsroom_newsroom_rss',
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK,
    'file' => 'nexteuropa_newsroom.pages.inc',
  );

  return $items;
}
