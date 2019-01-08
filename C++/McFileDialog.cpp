#include "McFileDialog.h"
#include <qlistview.h>
#include <qtreeview.h>
#include <qlineedit.h>

McFileDialog::McFileDialog(QWidget *parent)
	: QFileDialog(parent)
{
	setLabelText(QFileDialog::Reject, QString("取消"));
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
	// 需要添加这个
	QLineEdit *edit = findChild<QLineEdit *>("fileNameEdit");
	if (NULL != edit){
		//pFileDialog = &fileDialog; // 保存指针留在槽函数中使用
		//pFileNameEdit = edit;
		connect(edit, SIGNAL(textChanged(QString)), SLOT(slot_removeHistory(QString)));
	}

	/*	需要在filesSelected信号接收的槽函数里调用下面的语句，去掉可能被选中的父文件夹
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
	// 根目录下的文件夹
	if ((this->history().first().split("\\").size() <= 2) &&
		(this->history().first().split("\\").last().isEmpty())){
		history = QString("\"") + this->history().first().split("\\").first() + QString("\"");
	}
	// 非根目录下的文件夹
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