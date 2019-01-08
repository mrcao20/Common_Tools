#pragma once
#pragma execution_character_set("utf-8")

#include <QFileDialog>

class McFileDialog : public QFileDialog
{
	Q_OBJECT

public:
	explicit McFileDialog(QWidget *parent = 0);
	~McFileDialog();

public slots:
	void slot_removeHistory(const QString &text);
};
