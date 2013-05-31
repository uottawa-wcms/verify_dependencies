This module can be installed as normal. You will then have access to a 
drush command:

drush -y @sitealias verify-dependencies

or it's alias "vdep".

When run from the command line, it will look at all your current active modules,
identify any missing ones from the dependencies and attempt to enable them
(by invoking pm-enable).

You will receive the normal warning from pm-enable if a dependency does
not exist in the code base.


