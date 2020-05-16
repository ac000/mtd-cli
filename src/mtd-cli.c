#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <linux/limits.h>

#include <libmtdac/mtd-sa.h>
#include <libmtdac/mtd-saac.h>

#include <jansson.h>

#define MTD_CLI		"mtd-cli"

#define APIS		"init oauth config sa saac"
#define SA_ENDPOINTS \
"list-employments get-employment list-obligations list-periods create-period\n"\
"get-period update-period get-annual-summary update-annual-summary\n"\
"submit-end-of-period-statement get-end-of-period-statement"
#define SAAC_ENDPOINTS \
"get-balance list-transactions get-transaction list-charges get-charge\n"\
"list-payments get-payment"\

#define MTD_CLI_SA	MTD_CLI " sa "
#define MTA_CLI_SAAC	MTD_CLI " saac "

static const struct api_ep {
	const char *api;
	int (*api_func)(int argc, char *argv[], char **buf);
} api_ep_map[] = {
	{ "sa", &do_sa },
	{ "saac", &do_saac },
	{ NULL, NULL }
};

struct endpoint_help {
	const char *ep;
	const char *use;
	const int nargs;
};

static const struct endpoint_help sa_endpoint_help[] = {
	{ "list-employments", MTD_CLI_SA "list-employments", 0 },
	{ "get-employment", MTD_CLI_SA "get-employment selfEmploymentId", 1 },
	{ "list-obligations", MTD_CLI_SA "list-obligations selfEmploymentId",
	   1 },
	{ "list-periods", MTD_CLI_SA "list-periods selfEmploymentId", 1 },
	{ "create-period", MTD_CLI_SA "create-period <file> selfEmploymentId",
	   2 },
	{ "get-period", MTD_CLI_SA "get-period selfEmploymentId periodId", 2 },
	{ "update-period",
	   MTD_CLI_SA "update-period <file> selfEmploymentId periodId", 3 },
	{ "get-annual-summary",
	   MTD_CLI_SA "get-annual-summary selfEmploymentId taxYear", 2 },
	{ "update-annual-summary",
	   MTD_CLI_SA "update-annual-summary <file> selfEmploymentId taxYear",
	   3 },
	{ "submit-end-of-period-statement",
	   MTD_CLI_SA "submit-end-of-period-statement <file> selfEmploymentId start end",
	   3 },
	{ "get-end-of-period-statement",
	   MTD_CLI_SA "get-end-of-period-statement selfEmploymentId start|- end|-",
	   3 },
	{ NULL, NULL, 0 }
};

static const struct endpoint_help saac_endpoint_help[] = {
	{ "get-balance", MTA_CLI_SAAC "get-balance", 0 },
	{ "list-transactions", MTA_CLI_SAAC "list-transactions from to", 2 },
	{ "get-transaction", MTA_CLI_SAAC "get-transaction transactionId", 1 },
	{ "list-charges", MTA_CLI_SAAC "list-charges from to", 2 },
	{ "get-charge", MTA_CLI_SAAC "get-charge transactionId", 1 },
	{ "list-payments", MTA_CLI_SAAC "list-payments from to", 2 },
	{ "get-payment", MTA_CLI_SAAC "get-payment paymentId", 1 },
	{ NULL, NULL, 0 }
};

static int print_sa_endpoints(void)
{
	printf("Available self-assessment endpoints :-\n\n%s\n", SA_ENDPOINTS);

	return -1;
}

static int print_saac_endpoints(void)
{
	printf("Available self-assessment accounts endpoints :-\n\n%s\n",
	       SAAC_ENDPOINTS);

	return -1;
}

static int print_api_help(void)
{
	printf("Available APIs :-\n\n%s\n", APIS);

	return -1;
}

static int check_args(int argc, const char *endpoint,
		      const struct endpoint_help *eh, int (*print_help)(void))
{
	int ret = -1;
	unsigned i = 0;
	bool found = false;

	if (!endpoint)
		goto out_not_found;

	for ( ; eh[i].ep != NULL; i++) {
		if (strcmp(eh[i].ep, endpoint) == 0) {
			if (eh[i].nargs == argc)
				return 0;

			found = true;
			printf("Usage:\t%s\n", eh[i].use);
		}
	}

out_not_found:
	if (!found)
		print_help();

	return ret;
}

static int get_end_of_period_statement(char *argv[], char **buf)
{
	const char *start;
	const char *end;

	start = *argv[2] == '-' ? NULL : argv[2];
	end = *argv[3] == '-' ? NULL : argv[3];

	return mtd_sa_get_end_of_period_statement(argv[1], start, end, buf);
}

#define IS_EP(endpoint)		(strcmp(argv[0], endpoint) == 0)
static int do_sa(int argc, char *argv[], char **buf)
{
	int err;

	err = check_args(argc, argv[0], sa_endpoint_help, print_sa_endpoints);
	if (err)
		return err;

	if (IS_EP("list-employments"))
		return mtd_sa_list_employments(buf);
	else if (IS_EP("get-employment"))
		return mtd_sa_get_employment(argv[1], buf);
	else if (IS_EP("list-obligations"))
		return mtd_sa_list_obligations(argv[1], buf);
	else if (IS_EP("list-periods"))
		return mtd_sa_list_periods(argv[1], buf);
	else if (IS_EP("create-period"))
		return mtd_sa_create_period(argv[1], argv[2], buf);
	else if (IS_EP("get-period"))
		return mtd_sa_get_period(argv[1], argv[2], buf);
	else if (IS_EP("update-period"))
		return mtd_sa_update_period(argv[1], argv[2], argv[3], buf);
	else if (IS_EP("get-annual-summary"))
		return mtd_sa_get_annual_summary(argv[1], argv[2], buf);
	else if (IS_EP("update-annual-summary"))
		return mtd_sa_update_annual_summary(argv[1], argv[2], argv[3],
						    buf);
	else if (IS_EP("submit-end-of-period-statement"))
		return mtd_sa_submit_end_of_period_statement(argv[1], argv[2],
							     argv[3], argv[4],
							     buf);
	else if (IS_EP("get-end-of-period-statement"))
		return get_end_of_period_statement(argv, buf);

	return -1;
}

static int do_saac(int argc, char *argv[], char **buf)
{
	int err;

	err = check_args(argc, argv[0], saac_endpoint_help,
			 print_saac_endpoints);
	if (err)
		return err;

	if (IS_EP("get-balance"))
		return mtd_saac_get_balance(buf);
	else if (IS_EP("list-transactions"))
		return mtd_saac_list_transactions(argv[1], argv[2], buf);
	else if (IS_EP("get-transaction"))
		return mtd_saac_get_transaction(argv[1], buf);
	else if (IS_EP("list-charges"))
		return mtd_saac_list_charges(argv[1], argv[2], buf);
	else if (IS_EP("get-charge"))
		return mtd_saac_get_charge(argv[1], buf);
	else if (IS_EP("list-payments"))
		return mtd_saac_list_payments(argv[1], argv[2], buf);
	else if (IS_EP("get-payment"))
		return mtd_saac_get_payment(argv[1], buf);

	return -1;
}

static int do_mtd_api(const char *ep, int argc, char *argv[])
{
	char *buf = NULL;
	json_t *rootbuf;
	int i = 0;
	int err = -1;

	for ( ; api_ep_map[i].api != NULL; i++) {
		if (strcmp(api_ep_map[i].api, ep) != 0)
			continue;

		err = api_ep_map[i].api_func(argc, argv, &buf);
	}

	if (!buf)
		return err;

	rootbuf = json_loads(buf, 0, NULL);
	json_dumpf(rootbuf, stdout, JSON_INDENT(4));
	printf("\n");
	json_decref(rootbuf);

	free(buf);

	return err;
}

static int do_config(void)
{
	return mtd_init_config();
}

static int do_oauth(void)
{
	return mtd_init_auth();
}

static int do_init(void)
{
	int err;

	printf("Initialising...\n\n");
	err = mtd_init_config();
	if (err)
		return err;

	printf("\n");
	err = mtd_init_auth();
	if (err)
		return err;

	printf("\nInitialisation complete. Re-run command if something looks "
	       "wrong.\n");

	return err;
}


#define IS_API(api)		(strcmp(api, ep) == 0)
static int dispatcher(int argc, char *argv[])
{
	const char *ep = argv[0];
	int err = -1;

	if (IS_API("init"))
		err = do_init();
	else if (IS_API("oauth"))
		err = do_oauth();
	else if (IS_API("config"))
		err = do_config();
	else
		err = do_mtd_api(ep, argc - 2, argv + 1);

	return err;
}

int main(int argc, char *argv[])
{
	int err;
	int ret = EXIT_SUCCESS;

	if (argc == 1) {
		print_api_help();
		exit(EXIT_FAILURE);
	}

	err = mtd_init(MTD_OPT_LOG_ERR);
	if (err && strcmp(argv[1], "init") != 0) {
		if (err == MTD_ERR_MISSING_CONFIG)
			fprintf(stderr, "Please run 'mtd-cli init\n");
		exit(EXIT_FAILURE);
	}

	err = dispatcher(argc - 1, argv + 1);
	if (err) {
	       if (err == MTD_ERR_NEEDS_AUTHORISATION)
		       fprintf(stderr, "Please run 'mtd-cli oauth\n");
	       ret = EXIT_FAILURE;
	}

	mtd_deinit();

	exit(ret);
}
