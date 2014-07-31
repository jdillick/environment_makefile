# Environment Makefile

environment_modules is a Drupal 7 module that provides a facility to auto enable / disable modules based on makefile and environments.
Copyright (C) 2014 John Dillick

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

## Requirements
- Drupal 7.x
- PHP 5.3+

## Configuration
To configure production environments, have your system administrator configure the ENVTYPE environment variable, setting to _production_, _staging_, _dev_, or _local_ as appropriate.

In linux, add a /etc/profile.d/envtype.sh file:
```bash
#!/bin/bash
ENVTYPE=production
readonly ENVTYPE
export ENVTYPE
```

Configure your virtual host in Apache with:
```
SetEnv ENVTYPE production
```

### Optional Configuration
To set an alternate set of production environments, use strongarm or $conf array to set the _environment_makefile_product_environments_ variable:

```php
$conf['environment_makefile_product_environments'] = array(
  'prod',
  'stag',
  'test',
);
```

### Makefile location
environment_makefile assumes your makefile will be located in a makefiles directory adjacent to the Drupal webroot, and named to match the parent directory:

```
example.com/
├── makefiles
│   └── example.com.make
└── webroot
```

If you would like to specify the full path to your makefile, use strongarm or $conf to set the _makefile_path_ variable.

## To Use

environment_makefile uses an augmented drush make file to manage the enabling and disabling of modules in your Drupal deployment environments.

In your makefile, you can specify modules and submodules that should be enabled or disabled by using the following groupings:

- *enabled*: these modules will be enabled in all environments
- *disabled*: these modules will be disabled in all environments
- *dev_only*: these modules will be disabled in production environments, and enabled everywhere else.

### Example Makefile

```
core = 7.x

api = 2

projects[drupal][version] = "7.28"

disabled[] = overlay
disabled[] = dashboard

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.4"
enabled[] = ctools
enabled[] = views_content
dev_only[] = bulk_export
```

## Drush Support
Drush is the primary means of initiating environment_makefile.

```bash
drush @alias environment-makefile # alias envm
```

## License
GNU GPL version 2 or later
