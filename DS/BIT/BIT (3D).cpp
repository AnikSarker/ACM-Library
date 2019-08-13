//Point Update and Range Query similar as 2D BIT

void update(int x1, int y1, int z1, int x2, int y2, int z2){
    update(x2, y2, z2, 1),          update(x1 - 1, y1 - 1, z2, 1);
    update(x1 - 1, y2, z1 - 1, 1),  update(x2, y1 - 1, z1 - 1, 1);
    update(x1 - 1, y2, z2, -1),     update(x2, y1 - 1, z2, -1);
    update(x2, y2, z1 - 1, -1),     update(x1 - 1, y1 - 1, z1 - 1, -1);
}
