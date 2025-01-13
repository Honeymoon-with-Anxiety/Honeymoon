<<<<<<< Updated upstream
<?php

namespace controllers;

class Index
{
    public function index(\Base $base)
    {
        echo "funguje";
    }

    public function pokus(\Base $base)
    {
        //$base->set('title', 'Pokus');
        echo \Template::instance()->render('nastenka.html');
    }
=======
<?php

namespace controllers;

class Index
{
    public function index(\Base $base)
    {
        echo "funguje";
    }

    public function pokus(\Base $base)
    {
        //$base->set('title', 'Pokus');
        echo \Template::instance()->render('nastenka.html');
    }
>>>>>>> Stashed changes
}