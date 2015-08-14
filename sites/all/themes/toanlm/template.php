<?php 
/**
* Override or insert variables into the page template.
*/
function toanlm_process_page(&$variables) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_page_alter($variables);
  }
}

/**
* Override or insert variables into the page template for HTML output.
*/
function toanlm_process_html(&$variables) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_html_alter($variables);
  }
}

/**
* Khai bao bien dung ca site global.
*/
function toanlm_preprocess_node(&$variables) {
    $variables['bien_dung_toancuc'] = t('mysite takes no responsibility for user contributed content and comments.');
}

/**
* Hide các region.
*/
/*
function toanlm_preprocess(&$variables, $hook) {
    if ($variables['is_front']) {
        switch ($hook) {
            case 'html':
            // Override the node title and use a custom title
            // for the front page.
            $variables['head_title'] = t('Welcome to My site!');
            break;
            case 'region':
            // Empty all regions besides the content.
            if ($variables['region'] != 'content') {
            $variables['content'] = '';
            }
            break;
            case 'page':
            // Do not display the node title for the front page.
            $variables['title'] = '';
            break;
            case 'node':
            // Hide submission information and links.
            $variables['display_submitted'] = FALSE;
            unset($variables['content']['links']);
            break;
        }
    }
}*/

?>