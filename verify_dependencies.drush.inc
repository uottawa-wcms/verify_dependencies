<?php

/**
 * Implements hook_drush_command().
 */
function verify_dependencies_drush_command() {
  return array(
    'verify-dependencies' => array(
      'aliases' => array(
        'vdep'
      ),
      'description' => 'Verifies that all dependencies are enabled',
      'examples' => array(
        'drush vd',
      ),
      'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    ),
  );
}

/**
 * Command callback for verify-dependencies (vd). 
 * 
 * This command will search the dependencies of all enabled modules, find those
 * that have disabled dependencies and enable them.
 */
function drush_verify_dependencies() {
  $modules_to_enable = array();
  $modules = _system_rebuild_module_data();
  foreach ($modules as $module) {
    if (module_exists($module->name)) {
      foreach ($module->info['dependencies'] as $dependency_tokens) {
        $dinfo = _verify_dependencies_parse_dependency($dependency_tokens);
        $dependency = $dinfo['module'];
        if (!module_exists($dependency)) {
          $modules_to_enable[$dependency] = $dependency;
        }
      }
    }
  }
  if (empty($modules_to_enable)) {
    return drush_log(dt('Dependencies are up to date'), 'ok');
  } else {
    return drush_invoke('pm-enable', array(
      'extensions' => implode(',', $modules_to_enable),
    ));
  }
}

/**
 * Parses a dependency string and returns information about it.
 * 
 * This is to support dependencies like system (> 7.12) for example.
 * 
 * @param string $dependency A dependency string
 * @return array An array of dependency information:
 * - module: The name of the module that is part of the dependency
 */
function _verify_dependencies_parse_dependency($dependency) {
  $pieces = explode(' ', $dependency, 2);
  $results = array(
    'module' => $pieces[0],
  );
  return $results;
}