<?php
require 'vendor/autoload.php';
$f3 = \Base::instance();
$f3->config('./app/configs/config.ini');

$f3->set('DB', new \DB\SQL(
    $f3->get('db.dsn'),
    $f3->get('db.username'),
    $f3->get('db.password')
));

$f3->run();