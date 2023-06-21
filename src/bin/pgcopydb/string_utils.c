/*
 * src/bin/pgcopydb/string_utils.c
 *   Implementations of utility functions for string handling
 */

#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#if (__STDC_VERSION__ >= 199901L)
#include <stdint.h>
#endif

#include "postgres_fe.h"
#include "pqexpbuffer.h"

#include "defaults.h"
#include "file_utils.h"
#include "log.h"
#include "string_utils.h"

/*
 * intToString converts an int to an IntString, which contains a decimal string
 * representation of the integer.
 */
IntString
intToString(int64_t number)
{
	IntString intString;

	intString.intValue = number;

	sformat(intString.strValue, INTSTRING_MAX_DIGITS, "%" PRId64, number);

	return intString;
}


/*
 * converts given string to 64 bit integer value.
 * returns 0 upon failure and sets error flag
 */
bool
stringToInt(const char *str, int *number)
{
	char *endptr;

	if (str == NULL)
	{
		return false;
	}

	if (number == NULL)
	{
		return false;
	}

	errno = 0;

	long long int n = strtoll(str, &endptr, 10);

	if (str == endptr)
	{
		return false;
	}
	else if (errno != 0)
	{
		return false;
	}
	else if (*endptr != '\0')
	{
		return false;
	}
	else if (n < INT_MIN || n > INT_MAX)
	{
		return false;
	}

	*number = n;

	return true;
}


/*
 * converts given string to 64 bit integer value.
 * returns 0 upon failure and sets error flag
 */
bool
stringToInt64(const char *str, int64_t *number)
{
	char *endptr;

	if (str == NULL)
	{
		return false;
	}

	if (number == NULL)
	{
		return false;
	}

	errno = 0;

	long long int n = strtoll(str, &endptr, 10);

	if (str == endptr)
	{
		return false;
	}
	else if (errno != 0)
	{
		return false;
	}
	else if (*endptr != '\0')
	{
		return false;
	}
	else if (n < INT64_MIN || n > INT64_MAX)
	{
		return false;
	}

	*number = n;

	return true;
}


/*
 * converts given string to 64 bit unsigned integer value.
 * returns 0 upon failure and sets error flag
 */
bool
stringToUInt(const char *str, unsigned int *number)
{
	char *endptr;

	if (str == NULL)
	{
		return false;
	}

	if (number == NULL)
	{
		return false;
	}

	errno = 0;
	unsigned long long n = strtoull(str, &endptr, 10);

	if (str == endptr)
	{
		return false;
	}
	else if (errno != 0)
	{
		return false;
	}
	else if (*endptr != '\0')
	{
		return false;
	}
	else if (n > UINT_MAX)
	{
		return false;
	}

	*number = n;

	return true;
}


/*
 * converts given string to 64 bit unsigned integer value.
 * returns 0 upon failure and sets error flag
 */
bool
stringToUInt64(const char *str, uint64_t *number)
{
	char *endptr;

	if (str == NULL)
	{
		return false;
	}

	if (number == NULL)
	{
		return false;
	}

	errno = 0;
	unsigned long long n = strtoull(str, &endptr, 10);

	if (str == endptr)
	{
		return false;
	}
	else if (errno != 0)
	{
		return false;
	}
	else if (*endptr != '\0')
	{
		return false;
	}
	else if (n > UINT64_MAX)
	{
		return false;
	}

	*number = n;

	return true;
}


/*
 * converts given string to short value.
 * returns 0 upon failure and sets error flag
 */
bool
stringToShort(const char *str, short *number)
{
	char *endptr;

	if (str == NULL)
	{
		return false;
	}

	if (number == NULL)
	{
		return false;
	}

	errno = 0;

	long long int n = strtoll(str, &endptr, 10);

	if (str == endptr)
	{
		return false;
	}
	else if (errno != 0)
	{
		return false;
	}
	else if (*endptr != '\0')
	{
		return false;
	}
	else if (n < SHRT_MIN || n > SHRT_MAX)
	{
		return false;
	}

	*number = n;

	return true;
}


/*
 * converts given string to unsigned short value.
 * returns 0 upon failure and sets error flag
 */
bool
stringToUShort(const char *str, unsigned short *number)
{
	char *endptr;

	if (str == NULL)
	{
		return false;
	}

	if (number == NULL)
	{
		return false;
	}

	errno = 0;
	unsigned long long n = strtoull(str, &endptr, 10);

	if (str == endptr)
	{
		return false;
	}
	else if (errno != 0)
	{
		return false;
	}
	else if (*endptr != '\0')
	{
		return false;
	}
	else if (n > USHRT_MAX)
	{
		return false;
	}

	*number = n;

	return true;
}


/*
 * converts given string to 32 bit integer value.
 * returns 0 upon failure and sets error flag
 */
bool
stringToInt32(const char *str, int32_t *number)
{
	char *endptr;

	if (str == NULL)
	{
		return false;
	}

	if (number == NULL)
	{
		return false;
	}

	errno = 0;

	long long int n = strtoll(str, &endptr, 10);

	if (str == endptr)
	{
		return false;
	}
	else if (errno != 0)
	{
		return false;
	}
	else if (*endptr != '\0')
	{
		return false;
	}
	else if (n < INT32_MIN || n > INT32_MAX)
	{
		return false;
	}

	*number = n;

	return true;
}


/*
 * converts given string to 32 bit unsigned int value.
 * returns 0 upon failure and sets error flag
 */
bool
stringToUInt32(const char *str, uint32_t *number)
{
	char *endptr;

	if (str == NULL)
	{
		return false;
	}

	if (number == NULL)
	{
		return false;
	}

	errno = 0;
	unsigned long long n = strtoull(str, &endptr, 10);

	if (str == endptr)
	{
		return false;
	}
	else if (errno != 0)
	{
		return false;
	}
	else if (*endptr != '\0')
	{
		return false;
	}
	else if (n > UINT32_MAX)
	{
		return false;
	}

	*number = n;

	return true;
}


/*
 * converts given string to a double precision float value.
 * returns 0 upon failure and sets error flag
 */
bool
stringToDouble(const char *str, double *number)
{
	char *endptr;

	if (str == NULL)
	{
		return false;
	}

	if (number == NULL)
	{
		return false;
	}

	errno = 0;
	double n = strtod(str, &endptr);

	if (str == endptr)
	{
		return false;
	}
	else if (errno != 0)
	{
		return false;
	}
	else if (*endptr != '\0')
	{
		return false;
	}
	else if (n > DBL_MAX)
	{
		return false;
	}

	*number = n;

	return true;
}


/*
 * IntervalToString prepares a string buffer to represent a given interval
 * value given as a double precision float number.
 */
bool
IntervalToString(uint64_t millisecs, char *buffer, size_t size)
{
	double seconds = millisecs / 1000.0;

	if (millisecs < 1000)
	{
		sformat(buffer, size, "%3lldms", (long long) millisecs);
	}
	else if (seconds < 10.0)
	{
		int s = (int) seconds;
		uint64_t ms = millisecs - (1000 * s);

		sformat(buffer, size, "%2ds%03lld", s, (long long) ms);
	}
	else if (seconds < 60.0)
	{
		int s = (int) seconds;

		sformat(buffer, size, "%2ds", s);
	}
	else if (seconds < (60.0 * 60.0))
	{
		int mins = (int) (seconds / 60.0);
		int secs = (int) (seconds - (mins * 60.0));

		sformat(buffer, size, "%2dm%02ds", mins, secs);
	}
	else if (seconds < (24.0 * 60.0 * 60.0))
	{
		int hours = (int) (seconds / (60.0 * 60.0));
		int mins = (int) ((seconds - (hours * 60.0 * 60.0)) / 60.0);

		sformat(buffer, size, "%2dh%02dm", hours, mins);
	}
	else
	{
		long days = (long) (seconds / (24.0 * 60.0 * 60.0));
		long hours =
			(long) ((seconds - (days * 24.0 * 60.0 * 60.0)) / (60.0 * 60.0));

		sformat(buffer, size, "%2ldd%02ldh", days, hours);
	}

	return true;
}


/*
 * countLines returns how many line separators (\n) are found in the given
 * string.
 */
int
countLines(char *buffer)
{
	int lineNumber = 0;
	char *currentLine = buffer;

	if (buffer == NULL)
	{
		return 0;
	}

	do {
		char *newLinePtr = strchr(currentLine, '\n');

		if (newLinePtr == NULL)
		{
			if (strlen(currentLine) > 0)
			{
				++lineNumber;
			}
			currentLine = NULL;
		}
		else
		{
			++lineNumber;
			currentLine = ++newLinePtr;
		}
	} while (currentLine != NULL && *currentLine != '\0');

	return lineNumber;
}


/*
 * splitLines prepares a multi-line error message in a way that calling code
 * can loop around one line at a time and call log_error() or log_warn() on
 * individual lines.
 */
int
splitLines(char *buffer, char **linesArray, int size)
{
	int lineNumber = 0;
	char *currentLine = buffer;

	if (buffer == NULL)
	{
		return 0;
	}

	if (linesArray == NULL)
	{
		return -1;
	}

	do {
		char *newLinePtr = strchr(currentLine, '\n');

		if (newLinePtr == NULL)
		{
			if (strlen(currentLine) > 0)
			{
				linesArray[lineNumber++] = currentLine;
			}

			currentLine = NULL;
		}
		else
		{
			*newLinePtr = '\0';

			linesArray[lineNumber++] = currentLine;

			currentLine = ++newLinePtr;
		}
	} while (currentLine != NULL && *currentLine != '\0' && lineNumber < size);

	return lineNumber;
}


/*
 * processBufferCallback is a function callback to use with the subcommands.c
 * library when we want to output a command's output as it's running, such as
 * when running a pg_basebackup command.
 */
void
processBufferCallback(const char *buffer, bool error)
{
	char *outLines[BUFSIZE] = { 0 };
	int lineCount = splitLines((char *) buffer, outLines, BUFSIZE);
	int lineNumber = 0;

	int logLevel = error ? LOG_ERROR : LOG_INFO;

	for (lineNumber = 0; lineNumber < lineCount; lineNumber++)
	{
		if (strneq(outLines[lineNumber], ""))
		{
			log_level(logLevel, "%s", outLines[lineNumber]);
		}
	}
}


/*
 * pretty_print_bytes pretty prints bytes in a human readable form. Given
 * 17179869184 it places the string "16 GB" in the given buffer.
 */
void
pretty_print_bytes(char *buffer, size_t size, uint64_t bytes)
{
	const char *suffixes[7] = {
		"B",                    /* Bytes */
		"kB",                   /* Kilo */
		"MB",                   /* Mega */
		"GB",                   /* Giga */
		"TB",                   /* Tera */
		"PB",                   /* Peta */
		"EB"                    /* Exa */
	};

	uint sIndex = 0;
	long double count = bytes;

	while (count >= 10240 && sIndex < 7)
	{
		sIndex++;
		count /= 1024;
	}

	/* forget about having more precision, Postgres wants integers here */
	sformat(buffer, size, "%d %s", (int) count, suffixes[sIndex]);
}


/*
 * pretty_print_bytes pretty prints bytes in a human readable form. Given
 * 17179869184 it places the string "16 GB" in the given buffer.
 */
void
pretty_print_count(char *buffer, size_t size, uint64_t number)
{
	const char *suffixes[7] = {
		"",                     /* units */
		"",                     /* thousands */
		"million",              /* 10^6 */
		"billion",              /* 10^9 */
		"trillion",             /* 10^12 */
		"quadrillion",          /* 10^15 */
		"quintillion"           /* 10^18 */
	};

	if (number < 1000)
	{
		sformat(buffer, size, "%lld", (long long) number);
	}
	else if (number < (1000 * 1000))
	{
		int t = number / 1000;
		int u = number - (t * 1000);

		sformat(buffer, size, "%d %d", t, u);
	}
	else
	{
		uint sIndex = 0;
		long double count = number;

		/* issue 1234 million rather than 1 billion or 1.23 billion */
		while (count >= 10000 && sIndex < 7)
		{
			sIndex++;
			count /= 1000;
		}

		sformat(buffer, size, "%d %s", (int) count, suffixes[sIndex]);
	}
}

/*
 * Source: https://creativeandcritical.net/str-replace-c.
 * Replaces in the string str all the occurrences of the source string from with the destination string to.
 * The lengths of the strings from and to may differ. The string to may be of any length,
 * but the string from must be of non-zero length - the penalty for providing an empty string
 * for the from parameter is an infinite loop. In addition, none of the three parameters may be NULL.
 */
char *
repl_str(const char *str, const char *from, const char *to) {

	/* Adjust each of the below values to suit your needs. */

	/* Increment positions cache size initially by this number. */
	size_t cache_sz_inc = 16;
	/* Thereafter, each time capacity needs to be increased,
	 * multiply the increment by this factor. */
	const size_t cache_sz_inc_factor = 3;
	/* But never increment capacity by more than this number. */
	const size_t cache_sz_inc_max = 1048576;

	char *pret, *ret = NULL;
	const char *pstr2, *pstr = str;
	size_t i, count = 0;
	#if (__STDC_VERSION__ >= 199901L)
	uintptr_t *pos_cache_tmp, *pos_cache = NULL;
	#else
	ptrdiff_t *pos_cache_tmp, *pos_cache = NULL;
	#endif
	size_t cache_sz = 0;
	size_t cpylen, orglen, retlen, tolen, fromlen = strlen(from);

	/* Find all matches and cache their positions. */
	while ((pstr2 = strstr(pstr, from)) != NULL) {
		count++;

		/* Increase the cache size when necessary. */
		if (cache_sz < count) {
			cache_sz += cache_sz_inc;
			pos_cache_tmp = realloc(pos_cache, sizeof(*pos_cache) * cache_sz);
			if (pos_cache_tmp == NULL) {
				goto end_repl_str;
			} else pos_cache = pos_cache_tmp;
			cache_sz_inc *= cache_sz_inc_factor;
			if (cache_sz_inc > cache_sz_inc_max) {
				cache_sz_inc = cache_sz_inc_max;
			}
		}

		pos_cache[count-1] = pstr2 - str;
		pstr = pstr2 + fromlen;
	}

	orglen = pstr - str + strlen(pstr);

	/* Allocate memory for the post-replacement string. */
	if (count > 0) {
		tolen = strlen(to);
		retlen = orglen + (tolen - fromlen) * count;
	} else	retlen = orglen;
	ret = malloc(retlen + 1);
	if (ret == NULL) {
		goto end_repl_str;
	}

	if (count == 0) {
		/* If no matches, then just duplicate the string. */
		strcpy(ret, str);
	} else {
		/* Otherwise, duplicate the string whilst performing
		 * the replacements using the position cache. */
		pret = ret;
		memcpy(pret, str, pos_cache[0]);
		pret += pos_cache[0];
		for (i = 0; i < count; i++) {
			memcpy(pret, to, tolen);
			pret += tolen;
			pstr = str + pos_cache[i] + fromlen;
			cpylen = (i == count-1 ? orglen : pos_cache[i+1]) - pos_cache[i] - fromlen;
			memcpy(pret, pstr, cpylen);
			pret += cpylen;
		}
		ret[retlen] = '\0';
	}

end_repl_str:
	/* Free the cache and return the post-replacement string,
	 * which will be NULL in the event of an error. */
	free(pos_cache);
	return ret;
}
