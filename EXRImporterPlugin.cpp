#include <stdio.h>
#include <OpenEXR/ImfRgbaFile.h>
#include <OpenEXR/ImathBox.h>
#include <OpenEXR/ImfArray.h>

#define DLLEXPORT extern "C" __declspec(dllexport) 
#define DLLAPI __stdcall

using namespace Imf;
using namespace Imath;

struct EXRData
{
	Array2D<Rgba> pixels;
	int width;
	int height;

	EXRData(const char* path)
	{
		RgbaInputFile file(path);

		Box2i dw = file.dataWindow();
		width = dw.max.x - dw.min.x + 1;
		height = dw.max.y - dw.min.y + 1;
		pixels.resizeErase(width, height);

		file.setFrameBuffer(&pixels[0][0] - dw.min.x - dw.min.y * width, 1, width);
		file.readPixels(dw.min.y, dw.max.y);
	}
};

DLLEXPORT EXRData* DLLAPI OpenEXR(const char* path, int* width, int* height)
{
	EXRData* data = new EXRData(path);
	*width = data->width;
	*height = data->height;
	return data;
}

DLLEXPORT int DLLAPI CopyRGBAData(EXRData* handle, void* dest, int destLen)
{
	if (!handle || !dest || destLen != handle->width * handle->height * sizeof(float) * 4)
	{
		return -1;
	}

	float* ptr = (float*)dest;

	for (int y = 0; y < handle->height; ++y)
	{
		for (int x = 0; x < handle->width; ++x)
		{
			*ptr++ = handle->pixels[y][x].r;
			*ptr++ = handle->pixels[y][x].g;
			*ptr++ = handle->pixels[y][x].b;
			*ptr++ = handle->pixels[y][x].a;
		}
	}

	return 0;
}

DLLEXPORT void DLLAPI CloseEXR(EXRData* handle)
{
	if (handle)
	{
		delete handle;
	}
}
