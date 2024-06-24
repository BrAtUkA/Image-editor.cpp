#include <vector>
#include <thread>
#include <cmath>
#include <string>
#include <algorithm>  // For std::sort
#include <numeric>    // For std::accumulate
#include <ctime>

#pragma once
using namespace System;
using namespace System::IO;
using namespace System::Drawing;
using namespace System::Threading::Tasks;
using namespace System::Net;
using namespace System::Drawing::Imaging;

// ==================== CONSTANTS ====================
namespace ImageConstants {
	const double GRAYSCALE_R_WEIGHT = 0.299;
	const double GRAYSCALE_G_WEIGHT = 0.587;
	const double GRAYSCALE_B_WEIGHT = 0.114;
	const int OIL_PAINTING_RADIUS = 4;
	const int OIL_PAINTING_INTENSITY_LEVELS = 20;
	const int COLOR_BOOST_DIVISOR = 20;
}


bool IsImage(String^ filePath) {
	array<String^>^ validExtensions = { ".bmp", ".jpg", ".jpeg", ".gif", ".png", ".tiff", ".ico" };
	String^ fileExtension = System::IO::Path::GetExtension(filePath);
	for each (String ^ extension in validExtensions) {
		if (fileExtension->Equals(extension, StringComparison::InvariantCultureIgnoreCase)) {
			return true;
		}
	}
	return false;
}

double Clamp(double value, double min, double max) {
	return Math::Min(max, Math::Max(min, value));
}

void RGBtoHSV(int r, int g, int b, double% h, double% s, double% v) {
	double rd = r / 255.0;
	double gd = g / 255.0;
	double bd = b / 255.0;

	double max = Math::Max(rd, Math::Max(gd, bd));
	double min = Math::Min(rd, Math::Min(gd, bd));
	v = max;

	double delta = max - min;

	if (max == 0.0) {
		s = 0;
		h = 0;
	}
	else {
		s = delta / max;
		if (rd == max) {
			h = (gd - bd) / delta;
		}
		else if (gd == max) {
			h = 2 + (bd - rd) / delta;
		}
		else {
			h = 4 + (rd - gd) / delta;
		}

		h *= 60;
		if (h < 0) h += 360;
	}
}

void HSVtoRGB(double h, double s, double v, int% r, int% g, int% b) {
	int i;
	double f, p, q, t;

	if (s == 0) {
		r = g = b = (int)(v * 255.0);
		return;
	}

	h /= 60;
	i = (int)Math::Floor(h);
	f = h - i;
	p = v * (1 - s);
	q = v * (1 - s * f);
	t = v * (1 - s * (1 - f));

	switch (i) {
	case 0:
		r = (int)(v * 255.0);
		g = (int)(t * 255.0);
		b = (int)(p * 255.0);
		break;
	case 1:
		r = (int)(q * 255.0);
		g = (int)(v * 255.0);
		b = (int)(p * 255.0);
		break;
	case 2:
		r = (int)(p * 255.0);
		g = (int)(v * 255.0);
		b = (int)(t * 255.0);
		break;
	case 3:
		r = (int)(p * 255.0);
		g = (int)(q * 255.0);
		b = (int)(v * 255.0);
		break;
	case 4:
		r = (int)(t * 255.0);
		g = (int)(p * 255.0);
		b = (int)(v * 255.0);
		break;
	default:
		r = (int)(v * 255.0);
		g = (int)(p * 255.0);
		b = (int)(q * 255.0);
		break;
	}
}


Bitmap^ ConvertToGrayScale(Bitmap^ image)
{
	if (image == nullptr) return nullptr;

	System::Drawing::Imaging::BitmapData^ data = image->LockBits(
		System::Drawing::Rectangle(0, 0, image->Width, image->Height),
		System::Drawing::Imaging::ImageLockMode::ReadWrite,
		image->PixelFormat
	);

	int bytesPerPixel = System::Drawing::Image::GetPixelFormatSize(image->PixelFormat) / 8;
	int stride = data->Stride;
	int height = image->Height;
	int width = image->Width;

	System::Byte* ptr = (System::Byte*)data->Scan0.ToPointer();

	// Process all rows using LockBits for performance
	for (int y = 0; y < height; y++) {
		System::Byte* rowPtr = ptr + (y * stride);
		for (int x = 0; x < width; x++) {
			int index = x * bytesPerPixel;
			int blue = rowPtr[index];
			int green = rowPtr[index + 1];
			int red = rowPtr[index + 2];

			int grayValue = (int)(red * ImageConstants::GRAYSCALE_R_WEIGHT + 
								  green * ImageConstants::GRAYSCALE_G_WEIGHT + 
								  blue * ImageConstants::GRAYSCALE_B_WEIGHT);

			rowPtr[index] = grayValue;
			rowPtr[index + 1] = grayValue;
			rowPtr[index + 2] = grayValue;
		}
	}

	image->UnlockBits(data);
	return image;
}


Bitmap^ SetContrast(Bitmap^ originalImage, int contrastValue) {
		if (originalImage != nullptr) {
			double contrastFactor = (contrastValue) / 100.0;
			contrastFactor *= contrastFactor;

			// Using the System::Drawing::Imaging namespace
			System::Drawing::Imaging::BitmapData^ data = originalImage->LockBits(
				System::Drawing::Rectangle(0, 0, originalImage->Width, originalImage->Height),
				System::Drawing::Imaging::ImageLockMode::ReadWrite,
				originalImage->PixelFormat
			);

			int bytesPerPixel = System::Drawing::Image::GetPixelFormatSize(originalImage->PixelFormat) / 8;
			IntPtr ptrFirstPixel = data->Scan0;

			// Use a managed pointer instead of unsafe context
			System::IntPtr scanPtr = data->Scan0;
			int stride = data->Stride;

			for (int y = 0; y < originalImage->Height; y++) {
				System::Byte* rowPtr = (System::Byte*)scanPtr.ToPointer();
				for (int x = 0; x < originalImage->Width; x++) {
					int index = x * bytesPerPixel;

					int red = rowPtr[index + 2];
					int green = rowPtr[index + 1];
					int blue = rowPtr[index];

					red = Math::Min(255, Math::Max(0, (int)((red - 128) * contrastFactor + 128)));
					green = Math::Min(255, Math::Max(0, (int)((green - 128) * contrastFactor + 128)));
					blue = Math::Min(255, Math::Max(0, (int)((blue - 128) * contrastFactor + 128)));

					rowPtr[index + 2] = red;
					rowPtr[index + 1] = green;
					rowPtr[index] = blue;
				}
				scanPtr = IntPtr::Add(scanPtr, stride);
			}

			originalImage->UnlockBits(data);
			return  originalImage;
		}
	return nullptr;
}

Bitmap^ SharpenImage(Bitmap^ image, int sharpValue) {
	if (image == nullptr) return nullptr;

	double factor = static_cast<double>(sharpValue) / 100.0;

	// Define a sharpening kernel
	int kernel[3][3] = {
		{ 0, -1, 0 },
		{ -1, 5, -1 },
		{ 0, -1, 0 }
	};

	int width = image->Width;
	int height = image->Height;

	// Lock the bitmap's bits
	System::Drawing::Imaging::BitmapData^ srcData = image->LockBits(
		System::Drawing::Rectangle(0, 0, width, height),
		System::Drawing::Imaging::ImageLockMode::ReadOnly,
		image->PixelFormat
	);

	// Create a new bitmap for the result
	Bitmap^ resultImage = gcnew Bitmap(width, height, image->PixelFormat);

	System::Drawing::Imaging::BitmapData^ dstData = resultImage->LockBits(
		System::Drawing::Rectangle(0, 0, width, height),
		System::Drawing::Imaging::ImageLockMode::WriteOnly,
		image->PixelFormat
	);

	int bytesPerPixel = System::Drawing::Image::GetPixelFormatSize(image->PixelFormat) / 8;
	int heightInPixels = srcData->Height;
	int widthInBytes = srcData->Width * bytesPerPixel;

	Byte* srcPtr = (Byte*)srcData->Scan0.ToPointer();
	Byte* dstPtr = (Byte*)dstData->Scan0.ToPointer();

	for (int y = 1; y < heightInPixels - 1; ++y) {
		for (int x = bytesPerPixel; x < widthInBytes - bytesPerPixel; x += bytesPerPixel) {
			int r = 0, g = 0, b = 0;

			for (int ky = -1; ky <= 1; ++ky) {
				for (int kx = -1; kx <= 1; ++kx) {
					int pixelIndex = (y + ky) * srcData->Stride + (x + kx * bytesPerPixel);
					b += srcPtr[pixelIndex] * kernel[ky + 1][kx + 1];
					g += srcPtr[pixelIndex + 1] * kernel[ky + 1][kx + 1];
					r += srcPtr[pixelIndex + 2] * kernel[ky + 1][kx + 1];
				}
			}

			int dstIndex = y * dstData->Stride + x;
			dstPtr[dstIndex] = Math::Min(255, Math::Max(0, b));
			dstPtr[dstIndex + 1] = Math::Min(255, Math::Max(0, g));
			dstPtr[dstIndex + 2] = Math::Min(255, Math::Max(0, r));
		}
	}

	image->UnlockBits(srcData);
	resultImage->UnlockBits(dstData);

	// Apply factor to the result image if necessary
	if (factor != 1.0) {
		srcData = resultImage->LockBits(
			System::Drawing::Rectangle(0, 0, width, height),
			System::Drawing::Imaging::ImageLockMode::ReadOnly,
			resultImage->PixelFormat
		);

		dstData = image->LockBits(
			System::Drawing::Rectangle(0, 0, width, height),
			System::Drawing::Imaging::ImageLockMode::WriteOnly,
			image->PixelFormat
		);

		srcPtr = (Byte*)srcData->Scan0.ToPointer();
		dstPtr = (Byte*)dstData->Scan0.ToPointer();

		for (int y = 0; y < heightInPixels; ++y) {
			for (int x = 0; x < widthInBytes; x += bytesPerPixel) {
				int b = srcPtr[y * srcData->Stride + x];
				int g = srcPtr[y * srcData->Stride + x + 1];
				int r = srcPtr[y * srcData->Stride + x + 2];

				b = Math::Min(255, Math::Max(0, (int)(b * factor)));
				g = Math::Min(255, Math::Max(0, (int)(g * factor)));
				r = Math::Min(255, Math::Max(0, (int)(r * factor)));

				dstPtr[y * dstData->Stride + x] = b;
				dstPtr[y * dstData->Stride + x + 1] = g;
				dstPtr[y * dstData->Stride + x + 2] = r;
			}
		}

		resultImage->UnlockBits(srcData);
		image->UnlockBits(dstData);
	}
	else {
		image = resultImage;
	}

	return image;
}


Bitmap^ PixelateImage(Bitmap^ image, int blockSize) {
	if (image == nullptr || blockSize < 1) return nullptr;

	System::Drawing::Imaging::BitmapData^ data = image->LockBits(
		System::Drawing::Rectangle(0, 0, image->Width, image->Height),
		System::Drawing::Imaging::ImageLockMode::ReadWrite,
		image->PixelFormat
	);

	int bytesPerPixel = System::Drawing::Image::GetPixelFormatSize(image->PixelFormat) / 8;
	int stride = data->Stride;
	int height = image->Height;
	int width = image->Width;
	System::Byte* ptr = (System::Byte*)data->Scan0.ToPointer();

	for (int y = 0; y < height; y += blockSize) {
		for (int x = 0; x < width; x += blockSize) {
			int avgR = 0, avgG = 0, avgB = 0;
			int pixelCount = 0;

			// Calculate average color within the block
			for (int j = 0; j < blockSize && (y + j) < height; j++) {
				for (int i = 0; i < blockSize && (x + i) < width; i++) {
					int index = (y + j) * stride + (x + i) * bytesPerPixel;
					avgB += ptr[index];
					avgG += ptr[index + 1];
					avgR += ptr[index + 2];
					pixelCount++;
				}
			}

			if (pixelCount > 0) {
				avgR /= pixelCount;
				avgG /= pixelCount;
				avgB /= pixelCount;

				// Fill the block with the average color
				for (int j = 0; j < blockSize && (y + j) < height; j++) {
					for (int i = 0; i < blockSize && (x + i) < width; i++) {
						int index = (y + j) * stride + (x + i) * bytesPerPixel;
						ptr[index] = avgB;
						ptr[index + 1] = avgG;
						ptr[index + 2] = avgR;
					}
				}
			}
		}
	}

	image->UnlockBits(data);
	return image;
}

Bitmap^ SetBrightness(Bitmap^ image, int brightnessValue) {
	if (image != nullptr) {
		// The brightnessValue should be a value between -100 and 100
		double brightnessFactor = brightnessValue / 100.0;

		// Using the System::Drawing::Imaging namespace
		System::Drawing::Imaging::BitmapData^ data = image->LockBits(
			System::Drawing::Rectangle(0, 0, image->Width, image->Height),
			System::Drawing::Imaging::ImageLockMode::ReadWrite,
			image->PixelFormat
		);

		int bytesPerPixel = System::Drawing::Image::GetPixelFormatSize(image->PixelFormat) / 8;
		IntPtr ptrFirstPixel = data->Scan0;

		// Use a managed pointer instead of unsafe context
		System::IntPtr scanPtr = data->Scan0;
		int stride = data->Stride;

		for (int y = 0; y < image->Height; y++) {
			System::Byte* rowPtr = (System::Byte*)scanPtr.ToPointer();
			for (int x = 0; x < image->Width; x++) {
				int index = x * bytesPerPixel;

				int red = rowPtr[index + 2];
				int green = rowPtr[index + 1];
				int blue = rowPtr[index];

				red = Math::Min(255, Math::Max(0, (int)(red + 255 * brightnessFactor)));
				green = Math::Min(255, Math::Max(0, (int)(green + 255 * brightnessFactor)));
				blue = Math::Min(255, Math::Max(0, (int)(blue + 255 * brightnessFactor)));

				rowPtr[index + 2] = red;
				rowPtr[index + 1] = green;
				rowPtr[index] = blue;
			}
			scanPtr = IntPtr::Add(scanPtr, stride);
		}

		image->UnlockBits(data);
		return image;
	}
	return nullptr;
}

Bitmap^ AdjustVibrance(Bitmap^ image, int vibranceValue)
{
	if (image != nullptr) {
		double vibranceFactor = vibranceValue / 100.0;

		// Using the System::Drawing::Imaging namespace
		System::Drawing::Imaging::BitmapData^ data = image->LockBits(
			System::Drawing::Rectangle(0, 0, image->Width, image->Height),
			System::Drawing::Imaging::ImageLockMode::ReadWrite,
			image->PixelFormat
		);

		int bytesPerPixel = System::Drawing::Image::GetPixelFormatSize(image->PixelFormat) / 8;
		IntPtr ptrFirstPixel = data->Scan0;

		// Use a managed pointer instead of unsafe context
		System::IntPtr scanPtr = data->Scan0;
		int stride = data->Stride;

		for (int y = 0; y < image->Height; y++) {
			System::Byte* rowPtr = (System::Byte*)scanPtr.ToPointer();
			for (int x = 0; x < image->Width; x++) {
				int index = x * bytesPerPixel;

				int red = rowPtr[index + 2];
				int green = rowPtr[index + 1];
				int blue = rowPtr[index];

				// Calculate the average and max components
				double avgComponent = (red + green + blue) / 3.0;
				double maxComponent = Math::Max(red, Math::Max(green, blue));
				double vibranceAmount = vibranceFactor * (maxComponent - avgComponent) / 255.0;

				// Adjust the vibrance
				red += (int)((red - avgComponent) * vibranceAmount);
				green += (int)((green - avgComponent) * vibranceAmount);
				blue += (int)((blue - avgComponent) * vibranceAmount);

				red = Math::Min(255, Math::Max(0, red));
				green = Math::Min(255, Math::Max(0, green));
				blue = Math::Min(255, Math::Max(0, blue));

				rowPtr[index + 2] = red;
				rowPtr[index + 1] = green;
				rowPtr[index] = blue;
			}
			scanPtr = IntPtr::Add(scanPtr, stride);
		}

		image->UnlockBits(data);
		return image;
	}
	return nullptr;
}

Bitmap^ AdjustHue(Bitmap^ image, int hueShift)
{
	if (image != nullptr) {
		// Using the System::Drawing::Imaging namespace
		System::Drawing::Imaging::BitmapData^ data = image->LockBits(
			System::Drawing::Rectangle(0, 0, image->Width, image->Height),
			System::Drawing::Imaging::ImageLockMode::ReadWrite,
			image->PixelFormat
		);

		int bytesPerPixel = System::Drawing::Image::GetPixelFormatSize(image->PixelFormat) / 8;
		IntPtr ptrFirstPixel = data->Scan0;

		// Use a managed pointer instead of unsafe context
		System::IntPtr scanPtr = data->Scan0;
		int stride = data->Stride;

		for (int y = 0; y < image->Height; y++) {
			System::Byte* rowPtr = (System::Byte*)scanPtr.ToPointer();
			for (int x = 0; x < image->Width; x++) {
				int index = x * bytesPerPixel;

				int red = rowPtr[index + 2];
				int green = rowPtr[index + 1];
				int blue = rowPtr[index];

				double h, s, v;
				RGBtoHSV(red, green, blue, h, s, v);
				h = fmod(h + hueShift, 360.0);
				if (h < 0) h += 360.0;
				HSVtoRGB(h, s, v, red, green, blue);

				rowPtr[index + 2] = red;
				rowPtr[index + 1] = green;
				rowPtr[index] = blue;
			}
			scanPtr = IntPtr::Add(scanPtr, stride);
		}

		image->UnlockBits(data);
		return image;
	}
	return nullptr;
}

Bitmap^ ColorBoost(Bitmap^ image, double redFactor, double greenFactor, double blueFactor)
{
	redFactor = (redFactor / 20.0);
	greenFactor = (greenFactor / 20.0);
	blueFactor = (blueFactor / 20.0);

	if (image != nullptr) {
		// Using the System::Drawing::Imaging namespace
		System::Drawing::Imaging::BitmapData^ data = image->LockBits(
			System::Drawing::Rectangle(0, 0, image->Width, image->Height),
			System::Drawing::Imaging::ImageLockMode::ReadWrite,
			image->PixelFormat
		);

		int bytesPerPixel = System::Drawing::Image::GetPixelFormatSize(image->PixelFormat) / 8;
		IntPtr ptrFirstPixel = data->Scan0;

		// Use a managed pointer instead of unsafe context
		System::IntPtr scanPtr = data->Scan0;
		int stride = data->Stride;

		for (int y = 0; y < image->Height; y++) {
			System::Byte* rowPtr = (System::Byte*)scanPtr.ToPointer();
			for (int x = 0; x < image->Width; x++) {
				int index = x * bytesPerPixel;

				int red = rowPtr[index + 2];
				int green = rowPtr[index + 1];
				int blue = rowPtr[index];

				// Apply boost factors
				red = Math::Min(255, Math::Max(0, (int)(red * redFactor)));
				green = Math::Min(255, Math::Max(0, (int)(green * greenFactor)));
				blue = Math::Min(255, Math::Max(0, (int)(blue * blueFactor)));

				rowPtr[index + 2] = red;
				rowPtr[index + 1] = green;
				rowPtr[index] = blue;
			}
			scanPtr = IntPtr::Add(scanPtr, stride);
		}

		image->UnlockBits(data);
		return image;
	}
	return nullptr;
}

Bitmap^ InvertColors(Bitmap^ image) {
	if (image == nullptr) return nullptr;

	System::Drawing::Imaging::BitmapData^ data = image->LockBits(
		System::Drawing::Rectangle(0, 0, image->Width, image->Height),
		System::Drawing::Imaging::ImageLockMode::ReadWrite,
		image->PixelFormat
	);

	int bytesPerPixel = System::Drawing::Image::GetPixelFormatSize(image->PixelFormat) / 8;
	int stride = data->Stride;
	int height = image->Height;
	int width = image->Width;
	System::Byte* ptr = (System::Byte*)data->Scan0.ToPointer();

	// Process all rows using LockBits for performance
	for (int y = 0; y < height; y++) {
		System::Byte* rowPtr = ptr + (y * stride);
		for (int x = 0; x < width; x++) {
			int index = x * bytesPerPixel;
			rowPtr[index] = 255 - rowPtr[index];         // Blue
			rowPtr[index + 1] = 255 - rowPtr[index + 1]; // Green
			rowPtr[index + 2] = 255 - rowPtr[index + 2]; // Red
		}
	}

	image->UnlockBits(data);
	return image;
}

Bitmap^ SepiaTone(Bitmap^ image) {
	if (image == nullptr) return nullptr;

	System::Drawing::Imaging::BitmapData^ data = image->LockBits(
		System::Drawing::Rectangle(0, 0, image->Width, image->Height),
		System::Drawing::Imaging::ImageLockMode::ReadWrite,
		image->PixelFormat
	);

	int bytesPerPixel = System::Drawing::Image::GetPixelFormatSize(image->PixelFormat) / 8;
	int stride = data->Stride;
	int height = image->Height;
	int width = image->Width;
	System::Byte* ptr = (System::Byte*)data->Scan0.ToPointer();

	// Sepia transformation constants
	const double sr_r = 0.393, sr_g = 0.769, sr_b = 0.189;
	const double sg_r = 0.349, sg_g = 0.686, sg_b = 0.168;
	const double sb_r = 0.272, sb_g = 0.534, sb_b = 0.131;

	// Process all rows using LockBits for performance
	for (int y = 0; y < height; y++) {
		System::Byte* rowPtr = ptr + (y * stride);
		for (int x = 0; x < width; x++) {
			int index = x * bytesPerPixel;
			int blue = rowPtr[index];
			int green = rowPtr[index + 1];
			int red = rowPtr[index + 2];

			int tr = Math::Min(255, (int)(sr_r * red + sr_g * green + sr_b * blue));
			int tg = Math::Min(255, (int)(sg_r * red + sg_g * green + sg_b * blue));
			int tb = Math::Min(255, (int)(sb_r * red + sb_g * green + sb_b * blue));

			rowPtr[index] = tb;
			rowPtr[index + 1] = tg;
			rowPtr[index + 2] = tr;
		}
	}

	image->UnlockBits(data);
	return image;
}

Bitmap^ PosterizeImage(Bitmap^ image, int levels)
{
	if (image != nullptr) {
		// Ensure levels are at least 2 to create a posterization effect
		levels = Math::Max(2, levels);

		// Calculate the interval for each level
		int interval = 256 / levels;

		// Using the System::Drawing::Imaging namespace
		System::Drawing::Imaging::BitmapData^ data = image->LockBits(
			System::Drawing::Rectangle(0, 0, image->Width, image->Height),
			System::Drawing::Imaging::ImageLockMode::ReadWrite,
			image->PixelFormat
		);

		int bytesPerPixel = System::Drawing::Image::GetPixelFormatSize(image->PixelFormat) / 8;
		IntPtr ptrFirstPixel = data->Scan0;

		// Use a managed pointer instead of unsafe context
		System::IntPtr scanPtr = data->Scan0;
		int stride = data->Stride;

		for (int y = 0; y < image->Height; y++) {
			System::Byte* rowPtr = (System::Byte*)scanPtr.ToPointer();
			for (int x = 0; x < image->Width; x++) {
				int index = x * bytesPerPixel;

				int red = rowPtr[index + 2];
				int green = rowPtr[index + 1];
				int blue = rowPtr[index];

				// Posterize each channel
				red = (red / interval) * interval + interval / 2;
				green = (green / interval) * interval + interval / 2;
				blue = (blue / interval) * interval + interval / 2;

				rowPtr[index + 2] = red;
				rowPtr[index + 1] = green;
				rowPtr[index] = blue;
			}
			scanPtr = IntPtr::Add(scanPtr, stride);
		}

		image->UnlockBits(data);
		return image;
	}
	return nullptr;
}

Bitmap^ ApplyEdgeDetection(Bitmap^ image)
{
	if (image != nullptr) {
		std::vector<std::vector<int>> kernel = {
			{ -1, -1, -1 },
			{ -1,  8, -1 },
			{ -1, -1, -1 }
		};

		int kernelSize = static_cast<int>(kernel.size());
		int radius = kernelSize / 2;

		Bitmap^ newImage = gcnew Bitmap(image->Width, image->Height, image->PixelFormat);

		System::Drawing::Imaging::BitmapData^ srcData = image->LockBits(
			System::Drawing::Rectangle(0, 0, image->Width, image->Height),
			System::Drawing::Imaging::ImageLockMode::ReadOnly,
			image->PixelFormat
		);

		System::Drawing::Imaging::BitmapData^ destData = newImage->LockBits(
			System::Drawing::Rectangle(0, 0, newImage->Width, newImage->Height),
			System::Drawing::Imaging::ImageLockMode::WriteOnly,
			newImage->PixelFormat
		);

		int bytesPerPixel = System::Drawing::Image::GetPixelFormatSize(image->PixelFormat) / 8;
		int srcStride = srcData->Stride;
		int destStride = destData->Stride;
		IntPtr srcScan0 = srcData->Scan0;
		IntPtr destScan0 = destData->Scan0;

		System::Byte* srcPtr = (System::Byte*)srcScan0.ToPointer();
		System::Byte* destPtr = (System::Byte*)destScan0.ToPointer();

		for (int y = 0; y < image->Height; ++y) {
			for (int x = 0; x < image->Width; ++x) {
				int r = 0, g = 0, b = 0;

				for (int ky = -radius; ky <= radius; ++ky) {
					for (int kx = -radius; kx <= radius; ++kx) {
						int pixelX = x + kx;
						int pixelY = y + ky;

						if (pixelX >= 0 && pixelX < image->Width && pixelY >= 0 && pixelY < image->Height) {
							System::Byte* pixel = srcPtr + (pixelY * srcStride) + (pixelX * bytesPerPixel);
							int weight = kernel[ky + radius][kx + radius];

							b += pixel[0] * weight;
							g += pixel[1] * weight;
							r += pixel[2] * weight;
						}
					}
				}

				r = Math::Min(255, Math::Max(0, r));
				g = Math::Min(255, Math::Max(0, g));
				b = Math::Min(255, Math::Max(0, b));

				System::Byte* destPixel = destPtr + (y * destStride) + (x * bytesPerPixel);
				destPixel[0] = b;
				destPixel[1] = g;
				destPixel[2] = r;
				// Set the alpha value to 255 (fully opaque)
				if (bytesPerPixel == 4) {
					destPixel[3] = 255;
				}
			}
		}

		image->UnlockBits(srcData);
		newImage->UnlockBits(destData);

		return newImage;
	}
	return nullptr;
}

Bitmap^ EmbossImage(Bitmap^ image)
{
	if (image == nullptr) return nullptr;

	int width = image->Width;
	int height = image->Height;
	Bitmap^ embossedImage = gcnew Bitmap(width, height, image->PixelFormat);

	System::Drawing::Imaging::BitmapData^ srcData = image->LockBits(
		System::Drawing::Rectangle(0, 0, width, height),
		System::Drawing::Imaging::ImageLockMode::ReadOnly,
		image->PixelFormat
	);

	System::Drawing::Imaging::BitmapData^ dstData = embossedImage->LockBits(
		System::Drawing::Rectangle(0, 0, width, height),
		System::Drawing::Imaging::ImageLockMode::WriteOnly,
		image->PixelFormat
	);

	int bytesPerPixel = System::Drawing::Image::GetPixelFormatSize(image->PixelFormat) / 8;
	int srcStride = srcData->Stride;
	int dstStride = dstData->Stride;
	System::Byte* srcPtr = (System::Byte*)srcData->Scan0.ToPointer();
	System::Byte* dstPtr = (System::Byte*)dstData->Scan0.ToPointer();

	// Process rows (skip first and last row)
	for (int y = 1; y < height - 1; y++) {
		for (int x = 1; x < width - 1; x++) {
			int srcIndex1 = y * srcStride + x * bytesPerPixel;
			int srcIndex2 = (y + 1) * srcStride + (x + 1) * bytesPerPixel;
			int dstIndex = y * dstStride + x * bytesPerPixel;

			int b = Math::Min(255, Math::Max(0, srcPtr[srcIndex1] - srcPtr[srcIndex2] + 128));
			int g = Math::Min(255, Math::Max(0, srcPtr[srcIndex1 + 1] - srcPtr[srcIndex2 + 1] + 128));
			int r = Math::Min(255, Math::Max(0, srcPtr[srcIndex1 + 2] - srcPtr[srcIndex2 + 2] + 128));

			dstPtr[dstIndex] = b;
			dstPtr[dstIndex + 1] = g;
			dstPtr[dstIndex + 2] = r;
			if (bytesPerPixel == 4) dstPtr[dstIndex + 3] = 255;
		}
	}

	image->UnlockBits(srcData);
	embossedImage->UnlockBits(dstData);
	return embossedImage;
}

Bitmap^ BlurImage(Bitmap^ image, int blurSize) {
	if (image == nullptr || blurSize < 1) {
		return nullptr;
	}

	// Create blurred image
	Bitmap^ blurredImage = gcnew Bitmap(image->Width, image->Height);

	// Lock bits for the source image
	BitmapData^ srcData = image->LockBits(Rectangle(0, 0, image->Width, image->Height), ImageLockMode::ReadOnly, PixelFormat::Format24bppRgb);
	IntPtr srcScan0 = srcData->Scan0;
	int srcStride = srcData->Stride;
	int srcBytes = srcStride * image->Height;
	array<Byte>^ srcBuffer = gcnew array<Byte>(srcBytes);
	System::Runtime::InteropServices::Marshal::Copy(srcScan0, srcBuffer, 0, srcBytes);

	// Create integral images for each color channel
	int width = image->Width;
	int height = image->Height;
	std::vector<std::vector<int>> integralR(height + 1, std::vector<int>(width + 1, 0));
	std::vector<std::vector<int>> integralG(height + 1, std::vector<int>(width + 1, 0));
	std::vector<std::vector<int>> integralB(height + 1, std::vector<int>(width + 1, 0));

	// Compute integral images
	for (int y = 1; y <= height; ++y) {
		for (int x = 1; x <= width; ++x) {
			int srcIndex = (y - 1) * srcStride + (x - 1) * 3;
			int r = srcBuffer[srcIndex + 2];
			int g = srcBuffer[srcIndex + 1];
			int b = srcBuffer[srcIndex];

			integralR[y][x] = r + integralR[y - 1][x] + integralR[y][x - 1] - integralR[y - 1][x - 1];
			integralG[y][x] = g + integralG[y - 1][x] + integralG[y][x - 1] - integralG[y - 1][x - 1];
			integralB[y][x] = b + integralB[y - 1][x] + integralB[y][x - 1] - integralB[y - 1][x - 1];
		}
	}

	// Lock bits for the destination image
	BitmapData^ dstData = blurredImage->LockBits(Rectangle(0, 0, blurredImage->Width, blurredImage->Height), ImageLockMode::WriteOnly, PixelFormat::Format24bppRgb);
	IntPtr dstScan0 = dstData->Scan0;
	int dstStride = dstData->Stride;
	int dstBytes = dstStride * blurredImage->Height;
	array<Byte>^ dstBuffer = gcnew array<Byte>(dstBytes);

	// Apply blur using integral images
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int x0 = std::max(0, x - blurSize);
			int x1 = std::min(width - 1, x + blurSize);
			int y0 = std::max(0, y - blurSize);
			int y1 = std::min(height - 1, y + blurSize);

			int area = (x1 - x0 + 1) * (y1 - y0 + 1);

			int sumR = integralR[y1 + 1][x1 + 1] - integralR[y1 + 1][x0] - integralR[y0][x1 + 1] + integralR[y0][x0];
			int sumG = integralG[y1 + 1][x1 + 1] - integralG[y1 + 1][x0] - integralG[y0][x1 + 1] + integralG[y0][x0];
			int sumB = integralB[y1 + 1][x1 + 1] - integralB[y1 + 1][x0] - integralB[y0][x1 + 1] + integralB[y0][x0];

			int dstIndex = y * dstStride + x * 3;
			dstBuffer[dstIndex + 2] = sumR / area;
			dstBuffer[dstIndex + 1] = sumG / area;
			dstBuffer[dstIndex] = sumB / area;
		}
	}

	// Copy the blurred data back to the destination image
	System::Runtime::InteropServices::Marshal::Copy(dstBuffer, 0, dstScan0, dstBytes);
	blurredImage->UnlockBits(dstData);
	image->UnlockBits(srcData);

	return blurredImage;
}

Bitmap^ GlitchEffect(Bitmap^ image, int glitchAmount)
{
	if (image == nullptr) return nullptr;

	// Lock the bitmap's bits
	System::Drawing::Imaging::BitmapData^ data = image->LockBits(
		System::Drawing::Rectangle(0, 0, image->Width, image->Height),
		System::Drawing::Imaging::ImageLockMode::ReadWrite,
		image->PixelFormat
	);

	int bytesPerPixel = System::Drawing::Image::GetPixelFormatSize(image->PixelFormat) / 8;
	int heightInPixels = data->Height;
	int widthInBytes = data->Width * bytesPerPixel;

	Byte* ptr = (Byte*)data->Scan0.ToPointer();

	// Apply random horizontal displacement
	for (int y = 0; y < heightInPixels; ++y) {
		if (rand() % 100 < glitchAmount) {
			int displacement = rand() % 10 - 5; // Random displacement between -5 and 5
			for (int x = 0; x < widthInBytes; x += bytesPerPixel) {
				int newX = x + displacement * bytesPerPixel;
				if (newX >= 0 && newX < widthInBytes) {
					for (int i = 0; i < bytesPerPixel; ++i) {
						std::swap(ptr[y * data->Stride + x + i], ptr[y * data->Stride + newX + i]);
					}
				}
			}
		}
	}

	// Apply random color channel shifts
	for (int y = 0; y < heightInPixels; ++y) {
		for (int x = 0; x < widthInBytes; x += bytesPerPixel) {
			if (rand() % 100 < glitchAmount) {
				int channelShift = rand() % 3; // Random channel shift
				if (channelShift == 0) {
					std::swap(ptr[y * data->Stride + x], ptr[y * data->Stride + x + 1]);
				}
				else if (channelShift == 1) {
					std::swap(ptr[y * data->Stride + x + 1], ptr[y * data->Stride + x + 2]);
				}
				else {
					std::swap(ptr[y * data->Stride + x], ptr[y * data->Stride + x + 2]);
				}
			}
		}
	}

	image->UnlockBits(data);
	return image;
}

Bitmap^ ExaGlitchEffect(Bitmap^ image, int glitchAmount)
{
	if (image == nullptr) return nullptr;

	// Seed the random number generator
	srand(static_cast<unsigned int>(time(nullptr)));

	// Lock the bitmap's bits
	System::Drawing::Imaging::BitmapData^ data = image->LockBits(
		System::Drawing::Rectangle(0, 0, image->Width, image->Height),
		System::Drawing::Imaging::ImageLockMode::ReadWrite,
		image->PixelFormat
	);

	int bytesPerPixel = System::Drawing::Image::GetPixelFormatSize(image->PixelFormat) / 8;
	int heightInPixels = data->Height;
	int widthInBytes = data->Width * bytesPerPixel;

	Byte* ptr = (Byte*)data->Scan0.ToPointer();

	// Apply random thicker horizontal displacement
	for (int y = 0; y < heightInPixels; y += rand() % 20) {
		if (rand() % 100 < glitchAmount) {
			int displacement = (rand() % 40) - 20; // Random displacement between -20 and 20
			int rowHeight = rand() % 20 + 1;       // Random row height between 1 and 20

			for (int dy = 0; dy < rowHeight && (y + dy) < heightInPixels; ++dy) {
				for (int x = 0; x < widthInBytes; x += bytesPerPixel) {
					int newX = x + displacement * bytesPerPixel;
					if (newX >= 0 && newX < widthInBytes) {
						for (int i = 0; i < bytesPerPixel; ++i) {
							std::swap(ptr[(y + dy) * data->Stride + x + i], ptr[(y + dy) * data->Stride + newX + i]);
						}
					}
				}
			}
		}
	}

	// Apply random color channel shifts
	for (int y = 0; y < heightInPixels; ++y) {
		for (int x = 0; x < widthInBytes; x += bytesPerPixel) {
			if (rand() % 100 < glitchAmount) {
				int channelShift = rand() % 3; // Random channel shift
				if (channelShift == 0) {
					std::swap(ptr[y * data->Stride + x], ptr[y * data->Stride + x + 1]);
				}
				else if (channelShift == 1) {
					std::swap(ptr[y * data->Stride + x + 1], ptr[y * data->Stride + x + 2]);
				}
				else {
					std::swap(ptr[y * data->Stride + x], ptr[y * data->Stride + x + 2]);
				}
			}
		}
	}

	// Apply scan lines or noise
	for (int y = 0; y < heightInPixels; ++y) {
		if (rand() % 100 < glitchAmount / 2) { // Randomly decide to add noise or scan lines
			for (int x = 0; x < widthInBytes; x += bytesPerPixel) {
				if (rand() % 100 < glitchAmount) {
					for (int i = 0; i < bytesPerPixel; ++i) {
						ptr[y * data->Stride + x + i] = static_cast<Byte>(rand() % 256);
					}
				}
			}
		}
	}

	image->UnlockBits(data);
	return image;
}

// Function to convert RRGGBB string to AARRGGBB integer
int ConvertHexToArgb(String^ hexColor) {
	// Parse the RRGGBB hex value
	int rgb = int::Parse(hexColor, System::Globalization::NumberStyles::HexNumber);

	// Add alpha channel (FF)
	int argb = (0xFF << 24) | rgb;
	return argb;
}


Bitmap^ ReplaceColor(Bitmap^ image, String^ targetColorAA, String^ replacementColorAA, int threshold, bool interpolate) {
	if (image == nullptr) return nullptr;

	int targetColorHex = ConvertHexToArgb(targetColorAA);
	int replacementColorHex = ConvertHexToArgb(replacementColorAA);

	// Extract ARGB components from the hex values
	Color targetColor = Color::FromArgb(targetColorHex);
	Color replacementColor = Color::FromArgb(replacementColorHex);

	// Using the System::Drawing::Imaging namespace
	System::Drawing::Imaging::BitmapData^ data = image->LockBits(
		System::Drawing::Rectangle(0, 0, image->Width, image->Height),
		System::Drawing::Imaging::ImageLockMode::ReadWrite,
		image->PixelFormat
	);

	int bytesPerPixel = System::Drawing::Image::GetPixelFormatSize(image->PixelFormat) / 8;
	int heightInPixels = data->Height;
	int widthInBytes = data->Width * bytesPerPixel;
	Byte* ptrFirstPixel = (Byte*)data->Scan0.ToPointer();

	for (int y = 0; y < heightInPixels; ++y) {
		Byte* currentLine = ptrFirstPixel + (y * data->Stride);
		for (int x = 0; x < widthInBytes; x += bytesPerPixel) {
			int b = currentLine[x];
			int g = currentLine[x + 1];
			int r = currentLine[x + 2];
			int a = (bytesPerPixel == 4) ? currentLine[x + 3] : 255;

			Color pixelColor = Color::FromArgb(a, r, g, b); // Create a Color object from the pixel's ARGB values

			// Calculate the Euclidean distance between the pixel color and the target color
			double distance = Math::Sqrt(
				Math::Pow(pixelColor.R - targetColor.R, 2) +
				Math::Pow(pixelColor.G - targetColor.G, 2) +
				Math::Pow(pixelColor.B - targetColor.B, 2)
			);

			// Check if the distance is within the threshold
			if (distance <= threshold) {
				if (interpolate) {
					// Interpolate the replacement color based on the distance
					double factor = distance / threshold;
					Color newReplacementColor = Color::FromArgb(
						(int)Clamp(replacementColor.A + (targetColor.A - replacementColor.A) * factor, 0, 255),
						(int)Clamp(replacementColor.R + (targetColor.R - replacementColor.R) * factor, 0, 255),
						(int)Clamp(replacementColor.G + (targetColor.G - replacementColor.G) * factor, 0, 255),
						(int)Clamp(replacementColor.B + (targetColor.B - replacementColor.B) * factor, 0, 255)
					);

					currentLine[x] = newReplacementColor.B;
					currentLine[x + 1] = newReplacementColor.G;
					currentLine[x + 2] = newReplacementColor.R;
					if (bytesPerPixel == 4) {
						currentLine[x + 3] = newReplacementColor.A;
					}
				}
				else {
					// Replace the pixel color with the replacement color without interpolation
					currentLine[x] = replacementColor.B;
					currentLine[x + 1] = replacementColor.G;
					currentLine[x + 2] = replacementColor.R;
					if (bytesPerPixel == 4) {
						currentLine[x + 3] = replacementColor.A;
					}
				}
			}
		}
	}

	image->UnlockBits(data);
	return image;
}

Bitmap^ ApplyOilPaintingEffect(Bitmap^ image) {
	if (image == nullptr) return nullptr;

	int radius = 4; // Fixed radius for the effect
	int intensityLevels = 20; // Number of intensity levels for the effect

	Bitmap^ resultImage = gcnew Bitmap(image->Width, image->Height, image->PixelFormat);

	System::Drawing::Imaging::BitmapData^ srcData = image->LockBits(
		System::Drawing::Rectangle(0, 0, image->Width, image->Height),
		System::Drawing::Imaging::ImageLockMode::ReadOnly,
		image->PixelFormat
	);

	System::Drawing::Imaging::BitmapData^ dstData = resultImage->LockBits(
		System::Drawing::Rectangle(0, 0, resultImage->Width, resultImage->Height),
		System::Drawing::Imaging::ImageLockMode::WriteOnly,
		resultImage->PixelFormat
	);

	int bytesPerPixel = System::Drawing::Image::GetPixelFormatSize(image->PixelFormat) / 8;
	int widthInBytes = srcData->Width * bytesPerPixel;
	int heightInPixels = srcData->Height;

	Byte* srcPtr = (Byte*)srcData->Scan0.ToPointer();
	Byte* dstPtr = (Byte*)dstData->Scan0.ToPointer();

	// Pre-calculate intensity levels
	int* intensityCount = new int[intensityLevels];
	int* sumR = new int[intensityLevels];
	int* sumG = new int[intensityLevels];
	int* sumB = new int[intensityLevels];

	for (int y = 0; y < heightInPixels; ++y) {
		for (int x = 0; x < widthInBytes; x += bytesPerPixel) {
			memset(intensityCount, 0, intensityLevels * sizeof(int));
			memset(sumR, 0, intensityLevels * sizeof(int));
			memset(sumG, 0, intensityLevels * sizeof(int));
			memset(sumB, 0, intensityLevels * sizeof(int));

			// Calculate histogram of intensities for the local region
			for (int dy = -radius; dy <= radius; ++dy) {
				int yy = Math::Min(heightInPixels - 1, Math::Max(0, y + dy));
				for (int dx = -radius * bytesPerPixel; dx <= radius * bytesPerPixel; dx += bytesPerPixel) {
					int xx = Math::Min(widthInBytes - bytesPerPixel, Math::Max(0, x + dx));

					int blue = srcPtr[yy * srcData->Stride + xx];
					int green = srcPtr[yy * srcData->Stride + xx + 1];
					int red = srcPtr[yy * srcData->Stride + xx + 2];
					int alpha = bytesPerPixel == 4 ? srcPtr[yy * srcData->Stride + xx + 3] : 255;

					int intensity = ((red + green + blue) / 3) * intensityLevels / 256;
					intensityCount[intensity]++;
					sumR[intensity] += red;
					sumG[intensity] += green;
					sumB[intensity] += blue;
				}
			}

			// Find the most frequent intensity
			int maxCount = 0;
			int dominantIntensity = 0;
			for (int i = 0; i < intensityLevels; ++i) {
				if (intensityCount[i] > maxCount) {
					maxCount = intensityCount[i];
					dominantIntensity = i;
				}
			}

			// Set the pixel to the average color of the most frequent intensity
			int dstIndex = y * dstData->Stride + x;
			dstPtr[dstIndex] = sumB[dominantIntensity] / maxCount;
			dstPtr[dstIndex + 1] = sumG[dominantIntensity] / maxCount;
			dstPtr[dstIndex + 2] = sumR[dominantIntensity] / maxCount;
			if (bytesPerPixel == 4) {
				dstPtr[dstIndex + 3] = 255; // Set alpha to fully opaque
			}
		}
	}

	delete[] intensityCount;
	delete[] sumR;
	delete[] sumG;
	delete[] sumB;

	image->UnlockBits(srcData);
	resultImage->UnlockBits(dstData);

	return resultImage;
}



// Get API key from environment variable
String^ GetHuggingFaceApiKey() {
	String^ apiKey = Environment::GetEnvironmentVariable("HUGGINGFACE_API_KEY");
	if (String::IsNullOrEmpty(apiKey)) {
		return nullptr;
	}
	return apiKey;
}

Bitmap^ GenerateImageFromText(String^ prompt, String^ model) {
	try {
		// Check for API key
		String^ apiKey = GetHuggingFaceApiKey();
		if (String::IsNullOrEmpty(apiKey)) {
			throw gcnew Exception("HuggingFace API key not found.\n\nPlease set the HUGGINGFACE_API_KEY environment variable.\n\nHow to set it:\n1. Open System Properties > Environment Variables\n2. Add new User variable:\n   Name: HUGGINGFACE_API_KEY\n   Value: your_api_key_here\n3. Restart the application");
		}
		
		// Define the API endpoint and the request URL
		String^ apiUrl = "https://api-inference.huggingface.co/models/" + model;

		// Create a WebClient instance
		System::Net::WebClient^ client = gcnew System::Net::WebClient();
		client->Headers->Add("Authorization", "Bearer " + apiKey);
		client->Headers->Add("Content-Type", "application/json");
		
		// Escape special characters in prompt for JSON
		String^ escapedPrompt = prompt->Replace("\\", "\\\\")->Replace("\"", "\\\"");
		String^ jsonContent = "{\"inputs\": \"" + escapedPrompt + "\"}";

		array<Byte>^ responseBytes = client->UploadData(apiUrl, "POST", System::Text::Encoding::UTF8->GetBytes(jsonContent));

		// Convert the byte array to a MemoryStream
		System::IO::MemoryStream^ memoryStream = gcnew System::IO::MemoryStream(responseBytes);

		// Create a Bitmap from the MemoryStream
		Bitmap^ generatedImage = gcnew Bitmap(memoryStream);

		return generatedImage;
	}
	catch (System::Net::WebException^ ex) {
		System::Windows::Forms::MessageBox::Show(
			"Failed to generate image: " + ex->Message + "\n\nPlease check your internet connection and API key.",
			"AI Generation Error",
			System::Windows::Forms::MessageBoxButtons::OK,
			System::Windows::Forms::MessageBoxIcon::Error
		);
		return nullptr;
	}
	catch (Exception^ ex) {
		System::Windows::Forms::MessageBox::Show(
			"An error occurred: " + ex->Message,
			"Error",
			System::Windows::Forms::MessageBoxButtons::OK,
			System::Windows::Forms::MessageBoxIcon::Error
		);
		return nullptr;
	}
}

