;using namespace std;
using namespace System;
using namespace iTextSharp::text;
using namespace iTextSharp::text::pdf;

void savePDF(String^ path)
{
	Document ^ doc = gcnew Document();
	PdfWriter ^ wr= PdfWriter::GetInstance(doc, gcnew System::IO::FileStream(path, System::IO::FileMode::Create));
	doc->Open();
	BaseFont ^ fon = BaseFont::CreateFont("C:\\WINDOWS\\Fonts\\times.ttf", "CP1251", BaseFont::EMBEDDED);
	Font ^ ff = gcnew Font(fon, 12, Font::NORMAL);
	ff->Color = BaseColor::BLACK;
	doc->Add(gcnew Paragraph("sdfsdfsdfsdfsdfsdsdfsf", ff));
	doc->Close();
	wr->Close();
}

void saveTXT()
{}

void saveXLS()
{}