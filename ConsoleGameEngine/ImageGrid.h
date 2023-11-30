#pragma once
void initializeCharArray(char arr[], int size, char val)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = val;
	}
}

void drawToBuffer(char arr[], char buffer[], int width, int height)
{
    int bufferIndex = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            buffer[bufferIndex++] = arr[y * width + x];
            buffer[bufferIndex++] = ' ';
        }
        buffer[bufferIndex++] = '\n';
    }
}