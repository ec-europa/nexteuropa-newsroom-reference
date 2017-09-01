<?php

/**
 * @file
 * Code for the NexteuropaNewsroomAgendaSchedule class.
 */

/**
 * NexteuropaNewsroomAgendaSchedule class.
 */
class NexteuropaNewsroomAgendaSchedule extends NexteuropaNewsroomAgenda {

  protected $lastAgendaDate = NULL;
  protected $firstAgendaDate = NULL;

  /**
   * NexteuropaNewsroomAgendaSchedule constructor.
   *
   * @param object $type
   *   Newsroom type.
   * @param array $topics
   *   Newsroom topic.
   * @param object $current_day
   *   Current date.
   */
  public function __construct($type, $topics, $current_day) {
    $this->setCurrentDate($current_day);
    parent::__construct($type, $topics);
  }

  /**
   * Gets the first date in the agenda.
   *
   * @return Datetime
   *   First date in the agenda.
   */
  public function getFirstAgendaDate() {
    return $this->firstAgendaDate;
  }

  /**
   * Sets the first date in the agenda.
   *
   * @param object $value
   *   First date in the agenda.
   */
  public function setFirstAgendaDate($value) {
    $this->firstAgendaDate = $value;
  }

  /**
   * Gets the latest date in the agenda.
   *
   * @return Datetime
   *   Latest date in the agenda.
   */
  public function getLastAgendaDate() {
    return $this->lastAgendaDate;
  }

  /**
   * Sets the latest date in the agenda.
   *
   * @param object $value
   *   Latest date in the agenda.
   */
  public function setLastAgendaDate($value) {
    $this->lastAgendaDate = $value;
  }

  /**
   * Setups agenda conditions.
   */
  protected function setupAgenda() {
    $next_day = clone $this->getCurrentDate();
    // Build agenda for the current date.
    $next_day->modify('+1 day');
    $this->setCurrentItems($this->buildAgenda($this->getCurrentDate(), $next_day));
    $this->setLastAgendaDate($next_day);
    $this->findUpcomingItems();
    // We don't need navigation for the blocks.
    if (!$this->getIsBlock()) {
      $this->findPastItems();
    }
  }

  /**
   * Adds date url parts.
   *
   * @param object $date
   *   The current date.
   */
  protected function setUrlItems($date) {
    if ($date) {
      $this->addUrlPart($date->format('j'));
      $this->addUrlPart($date->format('n'));
      $this->addUrlPart($date->format('Y'));
    }
  }

  /**
   * Finds and sets upcoming items.
   */
  protected function findUpcomingItems() {
    $start_date = clone $this->getCurrentDate();
    // We start from the next day after the current.
    $start_date->modify('+1 day');
    $this->setLastAgendaDate($start_date);
    $upcoming_items = [];
    // We add one day to include the last day also.
    $last_event_date = $this->getUtmostDate(FALSE);
    if ($last_event_date) {
      $last_event_date->modify('+1 day');
      $number_to_display = $this->getItemsNumber();
      while ($this->getUpcommingNewsItemCount() < $number_to_display && $start_date <= $last_event_date) {
        $next_day = clone $start_date;
        $next_day->modify('+1 day');
        $current_items = $this->buildAgenda($start_date, $next_day, FALSE);
        $this->addUpcommingNewsItem($current_items);
        $upcoming_items = array_merge($upcoming_items, $current_items);
        $this->setLastAgendaDate($start_date);
        $start_date->modify('+1 day');
      }
    }
    if (!empty($upcoming_items)) {
      $this->setUpcomingDate($start_date);
    }
    $this->setUpcomingItems($upcoming_items);
  }

  /**
   * Finds and sets past items.
   */
  protected function findPastItems() {
    $start_date = clone $this->getCurrentDate();
    $this->setFirstAgendaDate($start_date);
    $past_items = [];
    // We add one day to include the last day also.
    $first_event_date = $this->getUtmostDate(TRUE);
    if ($first_event_date) {
      $number_to_display = $this->getItemsNumber();
      while ($this->getPastNewsItemCount() < $number_to_display && $start_date >= $first_event_date) {
        $next_day = clone $start_date;
        $next_day->modify('-1 day');
        $current_items = $this->buildAgenda($next_day, $start_date, FALSE);
        $this->addPastNewsItem($current_items);
        $past_items = array_merge($past_items, $current_items);
        $this->setFirstAgendaDate($start_date);
        $start_date->modify('-1 day');
      }
    }
    // We set the previous date for the "Previous link".
    if (!empty($past_items)) {
      $this->setPreviousDate($start_date->modify('-1 day'));
    }
    $this->setPastItems($past_items);
  }

  /**
   * Checks agenda items for existence of events.
   *
   * @param array $items
   *   Agenda items.
   *
   * @return bool
   *   Has events.
   */
  protected function hasItems($items) {
    $has_current_items = FALSE;
    if ($items) {
      foreach ($items as $item) {
        if (!empty($item->getItems())) {
          $has_current_items = TRUE;
          break;
        }
      }
    }
    return $has_current_items;
  }

  /**
   * Loads result from the current query.
   *
   * @return array
   *   Result.
   */
  protected function loadResult() {
    return $this->getQuery()->execute()->fetchAll();
  }

  /**
   * Gets utmost date.
   *
   * @param bool $first
   *   Return the first or last utmost date in the result.
   *
   * @return object
   *   Utmost date.
   */
  protected function getUtmostDate($first = TRUE) {
    $utmost_date = NULL;
    $result = $this->getResult();
    if ($result) {
      $last_item = $first ? reset($result) : array_pop($result);
      if ($last_item) {
        $utmost_date = clone $last_item->start_date_obj;
      }
    }
    return $utmost_date;
  }

}
