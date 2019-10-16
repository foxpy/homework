#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define BUF_SIZE 80

void help(char *program_name);
int collect_stats(FILE *power,
                  long long numsamples,
                  long long period,
                  FILE *output);

int main(int argc, char *argv[])
{
	FILE *power;
	long long numsamples;
	long long period;
	FILE *output;
	
	if (argc != 5) {
		help(argv[0]);
		return EXIT_FAILURE;
	}

	if ((power = fopen(argv[1], "r")) == NULL) {
		perror("fopen");
		return EXIT_FAILURE;
	}

	numsamples = 0;
	if ((numsamples = atoll(argv[2])) == 0) {
		fprintf(stderr, "Fatal: \"%s\": not a valid integer\n",
		                argv[2]);
		return EXIT_FAILURE;
	}

	period = 0;
	if((period = atoll(argv[3])) == 0) {
		fprintf(stderr, "Fatal: \"%s\": not a valid integer\n",
		                argv[3]);
		return EXIT_FAILURE;
	}

	if((output = fopen(argv[4], "w")) == NULL) {
		perror("fopen");
		return EXIT_FAILURE;
	}

	collect_stats(power, numsamples, period, output);

	fclose(power);
	fclose(output);
	return EXIT_SUCCESS;
}

void help(char *program_name)
{
	fprintf(stderr, "Usage: %s POWER NUMSAMPLES PERIOD OUTPUT\n",
		program_name);
	fprintf(stderr, "\tPOWER      file with battery power in microwatts\n");
	fprintf(stderr, "\tNUMSAMPLES number of samples to capture\n");
	fprintf(stderr, "\tPERIOD     milliseconds between sample captures\n");
	fprintf(stderr, "\tOUTPUT     output file to store captured data\n");
}


int collect_stats(FILE *power,
                  long long numsamples,
                  long long period,
                  FILE *output)
{
	struct timespec rqtp;
	char buf[BUF_SIZE];
	double power_now;

	rqtp.tv_sec = period/1000/1000;
	rqtp.tv_nsec = (period%(1000*1000))*1000;
	while (numsamples-- != 0) {
		nanosleep(&rqtp, NULL);
		buf[fread(buf, sizeof(char), BUF_SIZE-1, power)] = '\0';
		power_now = (double) (atoi(buf))/1000/1000;
		snprintf(buf, BUF_SIZE, "%.1f\n", power_now);
		fputs(buf, stdout);
		fputs(buf, output);
		rewind(power);
	}
	return EXIT_SUCCESS;
}
