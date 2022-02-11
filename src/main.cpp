#include <stdio.h>

#include "cah_file.h"

// do stuff here
void edit_cah(cah_file &cah)
{
	// make the current hero unique from another
#if 0
	printf("move MyHero_%s.cah ", cah.guid_str);
	cah.update_guid();
	printf("MyHero_%s.cah\n", cah.guid_str);
#endif

	// doesn't work, game has sanity checks
#if 0
	cah.set_armor_attr(20);
	cah.set_damage_mult_attr(20);
	cah.set_health_mult_attr(20);
	cah.set_auto_heal_attr(20);
	cah.set_vision_attr(20);
#endif

	printf("\n");
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("need input as arg (and output optionally as next arg)\n");

		return 1;
	}

	FILE *f = fopen(argv[1], "rb");

	if (!f)
	{
		printf("input could not be opened\n");

		return 1;
	}

	cah_file cah;

	if (!cah.read(f))
	{
		printf("input file is not a .cah file\n");
	}

	fclose(f);

	if (argc > 2)
	{
		f = fopen(argv[2], "wb");

		if (!f)
		{
			printf("output could not be opened\n");

			return 1;
		}

		edit_cah(cah);

		cah.write(f);
		fclose(f);
	}
	else
	{
		cah.update_checksum();
		cah.print_info();
	}

	return 0;
}
