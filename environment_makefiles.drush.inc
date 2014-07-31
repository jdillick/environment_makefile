<?php
/**
 * @file
 * environment_modules.drush.inc
 * Provides environment-modules (envm) drush command.
 */

use \Drupal\environment_modules as envm;

/**
 * Implements hook_drush_command().
 */
function environment_modules_drush_command() {
  return array(
    'environment-modules' => array(
      'description' => 'Ensure only environment appropriate modules are enabled.',
      'aliases' => array('envm'),
    ),
  );
}

function drush_environment_modules_environment_modules() {
  module_load_include('inc', 'environment_modules', 'environment_modules');
  drush_print(dt('Ensuring only environment appropriate modules are enabled.'));
  envm\revert_modules();
}
