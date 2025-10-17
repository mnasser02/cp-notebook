int insideRectangle(int x, int y, int w, int h, int a, int b) {
    if ((x < a) && (a < x + w) && (y < b) && (b < y + h))
        return 1;  // strictly inside
    else if ((x <= a) && (a <= x + w) && (y <= b) && (b <= y + h))
        return 0;  // at border
    else
        return -1;  // outside
}
