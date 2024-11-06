<?php

namespace models;

use DB\Cortex;

class User extends Cortex
{
    protected $db = 'DB';
    protected $table = 'uzivatel';

    public function set_heslo($value)
    {
        return password_hash($value, PASSWORD_DEFAULT);
    }
}