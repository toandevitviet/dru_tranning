<?php
function toanlm_form_system_theme_settings_alter(&$form, $form_state) {
    
  //group option
  $form['social'] = array(
    '#type' => 'fieldset',
    '#title' => 'Social setting',
    '#collapsible' => true,
    '#collapsed' => false,
  );
    
  $form['social']['google_url'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Google Url'),
    '#default_value' => theme_get_setting('google_url', 'toanlm'),
    '#description'   => t("Place this text of google url."),
  );
  
  $form['social']['social_display'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Display social icon'),
    '#default_value' => theme_get_setting('social_display', 'toanlm'),
    '#description'   => t("Checked this option to show social icon."),
  );
  
}
?>