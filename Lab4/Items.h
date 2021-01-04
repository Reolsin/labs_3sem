#pragma once
#include "Declarations.h"


namespace Gamma {

	/// Class that stores the state common to all Items. \details Cant be created.
	class Item {
	private:
		std::string name;
		int weight, use_points;
	protected:
		Item() : name("noname"), weight(), use_points() {}
		Item(std::string, int, int);
		Item(std::ifstream&); ///< Constructor that builds object with loading config file.

		virtual std::ostream& display(std::ostream&) const; ///< Method for displaying the panel of object on interface.
		virtual std::ofstream& save(std::ofstream&) const; ///< Method for saving the object in format of configuration file.
	public:
		inline int up() const { return use_points; }
		inline int w() const { return weight; }

		virtual const std::string* use(Operative*) = 0; ///< The signature of virtual funtion for using items.

		friend std::ofstream& operator<<(std::ofstream& ofile, const Item& item) { return item.save(ofile); }
		friend std::ostream& operator<<(std::ostream& os, const Item& item) { return item.display(os); }
	};

	/// Class representing an instance of a weapon.
	class weapon : public Item {
	private:
		int cur_clip_ammo,
			full_clip_ammo,
			damage, reload_points;
		double ammo_type;
	protected:
		virtual std::ostream& display(std::ostream&) const; ///< Method for displaying the panel of object on interface.
		virtual std::ofstream& save(std::ofstream&) const; ///< Method for saving the object in format of configuration file.
	public:
		weapon() : Item(), cur_clip_ammo(), full_clip_ammo(), damage(), reload_points(), ammo_type() {}
		weapon(std::string n, int w, int up, int cur, int full, int d, int rp, double a_type);
		weapon(std::ifstream&); ///< Constructor that builds object with loading config file.

		double deal_damage(); ///< Method that allows to replish weapon's ammo. \details Used in Attack_Unit.attack.
		int reload(int, double); ///< Method that allows to replish weapon's ammo. \details Used in Operative.load_ammo. Returns the amount of replenished ammunition.

		virtual const std::string* use(Operative*); ///< Method that changes current weapon of the unit. \details Does not require availability of MP for using.
	};

	/// Class representing an instance of an aidkit.
	class aidkit : public Item {
	private:
		int heal_amount, charges, full_charges;
	protected:
		virtual std::ostream& display(std::ostream&) const; ///< Method for displaying the panel of object on interface.
		virtual std::ofstream& save(std::ofstream&) const; ///< Method for saving the object in format of configuration file.
	public:
		aidkit() : Item(), heal_amount(), charges(), full_charges() {}
		aidkit(std::string n, int w, int up, int cur, int ful, int heal);
		aidkit(std::ifstream&); ///< Constructor that builds object with loading config file.

		virtual const std::string* use(Operative*); ///< Method that heals unit. \details Requires availability of MP for using.
	};

	/// Class representing an instance of an ammunition.
	class ammunition : public Item {
	private:
		int cur_count, full_count;
		double ammo_type;
	protected:
		virtual std::ostream& display(std::ostream&) const; ///< Method for displaying the panel of object on interface.
		virtual std::ofstream& save(std::ofstream&) const; ///< Method for saving the object in format of configuration file.
	public:
		ammunition() : Item(), cur_count(), full_count(), ammo_type() {}
		ammunition(std::string n, int w, int up, int cur, int ful, double a_type);
		ammunition(std::ifstream&); ///< Constructor that builds object with loading config file.

		virtual const std::string* use(Operative*); ///< Method that replish Unit's weapon ammo. \details Requires availability of MP for using.
	};
}
