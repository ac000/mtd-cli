## Overview

mtd-cli is a command line client for Linux (other Unices should not be hard to
support) to interface with the UK's HMRC
[Make Tax Digital](https://developer.service.hmrc.gov.uk/api-documentation) API

It makes use of [libmtdac](https://github.com/ac000/libmtdac)

Currently it just supports the Self-Assessment API.


## Build it

Once you have the above library built and installed, building this is as
simple as

    $ make


## How to use

It's ready to use straight away, you can place the binary anywhere you like
or just run it in place

    $ src/mtd-cli

It has a fairly straightforward interface, essentially

    mtd-cli init|oauth|sa [endpoint args ...]

The first argument specifies the API to interface with, currently just three
are supported

  * **init** is for doing an initial setup, creating appropriate oauth.json &
    config.json files.

  * **oauth** is for doing doing a reauthorisation.

  * **sa** is for interacting with the Self-Assessment API.


*init* and *oauth* don't take any arguments.

*sa* takes various arguments, the first of which is the endpoint of the API
to connect to. These are

    list-employments get-employment list-obligations list-periods create-period
    get-period update-period get-annual-summary update-annual-summary
    submit-end-of-period-statement get-end-of-period-statement

The following shows each of the above and what arguments (if any) they take.

    $ mtd-cli sa list-employments

    $ mtd-cli sa get-employment selfEmploymentId

    $ mtd-cli sa list-obligations selfEmploymentId

    $ mtd-cli sa list-periods selfEmploymentId

    $ mtd-cli sa create-period <file> selfEmploymentId

    $ mtd-cli sa get-period selfEmploymentId periodId

    $ mtd-cli sa update-period <file> selfEmploymentId periodId

    $ mtd-cli sa get-annual-summary selfEmploymentId taxYear

    $ mtd-cli sa update-annual-summary <file> selfEmploymentId taxYear

    $ mtd-cli sa submit-end-of-period-statement <file> selfEmploymentId start end

    $ mtd-cli sa get-end-of-period-statement selfEmploymentId start|- end|-


*selfEmploymentId* is an 'id' as returned from '*mtd-cli sa list-employments*'.

*periodId* is an 'id' as returned from '*mtd-cli sa list-periods ...*'.

*<file>* is a file containing JSON in the appropriate format for the endpoint
being used.

*get-end-of-period-statement* is a slight oddball as this endpoint is the
only one that takes an optional query string.

The optional bit being the *start* & *end* dates. If you don't want to specify
one or both of them use a '-' in place of one or both e.g

    $ mtd-cli sa get-end-of-period-statement XXXX1234567890 *start_date* -

When running you will get a JSON response in both cases of error and success.
E.g

```
$ ./mtd-cli sa list-periods XXXX1234567890
```
```JSON
{
    "status_code": 200,
    "status_str": "OK",
    "url": "https://test-api.service.hmrc.gov.uk/self-assessment/ni/XX123456/self-employments/XXXX1234567890/periods",
    "result": [
        {
            "id": "2020-04-06_2020-07-04",
            "from": "2020-04-06",
            "to": "2020-07-04"
        },
        {
            "id": "2020-07-05_2020-10-05",
            "from": "2020-07-05",
            "to": "2020-10-05"
        }
    ]
}
```
or in case of error

```
$ ./mtd-cli sa list-periods xxx
```
```JSON
{
    "status_code": 404,
    "status_str": "Not Found",
    "url": "https://test-api.service.hmrc.gov.uk/self-assessment/ni/XX123456/self-employments/xxx/periods",
    "result": null
}
```

## License

This is licensed under the GNU General Public License (GPL) version 2

See *COPYING* in the repository root for details.


## Contributing

See *CodingStyle.md* & *Contributing.md*
