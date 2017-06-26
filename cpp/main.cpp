#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <iostream>
#include <unistd.h>

int main()
{
	char *outText;

	tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
	// Initialize tesseract-ocr with English, without specifying tessdata path
	if (api->Init(NULL, "eng")) {
		//fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}

	while(1){
		// Open input image with leptonica library
		Pix *image = pixRead("https://vistar-capture.web.cern.ch/vistar-capture/lhc1.png");
		api->SetImage(image);
		int width = pixGetWidth(image);
		api->SetRectangle(10, 40, width-30, 40);
		api->SetVariable("tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZ:");
		api->SetPageSegMode(tesseract::PSM_SINGLE_LINE);
		// Get OCR result
		outText = api->GetUTF8Text();
		*std::remove(outText, outText + strlen(outText), '\n') = '\0';
		printf("OCR output: %s\n", outText);
		pixDestroy(&image);

		sleep(1);
	}

	// Destroy used object and release memory
	api->End();
	delete [] outText;

	return 0;
}
