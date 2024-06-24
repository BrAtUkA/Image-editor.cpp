#pragma once

#include <thread>
#include <vector>
#include <functional>

using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::Threading::Tasks;
using namespace System::IO;
using namespace System::Xml;

// ==================== THREADED IMAGE PROCESSING UTILITIES ====================

namespace ImageThreading {

// Get optimal thread count based on image size
int GetOptimalThreadCount(int imageWidth, int imageHeight) {
int pixelCount = imageWidth * imageHeight;
int baseThreads = std::thread::hardware_concurrency();
if (baseThreads == 0) baseThreads = 4;

// For small images, use fewer threads to avoid overhead
if (pixelCount < 100000) return 1;
if (pixelCount < 500000) return Math::Min(2, baseThreads);
if (pixelCount < 2000000) return Math::Min(4, baseThreads);
return baseThreads;
}
}

// ==================== STYLE PRESET MANAGEMENT ====================

ref class StylePreset {
public:
	// Essential adjustments
	int Contrast;
	int Brightness;
	int Sharpness;
	int Vibrance;
	int Hue;
	int RedBoost;
	int GreenBoost;
	int BlueBoost;
	
	// Effects
	int Pixelate;
	int Posterize;
	int Blur;
	int Glitch;
	bool ExaggeratedGlitch;
	
	// Color replacement
	String^ TargetColor;
	String^ ReplacementColor;
	int ColorThreshold;
	bool ColorInterpolate;
	
	// Checkbox effects
	bool Grayscale;
	bool Invert;
	bool Sepia;
	bool EdgeDetection;
	bool Emboss;
	bool OilPaint;
	
	// Metadata
	String^ PresetName;
	String^ Author;
	DateTime CreatedDate;

	StylePreset() {
		// Initialize with default/neutral values
		Contrast = 100;
		Brightness = 0;
		Sharpness = 100;
		Vibrance = 0;
		Hue = 0;
		RedBoost = 20;
		GreenBoost = 20;
		BlueBoost = 20;
		
		Pixelate = 1;
		Posterize = 1;
		Blur = 0;
		Glitch = 0;
		ExaggeratedGlitch = false;
		
		TargetColor = "";
		ReplacementColor = "";
		ColorThreshold = 0;
		ColorInterpolate = false;
		
		Grayscale = false;
		Invert = false;
		Sepia = false;
		EdgeDetection = false;
		Emboss = false;
		OilPaint = false;
		
		PresetName = "Untitled";
		Author = Environment::UserName;
		CreatedDate = DateTime::Now;
	}

	// Save preset to XML file
	bool SaveToFile(String^ filePath) {
		try {
			XmlWriterSettings^ settings = gcnew XmlWriterSettings();
			settings->Indent = true;
			settings->IndentChars = "\t";
			
			XmlWriter^ writer = XmlWriter::Create(filePath, settings);
			
			writer->WriteStartDocument();
			writer->WriteStartElement("ImageEditorStyle");
			writer->WriteAttributeString("version", "1.0");
			
			// Metadata
			writer->WriteStartElement("Metadata");
			writer->WriteElementString("Name", PresetName);
			writer->WriteElementString("Author", Author);
			writer->WriteElementString("Created", CreatedDate.ToString("yyyy-MM-dd HH:mm:ss"));
			writer->WriteEndElement();
			
			// Essential adjustments
			writer->WriteStartElement("Essentials");
			writer->WriteElementString("Contrast", Contrast.ToString());
			writer->WriteElementString("Brightness", Brightness.ToString());
			writer->WriteElementString("Sharpness", Sharpness.ToString());
			writer->WriteElementString("Vibrance", Vibrance.ToString());
			writer->WriteElementString("Hue", Hue.ToString());
			writer->WriteElementString("RedBoost", RedBoost.ToString());
			writer->WriteElementString("GreenBoost", GreenBoost.ToString());
			writer->WriteElementString("BlueBoost", BlueBoost.ToString());
			writer->WriteEndElement();
			
			// Effects
			writer->WriteStartElement("Effects");
			writer->WriteElementString("Pixelate", Pixelate.ToString());
			writer->WriteElementString("Posterize", Posterize.ToString());
			writer->WriteElementString("Blur", Blur.ToString());
			writer->WriteElementString("Glitch", Glitch.ToString());
			writer->WriteElementString("ExaggeratedGlitch", ExaggeratedGlitch.ToString());
			writer->WriteEndElement();
			
			// Color replacement
			writer->WriteStartElement("ColorReplacement");
			writer->WriteElementString("TargetColor", TargetColor);
			writer->WriteElementString("ReplacementColor", ReplacementColor);
			writer->WriteElementString("Threshold", ColorThreshold.ToString());
			writer->WriteElementString("Interpolate", ColorInterpolate.ToString());
			writer->WriteEndElement();
			
			// Checkbox effects
			writer->WriteStartElement("Filters");
			writer->WriteElementString("Grayscale", Grayscale.ToString());
			writer->WriteElementString("Invert", Invert.ToString());
			writer->WriteElementString("Sepia", Sepia.ToString());
			writer->WriteElementString("EdgeDetection", EdgeDetection.ToString());
			writer->WriteElementString("Emboss", Emboss.ToString());
			writer->WriteElementString("OilPaint", OilPaint.ToString());
			writer->WriteEndElement();
			
			writer->WriteEndElement(); // ImageEditorStyle
			writer->WriteEndDocument();
			writer->Close();
			
			return true;
		}
		catch (Exception^) {
			return false;
		}
	}
	
	// Load preset from XML file
	static StylePreset^ LoadFromFile(String^ filePath) {
		try {
			if (!File::Exists(filePath)) return nullptr;
			
			StylePreset^ preset = gcnew StylePreset();
			
			XmlDocument^ doc = gcnew XmlDocument();
			doc->Load(filePath);
			
			// Metadata
			XmlNode^ metaNode = doc->SelectSingleNode("//Metadata");
			if (metaNode != nullptr) {
				XmlNode^ nameNode = metaNode->SelectSingleNode("Name");
				if (nameNode != nullptr) preset->PresetName = nameNode->InnerText;
				XmlNode^ authorNode = metaNode->SelectSingleNode("Author");
				if (authorNode != nullptr) preset->Author = authorNode->InnerText;
			}
			
			// Essentials
			XmlNode^ essNode = doc->SelectSingleNode("//Essentials");
			if (essNode != nullptr) {
				XmlNode^ node;
				if ((node = essNode->SelectSingleNode("Contrast")) != nullptr) 
					preset->Contrast = Int32::Parse(node->InnerText);
				if ((node = essNode->SelectSingleNode("Brightness")) != nullptr) 
					preset->Brightness = Int32::Parse(node->InnerText);
				if ((node = essNode->SelectSingleNode("Sharpness")) != nullptr) 
					preset->Sharpness = Int32::Parse(node->InnerText);
				if ((node = essNode->SelectSingleNode("Vibrance")) != nullptr) 
					preset->Vibrance = Int32::Parse(node->InnerText);
				if ((node = essNode->SelectSingleNode("Hue")) != nullptr) 
					preset->Hue = Int32::Parse(node->InnerText);
				if ((node = essNode->SelectSingleNode("RedBoost")) != nullptr) 
					preset->RedBoost = Int32::Parse(node->InnerText);
				if ((node = essNode->SelectSingleNode("GreenBoost")) != nullptr) 
					preset->GreenBoost = Int32::Parse(node->InnerText);
				if ((node = essNode->SelectSingleNode("BlueBoost")) != nullptr) 
					preset->BlueBoost = Int32::Parse(node->InnerText);
			}
			
			// Effects
			XmlNode^ fxNode = doc->SelectSingleNode("//Effects");
			if (fxNode != nullptr) {
				XmlNode^ node;
				if ((node = fxNode->SelectSingleNode("Pixelate")) != nullptr) 
					preset->Pixelate = Int32::Parse(node->InnerText);
				if ((node = fxNode->SelectSingleNode("Posterize")) != nullptr) 
					preset->Posterize = Int32::Parse(node->InnerText);
				if ((node = fxNode->SelectSingleNode("Blur")) != nullptr) 
					preset->Blur = Int32::Parse(node->InnerText);
				if ((node = fxNode->SelectSingleNode("Glitch")) != nullptr) 
					preset->Glitch = Int32::Parse(node->InnerText);
				if ((node = fxNode->SelectSingleNode("ExaggeratedGlitch")) != nullptr) 
					preset->ExaggeratedGlitch = Boolean::Parse(node->InnerText);
			}
			
			// Color replacement
			XmlNode^ colorNode = doc->SelectSingleNode("//ColorReplacement");
			if (colorNode != nullptr) {
				XmlNode^ node;
				if ((node = colorNode->SelectSingleNode("TargetColor")) != nullptr) 
					preset->TargetColor = node->InnerText;
				if ((node = colorNode->SelectSingleNode("ReplacementColor")) != nullptr) 
					preset->ReplacementColor = node->InnerText;
				if ((node = colorNode->SelectSingleNode("Threshold")) != nullptr) 
					preset->ColorThreshold = Int32::Parse(node->InnerText);
				if ((node = colorNode->SelectSingleNode("Interpolate")) != nullptr) 
					preset->ColorInterpolate = Boolean::Parse(node->InnerText);
			}
			
			// Filters
			XmlNode^ filterNode = doc->SelectSingleNode("//Filters");
			if (filterNode != nullptr) {
				XmlNode^ node;
				if ((node = filterNode->SelectSingleNode("Grayscale")) != nullptr) 
					preset->Grayscale = Boolean::Parse(node->InnerText);
				if ((node = filterNode->SelectSingleNode("Invert")) != nullptr) 
					preset->Invert = Boolean::Parse(node->InnerText);
				if ((node = filterNode->SelectSingleNode("Sepia")) != nullptr) 
					preset->Sepia = Boolean::Parse(node->InnerText);
				if ((node = filterNode->SelectSingleNode("EdgeDetection")) != nullptr) 
					preset->EdgeDetection = Boolean::Parse(node->InnerText);
				if ((node = filterNode->SelectSingleNode("Emboss")) != nullptr) 
					preset->Emboss = Boolean::Parse(node->InnerText);
				if ((node = filterNode->SelectSingleNode("OilPaint")) != nullptr) 
					preset->OilPaint = Boolean::Parse(node->InnerText);
			}
			
			return preset;
		}
		catch (Exception^) {
			return nullptr;
		}
	}
};

// ==================== IMAGE CACHE FOR UNDO/REDO ====================

ref class ImageCache {
private:
static const int MAX_CACHE_SIZE = 10;
static System::Collections::Generic::List<Bitmap^>^ undoStack;
static System::Collections::Generic::List<Bitmap^>^ redoStack;
static Bitmap^ originalImage;

public:
static void Initialize() {
if (undoStack == nullptr) {
undoStack = gcnew System::Collections::Generic::List<Bitmap^>();
}
if (redoStack == nullptr) {
redoStack = gcnew System::Collections::Generic::List<Bitmap^>();
}
}

static void SetOriginal(Bitmap^ image) {
if (image != nullptr) {
originalImage = gcnew Bitmap(image);
}
}

static Bitmap^ GetOriginal() {
if (originalImage != nullptr) {
return gcnew Bitmap(originalImage);
}
return nullptr;
}

static void PushUndo(Bitmap^ image) {
Initialize();
if (image != nullptr) {
if (undoStack->Count >= MAX_CACHE_SIZE) {
if (undoStack[0] != nullptr) delete undoStack[0];
undoStack->RemoveAt(0);
}
undoStack->Add(gcnew Bitmap(image));
ClearRedo();
}
}

static Bitmap^ PopUndo() {
Initialize();
if (undoStack->Count > 0) {
int lastIndex = undoStack->Count - 1;
Bitmap^ image = undoStack[lastIndex];
undoStack->RemoveAt(lastIndex);
return image;
}
return nullptr;
}

static void PushRedo(Bitmap^ image) {
Initialize();
if (image != nullptr) {
if (redoStack->Count >= MAX_CACHE_SIZE) {
if (redoStack[0] != nullptr) delete redoStack[0];
redoStack->RemoveAt(0);
}
redoStack->Add(gcnew Bitmap(image));
}
}

static Bitmap^ PopRedo() {
Initialize();
if (redoStack->Count > 0) {
int lastIndex = redoStack->Count - 1;
Bitmap^ image = redoStack[lastIndex];
redoStack->RemoveAt(lastIndex);
return image;
}
return nullptr;
}

static bool CanUndo() {
Initialize();
return undoStack->Count > 0;
}

static bool CanRedo() {
Initialize();
return redoStack->Count > 0;
}

static void Clear() {
Initialize();
for each (Bitmap^ bmp in undoStack) {
if (bmp != nullptr) delete bmp;
}
undoStack->Clear();
ClearRedo();
if (originalImage != nullptr) {
delete originalImage;
originalImage = nullptr;
}
}

static void ClearRedo() {
Initialize();
for each (Bitmap^ bmp in redoStack) {
if (bmp != nullptr) delete bmp;
}
redoStack->Clear();
}
};
