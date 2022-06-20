#pragma once
#include <iostream>
#include <math.h>

#define K0 0.9996
#define	E 0.00669438
#define	E2 E * E
#define	E3 E2 * E
#define	E_P2 E / (1 - E)
#define	SQRT_E sqrt(1 - E)
#define	_E (1 - SQRT_E) / (1 + SQRT_E)
#define	_E2 _E * _E
#define	_E3 _E2 * _E
#define	_E4 _E3 * _E
#define	_E5 _E4 * _E
#define	M1 (1 - E / 4 - 3 * E2 / 64 - 5 * E3 / 256)
#define	M2 (3 * E / 8 + 3 * E2 / 32 + 45 * E3 / 1024)
#define	M3 (15 * E2 / 256 + 45 * E3 / 1024)
#define	M4 (35 * E3 / 3072)
#define	P2 (3 / 2 * _E - 27 / 32 * _E3 + 269 / 512 * _E5)
#define	P3 (21 / 16 * _E2 - 55 / 32 * _E4)
#define	P4 (151 / 96 * _E3 - 417 / 128 * _E5)
#define	P5 (1097 / 512 * _E4)
#define	R 6378137
#define	ZONE_LETTERS "CDEFGHJKLMNPQRSTUVWXX"
#define sucssec 1
#define fault 0
#define pi 3.14159265358979323846
#define RAD_TO_DEG 180.0 / pi
#define DEG_TO_RAD pi / 180.0

class RUTM
{
private:
	bool mixed_signs(double x)
		//
	{
		return (std::min(x, x) < 0) && (std::max(x, x) >= 0);
	}

	double negative(double x) {
		return x < 0;
	}

	double mod_angle(double value)
		//
	{
		// """Returns angle in radians to be between -pi and pi""" 
		int q = ((int)((int)(value + pi)) / ((int)(2 * pi)));
		while ((value + pi) < q * (2 * pi)) q--;
		return (((value + pi) - q * (2 * pi)) - pi);
	}

	bool check_valid_zone(int zone_number, char zone_letter)
		//
	{
		if (1 > zone_number && zone_number > 60)
		{
			std::cout << "OutOfRangeError : zone number out of range (must be between 1 and 60)";
			return false;
		}
		zone_letter = toupper(zone_letter);
		if (!('C' <= zone_letter && zone_letter <= 'X') || (zone_letter == 'I' || zone_letter == 'O'))
		{
			std::cout << "OutOfRangeError : zone letter out of range (must be between C and X)";
			return false;
		}
	}

	bool in_bounds(double x, double lower, double upper)
		//
	{
		if (lower <= x && x < upper)
			return true;
	}

public:
	struct  structUTMlatlong
	{
		double Latitude;
		double Logitude;
		int zoneUmber;
		char zoneLetter;
	};

	struct  structlatlong
	{
		double Latitude;
		double Logitude;
	};

	char latitude_to_zone_letter(double latitude)
	{
		if (latitude >= -80 && latitude <= 84)
			return ZONE_LETTERS[int(latitude + 80) >> 3];
		else
			return '?';
	}

	int latlon_to_zone_number(double latitude, double longitude)
	{
		if ((56 <= latitude && latitude < 64) && (longitude < 12))
			return 32;
		if ((72 <= latitude && latitude <= 84) && (longitude >= 0))
			if (longitude < 9) return 31;
			else if (longitude < 21) return 33;
			else if (longitude < 42)  return 37;
		return int((longitude + 180) / 6) + 1;
	}

	double zone_number_to_central_longitude(double zone_number)
	{
		return (zone_number - 1) * 6 - 180 + 3;
	}
	structUTMlatlong from_latlon(double latitude, double longitude, int force_zone_number, char force_zone_letter)
		/*
		*
		Parameters
			----------
			latitude: float
				Latitude between 80 deg S and 84 deg N, e.g. (-80.0 to 84.0)
			longitude: float
				Longitude between 180 deg W and 180 deg E, e.g. (-180.0 to 180.0).
			force_zone_number: int
				Zone number is represented by global map numbers of an UTM zone
				numbers map. You may force conversion to be included within one
				UTM zone number.  For more information see utmzones [1]_
			force_zone_letter: str
				You may force conversion to be included within one UTM zone
				letter.  For more information see utmzones [1]_
		Returns
			-------
			easting: float
				Easting value of UTM coordinates
			northing: float
				Northing value of UTM coordinates
			zone_number: int
				Zone number is represented by global map numbers of a UTM zone
				numbers map. More information see utmzones [1]_
			zone_letter: str
				Zone letter is represented by a string value. UTM zone designators
				can be accessed in [1]_
		*/
	{
		if (latitude < -80 || latitude > 84)
			std::cout << "latitude out of range (must be between 80 deg S and 84 deg N)";
		if (longitude < -180 || longitude > 180)
			std::cout << "longitude out of range (must be between 180 deg W and 180 deg E)";
		double lat_rad = DEG_TO_RAD * latitude;
		double lat_sin = sin(lat_rad);
		double lat_cos = cos(lat_rad);
		double lat_tan = lat_sin / lat_cos;
		double lat_tan2 = lat_tan * lat_tan;
		double lat_tan4 = lat_tan2 * lat_tan2;
		int zone_number = latlon_to_zone_number(latitude, longitude);
		char zone_letter = latitude_to_zone_letter(latitude);
		double lon_rad = DEG_TO_RAD * longitude;
		double central_lon = zone_number_to_central_longitude(zone_number);
		double  central_lon_rad = DEG_TO_RAD * central_lon;
		double n = R / sqrt(1 - E * lat_sin * lat_sin);
		double c = E_P2 * lat_cos * lat_cos;
		double a = lat_cos * mod_angle(lon_rad - central_lon_rad);
		double a2 = a * a;
		double a3 = a2 * a;
		double a4 = a3 * a;
		double a5 = a4 * a;
		double a6 = a5 * a;
		double m = R * (M1 * lat_rad - M2 * sin(2 * lat_rad) + M3 * sin(4 * lat_rad) - M4 * sin(6 * lat_rad));
		double easting = K0 * n * (a + a3 / 6 * (1 - lat_tan2 + c) + a5 / 120 * (5 - 18 * lat_tan2 + lat_tan4 + 72 * c - 58 * E_P2)) + 500000;
		double northing = K0 * (m + n * lat_tan * (a2 / 2 + a4 / 24 * (5 - lat_tan2 + 9 * c + 4 * (c * c)) + a6 / 720 * (61 - 58 * lat_tan2 + lat_tan4 + 600 * c - 330 * E_P2)));
		/*if (mixed_signs(latitude))
			 std::cout << "latitudes must all have the same sign";
		 else
			 northing += 10000000;*/
		structUTMlatlong fromLatLong;
		fromLatLong.Latitude = easting;
		fromLatLong.Logitude = northing;
		fromLatLong.zoneUmber = zone_number;
		fromLatLong.zoneLetter = zone_letter;
		return fromLatLong;
	}

	structlatlong to_latlon(double easting, double northing, int zone_number, char zone_letter, bool northern, bool strict = true)
		/*
		*
		Parameters
			----------
			easting: int
				Easting value of UTM coordinates
			northing: int
				Northing value of UTM coordinates
			zone_number: int
				Zone number is represented with global map numbers of a UTM zone
				numbers map. For more information see utmzones [1]_
			zone_letter: str
				Zone letter can be represented as string values.  UTM zone
				designators can be seen in [1]_
			northern: bool
				You can set True or False to set this parameter. Default is None
			strict: bool
				Raise an OutOfRangeError if outside of bounds
		Returns
			-------
			latitude: float
				Latitude between 80 deg S and 84 deg N, e.g. (-80.0 to 84.0)
			longitude: float
				Longitude between 180 deg W and 180 deg E, e.g. (-180.0 to 180.0).
		*/
	{
		if (!zone_letter && northern)
			std::cout << "ValueError : either zone_letter or northern needs to be set";
		else if (zone_letter && northern)
			std::cout << "ValueError : set either zone_letter or northern, but not both'";

		if (strict)
		{
			if (!in_bounds(easting, 100000, 1000000))
				std::cout << "OutOfRangeError : easting out of range (must be between 100,000 m and 999,999 m";
			if (!in_bounds(northing, 0, 10000000))
				std::cout << "OutOfRangeError : northing out of range (must be between 0 m and 10,000,000 m";
		}
		check_valid_zone(zone_number, zone_letter);
		if (zone_letter)
		{
			zone_letter = toupper(zone_letter);
			northern = (zone_letter >= 'N');
		}
		double x = easting - 500000;
		double y = northing;
		if (!northern)
			y -= 10000000;
		double m = y / K0;
		double mu = m / (R * M1);
		double p_rad = (mu + P2 * sin(2 * mu) + P3 * sin(4 * mu) + P4 * sin(6 * mu) + P5 * sin(8 * mu));
		double p_sin = sin(p_rad);
		double p_sin2 = p_sin * p_sin;
		double p_cos = cos(p_rad);
		double p_tan = p_sin / p_cos;
		double p_tan2 = p_tan * p_tan;
		double p_tan4 = p_tan2 * p_tan2;
		double ep_sin = 1 - E * p_sin2;
		double ep_sin_sqrt = sqrt(1 - E * p_sin2);
		double n = R / ep_sin_sqrt;
		double r = (1 - E) / ep_sin;
		double c = E_P2 * (p_cos * p_cos);
		double c2 = c * c;
		double d = x / (n * K0);
		double d2 = d * d;
		double d3 = d2 * d;
		double d4 = d3 * d;
		double d5 = d4 * d;
		double d6 = d5 * d;
		double latitude = (p_rad - (p_tan / r) * (d2 / 2 - d4 / 24 * (5 + 3 * p_tan2 + 10 * c - 4 * c2 - 9 * E_P2)) + d6 / 720 * (61 + 90 * p_tan2 + 298 * c + 45 * p_tan4 - 252 * E_P2 - 3 * c2));
		double longitude = (d - d3 / 6 * (1 + 2 * p_tan2 + c) + d5 / 120 * (5 - 2 * c + 28 * p_tan2 - 3 * c2 + 8 * E_P2 + 24 * p_tan4)) / p_cos;
		longitude = mod_angle(longitude + DEG_TO_RAD * (zone_number_to_central_longitude(zone_number)));
		structlatlong tolatlon;
		tolatlon.Latitude = RAD_TO_DEG * latitude;
		tolatlon.Logitude = RAD_TO_DEG * longitude;
		return tolatlon;

	}
};

