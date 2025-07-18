#include "stdafx.h"
#include "SVGReader.h"
#include "ProcessMain.h"
//#include "ProcessXML.h"


SVGReader& SVGReader::getInstance() {
	static SVGReader instance;
	return instance;
}

// set hinstance, nCmdShow
void SVGReader::setWinParams(HINSTANCE hInstance, INT nCmdShow) {
	this->hInstance = hInstance;
	this->nCmdShow = nCmdShow;
}

// init SVGReader variable
void SVGReader::init(std::string fileName) {
	this->curFileName = fileName;


	// read the shapes from the curFileName
	SVGReader::getInstance().processXML();


	// Initialize GDI+.
	GdiplusStartup(&this->gdiplusToken, &this->gdiplusStartupInput, NULL);

	// init wndClass, this class contains properties of the window
	WNDCLASSEX wndClass = WNDCLASSEX();

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SVGREADER));
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = MAKEINTRESOURCE(IDC_SVGREADER);
	wndClass.lpszClassName = L"WndClass";
	wndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassEx(&wndClass);

	// init the dialog (like the about in menu bar)
	WNDCLASSEX dialog = WNDCLASSEX();

	dialog.cbSize = sizeof(WNDCLASSEX);
	dialog.style = CS_HREDRAW | CS_VREDRAW;
	dialog.lpfnWndProc = DlgProc;
	dialog.cbClsExtra = 0;
	dialog.cbWndExtra = 0;
	dialog.hInstance = hInstance;
	//dialog.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SVGREADER));
	dialog.hCursor = LoadCursor(NULL, IDC_CROSS);
	dialog.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	dialog.lpszClassName = L"DialogClass";
	//dialog.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassEx(&dialog);


	// init HWND
	this->hWnd = CreateWindow(
		TEXT("WndClass"),			// window class name
		TEXT("SVG Reader"),			// window caption
		WS_OVERLAPPEDWINDOW,		// window style
		CW_USEDEFAULT,				// initial x position
		CW_USEDEFAULT,				// initial y position
		CW_USEDEFAULT,				// initial x size
		CW_USEDEFAULT,				// initial y size
		NULL,						// parent window handle
		NULL,						// window menu handle
		hInstance,					// program instance handle
		NULL);						// creation parameters

	// show window
	ShowWindow(this->hWnd, this->nCmdShow);
	UpdateWindow(this->hWnd);
}

// receive and send message to WndProc
void SVGReader::messageLoop() {
	while (GetMessage(&this->msg, NULL, 0, 0)) {
		TranslateMessage(&this->msg);
		DispatchMessage(&this->msg);		// send message to the WndProc function
	}
}

// clean things before close
INT SVGReader::cleanup() {
	// Shutdown GDI+.
	GdiplusShutdown(this->gdiplusToken);
	
	// clear vector<SVGShapes*> shapes
	clearShapes();

	return (INT)this->msg.wParam;
}

void SVGReader::clearShapes() {
	for (size_t i = 0; i < shapes.size(); i++) {
		delete shapes[i];
		shapes[i] = NULL;
	}
	shapes.clear();
}

void SVGReader::setScale(float val) {
	this->scale += val;
	// clamp value
	// min zoom is 10%
	if (this->scale < 0.1) {
		this->scale = 0.1;
	}
	// max zoom is 300%
	else if (this->scale > 3) {
		this->scale = 3;
	}
}



// process the open menu action in WndProc
void SVGReader::openFile() {
	OPENFILENAME ofile = OPENFILENAME();

	WCHAR fileName[256] = L"";

	ofile.lStructSize = sizeof(OPENFILENAME);
	ofile.hwndOwner = this->hWnd;
	ofile.lpstrFile = fileName;
	ofile.lpstrFile[0] = '\0';
	ofile.nMaxFile = sizeof(fileName) / sizeof(WCHAR);

	ofile.lpstrFilter = L"SVG Image\0*.svg\0";
	ofile.nFilterIndex = 1;

	if (GetOpenFileName(&ofile)) {
		wstring ws(ofile.lpstrFile);
		string str(ws.begin(), ws.end());

		this->curFileName = str;
	}	
}



// this function is used to put shape attributes to 
// SVGReader instance variable.
void SVGReader::processXML() {
	// clear all existing shapes
	clearShapes();


	// Ref: http://rapidxml.sourceforge.net/manual.html
	// Read XML
	xml_document<> doc;
	// Read the xml file into a vector
	ifstream file(this->curFileName);

	vector<char> buffer((istreambuf_iterator<char>(file)), 
						istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);

	xml_node<>* rootNode;

	rootNode = doc.first_node();
	xml_node<>* node = rootNode->first_node();

	while (node != NULL) {
		char* nodeName = node->name();
		SVGShape* shape = NULL;

		// allocate shape based on type
		if (strcmp(nodeName, "rect") == 0) {
			shape = new SVGRectangle();
		}
		else if (strcmp(nodeName, "ellipse") == 0) {
			shape = new SVGEllipse();
		}
		else if (strcmp(nodeName, "circle") == 0) {
			shape = new SVGCircle();
		}
		else if (strcmp(nodeName, "text") == 0) {
			shape = new SVGText();
		}
		else if (strcmp(nodeName, "line") == 0) {
			shape = new SVGLine();
		}
		else if (strcmp(nodeName, "polyline") == 0) {
			shape = new SVGPolyline();
		}
		else if (strcmp(nodeName, "polygon") == 0) {
			shape = new SVGPolygon();
		}


		if (shape == NULL) {
			throw("Shape is not defined");
			node = node->next_sibling();
			continue;
		}

		//
		// Get attributes
		//
		// if shape is SVGText, set the content
		// both are 2 pointers -> share the same memory space
		// if shape is SVGText -> textShape != NULL
		SVGText* textShape = dynamic_cast<SVGText*>(shape);
		if (textShape && node->value()) {
			textShape->setContent(node->value());
		}
		
		// extract the other attributes
		xml_attribute<>* curAttribute = node->first_attribute();
		while (curAttribute != NULL) {
			char* attributeName = curAttribute->name();
			char* attributeValue = curAttribute->value();

			shape->processAttribute(attributeName, attributeValue);

			curAttribute = curAttribute->next_attribute();
		}
		

		// push to SVGReader shapes
		shapes.push_back(shape);

		node = node->next_sibling();
	}
}




void SVGReader::render(Graphics& graphics) {
	if (!shapes.empty()) {
		for (size_t i = 0; i < shapes.size(); i++) {
			shapes[i]->draw(graphics);
		}
	}
}
