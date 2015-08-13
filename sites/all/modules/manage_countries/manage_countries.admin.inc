<?php
/**
 * Menu callback; Displays a list of all countries.
 */
function manage_countries_admin_overview() {
  $header = array();
  $header[] = array('data' => t('Name'), 'field' => 'c.country_name', 'sort' => 'asc');
  $header[] = array('data' => t('Status'), 'field' => 'c.status');
  $header[] = array('data' => t('Operations'));
  
  $query = db_select('manage_countries', 'c')->extend('PagerDefault')->extend('TableSort');

  $result = $query
    ->fields('c')
    ->orderByHeader($header)
    ->limit(50)
    ->execute();

  $destination = drupal_get_destination();

  $rows = array();
  // Note that additional id's are added for testing.
  foreach ($result as $country) {
    $row = array();
    $row[] = l($country->country_name, 'admin/config/regional/manage_countries/' . $country->cid . '/edit', array('query' => $destination));
    $row[] = $country->status;
    
    $operations = l(t('edit'), 'admin/config/regional/manage_countries/' . $country->cid . '/edit', array('query' => $destination));
    $operations .= '&nbsp;&nbsp;&nbsp;' . l(t('delete'), 'admin/config/regional/manage_countries/' . $country->cid . '/delete');
    $row[] = $operations;
    
    $rows[] = $row;
  }
  if (empty($rows)) {
    $rows[] = array(
      array('data' => t('No countries are available.'), 'colspan' => count($header)),
    );
  }

  $build['countries_table']  = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );
  $build['countries_pager'] = array('#theme' => 'pager');

  return $build;
}

function manage_countries_admin_page($country = NULL) {
  // Menu callbacks and local actions do not have page titles.
  if (isset($country)) {
    drupal_set_title(t('Edit country %title', array('%title' => $country->country_name)), PASS_THROUGH);
  }
  else {
    drupal_set_title(t('Add country'), PASS_THROUGH);
    $country = manage_country_load(0);
    if ( $country == false )
    {
      $country = new stdClass;
      $country->cid = null;
      $country->status = 1;
      $country->country_name = null;
    }
    //var_dump($country);die;
  }
  return drupal_get_form('manage_countries_admin_form', $country);
}



/**
 * Generate a country form.
 *
 * @ingroup forms
 * @see countries_admin_form_validate()
 * @see countries_admin_form_submit()
 */
function manage_countries_admin_form($form, &$form_state, $country) {
  $form['cid'] = array(
    '#type' => 'value',
    '#value' => $country->cid,
  );
  $form['country_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $country->country_name,
    '#description' => t('Specify an unique name for this country.'),
    '#required' => TRUE,
    '#maxlength' => 95,
  );
  
  
  $form['status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Status'),
    '#default_value' => $country->status,
    '#description' => t('Disabling a country should removing it from all country listings, with the exclusion of views and fields define by the Countries module. These will allow you to choose the status per field.'),
  );

  $form['#country'] = $country;
  //field_attach_form('manage_countries', $country, $form, $form_state);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 100,
  );
  return $form;
}

/**
 * Process country form submissions.
 */
function manage_countries_admin_form_submit($form, &$form_state) {
  $country = (object) $form_state['values'];
  //entity_form_submit_build_entity('manage_countries', $country, $form, $form_state);
  $data = array(
      'country_name' => $country->country_name,
      'status' => $country->status,
    );

  if ( is_object($country) && property_exists($country, 'cid') && $country->cid ) {
    $num_updated = db_update('manage_countries')
      ->fields($data)
      ->condition('cid', $country->cid, '=')
      ->execute();
    krumo($num_updated);
    $message = t('The country %country has been updated.', array('%country' => $country->country_name));
  }
  else {
    $nid = db_insert('manage_countries') // Table name no longer needs {}
    ->fields($data)
    ->execute();
    krumo($nid);
    $message = t('Added country %country.', array('%country' => $country->country_name));
  }
  drupal_set_message($message);
  $form_state['redirect'] = 'admin/config/regional/manage_countries';
}

/**
 * Menu callback; confirm deletion of a country.
 *
 * @ingroup forms
 * @see countries_admin_delete_submit()
 */
function manage_countries_admin_delete($form, &$form_state, $country) {
  /*if (country_is_locked($country)) {
    drupal_set_message(t('Core countries defined by the system can not be deleted.'), 'error');
    drupal_goto('admin/config/regional/countries');
  }*/
  $form['#country'] = $country;
  return confirm_form($form,
    t('Are you sure you want to delete the country %country?', array('%country' => $country->country_name)),
    'admin/config/regional/countries',
    t('References that use this country will become invalid. This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Process countries delete form submission.
 */
function manage_countries_admin_delete_submit($form, &$form_state) {
  $country = $form['#country'];
  manage_countries_delete_country($country->cid);

  drupal_set_message(t('Deleted country %country.', array('%country' => $country->country_name)));
  $form_state['redirect'] = 'admin/config/regional/manage_countries';
}

function manage_countries_delete_country($cid=0)
{
  $num_updated = db_delete('manage_countries')
    ->condition('cid', $cid, '=')
    ->execute();
  return $num_updated;
}
?>
