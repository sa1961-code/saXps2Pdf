# saXps2Pdf
### (DE) Impressum
Die Anbieterkennzeichnung nach TMG (Impressum) finden Sie unter https://www.it-crafts.de/impressum.
Dieses Angebot ist nicht für die Nutzung außerhalb Deutschlands bestimmt.
### (EN) Imprint
You can find the German version of the imprint above here.
This offer is not intended for use outside of Germany.

## About

### (DE) Konverter von xps-Dateiformat nach pdf
SaXps2Pdf-Converter ist eine einfache interaktive Benutzeroberfläche 
für die Microsoft Windows-Version der GhostXPS-Dokumentkonvertierungs-Engine.
Außerdem bietet es eine COM-Schnittstelle zur Konvertierung.
### (EN) Convert xps-files into pdf
SaXps2Pdf-Converter is a simple interactive userinterface for the 
Microsoft Windows version of GhostXPS document conversion engine. 
Also it provides a COM-interface for converting. 

## Dependencies

### (DE) Abhängigkeiten
Der Konverter benutzt GhostXps als PDF-Engine.
Die vollständige Version von GhostXps können Sie hier herunterladen:
https://www.ghostscript.com/releases/gxpsdnld.html
### (EN) Dependencies
The converter uses GhostXps as the PDF engine.
You can download the full version of GhostXps here:
https://www.ghostscript.com/releases/gxpsdnld.html

## Licensing

### (DE) Lizensierung
Die hier verwendete Version von GhostXps ist unter der 
GNU Affero General Public License (AGPL) lizenziert.
Deshalb habe ich dieses Tool ebenfalls unter der GPL/AGPL 
lizensiert.

Darüber hinaus erlaube ich Ihnen, die von mir bereitgestellten 
Programme Xps2Pdf.exe, Xps2PdfLib.dll und deren Quellcodes in 
eigenen, auch kommerziellen, Projekten zu verwenden.
In diesem Fall sind die verpflichtet, selbst für die korrekte 
Lizensierung der verwendeten GhostXps-Module zu sorgen.

### (EN) Licensing
The version of GhostXps used here is licensed under the 
GNU Affero General Public License (AGPL).
That's why I also have this tool under the GPL/AGPL licensed.

In addition, I allow you to use the Programs provided by me 
Xps2Pdf.exe, Xps2PdfLib.dll and their source codes in their own, 
including commercial, projects.
In this case, you are obliged to ensure the correct licensing 
of the GhostXps modules used.

## Components

### saXps2PdfLib32.dll und saXps2PdfLib64.dll
COM object that encapsulates the GhostXps API

### saXps2Pdf.exe
Provides GUI to help convert xps-files into pdf-format.
It uses the COM-interface implemented by saXps2PdfLib64.dll.

### saXps2PdfSetup.msi
Windows installer

## Compiling the project
Use Microsoft Visual Studio 2010 or later.

|step|used configuration|modules to build|
|----|------------------|-------------------|
1:|Release/Win32|saXps2PdfLib32.dll|
2a:|Release/x64|saXps2PdfLib64.dll|
2b:|Release/x64|saXps2Pdf.exe|
2c:|Release/x64|saXps2PdfSetup.msi|

Copy gxpsdll64.dll und qxpsdll32.dll from your GhostXps download into the 
folder bin/Release/GhostXps-10.02.1, then you can run saXps2Pdf.exe. 
Alternatively, you can take these files from the release package.

*** s.a. 2024-02-06
