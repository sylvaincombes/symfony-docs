by_reference
~~~~~~~~~~~~

**type**: ``boolean`` **default**: ``true``

In most cases, if you have a ``name`` field, then you expect ``setName()``
to be called on the underlying object. In some cases, however, ``setName()``
may *not* be called. Setting ``by_reference`` ensures that the setter is
called in all cases.

To explain this further, here's a simple example::

    $builder = $this->createFormBuilder($article);
    $builder
        ->add('title', 'text')
        ->add(
            $builder->create('author', 'form', array('by_reference' => ?))
                ->add('name', 'text')
                ->add('email', 'email')
        )

If ``by_reference`` is true, the following takes place behind the scenes
when you call ``submit()`` (or ``handleRequest()``) on the form::

    $article->setTitle('...');
    $article->getAuthor()->setName('...');
    $article->getAuthor()->setEmail('...');

Notice that ``setAuthor()`` is not called. The author is modified by reference.

If you set ``by_reference`` to false, submitting looks like this::

    $article->setTitle('...');
    $author = $article->getAuthor();
    $author->setName('...');
    $author->setEmail('...');
    $article->setAuthor($author);

So, all that ``by_reference=false`` really does is force the framework to
call the setter on the parent object.

Similarly, if you're using the :doc:`collection</reference/forms/types/collection>`
form type where your underlying collection data is an object (like with Doctrine's
``ArrayCollection``), then ``by_reference`` must be set to ``false`` if you
need the adder and remover (e.g. ``addAuthor()`` and ``removeAuthor()``) to be called.
