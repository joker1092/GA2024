#include "framework.h"
#include <stb_image.h>
#include "MyImage.h"

MyImage* MyImage::fromFile(const std::string& filename, int channel)
{
	MyImage* image = new MyImage();
	if (stbi_is_hdr(filename.c_str())) {
		float* pixels = stbi_loadf(filename.c_str(), &image->m_width, &image->m_height, &image->m_channels, channel);
		if (pixels)
		{
			image->m_pixels = reinterpret_cast<unsigned char*>(pixels);
			image->m_hdr = true;
		}
	}
	else {
		unsigned char* pixels = stbi_load(filename.c_str(), &image->m_width, &image->m_height, &image->m_channels, channel);
		if (pixels) {
			image->m_pixels = pixels;
			image->m_hdr = false;
		}
	}
	if (channel>0)
	{
		image->m_channels = channel;
	}
	if (!image->m_pixels)
	{
		throw std::runtime_error("Failed to load image file : " + filename);
	}
	return image;
}

MyImage::MyImage():m_width(0),m_height(0), m_channels(0), m_hdr(false)
{
}
