#pragma once

/**
* Klasa Location odpowiada za obs³ugê przestrzeni w grze.
*/
class Location
{
public:
	int x;
	int y;

	/**
	 * Funkcja dodaje wspó³rzêdne.
	 *
	 * \param[in] \& val wska¿nik na klase Location zawieraj¹c¹ wspo³rzêdne które maj¹ byæ dodane do zmiennych x, y obecnego obiektu. 
	 */
	void Add(const Location& val)
	{
		x += val.x;
		y += val.y;
	}

	/**
	 * Funkcja dodaje wspó³rzêdne.
	 *
	 * \param[in] \& rhs wska¿nik na klase Location zawieraj¹c¹ wspo³rzêdne które maj¹ byæ przyrównane do zmiennych x, y obecnego obiektu.
	 *
	 * \return true je¿eli s¹ równe, w innym wypadku false
	 */
	bool operator==(const Location& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	/**
	 * Funkcja dodaje wspó³rzêdne.
	 *
	 * \param[in] \& rhs wska¿nik na klase Location zawieraj¹c¹ wspo³rzêdne które maj¹ byæ sprawdzone pod k¹tem ró¿nicy ze zmiennymi x, y obecnego obiektu.
	 *
	 * \return true je¿eli s¹ ró¿ne, w innym wypadku false
	 */
	bool operator!=(const Location& rhs) const
	{
		return !(*this == rhs);
	}

	/**
	 * Funkcja zmienia x,y obiektu na przeciwne.
	 */
	Location operator-() const
	{
		return { -x, -y };
	}
};