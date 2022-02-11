#pragma once

#include <stdint.h>

typedef uint8_t bool8_t;
typedef int32_t bool32_t;

// pretty much 1:1 reversed from rotwk, names from Zero Hour
struct CRC
{
	static const uint32_t _Table[256];

	static uint32_t String(const char *str, uint32_t crc32);
	static uint32_t Memory(const void *data, uint32_t data_len, uint32_t crc32);
};

struct cah_file
{
	enum class_index
	{
		men_of_the_west,
		archer,
		wizard,
		dwarf,
		servant_of_sauron,
		corrupted_man,
		olog_hai,
	};

	enum men_of_the_west_sub_class_index
	{
		captain_of_gondor,
		shield_maiden,
	};

	enum archer_sub_class_index
	{
		male_elven_archer,
		female_elven_archer,
	};

	enum wizard_sub_class_index
	{
		wanderer,
		avatar,
		hermit,
	};

	enum dwarf_sub_class_index
	{
		taskmaster,
		sage,
	};

	enum servant_of_sauron_sub_class_index
	{
		orc_raider,
		uruk,
	};

	enum corrupted_man_sub_class_index
	{
		easterling,
		haradrim,
	};

	enum olog_hai_sub_class_index
	{
		great_troll,
		snow_troll,
		hill_troll,
	};

	enum
	{
		num_powers = 10, // 10 levels
		powers_array_size = num_powers + 5, // last 5 are unused
	};

	// generic header stuff
	uint32_t magic1; // EALA, 0x45414C41
	uint32_t magic2; // RTS2, 0x52545332
	int32_t header_unk1; // generally 1, num entries in file?, nope ... probably something else
	int32_t header_unk2; // generally 0, some kind of block type?, a4 != 0, and a4 is 0 ...

	// now the actual CreateAHero data begins
	uint8_t version; // can be 1 - 8, seems to all be 8

	// good / evil??
	// observed values:
	// 0: MyHero.dat
	// 19: good/wizard?
	// 55: evil?
	// 57: one system hero (fhaleen), could not be reproduced by creating the same hero again
	int32_t obj_id; // ID, ObjectID, 4 byte enum

	wchar_t *name; // Name

	int32_t class_index; // thanks c++, see class enum, ClassIndex
	int32_t sub_class_index; // see sub_class enums, SubClassIndex
	int32_t reserved1; // probably just padding or for further sub typing stuff, Dummy
	int32_t reserved2; // Dummy

	uint32_t color1; // PrimaryColor
	uint32_t color2; // SecondaryColor
	uint32_t color3; // TertiaryColor

	struct cah_power
	{
		char *command_button; // CommandBotton
		int32_t exp_level; // ExpLevel, always -1 from the actual value
		int32_t button_index; // 8 for dummy, ButtonIndex
	};

	cah_power powers[powers_array_size];

	// currently used names, in this order, but i don't think it's guaranteed, since they come from ini (and the sorting seems nonsensical, so probably hashmap):
#define CAH_BLING_WEAPON_STR			"CreateAHero_Weapon"
#define CAH_BLING_ARMOR_ATTR_STR		"CreateAHero_ArmorAttribute"
#define CAH_BLING_DAMAGE_MULT_ATTR_STR	"CreateAHero_DamageMultAttribute"
#define CAH_BLING_VISION_ATTR_STR		"CreateAHero_VisionAttribute"
#define CAH_BLING_AUTO_HEAL_ATTR_STR	"CreateAHero_AutoHealAttribute"
#define CAH_BLING_HEALTH_MULT_ATTR_STR	"CreateAHero_HealthMultAttribute"
#define CAH_BLING_SHOULDER_PLATES_ST	"CreateAHero_ShoulderPlates"
#define CAH_BLING_HELMET_STR			"CreateAHero_Helmet"
#define CAH_BLING_GAUNTLETS_STR			"CreateAHero_Gauntlets"
#define CAH_BLING_SHIELD_STR			"CreateAHero_Shield"
#define CAH_BLING_BOOTS_STR				"CreateAHero_Boots"
#define CAH_BLING_BODY_STR				"CreateAHero_Body"

	struct bling_entry
	{
		char *group_name; // GroupName
		int32_t bling_index; // for some reason always -1 from the value shown in game (at least for the stats), BlingIndex? maybe just stupid name?
	};

	int32_t bling_count; // always 12? stats and visual customizations, BlingCount
	bling_entry *bling;

	char *guid_str; // apparently converted from a GUID created by CoCreateGuid, see update_guid()

	bool8_t is_system_hero; // IsSystemHero

	uint32_t checksum; // standard crc32, see update_checksum()
	uint32_t my_checksum; // recalculated chekcsum for writing

	cah_file();
	~cah_file();

	bool32_t read(FILE *f); // returns FALSE if magic values in header aren't correct
	void write(FILE *f); // updates checksum automatically and regardless of changes
	void print_info(FILE *f = stdout);

	void update_checksum();
	void update_guid();

	void set_name(wchar_t *new_name);

	void set_power_command_button(uint32_t i, char *command_button);
	void set_power_exp_level(uint32_t i, int32_t exp_level); // will decrement input value by 1
	void set_power_button_index(uint32_t i, int32_t button_index); // valid are 1-5, and 8 for "Command_SpecialAbilityNoPowerDummy"

	void set_attribute(char *name, int32_t value); // will decrement input value by 1

	// helper functions that know the string to search
	void set_armor_attr(int32_t value); // will decrement input value by 1
	void set_damage_mult_attr(int32_t value); // will decrement input value by 1
	void set_health_mult_attr(int32_t value); // will decrement input value by 1
	void set_auto_heal_attr(int32_t value); // will decrement input value by 1
	void set_vision_attr(int32_t value); // will decrement input value by 1
};
