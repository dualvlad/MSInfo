#include "libxl.h"
#include < vcclr.h >

using namespace std;
using namespace System;
using namespace System::Windows::Forms;

void savePDF(String^ path, array<String^>^ os, array<String^>^ hard, ListView::ListViewItemCollection^ service)
{
	using namespace iTextSharp::text;
	using namespace iTextSharp::text::pdf;
	Document ^ doc = gcnew Document();
	PdfWriter ^ wr= PdfWriter::GetInstance(doc, gcnew System::IO::FileStream(path, System::IO::FileMode::Create));
	doc->Open();
	BaseFont ^ fon = BaseFont::CreateFont("C:\\WINDOWS\\Fonts\\times.ttf", "CP1251", BaseFont::EMBEDDED);
	Font^ ff = gcnew Font(fon, 12, Font::NORMAL);
	ff->Color = BaseColor::BLACK;
	doc->Add(gcnew Paragraph("System", gcnew Font(fon, 15, Font::BOLD)));
	for(int i=0; i<os->Length; i++)
		doc->Add(gcnew Paragraph(os[i], ff));
	doc->Add(gcnew Paragraph("Processor", gcnew Font(fon, 15, Font::BOLD)));
	for(int i=0; i<hard->Length-3; i++)
		doc->Add(gcnew Paragraph(hard[i], ff));
	doc->Add(gcnew Paragraph("Video", gcnew Font(fon, 15, Font::BOLD)));
	for(int i=3; i<hard->Length; i++)
		doc->Add(gcnew Paragraph(hard[i], ff));

	doc->Close();
	wr->Close();
}

void saveTXT(String^ path, array<String^>^ os, array<String^>^ hard, ListView::ListViewItemCollection^ service)
{
	using namespace System::IO;
	String^ fileName = path;
	StreamWriter^ sw = gcnew StreamWriter(fileName);
	
	sw->WriteLine("System");
	for(int i=0; i<os->Length; i++)
		sw->WriteLine(os[i]);

	sw->WriteLine("");
	sw->WriteLine("Processor");

	for(int i=0; i<hard->Length-3; i++)
		sw->WriteLine(hard[i]);

	sw->WriteLine("");
	sw->WriteLine("Video");

	for(int i=3; i<hard->Length; i++)
		sw->WriteLine(hard[i]);

	//sw->WriteLine(DateTime::Now);
	sw->Close();
}

void saveXLS(String^ path, array<String^>^ os, array<String^>^ hard, ListView::ListViewItemCollection^ service)
{
	pin_ptr<const wchar_t> wch;

	using namespace libxl;
	Book* book = xlCreateBook(); // xlCreateXMLBook() for xlsx
	if(book)
	{
		Sheet* sheet = book->addSheet(L"INFO");
		if(sheet)
		{
			int line = 1;
			sheet->writeStr(line, 0, L"System");
			line++;
			for(int i=0; i<os->Length; i++, line++)
			{
				wch = PtrToStringChars(os[i]);
				sheet->writeStr(line, 0, wch);
			}

			line++;
			sheet->writeStr(line, 0, L"Processor");
			line++;

			for(int i=0; i<hard->Length-3; i++, line++)
			{
				wch = PtrToStringChars(hard[i]);
				sheet->writeStr(line, 0, wch);
			}

			line++;
			sheet->writeStr(line, 0, L"Video");
			line++;


			for(int i=3; i<hard->Length; i++, line++)
			{
				wch = PtrToStringChars(hard[i]);
				sheet->writeStr(line, 0, wch);
			}

			//sheet->writeStr(0, 0, L"Hello, World !");
			//	sheet->writeNum(3, 1, 1000);
		}
		wch = PtrToStringChars(path);
		book->save(wch);
		book->release();
	}
}