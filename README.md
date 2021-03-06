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

    mtd-cli init|init-oauth|init-config|init-nino|sa|saac|ic|id|il|ni|biss|bsas|vat|test-cu|test-ni|test-fph [endpoint args ...]

The first argument specifies the API to interface with

  * **init** is for doing an initial setup, creating appropriate oauth.json &
    config.json files.

  * **init-oauth** is for doing a reauthorisation.

  * **init-config** is for regenerating the config.json file.

  * **init-nino** is for storing the National Insurance Number in the nino.json file.

  * **sa** is for interacting with the Self-Assessment API.

  * **saac** is for interacting with the Self-Assessment Accounts API.

  * **ic** is for interacting with the Individual Calculations API.

  * **id** is for interacting with the Individuals Disclosures API

  * **il** is for interacting with the Individual Loses API.

  * **ni** is for interacting with the National Insurance API.

  * **biss** is for interacting with the Business Income Source Summary API.

  * **bsas** is for interacting with the Business Source Adjustable Summary API.

  * **vat** is for interacting with the VAT API.

  * **test-cu** is for interacting with the Create Test User API.

  * **test-ni** is for interacting with the National Insurance Test Support API.

  * **test-fph** is for interacting with the Test Fraud Prevention Headers API.

*init*, *oauth* & *config* don't take any arguments.

**sa** takes various arguments, the first of which is the endpoint of the API
to connect to. These are

    Self-Employment

    se-list-employments se-create-employment se-get-employment
    se-list-obligations se-list-periods se-create-period se-get-period
    se-update-period se-get-annual-summary se-update-annual-summary
    se-submit-end-of-period-statement se-get-end-of-period-statement-obligations

    UK Property Business

    pb-get-property pb-create-property pb-list-obligations
    pb-list-non-fhl-periods pb-create-non-fhl-period pb-get-non-fhl-period
    pb-update-non-fhl-period pb-get-non-fhl-annual-summary
    pb-update-non-fhl-annual-summary pb-list-fhl-periods pb-create-fhl-period
    pb-get-fhl-period pb-update-fhl-period pb-get-fhl-annual-summary
    pb-update-fhl-annual-summary pb-submit-end-of-period-statement
    pb-get-end-of-period-statement

    Dividends Income

    di-get-annual-summary di-update-annual-summary

    Savings Accounts

    sa-list-accounts sa-create-account sa-get-account sa-get-annual-summary
    sa-update-annual-summary

    Charitable Giving

    cg-get-charitable-giving cg-update-charitable-giving

    Crystallisation

    cr-intent-to-crystallise cr-crystallise cr-list-obligations

The following shows each of the above and what arguments (if any) they take.

    $ mtd-cli sa se-list-employments

    $ mtd-cli sa se-create-employment <file>

    $ mtd-cli sa se-get-employment selfEmploymentId

    $ mtd-cli sa se-list-obligations selfEmploymentId [[from=YYYY-MM-DD][,[to=YYYY-MM-DD]]]

    $ mtd-cli sa se-list-periods selfEmploymentId

    $ mtd-cli sa se-create-period <file> selfEmploymentId

    $ mtd-cli sa se-get-period selfEmploymentId periodId

    $ mtd-cli sa se-update-period <file> selfEmploymentId periodId

    $ mtd-cli sa se-get-annual-summary selfEmploymentId taxYear

    $ mtd-cli sa se-update-annual-summary <file> selfEmploymentId taxYear

    $ mtd-cli sa se-submit-end-of-period-statement <file> selfEmploymentId start end

    $ mtd-cli sa se-get-end-of-period-statement-obligations selfEmploymentId [[from=YYYY-MM-DD][,[to=YYYY-MM-DD]]]

    $ mtd-cli sa pb-get-property

    $ mtd-cli sa pb-create-property <file>

    $ mtd-cli sa pb-list-obligations

    $ mtd-cli sa pb-list-non-fhl-periods

    $ mtd-cli sa pb-create-non-fhl-period <file>

    $ mtd-cli sa pb-get-non-fhl-period periodId

    $ mtd-cli sa pb-update-non-fhl-period <file> periodId

    $ mtd-cli sa pb-get-non-fhl-annual-summary taxYear

    $ mtd-cli sa pb-update-non-fhl-annual-summary <file> taxYear

    $ mtd-cli sa pb-list-fhl-periods

    $ mtd-cli sa pb-create-fhl-period <file>

    $ mtd-cli sa pb-get-fhl-period periodId

    $ mtd-cli sa pb-update-fhl-period <file> periodId

    $ mtd-cli sa pb-get-fhl-annual-summary taxYear

    $ mtd-cli sa pb-update-fhl-annual-summary <file> taxYear

    $ mtd-cli sa pb-submit-end-of-period-statement <file> start end

    $ mtd-cli sa pb-get-end-of-period-statement from=YYYY-MM-DD,to=YYYY-MM-DD

    $ mtd-cli sa di-get-annual-summary taxYear

    $ mtd-cli sa di-update-annual-summary <file> taxYear

    $ mtd-cli sa sa-list-accounts

    $ mtd-cli sa sa-create-account <file>

    $ mtd-cli sa sa-get-account savingsAccountId

    $ mtd-cli sa sa-get-annual-summary savingsAccountId taxYear

    $ mtd-cli sa sa-update-annual-summary <file> savingsAccountId taxYear

    $ mtd-cli sa cg-get-charitable-giving taxYear

    $ mtd-cli sa cg-update-charitable-giving taxYear

    $ mtd-cli sa cr-intent-to-crystallise taxYear

    $ mtd-cli sa cr-crystallise <file> taxYear

    $ mtd-cli sa cr-list-obligations from=YYYY-MM-DD,to=YYYY-MM-DD

*selfEmploymentId* is an 'id' as returned from '*mtd-cli sa se-list-employments*'.

*periodId* is an 'id' as returned from '*mtd-cli sa \*-list-periods ...*'.

*\<file\>* is a file containing JSON in the appropriate format for the endpoint
being used.

*get-end-of-period-statement* takes an optional query string.

Both the *from* & *to* parts are optional

    $ mtd-cli sa get-end-of-period-statement XXXX1234567890 from=2020-01-01,to=2020-05-01

*savingsAccountId* is an 'id' as returned from '*mtd-cli sa sa-list-accounts*'.

*taxYear* is in the form *YYYY-YY*


**saac** takes various arguments, the first of which is the endpoint of the API
to connect to. These are

    get-balance list-transactions get-transaction list-charges get-charge
    list-payments get-payment

The following shows each of the above and what arguments (if any) they take.

    $ mtd-cli saac get-balance

    $ mtd-cli saac list-transactions from=YYYY-MM-DD,to=YYYY-MM-DD

    $ mtd-cli saac get-transaction transactionId

    $ mtd-cli saac list-charges from=YYYY-MM-DD,to=YYYY-MM-DD

    $ mtd-cli saac get-charge transactionId

    $ mtd-cli saac list-payments from=YYYY-MM-DD,to=YYYY-MM-DD

    $ mtd-cli saac get-payment paymentId

*transactionId* is an 'id' as returned from
'*mtd-cli saac list-transactions from to*'.

*paymentId* is an 'id' as returned from '*mtd-cli saac list-payments from to*'.


**ic** supports the following commands

    Self-Assessment

    sa- list-calculations sa-trigger-calculation sa-get-calculation-metadata
    sa-get-income-tax-nics-calc sa-get-taxable-income
    sa-get-allowances-deductions-reliefs sa-get-end-of-year-estimate
    sa-get-messages

    Crystallisation

    cr-intent-to-crystallise cr-crystallise

with the following usage

    $ mtd-cli ic sa-list-calculations [taxYear=YYYY-YY]

    $ mtd-cli ic sa-trigger-calculation <file>

    $ mtd-cli ic sa-get-calculation-metadata calculationId

    $ mtd-cli ic sa-get-income-tax-nics-calc calculationId

    $ mtd-cli ic sa-get-taxable-income calculationId

    $ mtd-cli ic sa-get-allowances-deductions-reliefs calculationId

    $ mtd-cli ic sa-get-end-of-year-estimate calculationId

    $ mtd-cli ic sa-get-messages calculationId [[type={info,warning,error}], ...]

    $ mtd-cli ic cr-intent-to-crystallise taxYear

    $ mtd-cli ic cr-crystallise <file> taxYear

*\<file\>* is a JSON file that looks like for sa-trigger-calculation

```JSON
{
    "taxYear": "2017-18"
}
```

or for cr-crystallise

```JSON
{
    "calculationId": "041f7e4d-87d9-4d4a-a296-3cfbdf92f7e2"
}
```

that is sent to the server.

*calculationId* is an *'id'* as returned by the
'*mtd-cli ic list-calculations*' command.


**id** supports the following commands

    get set delete

with the following usage

    $ mtd-cli id get taxYear

    $ mtd-cli id set <file> taxYear

    $ mtd-cli id delete taxYear

*taxYear* is a tax year in the form *YYYY-YY*

*\<file\>* is a JSON file that looks like

```JSON
{
    "taxAvoidance": [
        {
            "srn": "14211123",
            "taxYear": "2020-21"
        }
    ],
    "class2Nics": {
        "class2VoluntaryContributions": true
    }
}
```


**il** supports the following commands

    Brought Forward Loses

    bf-list-loses bf-create-loss bf-get-loss bf-delete-loss bf-update-loss-amnt

    Loss Claims

    lc-list-loses lc-create-loss lc-get-loss lc-delete-loss lc-update-loss-type
    lc-update-loss-order

with the following usage

    $ mtd-cli il bf-list-loses [[selfEmploymentId=][,[taxYear=YYYY-YY][,[typeOfLoss={self-employment,uk-property-fhl,uk-property-non-fhl}]]]]

    $ mtd-cli il bf-create-loss <file>

*\<file\>* is a JSON file that looks like

```JSON
{
    "typeOfLoss": "self-employment-class4",
    "selfEmploymentId": "XGIS00000001319",
    "lossAmount": 12345.67,
    "taxYear": "2018-19"
}
```

    $ mtd-cli il bf-get-loss lossId

    $ mtd-cli il bf-delete-loss lossId

    $ mtd-cli il bf-update-loss-amnt <file> lossId

*\<file\>* is a JSON file that looks like

```JSON
{
    "lossAmount": 12345.67
}
```

    $ mtd-cli il lc-list-loses [[selfEmploymentId=][,[taxYear=YYYY-YY][,[typeOfLoss={self-employment,uk-property-fhl,uk-property-non-fhl}][,[claimType=carry-sideways]]]]]

    $ mtd-cli il lc-create-loss <file> [taxYear=YYYY-YY]

*\<file\>* is a JSON file that looks like

```JSON
{
    "typeOfLoss":"self-employment",
    "selfEmploymentId": "XGIS00000001319",
    "typeOfClaim": "carry-forward",
    "taxYear": "2019-20"
}
```

    $ mtd-cli il lc-get-loss claimId

    $ mtd-cli il lc-delete-loss claimId

    $ mtd-cli il lc-update-loss-type <file> claimId

*\<file\>* is a JSON file that looks like

```JSON
{
    "typeOfClaim": "carry-forward"
}
```

    $ mtd-cli il lc-update-loss-order <file>

*\<file\>* is a JSON file that looks like

```JSON
{
    "claimType": "carry-sideways",
    "listOfLossClaims": [
        {
            "id": "1234567890ABCDE",
            "sequence": 2
        },
        {
            "id": "1234567890ABDE0",
            "sequence": 3
        },
        {
            "id": "1234567890ABEF1",
            "sequence": 1
        }
    ]
}
```

*lossId* is an 'id' as returned by the '*mtd-cli il bf-list-loses*' command

*claimId* is an 'id' as returned by the '*mtd-cli il lc-list-loses*' command


**ni** currently has a single endpoint

    get-annual-summary

which takes two arguments

    $ mtd-cli ni get-annual-summary utr taxYear

*utr* is the Unique Tax Reference.

*taxYear* is the Tax year to get in the form; *YYYY-YY*


**biss** has the following endpoints

    get-self-employment get-uk-property get-foreign-property

with the following usage

    $ mtd-cli biss get-self-employment selfEmploymentId=[,taxYear=YYYY-YY]

    $ mtd-cli biss get-uk-property typeOfBusiness={uk-property-non-fhl,uk-property-fhl}[,taxYear=YYYY-YY]

    $ mtd-cli biss get-foreign-property businessId=,typeOfBusiness={foreign-property-fhl-eea,foreign-property}[,taxYear=YYYY-YY]


**bsas** has the following endpoints

    bsas-list-summaries bsas-trigger-summary

    Self-Employment

    bsas-se-get-summary bsas-se-list-summary-adjustments
    bsas-se-update-summary-adjustments

    UK Property Business

    bsas-pb-get-summary bsas-pb-list-summary-adjustments
    bsas-pb-update-summary-adjustments

with the following usage

    $ mtd-cli bsas bsas-list-summaries [[selfEmploymentId=][,[typeOfBusiness={self-employment,uk-property-non-fhl,uk-property-fhl}][,[taxYear=YYYY-YY]]]]

    $ mtd-cli bsas bsas-trigger-summary <file>

    $ mtd-cli bsas bsas-se-get-summary bsasId [adjustedStatus={true,false}]

    $ mtd-cli bsas bsas-se-list-summary-adjustments bsasId

    $ mtd-cli bsas bsas-se-update-summary-adjustments <file> bsasId

    $ mtd-cli bsas bsas-pb-get-summary bsasId [adjustedStatus={true,false}]

    $ mtd-cli bsas bsas-pb-list-summary-adjustments bsasId

    $ mtd-cli bsas bsas-pb-update-summary-adjustments <file> bsasId

*bsasId* is as returned by '*mtd-cli bsas bsas-list-summaries*'.


**vat** has the following commands

    list-obligations submit-period get-period list-liabilities list-payments

with the following usage

    $ mtd-cli vat list-obligations vrn [from=YYY-MM-DD][,[to=YYYY-MM-DD]][,[status=O|F]]

    $ mtd-cli vat submit-period <file> vrn

    $ mtd-cli vat get-period vrn periodKek

    $ mtd-cli vat list-liabilities vrn from=YYYY-MM-DD,to=YYYY-MM-DD

    $ mtd-cli vat list-payments vrn from=YYYY-MM-DD,to=YYYY-MM-DD

*vrn* is the VAT Registration Number

In the query string, *status=*; *O* is open and *F* is Fulfilled. Omit status
to retrieve all obligations.

*\<file\>* is a JSON file that looks like

```JSON
{
    "periodKey": "A001",
    "vatDueSales": 105.50,
    "vatDueAcquisitions": -100.45,
    "totalVatDue": 5.05,
    "vatReclaimedCurrPeriod": 105.15,
    "netVatDue": 100.10,
    "totalValueSalesExVAT": 300,
    "totalValuePurchasesExVAT": 300,
    "totalValueGoodsSuppliedExVAT": 3000,
    "totalAcquisitionsExVAT": 3000,
    "finalised": true
}
```


**test-cu** has the following commands

    create-individual create-organisation create-agent list-service

with the following usage

    $ mtd-cli test-cu create-individual <file>

    $ mtd-cli test-cu create-organisation <file>

    $ mtd-cli test-cu create-agent <file>

    $ mtd-cli test-cu list-service

*\<file\>* is a JSON file containing a list of service names


**test-ni** currently has a single endpoint

    create-annual-summary

which takes three arguments

    $ mtd-cli test-ni create-annual-summary <file> utr taxYear


**test-fph** currently has a single endpoint

    validate

which takes no arguments

    $ mtd-cli test-fph validate


When running you will get a JSON response in both cases of error and success.
The response(s) will be wrapped in an array to cater for multiple responses
being returned in the case of re-directs occurring. E.g

```
$ ./mtd-cli sa list-periods XXXX1234567890
```
```JSON
[
    {
        "status_code": 200,
        "status_str": "OK",
        "url": "https://test-api.service.hmrc.gov.uk/self-assessment/ni/XX123456/self-employments/XXXX1234567890/periods",
        "method": "GET",
        "xid": "cdadffb4-3836-4062-a84c-c03d9f28ff00",
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
]
```

in the case of multiple responses

```
$ ./mtd-cli sa cr-intent-to-crystallise 2018-19
```
```JSON
[
    {
        "status_code": 303,
        "status_str": "See Other",
        "url": "https://test-api.service.hmrc.gov.uk/self-assessment/ni/XX1234567/2018-19/intent-to-crystallise",
        "method": "POST",
        "xid": "a1e8057e-fbbc-47a8-a8b4-78d9f015c253",
        "result": null
    },
    {
        "status_code": 200,
        "status_str": "OK",
        "url": "https://test-api.service.hmrc.gov.uk/self-assessment/ni/XX1234567/calculations/c2c82d00-c407-4f98-ab7d-c8319c522e6b",
        "method": "GET",
        "xid": "a1e8057e-fbbc-47a8-a8b4-78d9f015c253",
        "result": {
            ...
        }
    }
]
````

or in case of error


```
$ ./mtd-cli sa list-periods xxx
```
```JSON
[
    {
        "status_code": 404,
        "status_str": "Not Found",
        "url": "https://test-api.service.hmrc.gov.uk/self-assessment/ni/XX123456/self-employments/xxx/periods",
        "method": "GET",
        "xid": "dc1411d0-5ae4-48b8-84e0-4c5379b245b8",
        "result": null
    }
]
```

## Environment variables

Currently there are two environment variables that can bet set to control
behaviour

#### **MTD_CLI_OPT_LOG_LEVEL**

This can be used to override the default log level (MTD\_OPT\_LOG\_ERR).

Currently recognised values are; *debug* & *info*

#### **MTD_CLI_OPT_NO_FPH_HDRS**

This can be used to disable the sending of 'Fraud Prevention Headers', set it
to

*true* or *1*

#### **MTD_CLI_HDRS**

This can be used to set extra HTTP headers to be sent.

Currently only one header is supported which should be sufficient for setting
the *Gov-Test-Scenario* Test API header. e.g

    MTD_CLI_HDRS="Gov-Test-Scenario: NO_SUBMISSIONS_EXIST" mtd-cli sa cr-intent-to-crystallise 2018-19


## License

This is licensed under the GNU General Public License (GPL) version 2

See *COPYING* in the repository root for details.


## Contributing

See *CodingStyle.md* & *Contributing.md*
