mtd-cli
=======

|Builds| |FreeBSD Build Status| |CodeQL|

Overview
--------

mtd-cli is a command line client for Linux (other Unices should not be
hard to support) to interface with the UK’s HMRC `Make Tax
Digital <https://developer.service.hmrc.gov.uk/api-documentation>`__ API

It makes use of `libmtdac <https://github.com/ac000/libmtdac>`__

Build it
--------

mtd-cli is primarily developed under Linux but it also builds and runs
under FreeBSD.

Linux
~~~~~

Once you have the above library built and installed, building this is as
simple as

::

   $ make

FreeBSD
~~~~~~~

::

   $ gmake

or if you don’t have GCC installed

::

   $ gmake CC=clang

How to use
----------

It’s ready to use straight away, you can place the binary anywhere you
like or just run it in place

::

   $ src/mtd-cli

It has a fairly straightforward interface, essentially

::

   mtd-cli init|init-creds|init-oauth|init-nino|bd|biss|bsas|ical|ilos|isi|ob|pb|said|seb|vat|test_cu|test_fph

The first argument specifies the API to interface with

-  **init** is for doing an initial setup, creating the JSON config
   files. This runs the equivalent of; *init-creds*, *init-oauth* &
   *init-nino*.

-  **init-creds** is for regenerating the creds.json file.

-  **init-oauth** is for doing a reauthorisation.

-  **init-nino** is for storing the National Insurance Number in the
   nino.json file.

Each of the above init functions (except *init-nino*) takes an argument
of either *itsa* or *vat* depending on which API is to be initialised.

Supported API endpoints
=======================

See
`libmtdac <https://github.com/ac000/libmtdac/blob/master/README.rst#overview>`__

Environment variables
---------------------

Currently there are two environment variables that can bet set to
control behaviour

**MTD_CLI_OPT_LOG_LEVEL**
~~~~~~~~~~~~~~~~~~~~~~~~~

This can be used to override the default log level (MTD_OPT_LOG_ERR).

Currently recognised values are; *debug* & *info*

**MTD_CLI_OPT_NO_FPH_HDRS**
~~~~~~~~~~~~~~~~~~~~~~~~~~~

This can be used to disable the sending of ‘Fraud Prevention Headers’,
set it to

*true* or *1*

**MTD_CLI_HDRS**
~~~~~~~~~~~~~~~~

This can be used to set extra HTTP headers to be sent.

Currently only one header is supported which should be sufficient for
setting the *Gov-Test-Scenario* Test API header. e.g

::

   $ MTD_CLI_HDRS="Gov-Test-Scenario: NO_SUBMISSIONS_EXIST" mtd-cli sa cr-intent-to-crystallise 2018-19

License
-------

This is licensed under the GNU General Public License (GPL) version 2

See *COPYING* in the repository root for details.

Contributing
------------

See `CodingStyle.rst </CodingStyle.rst>`__ &
`Contributing.rst </Contributing.rst>`__

Andrew Clayton <ac@sigsegv.uk>

.. |Builds| image:: https://github.com/ac000/mtd-cli/actions/workflows/build_tests.yaml/badge.svg
   :target: https://github.com/ac000/mtd-cli/actions/workflows/build_tests.yaml
.. |FreeBSD Build Status| image:: https://api.cirrus-ci.com/github/ac000/mtd-cli.svg
   :target: https://cirrus-ci.com/github/ac000/mtd-cli
.. |CodeQL| image:: https://github.com/ac000/mtd-cli/workflows/CodeQL/badge.svg
   :target: https://github.com/ac000/mtd-cli/actions?query=workflow:CodeQL
