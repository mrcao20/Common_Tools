#pragma once

#include <qlabel.h>

class LyricLabel : public QLabel{
	Q_OBJECT

public:
	LyricLabel(QWidget *parent = 0);

	const QFont &font() const { return m_font; }
	void start_lrc_mask(qint64 intervaltime);
	void stop_lrc_mask();
protected:
	void paintEvent(QPaintEvent *);

signals:

public slots :

private slots :
	void timeout();

private:
	QLinearGradient m_linear_gradient;
	QLinearGradient m_mask_linear_gradient;
	QFont m_font;
	QTimer *m_timer;
	qreal m_lrc_mask_width;

	qreal m_lrc_mask_width_interval;
	QPoint m_offset;
};
