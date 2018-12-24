# Applyst

Applyst is a web based front-end for [AppStreamQt](https://github.com/ximion/appstream/tree/master/qt). With Applyst, you can search for applications by name, and view applications' icon, screenshots, descriptions, and features.

The application is currently being updated and may have non-functioning features. There is also a lack of documentation. Please feel free to contribute.

## Dependencies
 * Grantlee
 * AppStreamQt
 * Cutelyst 2.0.0 or newer with enabled Grantlee plugin

## Running
You can run it with cutelyst-wsgi or uWSGI, both have similar command line options, and you should look at their documentation to know their options, the simplest one:

    cutelyst-wsgi2 --application path/to/libApplyst.so --http-socket :3000 --chdir parent_of_root_dir --static-map /static=root/static

The chdir needs to point to the parent of the root directory that came from this project. The option --static-map is used to serve the static files.

Now point your browser to http://localhost:3000

## Known issues

- Icons not shown.
