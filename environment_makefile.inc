<?php
/**
 * @file
 * environment_makefile.inc
 *
 * Environmentally aware module handling.
 */

namespace Drupal\environment_makefile;
use \Exception;

if ( ! defined(ENVIRONMENT) ) {
  define(ENVIRONMENT, getenv('ENVTYPE'));
}

/**
 * Reverts Modules to environment appropriate state.
 */
function revert_modules() {
  enable_modules();
  dev_only_modules();
  disable_unwanted_modules();
}

/**
 * Enable appropriate modules for this environment.
 */
function enable_modules($type = 'enabled') {
  // Enable each module individually so we can capture errors better
  foreach ( makefile_metadata($type) as $module ) {
    drupal_set_message(t('Enabling @type @module', array('@type' => $type, '@module' => $module)), 'ok', FALSE);
    if ( ! module_exists($module) && ! module_enable(array($module), TRUE) ) {
      throw new Exception(t('Unable to enable @module.', array('@module' => $module)));
    }
  }
}

/**
 * Enable appropriate modules for this environment.
 */
function dev_only_modules() {
  if ( is_production() ) {
    disable_unwanted_modules('dev_only');
  } else {
    enable_modules('dev_only');
  }
}

function is_production() {
  return ENVIRONMENT && in_array(ENVIRONMENT,
    variable_get('environment_makefile_product_environments',
      array('production', 'staging')));
}

/**
 * Disables modules, by default it disables core modules that we don't use
 */
function disable_unwanted_modules($type = 'disabled') {
  foreach ( makefile_metadata($type)as $module ) {
    drupal_set_message(t('Disabling @type @module', array('@type' => $type, '@module' => $module)), 'ok', FALSE);
    if ( module_exists($module) ) module_disable(array($module), TRUE);
  }
}

/**
 * Parse site makefile and return configuration metadata.
 *
 * @param string $type disabled_projects, dev_only_projects, sub_projects, projects
 * @return array list of projects from makefile
 */
function makefile_metadata( $type = 'enabled' ) {
  $makefile = &drupal_static(__FUNCTION__);
  if ( ! isset($makefile) ) {
    $filename = makefile_location();
    $makefile = make_parse_info_file($filename);
  }

  if ( empty($makefile) ) {
    throw new Exception(t('Unable to read @makefile.', array('@makefile' => $filename)));
  }

  return isset($makefile[$type]) ? $makefile[$type] : array();
}

/**
 * Get the location of the site makefile.
 */
function makefile_location() {
  return variable_get('makefile_path',
    dirname(DRUPAL_ROOT) . '/makefiles/' . basename(dirname(DRUPAL_ROOT)) . ".make"
  );
}
