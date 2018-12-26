#include "LyricLabel.h"
#include <qtimer.h>
#include <QPainter>

LyricLabel::LyricLabel(QWidget *parent)
	: QLabel(parent) {

	//��ʵ����Խ������
	m_linear_gradient.setStart(0, 10);//�����������
	m_linear_gradient.setFinalStop(0, 40);//�����յ�����
										//��һ�������յ����꣬��������������������ԣ����ձ������м���
	m_linear_gradient.setColorAt(0.1, QColor(14, 179, 255));
	m_linear_gradient.setColorAt(0.5, QColor(114, 232, 255));
	m_linear_gradient.setColorAt(0.9, QColor(14, 179, 255));

	// ���ֵ����Խ������
	m_mask_linear_gradient.setStart(0, 10);
	m_mask_linear_gradient.setFinalStop(0, 40);
	m_mask_linear_gradient.setColorAt(0.1, QColor(222, 54, 4));
	m_mask_linear_gradient.setColorAt(0.5, QColor(255, 72, 16));
	m_mask_linear_gradient.setColorAt(0.9, QColor(222, 54, 4));

	// ��������
	m_font.setFamily("Times New Roman");
	m_font.setBold(true);
	m_font.setPointSize(24);
	
	// ���ö�ʱ��
	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
	m_lrc_mask_width = 0;
	m_lrc_mask_width_interval = 0;
}

// �������֣���Ҫָ����ǰ��ʿ�ʼ�����֮���ʱ����
void LyricLabel::start_lrc_mask(qint64 intervaltime)
{
	// ��������ÿ��30�������һ�����ֵĿ�ȣ���Ϊ�������̫Ƶ��
	// ������CPUռ���ʣ������ʱ����̫���򶯻�Ч���Ͳ�������
	qreal count = intervaltime / 30;
	// ��ȡ����ÿ����Ҫ���ӵĿ�ȣ������800�ǲ����Ĺ̶����
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

	// �Ȼ��Ƶײ����֣���Ϊ��Ӱ��������ʹ��ʾЧ�������������Ҹ����ʸ�
	painter.setPen(QColor(0, 0, 0, 200));
	painter.drawText(1, 1, 800, 60, Qt::AlignLeft, text());//�����

														   // ����������ƽ�������
	painter.setPen(QPen(m_linear_gradient, 0));
	painter.drawText(0, 0, 800, 60, Qt::AlignLeft, text());

	// ���ø������
	painter.setPen(QPen(m_mask_linear_gradient, 0));
	painter.drawText(0, 0, m_lrc_mask_width, 60, Qt::AlignLeft, text());

}

void LyricLabel::timeout()
{
	//ÿ��һ�ι̶���ʱ�����ֵĳ��Ⱦ�����һ��
	m_lrc_mask_width += m_lrc_mask_width_interval;
	update();//����widget�����ǲ��������ػ棬���ǰ���һ��Paint�¼�����������ѭ��ʱ��ϵͳ���ػ�
}