#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>
#include <cstdio>
#include <cstring>
#include <vector>
#include "Mode.hpp"
#include "Count.hpp"
#include "Image.hpp"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

	void addImage(const char *filename);
	void setMapping(void);
	void save(const char *filename);

private slots:
    //void on_pushButton_clicked();

private:
    Ui::Widget *ui;

	Mode mode;
	Count imageCount, lineCount, brakeCount;
	std::vector<uint16_t> imageAddress, lineAddress, brakeAddress;
	std::vector<QImage> images;
	uint8_t mapping[32];
};

#endif // WIDGET_H
