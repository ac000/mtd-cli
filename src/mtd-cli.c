#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <linux/limits.h>

#include <libmtdac/mtd-sa.h>

#include <jansson.h>

#define APIS		"init oauth sa"
#define SA_ENDPOINTS \
"list-employments get-employment list-obligations list-periods create-period\n"\
"get-period update-period get-annual-summary update-annual-summary\n"\
"submit-end-of-period-statement get-end-of-period-statement"

#define MTD_CLI_SA	"mtd-cli sa "

static const struct sa_endpoint_help {
	const char *ep;
	const char *use;
	const int nargs;
} sa_endpoint_help_map[] = {
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
};

static int print_sa_endpoints(void)
{
	printf("Available self-assessment endpoints :-\n\n%s\n", SA_ENDPOINTS);

	return -1;
}

static int print_api_help(void)
{
	printf("Available APIs :-\n\n%s\n", APIS);

	return -1;
}

static int check_sa_args(int argc, const char *endpoint)
{
	int ret = -1;
	int i = 0;
	int nr = sizeof(sa_endpoint_help_map) /
		 sizeof(sa_endpoint_help_map[0]);
	bool found = false;

	if (!endpoint)
		goto out_not_found;

	for ( ; i < nr; i++) {
		if (strcmp(sa_endpoint_help_map[i].ep, endpoint) == 0) {
			if (sa_endpoint_help_map[i].nargs == argc)
				return 0;

			found = true;
			printf("Usage:\t%s\n", sa_endpoint_help_map[i].use);
		}
	}

out_not_found:
	if (!found)
		print_sa_endpoints();

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

#define IS_EP(endpoint)		(strcmp(ep, endpoint) == 0)
static int do_sa(int argc, char *argv[])
{
	const char *ep = argv[0];	/* endpoint */
	char *buf = NULL;
	json_t *rootbuf;
	int err;

	err = check_sa_args(argc - 1, ep);
	if (err)
		return err;

	if (IS_EP("list-employments"))
		err = mtd_sa_list_employments(&buf);
	else if (IS_EP("get-employment"))
		err = mtd_sa_get_employment(argv[1], &buf);
	else if (IS_EP("list-obligations"))
		err = mtd_sa_list_obligations(argv[1], &buf);
	else if (IS_EP("list-periods"))
		err = mtd_sa_list_periods(argv[1], &buf);
	else if (IS_EP("create-period"))
		err = mtd_sa_create_period(argv[1], argv[2], &buf);
	else if (IS_EP("get-period"))
		err = mtd_sa_get_period(argv[1], argv[2], &buf);
	else if (IS_EP("update-period"))
		err = mtd_sa_update_period(argv[1], argv[2], argv[3], &buf);
	else if (IS_EP("get-annual-summary"))
		err = mtd_sa_get_annual_summary(argv[1], argv[2], &buf);
	else if (IS_EP("update-annual-summary"))
		err = mtd_sa_update_annual_summary(argv[1], argv[2], argv[3],
						   &buf);
	else if (IS_EP("submit-end-of-period-statement"))
		err = mtd_sa_submit_end_of_period_statement(argv[1], argv[2],
							    argv[3], argv[4],
							    &buf);
	else if (IS_EP("get-end-of-period-statement"))
		err = get_end_of_period_statement(argv, &buf);

	if (!buf)
		return err;

	rootbuf = json_loads(buf, 0, NULL);
	json_dumpf(rootbuf, stdout, JSON_INDENT(4));
	printf("\n");
	json_decref(rootbuf);

	free(buf);

	return err;
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

#define IS_API(api)		(strcmp(api, p) == 0)
static int dispatcher(int argc, char *argv[])
{
	const char *p = argv[0];
	int err = -1;

	if (IS_API("init"))
		err = do_init();
	else if (IS_API("oauth"))
		err = do_oauth();
	else if (IS_API("sa"))
		err = do_sa(argc - 1, argv + 1);

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

	err = mtd_init(MTD_OPT_UI_CLI|MTD_OPT_LOG_ERR);
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
