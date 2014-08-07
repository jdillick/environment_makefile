<?php
/**
 * @file
 * environment_makefile.drush.inc
 * Provides environment-makefile (envm) drush command.
 */

use \Drupal\environment_makefile as envm;

/**
 * Implements hook_drush_command().
 */
function environment_makefile_drush_command() {
  return array(
    'environment-makefile' => array(
      'description' => 'Ensure only environment appropriate modules are enabled.',
      'aliases' => array('envm'),
    ),
  );
}

/**
 * Drush envm command.
 *
 * Reverts module to appropriate state for the current environment.
 */
function drush_environment_makefile_environment_makefile() {
  module_load_include('inc', 'environment_makefile', 'environment_makefile');
  drush_print(dt('Ensuring only environment appropriate modules are enabled.'));
  envm\revert_modules();
}
