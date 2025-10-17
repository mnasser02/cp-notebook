double gcDist(double pLa, double pLo, double qLa, double qLo, double r) {
    pLa *= M_PI / 180;
    pLo *= M_PI / 180;
    qLa *= M_PI / 180;
    qLo *= M_PI / 180;
    return r * acos(cos(pLa) * cos(pLo) * cos(qLa) * cos(qLo) + cos(pLa) * sin(pLo) * cos(qLa) * sin(qLo) + sin(pLa) * sin(qLa));
}
