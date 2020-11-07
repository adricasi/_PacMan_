float get_cellPositonX(int column, int maxColumns, int WIDTH);

float get_cellPositonY(int row, int maxRows, int HEIGHT);

float get_cellPositonZ(int row, int maxRows, int HEIGHT);

float get_cellSizeX(int column, int maxColumns, int WIDTH);

float get_cellSizeY(int row, int maxRows, int HEIGHT);

float get_cellSizeZ(int row, int maxRows, int HEIGHT);

void draw_wall(float x,float y,float z,float sizeX,float sizeY,float sizeZ, float red, float green, float blue, float maxTexturePositionX, float minTexturePositionX, float maxTexturePositionY, float minTexturePositionY);

void draw_square(float x,float y,float z,float sizeX,float sizeY,float sizeZ, float red, float green, float blue, float maxTexturePositionX, float minTexturePositionX, float maxTexturePositionY, float minTexturePositionY);

void draw_floor(float x,float y,float z,float sizeX,float sizeY,float sizeZ, float red, float green, float blue, float maxTexturePositionX, float minTexturePositionX, float maxTexturePositionY, float minTexturePositionY);

void draw_sphere(float x,float y,float z, float radius, float red, float green, float blue);