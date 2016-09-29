<?php

/**
 * @file
 * Code for the NewsroomBuilder class.
 */

/**
 * NewsroomBuilder class.
 */
class NewsroomBuilder {

  /**
   * Builds agenda base on url params.
   *
   * @param string $view
   *   View (presentation type): schedule, month, week, day.
   * @param string $type_name
   *   Type url name.
   * @param string $topic_name
   *   Topic url name.
   * @param string $arg1
   *   Date param.
   * @param string $arg2
   *   Date param.
   * @param string $arg3
   *   Date param.
   *
   * @return object
   *   Agenda item.
   */
  public static function buildPageAgenda($view = NewsroomAgenda::AGENDA_VIEW_SCHEDULE, $type_name = NEXTEUROPA_NEWSROOM_ALL, $topic_name = NEXTEUROPA_NEWSROOM_ALL, $arg1 = NULL, $arg2 = NULL, $arg3 = NULL) {

    $agenda = NULL;
    $current_date = new DateTime();
    $type = NewsroomBuilder::getType($type_name);
    $topic = NewsroomBuilder::getTopic($topic_name);
    switch ($view) {
      case NewsroomAgenda::AGENDA_VIEW_MONTH:
        $month = NewsroomBuilder::getMonth($arg1);
        $year = NewsroomBuilder::getYear($arg2);
        $current_date->setDate($year, $month, 1);

        $agenda = new NewsroomAgendaMonth($type, $topic, $current_date);
        break;

      case NewsroomAgenda::AGENDA_VIEW_WEEK:
        $week = NewsroomBuilder::getWeek($arg1);
        $year = NewsroomBuilder::getYear($arg2);
        $current_date->setISODate($year, $week);

        $agenda = new NewsroomAgendaWeek($type, $topic, $current_date);
        break;

      case NewsroomAgenda::AGENDA_VIEW_DAY:
        $day = NewsroomBuilder::getDay($arg1);
        $month = NewsroomBuilder::getMonth($arg2);
        $year = NewsroomBuilder::getYear($arg3);
        $current_date->setDate($year, $month, $day);

        $agenda = new NewsroomAgendaDay($type, $topic, $current_date);
        break;

      default:
        $day = NewsroomBuilder::getDay($arg1);
        $month = NewsroomBuilder::getMonth($arg2);
        $year = NewsroomBuilder::getYear($arg3);

        $current_date->setDate($year, $month, $day);
        $agenda = new NewsroomAgendaSchedule($type, $topic, $current_date);

    }

    return $agenda;
  }

  /**
   * Builds Agenda item based on the current date.
   *
   * @param string $view
   *   View (presentation type): schedule, month, week, day.
   * @param string $type
   *   Newsroom type.
   * @param array $topics
   *   Newsroom topic.
   * @param object $date
   *   Current date.
   *
   * @return object
   *   Agenda item.
   */
  public static function buildAgenda($view, $type, $topics, $date, $operator = NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR) {
    $agenda = NULL;
    switch ($view) {
      case NewsroomAgenda::AGENDA_VIEW_MONTH:
        $agenda = new NewsroomAgendaMonth($type, $topics, $date);
        break;

      case NewsroomAgenda::AGENDA_VIEW_WEEK:
        $agenda = new NewsroomAgendaWeek($type, $topics, $date);
        break;

      case NewsroomAgenda::AGENDA_VIEW_DAY:
        $agenda = new NewsroomAgendaDay($type, $topics, $date);
        break;

      case NewsroomAgenda::AGENDA_VIEW_SCHEDULE_BLOCK:
        $agenda = new NewsroomAgendaBlockSchedule($type, $topics, $date, $operator);
        break;

      default:
        $agenda = new NewsroomAgendaSchedule($type, $topics, $date);

    }

    return $agenda;
  }

  /**
   * Builds newsroom importer generator.
   *
   * @param string $importer_id
   *   Importer ID.
   *
   * @return \NewsroomImporterGenerator
   *   Newsroom importer generator.
   */
  public static function buildImporter($importer_id) {
    switch ($importer_id) {
      case NEXTEUROPA_NEWSROOM_ITEM_IMPORTER:
        $title = 'Newsroom Items Multilingual';
        $description = 'Imports Newsroom Items from the Newsroom service.';
        $entity_type = 'node';
        $bundle = NEXTEUROPA_NEWSROOM_CONTENT_TYPE;
        $rss_context = '//channel/item';
        $import_period = 3600;
        $field_mapping = NewsroomBuilder::getItemImporterMappings();
        break;

      case NEXTEUROPA_NEWSROOM_NEWSLETTER_IMPORTER:
        $title = 'Newsroom Newsletter issues';
        $description = 'Imports newsletter issues.';
        $entity_type = 'node';
        $bundle = NEXTEUROPA_NEWSROOM_NEWSLETTER_CONTENT_TYPE;
        $rss_context = '//channel/item';
        $import_period = 3600;
        $field_mapping = NewsroomBuilder::getIssueImporterMappings();
        break;

      case NEXTEUROPA_NEWSROOM_TYPE_IMPORTER:
        $title = 'Newsroom Type Multilingual';
        $description = 'Imports Item Types from the Newsroom service.';
        $entity_type = 'taxonomy_term';
        $bundle = NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY;
        $rss_context = '//channel/item';
        $import_period = -1;
        $field_mapping = NewsroomBuilder::getTypeImporterMappings();
        break;

      case NEXTEUROPA_NEWSROOM_TOPIC_IMPORTER:
        $title = 'Newsroom Topics Multilingual';
        $description = 'Imports Topics from the Newsroom service';
        $entity_type = 'taxonomy_term';
        $bundle = NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY;
        $rss_context = '//channel/item[infsonewsroom:BasicSvType="Newsroom service"]/category[@domain!="Newsletter" and @lang="' . NewsroomHelper::getDefaultLanguageUppercase() . '"]';
        $import_period = -1;
        $field_mapping = NewsroomBuilder::getTopicImporterMappings();
        break;

      case NEXTEUROPA_NEWSROOM_SERVICE_IMPORTER:
        $title = 'Newsroom Services Multilingual';
        $description = 'Imports Services from the Newsroom service.';
        $entity_type = 'taxonomy_term';
        $bundle = NEXTEUROPA_NEWSROOM_SERVICE_VOCABULARY;
        $rss_context = '//channel/item';
        $import_period = -1;
        $field_mapping = NewsroomBuilder::getServiceImporterMappings();
        break;
    }

    return new NewsroomImporterGenerator($importer_id, $field_mapping, $title, $description, $rss_context, $entity_type, $bundle, $import_period);
  }

  /**
   * Gets item importer field mapping settings.
   *
   * @return array
   *   Item importer field mapping settings.
   */
  private static function getItemImporterMappings() {

    $field_mapping = array(
      array(
        'field' => 'title',
        'query' => 'title[@lang="' . NewsroomHelper::getDefaultLanguageUppercase() . '"]/text()',
      ),
      array(
        'field' => 'title_field',
        'query' => 'title',
      ),
      array(
        'field' => 'field_newsroom_item_date:start',
        'query' => 'infsonewsroom:BasicDate/text()',
        'tamper' => array(
          'plugin_id' => 'strtotime',
        ),
      ),
      array(
        'field' => 'field_newsroom_item_date:end',
        'query' => 'infsonewsroom:BasictoDate/text()',
        'tamper' => array(
          'plugin_id' => 'strtotime',
        ),
      ),
      array(
        'field' => 'field_newsroom_private_img:uri',
        'query' => 'enclosure[@type="image/jpeg" and @schema="Private"]/@url',
      ),
      array(
        'field' => 'field_newsroom_illustrative_img:uri',
        'query' => 'enclosure[@type="image/jpeg" and @schema="Public"]/@url',
      ),
      array(
        'field' => 'field_newsroom_private_img:title',
        'query' => 'infsonewsroom:PicTitle',
        'original_field' => 'field_file_image_title_text',
      ),
      array(
        'field' => 'field_newsroom_private_img:alt',
        'query' => 'infsonewsroom:PicAlt',
        'original_field' => 'field_file_image_alt_text',
      ),
      array(
        'field' => 'field_newsroom_private_img:copyright',
        'query' => 'infsonewsroom:PicCopyright',
        'original_field' => 'field_newsroom_copyrights',
      ),
      array(
        'field' => 'field_newsroom_private_img:caption',
        'query' => 'infsonewsroom:PicCaption',
        'original_field' => 'field_caption',
      ),
      array(
        'field' => 'field_newsroom_illustrative_img:uri',
        'query' => 'enclosure[@type="image/jpeg" and @schema="Public"]/@url',
      ),
      array(
        'field' => 'field_newsroom_illustrative_img:title',
        'query' => 'infsonewsroom:PicTitle',
        'original_field' => 'field_file_image_title_text',
      ),
      array(
        'field' => 'field_newsroom_illustrative_img:alt',
        'query' => 'infsonewsroom:PicAlt',
        'original_field' => 'field_file_image_alt_text',
      ),
      array(
        'field' => 'field_newsroom_illustrative_img:copyright',
        'query' => 'infsonewsroom:PicCopyright',
        'original_field' => 'field_newsroom_copyrights',
      ),
      array(
        'field' => 'field_newsroom_illustrative_img:caption',
        'query' => 'infsonewsroom:PicCaption',
        'original_field' => 'field_caption',
      ),
      array(
        'field' => 'field_newsroom_item_rapid_pr',
        'query' => 'infsonewsroom:BasicRapidPressRelease/text()',
      ),
      array(
        'field' => 'field_newsroom_item_type',
        'query' => 'infsonewsroom:NewsType/@id',
        'options' => array(
          'term_search' => '1',
          'autocreate' => 0,
        ),
        'tamper' => array(
          'entity_type' => 'taxonomy_term',
          'plugin_id' => 'efq_finder',
          'bundle' => NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY,
          'field' => 'field_newsroom_type_id',
        ),
      ),
      array(
        'field' => 'field_tags',
        'query' => 'category[@domain="Policy" or @domain="Activity" or @domain="Theme" or @domain="Collection" or @domain="Tag"]/text()',
        'options' => array(
          'term_search' => '0',
          'autocreate' => 0,
        ),
      ),
      array(
        'field' => 'field_newsroom_item_id',
        'query' => 'infsonewsroom:BasicId',
        'unique' => 1,
      ),
      array(
        'field' => 'field_newsroom_item_other_link:title',
        'query' => 'infsonewsroom:ContextOtherLinkText',
      ),
      array(
        'field' => 'field_newsroom_item_other_link:url',
        'query' => 'infsonewsroom:ContextOtherLinkUrl',
      ),
      array(
        'field' => 'field_newsroom_item_main_link:url',
        'query' => 'infsonewsroom:BasicUrl',
      ),
      array(
        'field' => 'field_newsroom_documents:url',
        'query' => 'enclosure[not(@type="image/jpeg")]/@url',
      ),
      array(
        'field' => 'field_newsroom_documents:title',
        'query' => 'enclosure[not(@type="image/jpeg")]/@title',
      ),
      array(
        'field' => 'promote',
        'query' => 'infsonewsroom:pubHighlight/text()',
      ),
      array(
        'field' => 'field_newsroom_topics',
        'query' => 'category[@domain!="Newsletter"]/@infsonewsroom:TopicId',
        'options' => array(
          'term_search' => '1',
          'autocreate' => 0,
        ),
        'tamper' => array(
          'plugin_id' => 'efq_finder',
          'entity_type' => 'taxonomy_term',
          'bundle' => NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY,
          'field' => 'field_newsroom_topic_id',
        ),
      ),
      array(
        'field' => 'field_newsroom_primary_topic',
        'query' => 'category[@infsonewsroom:TopicPrimary="1" and @domain!="Newsletter"]/@infsonewsroom:TopicId',
        'options' => array(
          'term_search' => '1',
          'autocreate' => 0,
        ),
        'tamper' => array(
          'plugin_id' => 'efq_finder',
          'entity_type' => 'taxonomy_term',
          'bundle' => NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY,
          'field' => 'field_newsroom_topic_id',
        ),
      ),
      array(
        'field' => 'created',
        'query' => 'infsonewsroom:BasicReferenceDate/text()',
        'tamper' => array(
          'plugin_id' => 'strtotime',
        ),
      ),
      array(
        'field' => 'sticky',
        'query' => 'infsonewsroom:pubIsCentral/text()',
      ),
      array(
        'field' => 'field_newsroom_short_item',
        'query' => 'infsonewsroom:pubIsLong/text()',
      ),
      array(
        'field' => 'field_newsroom_teaser_only',
        'query' => 'infsonewsroom:pubTeaserOnly/text()',
      ),
      array(
        'field' => 'field_newsroom_related_content',
        'query' => 'infsonewsroom:slave/@id',
      ),
      array(
        'field' => 'field_newsroom_parent_content',
        'query' => 'infsonewsroom:master/@id',
      ),
      array(
        'field' => 'field_newsroom_project_acr',
        'query' => 'infsonewsroom:ContextProjectAcronym/text()',
      ),
      array(
        'field' => 'field_newsroom_prj_coordinator',
        'query' => 'infsonewsroom:ContextProjectCoordinator/text()',
      ),
      array(
        'field' => 'field_newsroom_project',
        'query' => 'infsonewsroom:ContextProjectName',
      ),
      array(
        'field' => 'field_newsroom_project_website:url',
        'query' => 'infsonewsroom:ContextProjectURL',
      ),
      array(
        'field' => 'field_newsroom_project_website:title',
        'query' => 'infsonewsroom:ContextProjectURLDisplay',
      ),
      array(
        'field' => 'field_newsroom_location:wkt',
        'query' => 'infsonewsroom:ContextWellknowntext/text()',
      ),
      array(
        'field' => 'field_newsroom_highlighted_topic',
        'query' => 'category[@infsonewsroom:TopicHighlight="1" and @domain!="Newsletter"]/@infsonewsroom:TopicId',
        'options' => array(
          'term_search' => '1',
          'autocreate' => 0,
        ),
        'tamper' => array(
          'plugin_id' => 'efq_finder',
          'entity_type' => 'taxonomy_term',
          'bundle' => NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY,
          'field' => 'field_newsroom_topic_id',
        ),
      ),
      array(
        'field' => 'field_newsroom_ec_content',
        'query' => 'infsonewsroom:ContextECContent/text()',
      ),
      array(
        'field' => 'field_newsroom_item_venue',
        'query' => 'infsonewsroom:ContextVenue',
      ),
      array(
        'field' => 'field_newsroom_organiser',
        'query' => 'infsonewsroom:ContextOrganiser',
      ),
      array(
        'field' => 'field_newsroom_author',
        'query' => 'infsonewsroom:ContextAuthor',
      ),
      array(
        'field' => 'field_newsroom_eur_lex_link:url',
        'query' => 'infsonewsroom:ContextEurlex',
      ),
      array(
        'field' => 'field_newsroom_ted_link:url',
        'query' => 'infsonewsroom:ContextTed',
      ),
      array(
        'field' => 'field_newsroom_registration_link:url',
        'query' => 'infsonewsroom:ContextRegistrationLink',
      ),
      array(
        'field' => 'field_newsroom_registration_link:title',
        'query' => 'infsonewsroom:ContextRegistrationLinkText',
      ),
      array(
        'field' => 'body',
        'query' => 'infsonewsroom:FullContent',
      ),
      array(
        'field' => 'field_newsroom_item_contact_text',
        'query' => 'infsonewsroom:ContextContactText',
      ),
      array(
        'field' => 'field_newsroom_item_contact_mail',
        'query' => 'infsonewsroom:ContextContactEmail',
      ),
      array(
        'field' => 'field_newsroom_item_linked_obj',
        'query' => 'infsonewsroom:FullLinkedObject',
      ),
      array(
        'field' => 'field_newsroom_item_pre_title',
        'query' => 'infsonewsroom:FullPreTitle',
      ),
      array(
        'field' => 'field_newsroom_item_quote_box',
        'query' => 'infsonewsroom:FullQuoteBox',
      ),
      array(
        'field' => 'field_newsroom_item_short_title',
        'query' => 'infsonewsroom:BasicShortTitle',
      ),
      array(
        'field' => 'field_newsroom_item_speaker',
        'query' => 'infsonewsroom:ContextSpeaker',
      ),
      array(
        'field' => 'field_newsroom_teaser',
        'query' => 'infsonewsroom:BasicTeaser',
      ),
      array(
        'field' => 'guid',
        'query' => '$field_newsroom_item_id',
      ),
      array(
        'field' => '_feed_changed',
        'query' => 'infsonewsroom:pubUpdateDate/text()',
        'tamper' => array(
          'plugin_id' => 'strtotime',
        ),
      ),
      array(
        'field' => 'language',
        'source' => 'Blank source 1',
        'tamper' => array(
          'plugin_id' => 'default_value',
          'default_value' => NewsroomHelper::getDefaultLanguage(),
        ),
      ),
    );

    return $field_mapping;
  }

  /**
   * Gets issue importer field mapping settings.
   *
   * @return array
   *   Issue importer field mapping settings.
   */
  private static function getIssueImporterMappings() {
    $field_mapping = array(
      array(
        'field' => 'title',
        'query' => 'title[@lang="' . NewsroomHelper::getDefaultLanguageUppercase() . '"]/text()',
      ),
      array(
        'field' => 'title_field',
        'query' => 'title',
      ),
      array(
        'field' => 'field_newsroom_nl_issue_date:start',
        'query' => 'pubDate/text()',
        'tamper' => array(
          'plugin_id' => 'strtotime',
        ),
      ),
      array(
        'field' => 'field_newsroom_newsletter_id',
        'query' => 'infsonewsroom:BasicIssueId/text()',
      ),
      array(
        'field' => 'field_newsroom_item_main_link:url',
        'query' => 'link',
      ),
      array(
        'field' => 'field_newsroom_newsletter_items:etid',
        'query' => 'infsonewsroom:BasicSvItemId/text()',
        'tamper' => array(
          'plugin_id' => 'efq_finder',
          'entity_type' => 'node',
          'bundle' => 'newsroom_item',
          'field' => 'field_newsroom_item_id',
        ),
      ),
      array(
        'field' => 'field_newsroom_service',
        'query' => 'infsonewsroom:BasicSvId/text()',
        'options' => array(
          'term_search' => '1',
          'autocreate' => 0,
        ),
        'tamper' => array(
          'entity_type' => 'taxonomy_term',
          'plugin_id' => 'efq_finder',
          'bundle' => NEXTEUROPA_NEWSROOM_SERVICE_VOCABULARY,
          'field' => 'field_newsroom_service_id',
        ),
      ),
      array(
        'field' => 'guid',
        'query' => '$field_newsroom_newsletter_id',
        'unique' => 1,
      ),
      array(
        'field' => 'language',
        'source' => 'Blank source 1',
        'tamper' => array(
          'plugin_id' => 'default_value',
          'default_value' => NewsroomHelper::getDefaultLanguage(),
        ),
      ),
    );

    return $field_mapping;
  }

  /**
   * Gets type importer field mapping settings.
   *
   * @return array
   *   Type importer field mapping settings.
   */
  private static function getTypeImporterMappings() {
    // Define the needed infos to build the importer dinamically.
    $field_mapping = array(
      array(
        'field' => 'guid',
        'query' => '@nrid',
        'unique' => 1,
      ),
      array(
        'field' => 'field_newsroom_type_id',
        'query' => 'infsonewsroom:BasicTypeId/text()',
      ),
      array(
        'field' => 'name',
        'query' => 'title[@lang="' . NewsroomHelper::getDefaultLanguageUppercase() . '"]/text()',
      ),
      array(
        'field' => 'name_field',
        'query' => 'title',
      ),
      array(
        'field' => 'parentguid',
        'query' => 'infsonewsroom:BasicTypeParent/text()',
        'tamper' => array(
          'plugin_id' => 'rewrite',
          'prefix' => 'type-',
        ),
      ),
    );

    return $field_mapping;
  }

  /**
   * Gets topic importer field mapping settings.
   *
   * @return array
   *   Topic importer field mapping settings.
   */
  private static function getTopicImporterMappings() {
    $field_mapping = array(
      array(
        'field' => 'Temporary target 1',
        'query' => '@infsonewsroom:TopicId',
        'target' => 'Temporary target 1',
      ),
      array(
        'field' => 'guid',
        'query' => '@nrid',
        'unique' => 1,
      ),
      array(
        'field' => 'field_newsroom_topic_id',
        'query' => '@infsonewsroom:TopicId',
      ),
      array(
        'field' => 'name',
        'query' => 'text()',
      ),
      array(
        'field' => 'name_field',
        'query' => 'text()',
      ),
      array(
        'field' => 'field_newsroom_category_domain',
        'query' => '@domain',
      ),
      array(
        'field' => 'parentguid',
        'query' => '@infsonewsroom:parentTopicId',
        'tamper' => array(
          'plugin_id' => 'rewrite',
          'prefix' => 'topic-',
        ),
      ),
    );

    return $field_mapping;
  }

  /**
   * Gets service importer field mapping settings.
   *
   * @return array
   *   Service importer field mapping settings.
   */
  private static function getServiceImporterMappings() {
    $field_mapping = array(
      array(
        'field' => 'guid',
        'query' => '@nrid',
        'unique' => 1,
      ),
      array(
        'field' => 'field_newsroom_service_id',
        'query' => 'infsonewsroom:BasicSvId/text()',
      ),
      array(
        'field' => 'name',
        'query' => 'title[@lang="' . NewsroomHelper::getDefaultLanguageUppercase() . '"]/text()',
      ),
      array(
        'field' => 'name_field',
        'query' => 'title',
      ),
      array(
        'field' => 'field_newsroom_topic',
        'query' => 'category[@domain="Subchapter"]/@infsonewsroom:TopicId',
      ),
      array(
        'field' => 'field_newsroom_service_active',
        'query' => 'infsonewsroom:BasicSvStatus/text()',
      ),
      array(
        'field' => 'field_newsroom_service_sample:url',
        'query' => 'infsonewsroom:archivesLink',
      ),
      array(
        'field' => 'field_newsroom_service_type',
        'query' => 'infsonewsroom:BasicSvType',
      ),
      array(
        'field' => 'description',
        'query' => 'description/text()',
      ),
      array(
        'field' => 'field_newsroom_basic_mailing',
        'query' => 'infsonewsroom:BasicSvMailing/text()',
      ),
      array(
        'field' => 'field_newsroom_mailing_exists',
        'query' => 'infsonewsroom:mailingExists/text()',
      ),
      array(
        'field' => 'field_newsroom_service_image:uri',
        'query' => 'infsonewsroom:BasicSvVisuUrl/text()',
      ),
      array(
        'field' => 'parentguid',
        'query' => '@infsonewsroom:parentTopicId',
        'tamper' => array(
          'plugin_id' => 'rewrite',
          'prefix' => 'service-',
        ),
      ),
    );

    return $field_mapping;
  }


  /**
   * Validates and returns day number.
   *
   * @param string $value
   *   Day number.
   *
   * @return int
   *   Day number.
   */
  private static function getDay($value) {
    return preg_match('/^\d{1,2}$/', $value) ? (int) $value : NewsroomHelper::getFormatedDate('d');
  }

  /**
   * Validates and returns week number.
   *
   * @param string $value
   *   Day number.
   *
   * @return int
   *   Week number.
   */
  private static function getWeek($value) {
    return preg_match('/^\d{1,2}$/', $value) ? (int) $value : NewsroomHelper::getFormatedDate('W');
  }

  /**
   * Validates and returns month number.
   *
   * @param string $value
   *   Month number.
   *
   * @return int
   *   Month number.
   */
  private static function getMonth($value) {
    return preg_match('/^\d{1,2}$/', $value) ? (int) $value : NewsroomHelper::getFormatedDate('n');
  }

  /**
   * Validates and returns year number.
   *
   * @param string $value
   *   Year number.
   *
   * @return int
   *   Year number.
   */
  private static function getYear($value) {
    return preg_match('/^\d{4}$/', $value) ? (int) $value : NewsroomHelper::getFormatedDate('Y');
  }

  /**
   * Gets taxonomy term topic from url name.
   *
   * @param string $topic_url
   *   Topic taxonomy term name.
   *
   * @return object
   *   Taxonomy term object.
   */
  private static function getTopic($topic_url) {
    $topic = NewsroomBuilder::getTaxonomyTerm($topic_url, NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY);
    if ($topic) {
      // Try to find active menu.
      if ($path = NewsroomHelper::fetchActiveMenuPath($topic->tid)) {
        menu_tree_set_path('main-menu', $path);
      }
    }
    return $topic;
  }

  /**
   * Validates date.
   *
   * @param string $value
   *   Date string.
   *
   * @return string|null
   *   Date string.
   */
  private static function getDate($value) {
    return NewsroomHelper::checkDateFormat($value);
  }

  /**
   * Gets taxonomy term type from url name.
   *
   * @param string $type_url
   *   Type taxonomy term name.
   *
   * @return object
   *   Taxonomy term object.
   */
  private static function getType($type_url) {
    return NewsroomBuilder::getTaxonomyTerm($type_url, NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY);
  }

  /**
   * Gets taxonomy term from url name.
   *
   * @param string $taxonomy_term_url
   *   Taxonomy term url name.
   * @param string $vocabulary_name
   *   Vocabulary name.
   *
   * @return object
   *   Taxonomy term object.
   */
  private static function getTaxonomyTerm($taxonomy_term_url, $vocabulary_name) {
    return $taxonomy_term_url == NEXTEUROPA_NEWSROOM_ALL ? NULL : NewsroomHelper::getTermFromRequest($taxonomy_term_url, $vocabulary_name);
  }

  /**
   * Builds newsroom page object.
   *
   * @param string $type_url
   *   Type URL part.
   * @param string $topic_url
   *   Topic URL part.
   * @param string|null $start_date
   *   Start date.
   * @param string|null $end_date
   *   End date.
   *
   * @return NewsroomPage
   *   NewsroomPage object.
   */
  public static function buildPageNewsroomPage($type_url, $topic_url, $start_date = NULL, $end_date = NULL) {
    $type = NewsroomBuilder::getType($type_url);
    $topic = NewsroomBuilder::getTopic($topic_url);
    $start_date = NewsroomBuilder::getDate($start_date);
    $end_date = NewsroomBuilder::getDate($end_date);
    return new NewsroomPage($type, $topic, $start_date, $end_date);
  }

  /**
   * Builds newsroom page object.
   *
   * @param object|null $type
   *   Newsroom type taxonomy term.
   * @param object|null $topic
   *   Newsroom topic taxonomy term.
   * @param string|null $start_date
   *   Start date.
   * @param string|null $end_date
   *   End date.
   *
   * @return NewsroomPage
   *   NewsroomPage object.
   */
  public static function buildNewsroomPage($type = NULL, $topic = NULL, $start_date = NULL, $end_date = NULL) {
    $start_date = NewsroomBuilder::getDate($start_date);
    $end_date = NewsroomBuilder::getDate($end_date);
    return new NewsroomPage($type, $topic, $start_date, $end_date);
  }

}
