#pragma once
class MyImage
{
public:
	static MyImage* fromFile(const std::string& filename, int channel = 4);

	int width() const { return m_width; }
	int height() const { return m_height; }
	int channels() const { return m_channels; }
	int bytesPerPixel() const { return m_channels * (m_hdr ? sizeof(float) : sizeof(unsigned char)); }
	int pitch() const { return m_width * bytesPerPixel(); }

	bool isHDR() const { return m_hdr; }

	template<typename T>
	const T* pixels() const {
		return reinterpret_cast<const T*>(m_pixels);
	}

private:
	MyImage();

	int m_width;
	int m_height;
	int m_channels;
	bool m_hdr;
	unsigned char* m_pixels;
};

