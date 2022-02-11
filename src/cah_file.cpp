#include <Windows.h>
#include <ObjBase.h>

#include <stdio.h>
#include <malloc.h>

#include "cah_file.h"

const uint32_t CRC::_Table[256] =
{
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
	0xe963a535, 0x9e6495a3,	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
	0xf3b97148, 0x84be41de,	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,	0x14015c4f, 0x63066cd9,
	0xfa0f3d63, 0x8d080df5,	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,	0x35b5a8fa, 0x42b2986c,
	0xdbbbc9d6, 0xacbcf940,	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
	0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,	0x76dc4190, 0x01db7106,
	0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
	0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
	0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
	0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
	0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
	0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
	0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
	0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
	0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
	0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
	0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
	0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
	0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
	0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
	0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
	0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

uint32_t CRC::String(const char *str, uint32_t crc32)
{
	const char *p = str;
	uint32_t local_crc32 = ~crc32;

	while (*p)
	{
		local_crc32 = _Table[(local_crc32 ^ *p++) & UINT8_MAX] ^ (local_crc32 >> 8);
	}

	return ~local_crc32;
}

uint32_t CRC::Memory(const void *data, uint32_t data_len, uint32_t crc32)
{
	const uint8_t *p = (const uint8_t *)data;
	uint32_t local_crc32 = ~crc32;

	while (data_len--)
	{
		local_crc32 = _Table[(local_crc32 ^ *p++) & UINT8_MAX] ^ (local_crc32 >> 8);
	}

	return ~local_crc32;
}

cah_file::cah_file()
{
	magic1 = 0;
	magic2 = 0;
	header_unk1 = 0;
	header_unk2 = 0;

	version = 0;
	obj_id = 0;

	name = NULL;

	class_index = 0;
	sub_class_index = 0;
	reserved1 = 0;
	reserved2 = 0;

	color1 = 0;
	color2 = 0;
	color3 = 0;

	memset(powers, 0, sizeof(powers));

	bling_count = 0;
	bling = NULL;

	guid_str = NULL;

	is_system_hero = FALSE;

	checksum = 0;
	my_checksum = 0;
}

cah_file::~cah_file()
{
	free(name);

	for (uint32_t i = 0; i < powers_array_size; i++)
	{
		free(powers[i].command_button);
	}

	if (bling)
	{
		for (int32_t i = 0; i < bling_count; i++)
		{
			free(bling[i].group_name);
		}
	}

	free(bling);

	free(guid_str);
}

bool32_t cah_file::read(FILE *f)
{
	uint8_t str_len;

	fread(&magic1, sizeof(magic1), 1, f);
	fread(&magic2, sizeof(magic2), 1, f);

	if (magic1 != 'EALA' || magic2 != 'RTS2') return FALSE;

	fread(&header_unk1, sizeof(header_unk1), 1, f);
	fread(&header_unk2, sizeof(header_unk2), 1, f);

	fread(&version, sizeof(version), 1, f);
	fread(&obj_id, sizeof(obj_id), 1, f);

	fread(&str_len, sizeof(str_len), 1, f);
	name = (wchar_t *)calloc(str_len * sizeof(wchar_t) + 1, 1);
	fgetws(name, str_len + 1, f);

	fread(&class_index, sizeof(class_index), 1, f);
	fread(&sub_class_index, sizeof(sub_class_index), 1, f);
	fread(&reserved1, sizeof(reserved1), 1, f);
	fread(&reserved2, sizeof(reserved2), 1, f);

	fread(&color1, sizeof(color1), 1, f);
	fread(&color2, sizeof(color2), 1, f);
	fread(&color3, sizeof(color3), 1, f);

	for (uint32_t i = 0; i < powers_array_size; i++)
	{
		fread(&str_len, sizeof(str_len), 1, f);
		powers[i].command_button = (char *)calloc(str_len + 1, 1);
		fgets(powers[i].command_button, str_len + 1, f);

		fread(&powers[i].exp_level, sizeof(powers[i].exp_level), 1, f);
		fread(&powers[i].button_index, sizeof(powers[i].button_index), 1, f);
	}

	fread(&bling_count, sizeof(bling_count), 1, f);

	bling = (bling_entry *)calloc(bling_count, sizeof(bling_entry));

	for (int32_t i = 0; i < bling_count; i++)
	{
		fread(&str_len, sizeof(str_len), 1, f);
		bling[i].group_name = (char *)calloc(str_len + 1, 1);
		fgets(bling[i].group_name, str_len + 1, f);

		fread(&bling[i].bling_index, sizeof(bling[i].bling_index), 1, f);
	}

	fread(&str_len, sizeof(str_len), 1, f);
	guid_str = (char *)calloc(str_len + 1, 1);
	fgets(guid_str, str_len + 1, f);

	fread(&is_system_hero, sizeof(is_system_hero), 1, f);

	fread(&checksum, sizeof(checksum), 1, f);

	return TRUE;
}

void cah_file::write(FILE *f)
{
	uint8_t str_len;

	fwrite(&magic1, sizeof(magic1), 1, f);
	fwrite(&magic2, sizeof(magic2), 1, f);

	fwrite(&header_unk1, sizeof(header_unk1), 1, f);
	fwrite(&header_unk2, sizeof(header_unk2), 1, f);

	fwrite(&version, sizeof(version), 1, f);
	fwrite(&obj_id, sizeof(obj_id), 1, f);

	str_len = (uint8_t)wcslen(name);
	fwrite(&str_len, sizeof(str_len), 1, f);
	fputws(name, f);

	fwrite(&class_index, sizeof(class_index), 1, f);
	fwrite(&sub_class_index, sizeof(sub_class_index), 1, f);
	fwrite(&reserved1, sizeof(reserved1), 1, f);
	fwrite(&reserved2, sizeof(reserved2), 1, f);

	fwrite(&color1, sizeof(color1), 1, f);
	fwrite(&color2, sizeof(color2), 1, f);
	fwrite(&color3, sizeof(color3), 1, f);

	for (uint32_t i = 0; i < powers_array_size; i++)
	{
		str_len = (uint8_t)strlen(powers[i].command_button);
		fwrite(&str_len, sizeof(str_len), 1, f);
		fputs(powers[i].command_button, f);

		fwrite(&powers[i].exp_level, sizeof(powers[i].exp_level), 1, f);
		fwrite(&powers[i].button_index, sizeof(powers[i].button_index), 1, f);
	}

	fwrite(&bling_count, sizeof(bling_count), 1, f);

	for (int32_t i = 0; i < bling_count; i++)
	{
		str_len = (uint8_t)strlen(bling[i].group_name);
		fwrite(&str_len, sizeof(str_len), 1, f);
		fputs(bling[i].group_name, f);

		fwrite(&bling[i].bling_index, sizeof(bling[i].bling_index), 1, f);
	}

	str_len = (uint8_t)strlen(guid_str);
	fwrite(&str_len, sizeof(str_len), 1, f);
	fputs(guid_str, f);

	fwrite(&is_system_hero, sizeof(is_system_hero), 1, f);

	update_checksum();

	fwrite(&my_checksum, sizeof(my_checksum), 1, f);
}

void cah_file::print_info(FILE *f)
{
	fprintf(f, "magic1: %08X\n", magic1);
	fprintf(f, "magic2: %08X\n", magic2);

	fprintf(f, "header_unk1: %d\n", header_unk1);
	fprintf(f, "header_unk2: %d\n", header_unk2);

	fprintf(f, "\n");

	fprintf(f, "version: %d\n", version);
	fprintf(f, "obj_id: %d\n", obj_id);
	
	fwprintf(f, L"name: %s\n", name);

	fprintf(f, "class_index: %d\n", class_index);
	fprintf(f, "sub_class_index: %d\n", sub_class_index);
	fprintf(f, "reserved1: %d\n", reserved1);
	fprintf(f, "reserved2: %d\n", reserved2);

	fprintf(f, "color1: %08X\n", color1);
	fprintf(f, "color2: %08X\n", color2);
	fprintf(f, "color3: %08X\n", color3);

	fprintf(f, "\n");

	for (uint32_t i = 0; i < powers_array_size; i++)
	{
		fprintf(f, "powers[%u].command_button: %s\n", i, powers[i].command_button);
		fprintf(f, "powers[%u].exp_level: %d\n", i, powers[i].exp_level);
		fprintf(f, "powers[%u].button_index: %d\n", i, powers[i].button_index);
	}

	fprintf(f, "\n");

	fprintf(f, "bling_count: %d\n", bling_count);

	for (int32_t i = 0; i < bling_count; i++)
	{
		fprintf(f, "bling[%d].group_name: %s\n", i, bling[i].group_name);
		fprintf(f, "bling[%d].bling_index: %d\n", i, bling[i].bling_index);
	}

	fprintf(f, "\n");

	fprintf(f, "guid_str: %s\n", guid_str);
	fprintf(f, "is_system_hero: %d\n", is_system_hero);

	fprintf(f, "checksum: %08X\n", checksum);
	fprintf(f, "my_checksum: %08X\n", my_checksum); // to check if recalculation succeeded

	fprintf(f, "\n");
}

void cah_file::update_checksum()
{
	my_checksum = 0;

	my_checksum = CRC::Memory(&obj_id, sizeof(obj_id), my_checksum);

	int ascii_len = WideCharToMultiByte(CP_UTF8, 0, name, -1, NULL, 0, NULL, FALSE);
	char *ascii_name = (char *)calloc(ascii_len, 1);
	WideCharToMultiByte(CP_UTF8, 0, name, -1, ascii_name, ascii_len, NULL, FALSE);
	my_checksum = CRC::String(ascii_name, my_checksum);
	free(ascii_name);

	my_checksum = CRC::Memory(&class_index, sizeof(class_index), my_checksum);
	my_checksum = CRC::Memory(&sub_class_index, sizeof(sub_class_index), my_checksum);
	my_checksum = CRC::Memory(&reserved1, sizeof(reserved1), my_checksum);
	my_checksum = CRC::Memory(&reserved2, sizeof(reserved2), my_checksum);

	my_checksum = CRC::Memory(&color1, sizeof(color1), my_checksum);
	my_checksum = CRC::Memory(&color2, sizeof(color2), my_checksum);
	my_checksum = CRC::Memory(&color3, sizeof(color3), my_checksum);

	for (uint32_t i = 0; i < powers_array_size; i++)
	{
		my_checksum = CRC::String(powers[i].command_button, my_checksum);
		my_checksum = CRC::Memory(&powers[i].exp_level, sizeof(powers[i].exp_level), my_checksum);
		my_checksum = CRC::Memory(&powers[i].button_index, sizeof(powers[i].button_index), my_checksum);
	}

	my_checksum = CRC::Memory(&bling_count, sizeof(bling_count), my_checksum);

	for (int32_t i = 0; i < bling_count; i++)
	{
		my_checksum = CRC::String(bling[i].group_name, my_checksum);
		my_checksum = CRC::Memory(&bling[i].bling_index, sizeof(bling[i].bling_index), my_checksum);
	}

	my_checksum = CRC::Memory(&is_system_hero, sizeof(is_system_hero), my_checksum);
}

void cah_file::update_guid()
{
	GUID guid;
	CoCreateGuid(&guid);

	char temp_str[UINT8_MAX + 1];
	snprintf(temp_str, sizeof(temp_str), "%X%X%X%X%X%X%X", guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3]);

	free(guid_str);
	guid_str = strdup(temp_str);
}

void cah_file::set_name(wchar_t *new_name)
{
	free(name);
	name = wcsdup(new_name);
}

void cah_file::set_power_command_button(uint32_t i, char *command_button)
{
	if (i >= num_powers) return;

	free(powers[i].command_button);
	powers[i].command_button = strdup(command_button);
}

void cah_file::set_power_exp_level(uint32_t i, int32_t exp_level)
{
	if (i >= num_powers) return;

	if (exp_level <= 0) return;

	powers[i].exp_level = exp_level - 1;
}

void cah_file::set_power_button_index(uint32_t i, int32_t button_index)
{
	if (i >= num_powers) return;

	powers[i].button_index = button_index;
}

void cah_file::set_attribute(char *name, int32_t value)
{
	if (value <= 0) return;

	for (int32_t i = 0; i < bling_count; i++)
	{
		if (!strcmp(name, bling[i].group_name))
		{
			bling[i].bling_index = value - 1;

			break;
		}
	}
}

void cah_file::set_armor_attr(int32_t value)
{
	set_attribute(CAH_BLING_ARMOR_ATTR_STR, value);
}

void cah_file::set_damage_mult_attr(int32_t value)
{
	set_attribute(CAH_BLING_DAMAGE_MULT_ATTR_STR, value);
}

void cah_file::set_health_mult_attr(int32_t value)
{
	set_attribute(CAH_BLING_HEALTH_MULT_ATTR_STR, value);
}

void cah_file::set_auto_heal_attr(int32_t value)
{
	set_attribute(CAH_BLING_AUTO_HEAL_ATTR_STR, value);
}

void cah_file::set_vision_attr(int32_t value)
{
	set_attribute(CAH_BLING_VISION_ATTR_STR, value);
}
