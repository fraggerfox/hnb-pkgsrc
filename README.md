hnb-pkgsrc
==========

NetBSD pkgsrc script for Hierarchical Notebook (hnb)

You can find Hierarchical Notebook (hnb) [here][1]

NOTE: This is not a new package, but is a fixed version of the package that can
run in both i386 and amd64

Installation
------------

Copy `editors/hnb` folder to `/usr/pkgsrc` directory.

NOTE: If your pkgsrc directory is different from above, copy to the respective
place.

Usage
-----

Once you have copied the folder, install it as you would do for any package.

`$ cd /usr/pkgsrc/editors/hnb`<br>
`$ make install clean`

For a list of dependencies for the build check [here][2]

NOTE: If you are using pkgsrc in a non NetBSD system, replace `make` with
`bmake` in the above example.

Credits
-------

* Hierarchical Notebook (hnb) was originally written by `Øyvind Kolås`
* The original pkgsrc script was written by `jmmv@NetBSD.org`
* Thanks to `coypu` for reviewing and suggesting fixes / changes to conform to
  standardized `Makefile`.

License
-------

BSD 2-clause. See LICENSE.

[1]: http://hnb.sourceforge.net/
[2]: http://hnb.sourceforge.net/Documentation/
