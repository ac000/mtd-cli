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

    mtd-cli init|oauth|config|sa|saac|ic|ni [endpoint args ...]

The first argument specifies the API to interface with

  * **init** is for doing an initial setup, creating appropriate oauth.json &
    config.json files.

  * **oauth** is for doing a reauthorisation.

  * **config** is for regenerating the config.json file.

  * **sa** is for interacting with the Self-Assessment API.

  * **saac** is for interacting with the Self-Assessment Accounts API.

  * **ic** is for interacting with the Individual Calculations API.

  * **ni** is for interacting with the National Insurance API.

  * **test-cu** is for interacting with the Create Test User API.

  * **test-fph** if for interacting with the Test Fraud Prevention Headers API.

*init*, *oauth* & *config* don't take any arguments.

**sa** takes various arguments, the first of which is the endpoint of the API
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

*\<file\>* is a file containing JSON in the appropriate format for the endpoint
being used.

*get-end-of-period-statement* is a slight oddball as this endpoint is the
only one that takes an optional query string.

The optional bit being the *start* & *end* dates. If you don't want to specify
one or both of them use a '-' in place of one or both e.g

    $ mtd-cli sa get-end-of-period-statement XXXX1234567890 *start_date* -


**saac** takes various arguments, the first of which is the endpoint of the API
to connect to. These are

    get-balance list-transactions get-transaction list-charges get-charge
    list-payments get-payment

The following shows each of the above and what arguments (if any) they take.

    $ mtd-cli saac get-balance

    $ mtd-cli saac list-transactions from to

    $ mtd-cli saac get-transaction transactionId

    $ mtd-cli saac list-charges from to

    $ mtd-cli saac get-charge transactionId

    $ mtd-cli saac list-payments from to

    $ mtd-cli saac get-payment paymentId

*from* & *to* are dates in the format *YYYY-MM-DD*

*transactionId* is an 'id' as returned from
'*mtd-cli saac list-transactions from to*'.

*paymentId* is an 'id' as returned from '*mtd-cli saac list-payments from to*'.


**ic** supports the following commands

    list-calculations trigger-calculation get-calculation-metadata
    get-income-tax-nics-calc get-taxable-income
    get-allowances-deductions-reliefs get-end-of-year-estimate get-messages

with the following usage

    $ mtd-cli ic list-calculations

    $ mtd-cli ic trigger-calculation <file>

    $ mtd-cli ic get-calculation-metadata calculationId

    $ mtd-cli ic get-income-tax-nics-calc calculationId

    $ mtd-cli ic get-taxable-income calculationId

    $ mtd-cli ic get-allowances-deductions-reliefs calculationId

    $ mtd-cli ic get-end-of-year-estimate calculationId

    $ mtd-cli ic get-messages calculationId

*\<file\>* is a JSON file that looks like

```JSON
{
    "taxYear": "2017-18"
}
```

that is sent to the server.

*calculationId* is an *'id'* as returned by the
'*mtd-cli ic list-calculations*' command.


**ni** currently has a single endpoint

    get-annual-summary

which takes two arguments

    $ mtd-cli ni get-annual-summary utr taxYear

*utr* is the Unique Tax Reference.

*taxYear* is the Tax year to get in the form; *YYYY-YY*


**test-cu** has the following commands

    create-individual create-organisation create-agent list-service

with the following usage

    $ mtd-cli test-cu create-individual <file>

    $ mtd-cli test-cu create-organisation <file>

    $ mtd-cli test-cu create-agent <file>

    $ mtd-cli test-cu list-service

*\<file\>* is a JSON file containing a list of service names


**test-fph** currently has a single endpoint

    validate

which takes no arguments

    $ mtd-cli test-fph validate


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
    "method": "GET",
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
    "method": "GET",
    "result": null
}
```

## License

This is licensed under the GNU General Public License (GPL) version 2

See *COPYING* in the repository root for details.


## Contributing

See *CodingStyle.md* & *Contributing.md*
