_Bool isPar(int number);

int getMargin(int minimumNumber);

float get_cellPositonX(int column, int maxColumns, int WIDTH);

float get_cellPositonY(int row, int maxRows, int HEIGHT);

float get_cellSizeX(int column, int maxColumns, int WIDTH);

float get_cellSizeY(int row, int maxRows, int HEIGHT);

void drawWin();

void drawLose();

//Textures
void ReadJPEG(char *filename,unsigned char **image,int *width, int *height);

void LoadTexture(char *filename,int dim);