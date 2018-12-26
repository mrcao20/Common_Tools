#include "LyricLabel.h"
#include <qtimer.h>
#include <QPainter>

LyricLabel::LyricLabel(QWidget *parent)
	: QLabel(parent) {

	//歌词的线性渐变填充
	m_linear_gradient.setStart(0, 10);//填充的起点坐标
	m_linear_gradient.setFinalStop(0, 40);//填充的终点坐标
										//第一个参数终点坐标，相对于我们上面的区域而言，按照比例进行计算
	m_linear_gradient.setColorAt(0.1, QColor(14, 179, 255));
	m_linear_gradient.setColorAt(0.5, QColor(114, 232, 255));
	m_linear_gradient.setColorAt(0.9, QColor(14, 179, 255));

	// 遮罩的线性渐变填充
	m_mask_linear_gradient.setStart(0, 10);
	m_mask_linear_gradient.setFinalStop(0, 40);
	m_mask_linear_gradient.setColorAt(0.1, QColor(222, 54, 4));
	m_mask_linear_gradient.setColorAt(0.5, QColor(255, 72, 16));
	m_mask_linear_gradient.setColorAt(0.9, QColor(222, 54, 4));

	// 设置字体
	m_font.setFamily("Times New Roman");
	m_font.setBold(true);
	m_font.setPointSize(24);
	
	// 设置定时器
	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
	m_lrc_mask_width = 0;
	m_lrc_mask_width_interval = 0;
}

// 开启遮罩，需要指定当前歌词开始与结束之间的时间间隔
void LyricLabel::start_lrc_mask(qint64 intervaltime)
{
	// 这里设置每隔30毫秒更新一次遮罩的宽度，因为如果更新太频繁
	// 会增加CPU占用率，而如果时间间隔太大，则动画效果就不流畅了
	qreal count = intervaltime / 30;
	// 获取遮罩每次需要增加的宽度，这里的800是部件的固定宽度
	m_lrc_mask_width_interval = width() / count;
	m_lrc_mask_width = 0;
	m_timer->start(30);
}

void LyricLabel::stop_lrc_mask()
{
	m_timer->stop();
	m_lrc_mask_width = 0;
	update();
}


void LyricLabel::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setFont(m_font);

	// 先绘制底层文字，作为阴影，这样会使显示效果更加清晰，且更有质感
	painter.setPen(QColor(0, 0, 0, 200));
	painter.drawText(1, 1, 800, 60, Qt::AlignLeft, text());//左对齐

														   // 再在上面绘制渐变文字
	painter.setPen(QPen(m_linear_gradient, 0));
	painter.drawText(0, 0, 800, 60, Qt::AlignLeft, text());

	// 设置歌词遮罩
	painter.setPen(QPen(m_mask_linear_gradient, 0));
	painter.drawText(0, 0, m_lrc_mask_width, 60, Qt::AlignLeft, text());

}

void LyricLabel::timeout()
{
	//每隔一段固定的时间笼罩的长度就增加一点
	m_lrc_mask_width += m_lrc_mask_width_interval;
	update();//更新widget，但是并不立即重绘，而是安排一个Paint事件，当返回主循环时由系统来重绘
}