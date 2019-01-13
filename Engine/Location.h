#pragma once

/*!
* @brief Klasa Location odpowiada za obs�ug� przestrzeni w grze.
*/
class Location
{
public:
	int x;
	int y;

	/*!
	 * @brief Funkcja dodaje wsp�rz�dne.
	 *
	 * \param[in] \& val wska�nik na klase Location zawieraj�c� wspo�rz�dne kt�re maj� by� dodane do zmiennych x, y obecnego obiektu.
	 */
	void Add(const Location& val)
	{
		x += val.x;
		y += val.y;
	}

	/*!
	 * @brief Funkcja dodaje wsp�rz�dne.
	 *
	 * \param[in] \& rhs wska�nik na klase Location zawieraj�c� wspo�rz�dne kt�re maj� by� przyr�wnane do zmiennych x, y obecnego obiektu.
	 *
	 * \return true je�eli s� r�wne, w innym wypadku false
	 */
	bool operator==(const Location& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	/*!
	 * @brief Funkcja dodaje wsp�rz�dne.
	 *
	 * \param[in] \& rhs wska�nik na klase Location zawieraj�c� wspo�rz�dne kt�re maj� by� sprawdzone pod k�tem r�nicy ze zmiennymi x, y obecnego obiektu.
	 *
	 * \return true je�eli s� r�ne, w innym wypadku false
	 */
	bool operator!=(const Location& rhs) const
	{
		return !(*this == rhs);
	}

	/*!
	 * @brief Funkcja zmienia x,y obiektu na przeciwne.
	 */
	Location operator-() const
	{
		return { -x, -y };
	}
};