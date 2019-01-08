#include "McFileDialog.h"
#include <qlistview.h>
#include <qtreeview.h>
#include <qlineedit.h>

McFileDialog::McFileDialog(QWidget *parent)
	: QFileDialog(parent)
{
	setLabelText(QFileDialog::Reject, QString("ȡ��"));
	setFileMode(QFileDialog::Directory);
	setOptions(QFileDialog::DontUseNativeDialog | QFileDialog::ShowDirsOnly);

	QListView *listView = findChild<QListView*>("listView");
	if (NULL != listView){
		listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	}

	QTreeView *treeView = findChild<QTreeView*>();
	if (NULL != treeView){
		treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	}
	// ��Ҫ������
	QLineEdit *edit = findChild<QLineEdit *>("fileNameEdit");
	if (NULL != edit){
		//pFileDialog = &fileDialog; // ����ָ�����ڲۺ�����ʹ��
		//pFileNameEdit = edit;
		connect(edit, SIGNAL(textChanged(QString)), SLOT(slot_removeHistory(QString)));
	}

	/*	��Ҫ��filesSelected�źŽ��յĲۺ���������������䣬ȥ�����ܱ�ѡ�еĸ��ļ���
		if (selected.first().trimmed().replace("/", "\\") == fileDialog.history().first().trimmed()){
			selected.removeFirst();
		}
	*/
}

McFileDialog::~McFileDialog(){
}

void McFileDialog::slot_removeHistory(const QString &text){
	int index = text.indexOf("\"", 1);
	if (index == -1){
		return;
	}

	QString history;
	// ��Ŀ¼�µ��ļ���
	if ((this->history().first().split("\\").size() <= 2) &&
		(this->history().first().split("\\").last().isEmpty())){
		history = QString("\"") + this->history().first().split("\\").first() + QString("\"");
	}
	// �Ǹ�Ŀ¼�µ��ļ���
	else{
		history = QString("\"") + this->history().first().split("\\").last() + QString("\"");
	}
	//    qDebug() << "slot_removeHistory(QString text)" << text.left(index+1) << history;
	if (history.compare(text.left(index + 1)) == 0){
		QLineEdit *edit = findChild<QLineEdit *>("fileNameEdit");
		if (NULL != edit) {
			edit->clear();
			edit->setText(text.mid(text.indexOf("\"", index + 1)));
		}
		/*pFileNameEdit->clear();
		pFileNameEdit->setText(text.mid(text.indexOf("\"", index + 1)));*/
	}
}