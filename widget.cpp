#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

	this->setMapping();
	this->addImage("archlinux.png");
	this->addImage("ubuntu.png");
	this->save("out");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::addImage(const char *filename) {
	QImage qImage(filename);
	images.push_back(qImage.scaledToHeight(32).convertToFormat(QImage::Format_RGB888));

	++imageCount.count;
}

void Widget::save(const char *filename) {
	mode.imageIndexAddresss = sizeof(Mode);
	mode.lineIndexAddress = mode.imageIndexAddresss + sizeof(Count) + imageCount.count * sizeof(uint16_t);
	mode.brakeIndexAddress = mode.lineIndexAddress + sizeof(Count) + lineCount.count * sizeof(uint16_t);

	imageAddress.push_back(mode.brakeIndexAddress + sizeof(Count) + brakeCount.count * sizeof(uint16_t));
	for (unsigned int i = 1; i < images.size(); ++i) {
		imageAddress.push_back(imageAddress.at(i-1) + sizeof(Image)
									+ images.at(i-1).height() * images.at(i-1).width() * 3 * sizeof(uint8_t));
	}
/*
	int last = imageAddress.size() - 1;
	lineAddress.push_back(imageAddress.at(last) + sizeof(Image)
									+ images.at(last).height() * images.at(last).width() * 3 * sizeof(uint8_t));
	for (unsigned int i = 1; i < lines.size(); ++i) {
		lineAddress.push_back(lineAddress.at(i-1) + sizeof(Image)
									+ lines.at(i-1).height() * lines.at(i-1).width() * 3 * sizeof(uint8_t));
	}

	last = lineAddress.size() - 1;
	brakeAddress.push_back(lineAddress.at(last) + sizeof(Image)
									+ lines.at(last).height() * lines.at(last).width() * 3 * sizeof(uint8_t));
	for (unsigned int i = 1; i < brakes.size(); ++i) {
		brakeAddress.push_back(brakeAddress.at(i-1) + sizeof(Image)
									+ brakes.at(i-1).height() * brakes.at(i-1).width() * 3 * sizeof(uint8_t));
	}
*/
	FILE *file = fopen(filename, "w");

	// Mode
	fwrite(&mode, sizeof(Mode), 1, file);

	// Count and addresses
	fwrite(&imageCount, sizeof(Count), 1, file);
	for (int i = 0; i < imageCount.count; ++i)
		fwrite(&imageAddress.at(i), sizeof(uint16_t), 1, file);

	fwrite(&lineCount, sizeof(Count), 1, file);
	for (int i = 0; i < lineCount.count; ++i)
		fwrite(&lineAddress.at(i), sizeof(uint16_t), 1, file);

	fwrite(&brakeCount, sizeof(Count), 1, file);
	for (int i = 0; i < brakeCount.count; ++i)
		fwrite(&brakeAddress.at(i), sizeof(uint16_t), 1, file);

	// Image and bytes
	for (int i = 0; i < imageCount.count; ++i) {
		Image img;
		img.width = images.at(i).width();
		fwrite(&img, sizeof(Image), 1, file);

		uint8_t *dataOut = (uint8_t *) malloc(sizeof(*dataOut) * img.height * img.width * 3);
		for (int j = 0; j < 32; ++j) {
			memcpy(dataOut + img.width * 3 * mapping[j],
					images.at(i).bits() + img.width * 3 * j,
					img.width * 3 * sizeof(uint8_t));
		}

		fwrite(dataOut, sizeof(uint8_t), img.height * img.width * 3, file);
	}

	fclose(file);
}

void Widget::setMapping(void) {
	mapping[0] = 0;
	mapping[1] = 1;
	mapping[2] = 2;
	mapping[3] = 3;
	mapping[4] = 4;
	mapping[5] = 5;
	mapping[6] = 6;
	mapping[7] = 7;
	mapping[8] = 8;
	mapping[9] = 9;
	mapping[10] = 10;
	mapping[11] = 11;
	mapping[12] = 12;
	mapping[13] = 13;
	mapping[14] = 14;
	mapping[15] = 15;
	mapping[16] = 16;
	mapping[17] = 17;
	mapping[18] = 18;
	mapping[19] = 19;
	mapping[20] = 20;
	mapping[21] = 21;
	mapping[22] = 22;
	mapping[23] = 23;
	mapping[24] = 24;
	mapping[25] = 25;
	mapping[26] = 26;
	mapping[27] = 27;
	mapping[28] = 28;
	mapping[29] = 29;
	mapping[30] = 30;
	mapping[31] = 31;
}
