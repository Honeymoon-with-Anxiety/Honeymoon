<?php

namespace controllers;

class User
{
    public function getAddUser(\Base $base)
    {
        $base->set('title', 'Add User');
        echo \Template::instance()->render('/user/pridat.html');
    }

    public function postAddUser(\Base $base)
    {
        $user = new \models\User();
        $user->copyFrom('POST');
        $user->save();
        $base->reroute('/pokus');
    }
}
