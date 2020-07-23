
inline double inner(pdd a, pdd b) {
	double fdif = a.first - b.first, sdif = a.second - b.second;
	return fdif * fdif + sdif * sdif;
}

inline double dist(pdd a, pdd b) {
	return sqrt(inner(a, b));
}
