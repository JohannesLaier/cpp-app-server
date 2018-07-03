# Eros C++ Cloud App Server #

This is a simple cpp based web server that allows to host small cpp based web apps. The webb apps only contains servlets for dynamic request processing and static files.

## Installation ##

To install the server first it needs to get compiled and moved to thr right place:

```sh
make
make install
```

This command is compiling the app, generating a new user called eroscloud. And placed a sample comfig file into the config folder

```
/etc/eroscloud
```
This server has multisite support. To create a new file in the following folder:

```
/etc/eroscloud/sites-enabled/
```

To enable this site create an symbolic link in this folder to sour enabled site:

```
cd /etc/eroscloud/sites-available/
ln -s ../sites-enabled/your-site.conf .
```
An example site is pre configered in your project after installation and just needs to get activated. The app server is listening to the port 10105 and the htdocs folder of it is in the /var/www directory.

```
(10105){
	[/var/www]
}
```
## Create you first project ##

To create a new web app you can use the dev-tools placed in the sdk folder to create a new project. This dev-tools are written in php for the php-cli tool. In future this tools sould be written in a different language.

Use this command to create a new project:

```php
php create_project.php myapp /var/www/myapp
```
To add a new servlet to this project use the following command:

```php
php create_class.php MyNewServlet /var/www/myapp
```
## Project structure ##

In the created webapp the structure is divided into a src/ and a war/ folder. The src/ folder conatins all servlets and other cpp files to build the project. The war/ directory contains all static files like images, css and html files, fonts, ... Library of the project like libmysql.a can be placed in the lib/ directory.

To build you webapp execute the following command in the directory of the webapp:

```sh
make
```